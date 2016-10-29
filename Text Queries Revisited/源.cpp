#include "TextQuery.h"
#include "Query.h"
#include "Query_base.h"
#include "WordQuery.h"
#include <fstream>
using namespace std;
void print_results(const set<TextQuery::line_no>& locs,
	const string& sought, const TextQuery &file)
{
	// if the word was found, then print count and all occurrences
	typedef set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();
	cout << "\n" << sought << " occurs "
		<< size << " "
		<< "time"<< endl;
	// print each line in which the word appeared
	line_nums::const_iterator it = locs.begin();
	for (; it != locs.end(); ++it) {
		cout << "\t(line "
			// don't confound user with text lines starting at 0
			<< (*it) + 1 << ") "
			<< file.text_line(*it) << endl;
	}
}
int main()
{
	ifstream infile;
	string file_name;
	file_name = "Text.txt";
	infile.open(file_name.c_str());
	TextQuery tq;
	tq.read_file(infile);
	while (true) {
		cout << "enter three word to look for ,or q to quit: ";
		string word1, word2, word3;
		cin >> word1 >> word2 >> word3;
		if (!cin || word1 == "q")break;
		//set<TextQuery::line_no> locs = tq.run_query(s);
		//print_results(locs, s, tq);
		Query q = Query(word1) | Query(word2) & Query(word3);
		cout << "Executing Query for: " << q << endl;
		auto ret = q.eval(tq);
		print_results(ret, word1, tq);
	}
}