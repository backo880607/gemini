#pragma once
#include "../../public/Common.h"

namespace gemini {
namespace graph {

class Vertex;
class Edge {
protected:
	typedef std::iterator<std::forward_iterator_tag, Vertex*> iterator;
public:
	virtual void add(Vertex* vertex) = 0;
	virtual void remove(Vertex* vertex) = 0;
	virtual void remove() = 0;

private:
	Int _sign = -1;
	Int _reverseSign = -1;

	friend class Graph;
};

}
}