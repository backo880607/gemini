#ifndef GEMINI_IO_DSXML_INCLUDE
#define GEMINI_IO_DSXML_INCLUDE
#include "../../../public/io/DataSource.h"

namespace gemini {
namespace io {

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

}  // namespace io
}  // namespace gemini
#endif  // GEMINI_IO_DSXML_INCLUDE
