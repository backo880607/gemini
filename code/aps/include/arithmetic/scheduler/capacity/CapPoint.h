#ifndef APS_SCHEDULER_CapPoint_INCLUDE
#define APS_SCHEDULER_CapPoint_INCLUDE
#include "Common.h"

namespace aps {
namespace scheduler {

class CapPoint {
  struct Node {
    ID id;
    Double cap;
  };

 public:
  CapPoint();
  ~CapPoint();

 private:
  gemini::Long _time;
  gemini::Double _used;
  std::vector<Node> _nodes;
};

}  // namespace scheduler
}  // namespace aps
#endif  // APS_SCHEDULER_CapPoint_INCLUDE