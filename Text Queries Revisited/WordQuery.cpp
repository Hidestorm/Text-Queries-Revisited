#include "WordQuery.h"
#include "Query.h"
#include <algorithm>
#include <iterator>
using namespace std;

set<TextQuery::line_no>
OrQuery::eval(const TextQuery& file)const
{
	//virtual calls through the Query handle to get result sets for the operands
	set<line_no> right = rhs.eval(file),
		ret_line = lhs.eval(file);//destination to hold results
	ret_line.insert(right.begin(), right.end());

	return ret_line;
}

//returns intersection of its operands' result sets
set<TextQuery::line_no>
AndQuery::eval(const TextQuery & file)const
{
	set<line_no> left = lhs.eval(file),
		right = rhs.eval(file);
	set<line_no> ret_lines;
	set_intersection(left.begin(), left.end(),
		right.begin(), right.end(), inserter(ret_lines, ret_lines.begin()));
	return ret_lines;
}

set<TextQuery::line_no>
NotQuery::eval(const TextQuery & file)const
{
	set<TextQuery::line_no> has_val = query.eval(file);
	set<line_no> ret_lines;

	for (TextQuery::line_no n = 0; n != file.size(); ++n)
		if (has_val.find(n) == has_val.end())
			ret_lines.insert(n);
	return ret_lines;
}