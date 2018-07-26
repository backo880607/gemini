#ifndef GEMINI_GRAPH_EdgeSet_INCLUDE
#define GEMINI_GRAPH_EdgeSet_INCLUDE
#include "Edge.h"

namespace gemini {
namespace graph {

class EdgeSet : public Edge, std::set<Vertex *> {
  typedef std::set<Vertex *> base_type;

 public:
  virtual void add(Vertex *vertex) { base_type::insert(vertex); }
  virtual void remove(Vertex *vertex) { base_type::erase(vertex); }
  virtual void remove() { base_type::clear(); }
};

}  // namespace graph
}  // namespace gemini
#endif  // !GEMINI_GRAPH_EdgeSet_INCLUDE