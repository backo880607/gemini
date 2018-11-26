#include "propagate/GraphPropagate.h"
#include "propagate/VertexPropagate.h"

namespace gemini {

VertexPropagate::VertexPropagate() : _visited(0) {}

VertexPropagate::~VertexPropagate() {}

graph::Graph* VertexPropagate::createGraph() { return new GraphPropagate(); }

VertexPropagate* VertexPropagate::createVertex(const BaseEntity::SPtr& entity,
                                               const Propagate::Data* data) {
  GraphPropagate* graph = (GraphPropagate*)_graph;
  VertexPropagate* target = new VertexPropagate();
  target->_entity = entity;
  target->_data = data;
  graph::Graph::createEdge(this, 0, target, -1);
  graph->add(target);
  return target;
}

VertexPropagate* VertexPropagate::getVertex(const BaseEntity::SPtr& entity,
                                            const Propagate::Data* data) {
  GraphPropagate* graph = (GraphPropagate*)_graph;
  VertexPropagate target;
  target._entity = entity;
  target._data = data;
  return graph->get(&target);
}

}  // namespace gemini