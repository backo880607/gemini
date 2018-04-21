#pragma once
#include "../../public/Common.h"

namespace gemini {
namespace graph {

class Graph;
class Vertex {

public:
	virtual Graph* createGraph() = 0;
protected:
	Graph* _graph = nullptr;
	Long _adjvex = -1;

	friend class Graph;
};

}
}