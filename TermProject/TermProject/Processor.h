#pragma once
// Assembly Line Milestone - Processor Interface
// Processor.h
// Chris Szalwinski
// v1.0 30/11/2015
#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <functional>
#include "CustomerOrder.h"
#include "Task.h"
#include <vector>
class Item;
class OrderManager;

class Processor : public Task {
	Item* item;
	std::deque<CustomerOrder> waiting;
	std::deque<CustomerOrder> process;
	std::deque<CustomerOrder> complete;
	unsigned int end_gap;
	bool is_a_filler;
	std::function<Task::Quality(int)> inspector;
	std::ofstream& logFile;
public:
	Processor(const std::string& record, std::function<Task::Quality(int)>,
		std::ofstream&);
	bool load(Item&);
	void accept(CustomerOrder&&);
	void advance(unsigned int);
	bool readyToPass() const;
	void pass(int);
	bool readyToShip() const;
	void ship(OrderManager&);
	bool empty() const;
	void display(std::ostream&) const;
	~Processor();
};