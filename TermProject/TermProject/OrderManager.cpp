#include <algorithm>
#include <functional>
#include "OrderManager.h"
#include "CustomerOrder.h"
#include "ItemOrder.h"
#include "ItemManager.h"

//Push back CustomerOrder
void OrderManager::push_back(CustomerOrder&& _back){
	customerOrders.push_back(std::move(_back));
}

//Return begin Iterator
std::vector<CustomerOrder>::iterator OrderManager::begin(){
	return customerOrders.begin();
}

//Return end Iterator
std::vector<CustomerOrder>::iterator OrderManager::end(){
	return customerOrders.end();
}

//Return const begin iterator
const std::vector<CustomerOrder>::const_iterator OrderManager::cbegin() const{
	return customerOrders.cbegin();
}

//Return const end iterator
const std::vector<CustomerOrder>::const_iterator OrderManager::cend() const{
	return customerOrders.cend();
}

//Display
void OrderManager::display(std::ostream& os) const{
	std::vector<CustomerOrder>::const_iterator customerOrderIterator;
	customerOrderIterator = customerOrders.cbegin();

	for (; customerOrderIterator != customerOrders.cend(); customerOrderIterator++){
		customerOrderIterator->display(os);
	}
}

//empty function
bool OrderManager::empty() const{
	return customerOrders.empty();
}

//pop function
void OrderManager::pop(){
	customerOrders.pop_back();
}

//extract from CustomerOrder
CustomerOrder&& OrderManager::extract(){
	return std::move(customerOrders.back());
}

//Validation Function
void validate(const OrderManager& orderManager, const ItemManager& itemManager, std::ostream& os){

	std::vector<CustomerOrder>::const_iterator iter1 = orderManager.cbegin();
	std::vector<CustomerOrder>::const_iterator iter2 = orderManager.cend();


	for (; iter1 != orderManager.cend(); iter1++){
		for (int i = 0; i < iter1->noOrders(); i++){
			if (std::find_if(itemManager.cbegin(), itemManager.cend(), [&](const Item & _item)->bool{
				return iter1->operator[](i) == _item.getName();
			}) == itemManager.cend()){
				os << iter1->operator[](i) << " not available" << std::endl;
			}
		}
	}
	
}