#include <iomanip>
#include "ItemOrder.h"
#include "Item.h"

ItemOrder::ItemOrder(const std::string& _name){

	//Define name
	if (_name != ""){
		name = _name;
	}
	else{
		name.empty();
	}

	filled = false;
	code = 0;
}

bool ItemOrder::asksFor(const Item& _item) const{
	bool check = false;
	if (isFilled()){
		if (_item.getName() == name &&
			_item.getCode() == code){
			check = true;
		}
	} else{
		if (_item.getName() == name){
			check = true;
		}
	}
	return check;
}

bool ItemOrder::isFilled() const{
	return filled;
}

void ItemOrder::fill(const unsigned int _code){
	code = _code;
	filled = true;
}

void ItemOrder::clear(){
	name = "";
	code = 0;
	filled = false;
}

const std::string& ItemOrder::getName() const{
	return name;
}

void ItemOrder::display(std::ostream& _os) const{
	char status;
	if (getName() != ""){
		if (filled){
			status = '+';
		} else{
			status = '-';
		}
		_os << status << "[" << std::right << std::setfill('0') << std::setw(5) << code << "]"
			<< name << std::endl;
		_os << std::setfill(' ');
	}
}