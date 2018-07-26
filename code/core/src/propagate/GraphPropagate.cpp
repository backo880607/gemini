#include "propagate/EdgePropagate.h"
#include "propagate/GraphPropagate.h"

namespace gemini {

GraphPropagate::GraphPropagate() {}

GraphPropagate::~GraphPropagate() {}

VertexPropagate* GraphPropagate::get(VertexPropagate* target) {
  VertexPropagate::colls::iterator iter = _caches.find(target);
  return iter != _caches.end() ? *iter : nullptr;
}

void GraphPropagate::add(VertexPropagate* target) { _caches.insert(target); }

graph::Edge* GraphPropagate::createEdge() { return new EdgePropagate(); }

}  // namespace gemini