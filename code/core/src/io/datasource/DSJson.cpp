#include "io/datasource/DSJson.h"

namespace gemini {
namespace io {

DSJson::DSJson() { setName("json"); }

DSJson::~DSJson() {}

Boolean DSJson::open(const String &connection) {
  _json.reset(connection.c_str());
  if (!_json.valid()) {
    return false;
  }

  _json.getNode().foreach ([&](DataNode node) { _datas.push_back(node); });
  _index = -1;
  return true;
}

void DSJson::close() {
  _index = -1;
  _json.reset(nullptr);
  _datas.clear();
}

Boolean DSJson::step() { return (++_index) < _datas.size(); }

String DSJson::getData(const Field *fd) { return ""; }

Boolean DSJson::write(const Field *fd, const String &data) { return true; }

DSJsonFile::DSJsonFile() { setName("jsonFile"); }

DSJsonFile::~DSJsonFile() {}

Boolean DSJsonFile::open(const String &connection) {
  _jsonFile.reset(new JsonFile(connection));
  if (!_jsonFile->valid()) {
    return false;
  }
  _jsonFile->getNode().foreach ([&](DataNode node) { _datas.push_back(node); });
  _index = -1;
  return true;
}

void DSJsonFile::close() {
  _jsonFile = nullptr;
  DSJson::close();
}

}  // namespace io
}  // namespace gemini