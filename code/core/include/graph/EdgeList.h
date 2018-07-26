#ifndef GEMINI_GRAPH_EdgeList_INCLUDE
#define GEMINI_GRAPH_EdgeList_INCLUDE
#include "Edge.h"

namespace gemini {
namespace graph {

class EdgeList : public Edge, std::list<Vertex *> {
  typedef std::list<Vertex *> base_type;

 public:
  virtual void add(Vertex *vertex) { base_type::push_back(vertex); }
  virtual void remove(Vertex *vertex) { base_type::remove(vertex); }
  virtual void remove() { base_type::clear(); }
};

}  // namespace graph
}  // namespace gemini
#endif  // !GEMINI_GRAPH_EdgeList_INCLUDE