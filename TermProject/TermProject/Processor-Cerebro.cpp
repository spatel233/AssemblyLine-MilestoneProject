#include"Processor.h"
#include"Item.h"
#include"OrderManager.h"

//Constructor
Processor::Processor(const std::string& record, std::function<Task::Quality(int)> _inspector, std::ofstream& os):
Task(record),
item(nullptr),
inspector(_inspector),
end_gap(getSlots()),
is_a_filler(true),
logFile(os)
{}

//Loads Item
void Processor::load(Item& _item){

	if (_item.getSource() == getName()){
		is_a_filler = true;
		item = &_item;
	} else{
		is_a_filler = false;
	}
}

//Accepts CustomerOrder 
void Processor::accept(CustomerOrder&& _toMve){
	waiting.push_back(std::move(_toMve));
}

//Advances Process
void Processor::advance(){
	std::deque<CustomerOrder>::iterator iterCustomerOrder = process.begin();
	std::deque<CustomerOrder>::iterator iterCustomerOrderEnd = process.end();

	if (end_gap != 0 && !process.empty()){
		end_gap--;
		for (; iterCustomerOrder != iterCustomerOrderEnd; iterCustomerOrder++){
			if (is_a_filler){
				iterCustomerOrder->fill(*item);
			}
			else{
				iterCustomerOrder->remove(*item);
			}
		}
		if (end_gap == 0){
			complete.push_back(std::move(process.at(0)));
			end_gap = 1;
			if (process.empty()){
				end_gap = getSlots();
			}
		}
		if (!waiting.empty()){
			process.push_back(std::move(waiting.at(0)));
		}
	}
	
}

//Checks if it is ready to pass
bool Processor::readyToPass() const{
	const Task* temp = nullptr;
	temp = getNextTask(inspector(0));

	const Task* temp2 = nullptr;
	temp = getNextTask(inspector(1));
	return (temp || temp2 && !complete.empty());
}

//Processes follow up task
void Processor::pass(int _i){
	if (readyToPass()){
		logFile << "Ready to pass Order\n";
		accept(std::move(complete[_i]));
	}
}

//Check if it is ready to ship
bool Processor::readyToShip() const{
	return(readyToPass());
}

//Ships Item
void Processor::ship(OrderManager& finished){
	if (!complete.empty()){
		finished.push_back(std::move(complete.front()));
		logFile << "Moved CustomerOrder into finished Pile\n";
	}
}

//Check if processors are empty
bool Processor::empty() const{
	return (waiting.empty() &&
		    process.empty() &&
		    complete.empty());
}

//Display CustomerOrders in waiting process & complete
void Processor::display(std::ostream& os) const{
	std::deque<CustomerOrder>::const_iterator iterWaiting = waiting.cbegin();
	std::deque<CustomerOrder>::const_iterator iterWaitingEnd = waiting.cend();

	for (; iterWaiting != iterWaitingEnd; iterWaiting++){
		iterWaiting->display(os);
	}

	std::deque<CustomerOrder>::const_iterator iterProcess = process.cbegin();
	std::deque<CustomerOrder>::const_iterator iterProcessEnd = process.cend();

	for (; iterProcess != iterProcessEnd; iterProcess++){
		iterProcess->display(os);
	}

	std::deque<CustomerOrder>::const_iterator iterComplete = complete.cbegin();
	std::deque<CustomerOrder>::const_iterator iterCompleteEnd = complete.cend();

	for (; iterComplete != iterCompleteEnd; iterComplete++){
		iterComplete->display(os);
	}
}

//Destructor
Processor::~Processor(){
	logFile.close();
}