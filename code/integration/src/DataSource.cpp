#include "../public/DataSource.h"
#include "message/Exception.h"

namespace gemini {
namespace integration {

DataSource::DataSource() {
  _matrix = false;
  _config._sepField = "\t";
  _config._sepEntity = "\n";
  _config._replaceField = 0x1A;
  _config._replaceEntity = 0x19;
  _config._cls = nullptr;
  _config._field = nullptr;
}

DataSource::~DataSource() {}

String DataSource::getData(Int index) { THROW(NoSupportException); }

String DataSource::getData(const Field* fd) { THROW(NoSupportException); }

}  // namespace integration
}  // namespace gemini