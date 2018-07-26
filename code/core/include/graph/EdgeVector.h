#ifndef GEMINI_GRAPH_EdgeVector_INCLUDE
#define GEMINI_GRAPH_EdgeVector_INCLUDE
#include "Edge.h"

namespace gemini {
namespace graph {

class EdgeVector : public Edge, std::vector<Vertex *> {
  typedef std::vector<Vertex *> base_type;

 public:
  virtual void add(Vertex *vertex) { base_type::push_back(vertex); }
  virtual void remove(Vertex *vertex) {}
  virtual void remove() { base_type::clear(); }
};

}  // namespace graph
}  // namespace gemini
#endif  // !GEMINI_GRAPH_EdgeVector_INCLUDE