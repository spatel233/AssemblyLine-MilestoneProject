#include <algorithm>

#include "ItemManager.h"
#include "AssemblyLine.h"
#include "Processor.h"
#include "CustomerOrder.h"
#include"OrderManager.h"


//One-Argument Constructor
AssemblyLine::AssemblyLine(const char *record){
	logFile.open(record, std::ios::trunc);
}

//Move processor to the back of the processors vector
void AssemblyLine::push_back(Processor&& _toMve){
	processors.push_back(std::move(_toMve));
}

//Validate processor tasks
void AssemblyLine::validate(std::ostream& os){
	for (auto i : processors){
		for (auto j : processors){
			if (i.validate(j)){
				break;
			}
		}
	}
}

//Validate item task with processor tasks
void AssemblyLine::validate(ItemManager& item, std::ostream& os){
	std::vector<Item>::iterator iter1 = item.begin();
	std::vector<Item>::iterator iter2 = item.end();
	bool check = false;
	
	for (; iter1 != iter2; iter1++){
		//Check Destination
		if (std::find_if(processors.cbegin(), processors.cend(), [&](const Processor &_processor)->bool{
			return _processor.getName() == iter1->getDestination() && _processor.getName() == iter1->getSource();
		}) == processors.cend()){
			os << iter1->getDestination() << " is not available\n";
		}
		//Check Source
		if (std::find_if(processors.cbegin(), processors.cend(), [&](const Processor &_processor)->bool{
			return _processor.getName() == iter1->getSource();
		}) == processors.cend()){
			os << iter1->getSource() << " is not available\n";
		}
	}
}

//Load items into process
void AssemblyLine::loadItem(ItemManager& _item){
	std::vector<Item>::iterator iterItem = _item.begin();
	std::vector<Item>::iterator iterItemEnd = _item.end();
	std::vector<Processor>::iterator iterProcess = processors.begin();
	std::vector<Processor>::iterator iterProcessEnd = processors.end();

	for (; iterProcess != iterProcessEnd; iterProcess++){
		for (; iterItem != iterItemEnd; iterItem++){
			iterProcess->load(*iterItem);
		}
	}
}

//Load Orders
void AssemblyLine::loadOrders(OrderManager& _order, const std::string& entryProcessor, std::ostream& os){
	std::vector<CustomerOrder>::iterator iter1 = _order.begin();
	std::vector<CustomerOrder>::iterator iter2 = _order.end();
	//std::vector<Processor>::iterator iterProcessor = processors.begin();
	//std::vector<Processor>::iterator iterProcessorEnd = processors.end();
	//static int i = 0;

	//for (; iterProcessor != iterProcessorEnd; iterProcessor++){
		std::find_if(iter1, iter2, [&](CustomerOrder &_corder)->bool{
			(CustomerOrder)entryProcessor = _order.extract();
			return 0;
		});
	//}
}

//Process Function
bool AssemblyLine::process(OrderManager& _order, unsigned int steps){

	std::vector<CustomerOrder>::iterator iterCustomerOrder = _order.begin();
	std::vector<CustomerOrder>::iterator iterCustomerOrderEnd = _order.end();

	std::vector<Processor>::iterator iterProcessor = processors.begin();
	std::vector<Processor>::iterator iterProcessorEnd = processors.end();

	for (; iterCustomerOrder != iterCustomerOrderEnd; iterCustomerOrder++){
		for (; iterProcessor != iterProcessorEnd; iterProcessor++){
			for (unsigned int count = 0; count < steps; count++){
				iterProcessor->accept(std::move(*iterCustomerOrder));
				iterProcessor->advance();

				if (iterProcessor->readyToPass()){
					iterProcessor->pass(std::rand() % 100 + 1);
				} else{
					if (iterProcessor->readyToShip()){
						iterProcessor->ship(_order);
					}
				}
			}
		}
	}
	return processors.empty();
}

//Get logFile
std::ofstream& AssemblyLine::getLogFile(){
	return logFile;
}

//Display Function
void AssemblyLine::display(std::ostream& os) const{
	std::vector<Processor>::const_iterator iterProcessor = processors.cbegin();
	std::vector<Processor>::const_iterator iterProcessorEnd = processors.cend();

	for (; iterProcessor != iterProcessorEnd; iterProcessor++){
		iterProcessor->display(os);
	}
}

//Destructor
AssemblyLine::~AssemblyLine(){
	logFile.close();
}