#include"Processor.h"
#include"Item.h"
#include"OrderManager.h"
#include <memory>
#include <algorithm>
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
bool Processor::load(Item& _item){
	int i = 0;
	Processor *find = this;
	while (this){
		if (find[i].getName() == _item.getSource()){
			is_a_filler = true;
			item = &_item;
			return true;
		}
		i++;
	}
	return false;
}

//Accepts CustomerOrder 
void Processor::accept(CustomerOrder&& _toMve){
	waiting.push_back(std::move(_toMve));
}

//Advances Process
void Processor::advance(unsigned int size){
	std::deque<CustomerOrder>::iterator iterCustomerOrder = process.begin();
	std::deque<CustomerOrder>::iterator iterCustomerOrderEnd = process.end();
	const Item* temp = item;

	for (int i = 0; i < process.size(); i++){
		if (end_gap != 0 && !process.empty()){
			end_gap--;
			if (is_a_filler){
				for (unsigned int i = 0; i < size; i++){
					iterCustomerOrder->fill(item[i]);
				}
			}
			else{
				for (unsigned int i = 0; i < size; i++){
					iterCustomerOrder->remove(*item);
				}
			}
		}
	}
	
		if (end_gap == 0){
			complete.push_back(std::move(process.front()));
			process.pop_front();
			end_gap = 1;
			if (process.empty()){
				end_gap = getSlots();
			}
		}
		if (!waiting.empty()){
			process.push_back(std::move(waiting.front()));
			waiting.pop_front();
		}
	
}

//Checks if it is ready to pass
bool Processor::readyToPass() const{
	return (!complete.empty() && getNextTask(passed) != nullptr);
}

//Processes follow up task
void Processor::pass(int _i){
	if (readyToPass()){
		if (_i > 50){
			logFile << "Ready to pass Order\n";
		}
	}
}

//Check if it is ready to ship
bool Processor::readyToShip() const{
	return(!complete.empty() && getNextTask(passed) != nullptr);
}

//Ships Item
void Processor::ship(OrderManager& finished){
	finished.push_back(std::move(complete.front()));
	complete.pop_front();
	logFile << "Moved CustomerOrder into finished Pile\n";
}

//Check if processors are empty
bool Processor::empty() const{
	return (waiting.empty() &&
		    process.empty() &&
		    complete.empty());
}

//Display CustomerOrders in waiting process & complete
void Processor::display(std::ostream& os) const{
	Task::display(os);
}

//Destructor
Processor::~Processor(){
	logFile.close();
}