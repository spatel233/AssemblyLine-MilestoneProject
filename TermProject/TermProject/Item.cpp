#include <iomanip>
#include "Item.h"
#include "CustomerOrder.h"
#include "Utilities.h"

//Constructor One argument Containing one line of the file
Item::Item(const std::string& _input){
	//Make a string and temp Utilites Object
	Utilities tempUtilities;
	std::string tempInfo = _input;
	std::string recieved;

	//Default Values
	details = "no detailed description";
	code = 1;

	//Temporary Objects
	size_t current = 0;
	bool more = true;
	int assign = 0;

	while (more){
		//Get token
		recieved = tempUtilities.nextToken(tempInfo, current, more);
		
		//Put into class throw exception if nothing is there
		//increase field_width if size of string is bigger than 
		//field_width
		//Assign variables of Item Class
		switch (assign){
		case 0:
			if (recieved == "")
			{
				std::string msg = "No name";
				throw msg;
			}
			name = recieved;
			if (name.size() > field_width){
				field_width = name.size();
			}
			break;
		case 1:
			if (recieved == "")
			{
				std::string msg = "No source";
				throw msg;
			}
			source = recieved;
			if (source.size() > field_width){
				field_width = source.size();
			}
			break;
		case 2:
			if (recieved == "")
			{
				std::string msg = "No Destination";
				throw msg;
			}
			destination = recieved;
			if (destination.size() > field_width){
				field_width = destination.size();
			}
			break;
		case 3:
			code = stoi(recieved);
			break;
		case 4:
			details = recieved;
			if (details.size() > field_width){
				field_width = details.size();
			}
			break;
		default:
			break;
		}
		assign++;
	}
}

//empty function
bool Item::empty() const{
	return(name.empty() &&
		   source.empty() &&
		   destination.empty() &&
		   details == "no detailed description" &&
		   code == 1);
}

//Overloaded increment operator
void Item::operator++(int _increment){
	_increment++;
}

//getCode Function
unsigned int Item::getCode() const{
	return code;
}

//getName function
const std::string& Item::getName() const{
	return name;
}

//getSource function
const std::string& Item::getSource() const{
	return source;
}

//getDestination function
const std::string& Item::getDestination() const{
	return destination;
}

//Display function
void Item::display(std::ostream& _os, bool full) const{
	//String objects to be printed out with format &
	//calculated colon width for the next line format
	std::string colon = ":";
	std::string from = "From ";
	std::string to = "To ";
	int colonWidth = field_width + 7;
	_os << std::left << std::setw(field_width) << name
		<< "[" << std::right << std::setfill('0') << std::setw(5) << code << "]" << std::setfill(' ');
	if (!full){
		std::cout << std::endl;
	}
	//If full display the rest of the information
	if (full){
		_os << std::right << std::setw(6) << from
			<< std::left << std::setw(field_width) << source 
			<< std::right << std::setw(6)
			<< to << std::left << std::setw(field_width) 
			<< destination << std::endl;
		_os << std::right << std::setw(colonWidth) << colon
			<< " " << std::left << std::setw(field_width) << details << std::endl;
	}
}

//setDemlimiter Function
void Item::setDelimiter(const char _c){
	delimiter = _c;
}

//getFieldWidth Function
size_t Item::getFieldWidth(){
	return field_width;
}