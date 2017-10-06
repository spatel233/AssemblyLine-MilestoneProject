#include <iomanip>
#include "Utilities.h"
#include "Task.h"
using namespace std;

//Return name
const std::string& Task::getName() const{
	return m_name;
}

//Return Slot
const unsigned int Task::getSlots() const{
	unsigned int convert;
	convert = atoi(m_slots.c_str());
	return convert;
}

//Validate task
bool Task::validate(const Task& _task){
	bool check = false;
	if (*this == _task){
		for (int i = 0; i < 2; i++){
			if (m_nextTask[i] == _task.m_nextTask[i]){
				m_pNextTask[i] = &_task;
				check = true;
			}
		}
	}
	return check;
}

//Get Next task
const Task* Task::getNextTask(Quality _quality) const{
	//Check if it was validated if not throw exception back to the main
	//if (m_nextTask[0] != "" || m_nextTask[1] != ""){
		if (_quality == passed || _quality == redirect){
			if (!m_pNextTask[0] || !m_pNextTask[1]){
				std::string nextTask_t = "*** to be validated    @  [";
				nextTask_t += m_nextTask[0];
				nextTask_t += "]";
				nextTask_t += "@ ";
				nextTask_t += "[";
				nextTask_t += getName();
				nextTask_t += "] ***";
				throw  nextTask_t;
			}
			else{
				if (_quality == passed){
					return m_pNextTask[0];
				}
				else if (_quality == redirect){
					return m_pNextTask[1];
				}
			}
		//}
	}
	//CHANGED return this;
	return nullptr;
}

//Display information
void Task::display(std::ostream& _os) const{
	//Making nextTask string
	string nextTask1 = "[";
	nextTask1 += m_nextTask[0];
	nextTask1 += "]";

	string nextTask2 = "[";
	nextTask2 += m_nextTask[1];
	nextTask2 += "]";

	//Print out name and slot
	_os << std::left << std::setw(m_field_width) << "Task Name   :" << std::left << std::setw(m_field_width) << getName() 
	<< std::right << std::setw(m_field_width) << "[" << getSlots() << "]" << std::endl;
	//Print information out if m_pNextTask null print out to be validated
	//if m_pNextTask not null print out local pnextTask#
	if (m_nextTask[0] != ""){
		_os << std::right << std::setw(m_field_width) << "Continue to :" << std::left << std::setw(m_field_width) 
			<< nextTask1;
		((!m_pNextTask[0]) ? cout << std::right << std::setw(m_field_width) << "*** to be validated ***" : cout << ""); cout << endl;
	}
	if (m_nextTask[1] != ""){
		_os << std::right << std::setw(m_field_width) << "Redirect to :" << std::left << std::setw(m_field_width) 
			<< nextTask2;
		((!m_pNextTask[1]) ? cout << std::right << std::setw(m_field_width) << "*** to be validated ***" : cout << ""); cout << endl;
	}
}


//Read file into object
Task::Task(const std::string& record){

	//Default values
	m_pNextTask[0] = nullptr;
	m_pNextTask[1] = nullptr;
	m_slots = "1";
	m_nextTask[0] = "";
	m_nextTask[1] = "";

	//Temporary Objects
	Utilities m_utility;
	size_t current = 0;
	size_t passBy = 0;
	size_t next = 0;
	bool more = true;
	string temp;
	string newRecord = record;
	int assign = 0;
	int garbage = 0;


	while (more){
		 temp = m_utility.nextToken(newRecord, current, more);
		 switch (assign){
		 case 0:
			 if (temp == ""){
				 std::string exception = "|| <-- *** no token found before the delimiter ***\n";
				 exception += "| Remove SSD | 1 | SSD | <-- *** no token found before the delimiter **";
				 throw exception;
			 }
			  m_name = temp;
			 break;
		 case 1:
			 m_slots = temp;
			 break;
		 case 2:
			 m_nextTask[0] = temp;
			 break;
		 case 3:
			 m_nextTask[1] = temp;
			 break;
		 default:
			 garbage++;
		 }
		 //before reaching end of line update the current
		 //to shrink from the current string in getToken
		 if (garbage == 0){
			 current = 0;
			 current += temp.length();
			 current += 1;
			 if (current > m_field_width){
				 m_field_width = current;
			 }
			 ++assign;
		 }
	}
	
}

//Overloaded Operator for ==
bool operator==(const Task& t1, const Task& t2){
	bool confirm = false;
	if (t1.getName() == t2.getName()){
		confirm = true;
	}
	return confirm;
}

//Set dilimiter function
void Task::setDelimiter(const char c){
	Task::m_delimiter = c;
}

//Get fieldwith function
size_t Task::getFieldWidth(){
	return Task::m_field_width;
}