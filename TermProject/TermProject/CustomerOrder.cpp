#include <vector>
#include <iomanip>
#include <cstdlib>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "ItemOrder.h"
#include "Item.h"

//One argument constructor which has one line of the file
//Passed through its parameter
CustomerOrder::CustomerOrder(const std::string& _record){
	Utilities tempUtilities;
	std::string tempString;
	std::vector<std::string> vecString;
	order = nullptr;
	nOrders = 0;
	size_t field_width = tempUtilities.getFieldWidth();
	int assign = 0;
	bool more = true;
	size_t current = 0;
	field_width = 0;

	while (more){
		tempString = tempUtilities.nextToken(_record, current, more);
		switch (assign){
		case 0:
			if (tempString == ""){
				std::string exceptions = "No name";
				throw exceptions;
			}
			name = tempString;
			break;
		case 1:
			if(tempString == ""){
				std::string exceptions = "No Product";
				throw exceptions;
			}
			product = tempString;
			break;
		default:
			vecString.push_back(tempString);
			nOrders++;
			break;
		}

		if (tempUtilities.getFieldWidth() > field_width){
			field_width = tempUtilities.getFieldWidth();
		}
		assign++;
	}

	//Allocate order
	int reserve;
	reserve = vecString.size();
	order = new ItemOrder[reserve];
	ItemOrder *tempOrder = order;
	int i = 0;
	for (int i = 0; i < nOrders; i++){
		tempOrder[i] = ItemOrder(vecString.at(i));
	}
	vecString.clear();
}

//Checks if the object is in a safe empty state
bool CustomerOrder::empty() const{
	return(name == "" &&
		product == "" &&
		order == nullptr &&
		nOrders == 0 &&
		field_width == 0);
}

//Copy constructor
CustomerOrder::CustomerOrder(const CustomerOrder& _cpy){
	std::string exception = "No copying allowed";
	throw exception;
}

//Move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& _toMve){
	*this = std::move(_toMve);
}

//Move Operator
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& _toMve){
	if (!_toMve.empty()){
		if (!order){
			delete[] order;
		}
		name = _toMve.name;
		product = _toMve.product;
		order = _toMve.order;
		nOrders = _toMve.nOrders;
		field_width = _toMve.field_width;
		delimiter = _toMve.delimiter;
		_toMve.order = nullptr;
	}
	return std::move(*this);
}

//Destructor
CustomerOrder::~CustomerOrder(){
	delete[]order;
}

//Get number of orders
unsigned CustomerOrder::noOrders() const{
	return nOrders;
}

//Overloaded index operator
const std::string& CustomerOrder::operator[](unsigned int _i) const{
	if (_i <= nOrders){
		return order[_i].getName();
	}
	std::string exception = "Out of bounds";
	throw exception;
}

//Fill ItemOrder
void CustomerOrder::fill(Item& item){
	ItemOrder *ptrOrder = order;
	for (int i = 0; i < nOrders; i++){
		if (ptrOrder->asksFor(item)){
			ptrOrder->fill(item.getCode());
		}
		ptrOrder++;
	}
}

//Remove ItemOrder
void CustomerOrder::remove(Item& item){
	unsigned int count = noOrders();
	for (int i = 0; i < count; i++){
		if (order[i].asksFor(item)){
			if (order[i].isFilled()){
				order[i].clear();
			}
		}
	}
}

//Display the ItemOrder
void CustomerOrder::display(std::ostream& _os) const{
	if (order){
	_os << std::left << std::setw(field_width) << name
		<< std::left << std::setw(field_width) << product << std::endl;
	
		ItemOrder* ptrOrder = order;
		for (int i = 0; i < nOrders; i++){
			ptrOrder->display(std::cout);
			ptrOrder++;
		}
	}
}

//Sets delimiter
void CustomerOrder::setDelimiter(const char _c){
	delimiter = _c;
}