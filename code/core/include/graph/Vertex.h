#ifndef GEMINI_GRAPH_Vertex_INCLUDE
#define GEMINI_GRAPH_Vertex_INCLUDE
#include "../../public/Common.h"

namespace gemini {
namespace graph {

class Graph;
class Vertex {
 public:
  virtual Graph *createGraph() = 0;

 protected:
  Graph *_graph = nullptr;
  Long _adjvex = -1;

  friend class Graph;
};

}  // namespace graph
}  // namespace gemini
#endif  // !GEMINI_GRAPH_Vertex_INCLUDE