#include "graph/Graph.h"
#include "graph/Vertex.h"
#include "graph/Edge.h"

namespace gemini {
namespace graph {

Graph::Graph()
{
	_nodes.push_back(nullptr);
}

Graph::~Graph()
{

}

Graph* Graph::create(Vertex* vertex)
{
	Graph* temp = vertex->_graph;
	if (temp == nullptr) {
		temp = vertex->createGraph();
		vertex->_graph = temp;
	}
	return temp;
}

void Graph::merge(Graph* val)
{
	if (val == nullptr || this == val)
		return;

	Long count = getNodeSize();
	_nodes.insert(_nodes.end(), val->_nodes.begin(), val->_nodes.end());
	for (VertexNode* vertexNode : val->_nodes) {
		if (vertexNode->vertex != nullptr) {
			vertexNode->vertex->_graph = this;
			vertexNode->vertex->_adjvex += count;
		}
	}
}

void Graph::createEdge(Vertex* first, Int firstSign, Vertex* second, Int secondSign)
{
	Graph* firstGraph = first->_graph;
	Graph* secondGraph = second->_graph;
	if (firstGraph == nullptr) {
		firstGraph = secondGraph == nullptr ? first->createGraph() : secondGraph;
		first->_graph = firstGraph;
		if (secondGraph == nullptr) {
			second->_graph = secondGraph;
		}
	} else if (secondGraph == nullptr) {
		second->_graph = firstGraph;
	} else if (firstGraph != secondGraph) {
		if (firstGraph->getNodeSize() < secondGraph->getNodeSize()) {
			secondGraph->merge(firstGraph);
			firstGraph = secondGraph;
		} else {
			firstGraph->merge(secondGraph);
		}
	}

	VertexNode* firstNode = firstGraph->getNode(first, true);
	VertexNode* secondNode = firstGraph->getNode(second, true);

	Edge*& outEdge = firstNode->outEdge[firstSign];
	if (outEdge == nullptr) {
		outEdge = firstGraph->createEdge();
		outEdge->_sign = firstSign;
		outEdge->_reverseSign = secondSign;
	}
	outEdge->add(second);

	if (secondSign >= 0) {
		Edge*& inEdge = secondNode->inEdge[secondSign];
		if (inEdge == nullptr) {
			inEdge = firstGraph->createEdge();
			inEdge->_sign = secondSign;
			inEdge->_reverseSign = firstSign;
		}
		inEdge->add(first);
	}
}

Graph::VertexNode* Graph::getNode(Vertex* vertex, Boolean bCreate /* = false */)
{
	if (vertex->_adjvex >= 0) {
		VertexNode* node = _nodes[vertex->_adjvex];
		return node->vertex != nullptr ? node : nullptr;
	}

	if (!bCreate) {
		return nullptr;
	}

	vertex->_adjvex = _nodes.size();
	vertex->_graph = this;
	VertexNode* node = new VertexNode();
	_nodes.push_back(node);
	return node;
}

Vertex* Graph::get(Long adjvex)
{
	if (adjvex <= 0 || adjvex >= getNodeSize()) {
		return nullptr;
	}

	return _nodes[adjvex]->vertex;
}

Edge* Graph::getOutEdge(Vertex* vertex, Int sign)
{
	VertexNode* node = getNode(vertex);
	if (node == nullptr) {
		return nullptr;
	}

	auto iter = node->outEdge.find(sign);
	return iter != node->outEdge.end() ? iter->second : nullptr;
}

Edge* Graph::getInEdge(Vertex* vertex, Int sign)
{
	VertexNode* node = getNode(vertex);
	if (node == nullptr) {
		return nullptr;
	}

	auto iter = node->inEdge.find(sign);
	return iter != node->inEdge.end() ? iter->second : nullptr;
}

Edge* Graph::getEdge(Vertex* vertex, Int sign)
{
	VertexNode* node = getNode(vertex);
	if (node == nullptr) {
		return nullptr;
	}

	auto iter = node->outEdge.find(sign);
	if (iter != node->outEdge.end()) {
		return iter->second;
	}

	iter = node->inEdge.find(sign);
	return iter != node->inEdge.end() ? iter->second : nullptr;
}

void Graph::removeOutEdge(Vertex* vertex, Int sign, Vertex* target)
{
	Edge* outEdge = getOutEdge(vertex, sign);
	if (outEdge != nullptr) {
		Edge* inEdge = getInEdge(target, outEdge->_reverseSign);
		if (inEdge != nullptr) {
			inEdge->remove(vertex);
		}

		outEdge->remove(target);
	}
}

void Graph::removeOutEdge(Vertex* vertex, Int sign)
{
	Edge* outEdge = getOutEdge(vertex, sign);
	if (outEdge != nullptr && outEdge->_reverseSign >= 0) {
		/*Edge* inEdge = getInEdge(target, outEdge->_reverseSign);
		if (inEdge != nullptr) {
			inEdge->remove(vertex);
		}*/

		outEdge->remove();
	}
}

}
}