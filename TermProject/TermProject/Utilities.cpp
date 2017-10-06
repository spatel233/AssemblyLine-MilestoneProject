#include <string>
#include <sstream>
#include <vector>
#include "Utilities.h"
using namespace std;
std::string filterString(std::string line);
//One argument Constructor with a default value
Utilities::Utilities(size_t _minimum_field_width){
	m_field_width = _minimum_field_width;
}

//Extraction for each token
const std::string Utilities::nextToken(const std::string& _str, size_t& _next_pos, bool& _more){
	static string newRecord;
	string temp;
	static int count = 1;
	char c = getDelimiter();
	bool done = false;
	//if _next_pos is 0 put string inside newRecord
	if (!_next_pos){
		newRecord = _str;
	}
	//If reached end of line make _more false
	if (newRecord.find(c) == std::string::npos){
		_more = false;
	}
	//extract next token & shrink string by _next_pos till the new line
	temp = newRecord.substr(0, newRecord.find(c));
	_next_pos = temp.size() + 1;
	if (_more){
		newRecord = newRecord.substr(_next_pos, newRecord.find('\n'));
	}

	//Update m_field_width
	if (temp.size() > m_field_width){
		m_field_width = temp.size();
	}
	return filterString(temp);
}

//Set field width
void Utilities::setFieldWidth(size_t _fw){
	m_field_width = _fw;
}

//Gets field width
size_t Utilities::getFieldWidth() const{
	return m_field_width;
}

//Get delimiter
const char Utilities::getDelimiter(){
	return m_delimiter;
}

//Set delimiter
void Utilities::setDelimiter(const char _c){
	m_delimiter = _c;
}

std::string filterString(std::string line)
{
	std::string ret;
	string word;
	stringstream ss(line);
	std::vector<string> words;
	while (ss.eof() == false)
	{
		word = "";
		ss >> word;
		if (word.size() > 0)
			words.push_back(word);
	}


	for(int i = 0; i < words.size(); i++)
	{
		ret += words[i];
		if (i != words.size() - 1)
		{
			ret += " ";
		}
	}
return ret;
}