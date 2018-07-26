#include "io/datasource/DSXML.h"

namespace gemini {
namespace io {

DSXML::DSXML() { setName("xml"); }

DSXML::~DSXML() {}

DSXMLFile::DSXMLFile() { setName("xmlFile"); }

DSXMLFile::~DSXMLFile() {}

}  // namespace io
}  // namespace gemini