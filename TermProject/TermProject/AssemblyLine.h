#pragma once
// Assembly Line Milestone - Assembly Line Interface
// AssemblyLine.h
// Chris Szalwinski
// v1.0 30/11/2015
#include <iostream>
#include <vector>
#include <fstream>

class Processor;
class ItemManager;
class CustomerOrder;
class OrderManager;

class AssemblyLine {
	std::vector<Processor> processors;
	unsigned int itemSize;
	std::ofstream logFile;
public:
	int getItemSize();
	// initialization
	AssemblyLine(const char*);
	void push_back(Processor&&);
	void validate(std::ostream&);
	void validate(ItemManager&, std::ostream&);
	void loadItem(ItemManager&);
	// processing
	void loadOrders(OrderManager&, const std::string&, std::ostream&);
	bool process(OrderManager&, unsigned int steps);
	// reporting
	std::ofstream& getLogFile();
	void display(std::ostream&) const;
	//Destructor
	~AssemblyLine();
};