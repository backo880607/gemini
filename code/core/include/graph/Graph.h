#ifndef GEMINI_GRAPH_Graph_INCLUDE
#define GEMINI_GRAPH_Graph_INCLUDE
#include "../../public/Common.h"

namespace gemini {
namespace graph {

class Vertex;
class Edge;
class Graph {
  Graph(const Graph &) = delete;
  Graph &operator=(const Graph &) = delete;

 protected:
  class VertexNode {
   public:
    Vertex *vertex;
    std::map<Int, Edge *> outEdge;
    std::map<Int, Edge *> inEdge;
  };

  Graph();
  virtual Edge *createEdge() = 0;

 public:
  virtual ~Graph();

  Long getNodeSize() const { return _nodes.size(); }

  static Graph *create(Vertex *vertex);
  static void createEdge(Vertex *first, Int firstSign, Vertex *second,
                         Int secondSign);

  VertexNode *getNode(Vertex *vertex, Boolean bCreate = false);

  Vertex *get(Long adjvex);

  Edge *getOutEdge(Vertex *vertex, Int sign);
  Edge *getInEdge(Vertex *vertex, Int sign);
  Edge *getEdge(Vertex *vertex, Int sign);

  void removeOutEdge(Vertex *vertex, Int sign, Vertex *target);
  void removeOutEdge(Vertex *vertex, Int sign);

 private:
  void merge(Graph *val);

 private:
  std::vector<VertexNode *> _nodes;
};

}  // namespace graph
}  // namespace gemini
#endif  // !GEMINI_GRAPH_Graph_INCLUDE