#pragma once
#include "Edge.h"

namespace gemini {
namespace graph {

class EdgeSingleton : public Edge
{
public:
	virtual void add(Vertex* vertex) { _vertex = vertex; }
	virtual void remove(Vertex* vertex) { if (_vertex == vertex) _vertex = nullptr; }
	virtual void remove() { _vertex = nullptr; }

private:
	Vertex* _vertex;
};

}}