#include <algorithm>
#include <functional>
#include "TaskManager.h"
#include "ItemManager.h"
#include "Task.h"

//PushBack function
void TaskManager::push_back(Task&& _back){
	tasks.push_back(std::move(_back));
}

//Begin Iterator Function
std::vector<Task>::iterator TaskManager::begin(){
	return tasks.begin();
}

//Const begin Iterator Function
const std::vector<Task>::const_iterator TaskManager::cbegin() const{
	return tasks.cbegin();
}

//Const end iterator function
const std::vector<Task>::const_iterator TaskManager::cend() const{
	return tasks.cend();
}

//Validate function
void TaskManager::validate(std::ostream& os){
	for (auto i = 0; i < tasks.size(); i++){
		for (auto j = 0; j < tasks.size(); j++){
			if (tasks[i].validate(tasks[j])){
				break;
			}
		}
	}
}

//Display function
void TaskManager::display(std::ostream& os) const{
	std::vector<Task>::const_iterator beginTaskIter = tasks.cbegin();
	std::vector<Task>::const_iterator endTaskIter = tasks.cend();

	for (; beginTaskIter != endTaskIter; beginTaskIter++){
		beginTaskIter->display(os);
	}
}

//Validate TaskManager with ItemManager Function
void validate(const TaskManager& taskManager, const ItemManager& itemManager, std::ostream& os){
	std::vector<Item>::const_iterator iter1 = itemManager.cbegin();
	for (; iter1 != itemManager.cend(); iter1++){
		if (std::find_if(taskManager.cbegin(), taskManager.cend(), [&](const Task& _task){
			return _task.getName() == iter1->getDestination();
		}) == taskManager.cend()){
			os << iter1->getDestination() << " not available" << std::endl;
		}
	}
}