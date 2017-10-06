#pragma once
// Task Milestone - Task Interface
// Task.h
// Chris Szalwinski
// v1.0 - 24/10/2015
#include <iostream>
#include <string>
#include <wctype.h>

class Task {
	std::string m_name;
	std::string m_slots;
	std::string m_nextTask[2];
	const Task* m_pNextTask[2];
	static char m_delimiter;
	static size_t m_field_width;
public:

	enum Quality {
		passed,
		redirect
	};
	Task(const std::string& _record);
	const std::string& getName() const;
	const unsigned int getSlots() const;
	bool validate(const Task& _task);
	const Task* getNextTask(Quality _quality) const;
	void display(std::ostream& _os) const;
	static void setDelimiter(const char _c);
	static size_t getFieldWidth();
};

bool operator==(const Task&, const Task&);