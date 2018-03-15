#ifndef GEMINI_GraphPropagate_INCLUDE
#define GEMINI_GraphPropagate_INCLUDE
#include "../graph/Graph.h"
#include "VertexPropagate.h"

namespace gemini {

class GraphPropagate : public graph::Graph
{
public:
	GraphPropagate();
	~GraphPropagate();

	VertexPropagate* get(VertexPropagate* target);
	void add(VertexPropagate* target);
protected:
	virtual graph::Edge* createEdge();

private:
	VertexPropagate::colls _caches;
};

}
#endif // GEMINI_GraphPropagate_INCLUDE
