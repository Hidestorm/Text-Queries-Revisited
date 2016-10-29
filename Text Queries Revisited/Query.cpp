#include "Query.h"
#include "WordQuery.h"
#include <algorithm>
#include <iterator>
using namespace std;
Query::Query(const std::string &word):q(new WordQuery(word)),use(new size_t (1))
{
	
}

Query & Query::operator=(const Query &rhs)
{
	++*rhs.use;
	decr_use();
	q = rhs.q;
	use = rhs.use;
	return *this;
}


