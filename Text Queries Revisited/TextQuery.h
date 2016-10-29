#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>

class TextQuery
{
public:
	typedef std::vector<std::string>::size_type line_no;
	/* interface:
	 read_file build internal data structures for the given file
	 run_query finds the given word and returns set of lines on which it appears
	 text_line returns a requested line from the input file
	*/
	void read_file(std::ifstream &is)
	{
		store_file(is);
		build_map();
	}
	std::set<line_no> run_query(const std::string&)const;
	std::string text_line(line_no) const;
	line_no size() const{
		return lines_of_text.size();
	}
private:
	void store_file(std::ifstream&);	//store input file
	void build_map();					//associated each word with a set of numbers
	std::vector<std::string> lines_of_text;
	std::map < std::string, std::set<line_no>> word_map;
};