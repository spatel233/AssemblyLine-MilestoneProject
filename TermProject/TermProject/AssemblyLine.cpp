#include <algorithm>

#include "ItemManager.h"
#include "AssemblyLine.h"
#include "Processor.h"
#include "CustomerOrder.h"
#include"OrderManager.h"

//One-Argument Constructor
AssemblyLine::AssemblyLine(const char *record){
	logFile.open(record, std::ios::trunc);
	itemSize = 0;
}

//Move processor to the back of the processors vector
void AssemblyLine::push_back(Processor&& _toMve){
	processors.push_back(std::move(_toMve));
}

//Validate processor tasks
void AssemblyLine::validate(std::ostream& os){
	for (int i = 0; i < processors.size(); i++){
		for (int j = 0; j < processors.size(); j++){
			if (processors[i].validate(processors[j])){
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
	static int i = 0;
	for (; iterProcess != iterProcessEnd && iterItem != iterItemEnd; iterItem++, iterProcess++){
		if (iterProcess->load(*iterItem)){
			itemSize++;
		}
	}
}

//Load Orders
void AssemblyLine::loadOrders(OrderManager& _order, const std::string& entryProcessor, std::ostream& os){

	if (std::find_if(processors.begin(), processors.end(), [&](Processor &_order)->bool{
		return _order.getName() == entryProcessor;
	}) == processors.end()){
		std::cout << "DID NOT FIND entryProcessor" << std::endl;
	}
	else{
		while (!_order.empty()){
				processors[0].accept(_order.extract());
				_order.pop();
			}
	}
}

//Process Function
bool AssemblyLine::process(OrderManager& _order, unsigned int steps){
	std::vector<Processor>::iterator iterProcessor = processors.begin();

		for (int count = 0; count < steps; count++){
			iterProcessor->advance(itemSize);
			if (iterProcessor->readyToPass()){
				iterProcessor->pass(std::rand() % 100 + 2);
			}
			if(iterProcessor->readyToShip()){
				iterProcessor->ship(_order);
			}
	}
	return iterProcessor->empty();
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

int AssemblyLine::getItemSize(){
	return itemSize;
}