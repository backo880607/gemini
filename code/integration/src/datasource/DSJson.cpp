#include "../../include/datasource/DSJson.h"

namespace gemini {
namespace integration {

DSJson::DSJson() { setName("json"); }

DSJson::~DSJson() {}

Boolean DSJson::validConnection(const Source::SPtr &source,
                                const String &tblName) {
  return true;
}

Boolean DSJson::open(const Source::SPtr &source, const String &tblName) {
  //_json.reset(connection.c_str());
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

Boolean DSJsonFile::validConnection(const Source::SPtr &source,
                                    const String &tblName) {
  return true;
}

Boolean DSJsonFile::open(const Source::SPtr &source, const String &tblName) {
  //_jsonFile.reset(new JsonFile(connection));
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

}  // namespace integration
}  // namespace gemini