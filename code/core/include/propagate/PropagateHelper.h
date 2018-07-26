#ifndef GEMINI_PropagateHelp_INCLUDE
#define GEMINI_PropagateHelp_INCLUDE

namespace gemini {

class XMLNode;
class PropagateHelper final {
 public:
  PropagateHelper();
  ~PropagateHelper();

  void loadConfig();
};

}  // namespace gemini
#endif  // GEMINI_PropagateHelp_INCLUDE