#pragma once
// Milestone 1 - Utilities Interface
// Utilities.h
// Chris Szalwinski
// v1.0 - 24/10/2015
#include <string>

const unsigned int CODE_WIDTH = 5; // item code field width (later)

class Utilities {
	size_t m_field_width;
	static char m_delimiter;
public:
	Utilities(size_t _minimum_field_width = 1u);
	void setFieldWidth(size_t _fw);
	size_t getFieldWidth() const;
	const std::string nextToken(const std::string& _str, size_t& _next_pos,
		bool& _more);
	static void setDelimiter(const char _c);
	static const char getDelimiter();
};