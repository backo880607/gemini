#ifndef GEMINI_INTEGRATION_DSXML_INCLUDE
#define GEMINI_INTEGRATION_DSXML_INCLUDE
#include "../../public/DataSource.h"

namespace gemini {
namespace integration {

class DSXML : public DataSource {
 public:
  DSXML();
  ~DSXML();
};

class DSXMLFile : public DSXML {
 public:
  DSXMLFile();
  ~DSXMLFile();
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_DSXML_INCLUDE
