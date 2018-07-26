#include "io/datasource/DSLocaleFile.h"
#include "tools/File.h"

namespace gemini {
namespace io {

DSLocaleFile::DSLocaleFile() : _prevPos(0), _curPos(0) {
  setName("localeFile");
  setMatrix(true);
}

DSLocaleFile::~DSLocaleFile() {}

Boolean DSLocaleFile::open(const String &connection) {
  _file.reset(new File(connection.c_str()));
  return _file->open();
}

void DSLocaleFile::close() {
  _file->close();
  _prevPos = 0;
  _curPos = 0;
  _stream.clear();
  _fieldsPos.clear();
}

Boolean DSLocaleFile::step() {
  if (_curPos == String::npos) {
    return false;
  }

  _prevPos = _curPos;
  if (_prevPos != 0) {
    _prevPos += _config._sepEntity.size();
  }
  _curPos = _stream.find(_config._sepEntity, _prevPos);
  parseFields();
  return !_fieldsPos.empty();
}

String DSLocaleFile::getData(Int index) {
  const String::size_type fPos =
      index == 0 ? _prevPos : _fieldsPos[index - 1] + _config._sepField.size();
  const String::size_type lPos = _fieldsPos[index];
  return _stream.substr(fPos, lPos - fPos);
}

Boolean DSLocaleFile::write(const Field *fd, const String &data) {
  return true;
}

void DSLocaleFile::parseFields() {
  _fieldsPos.clear();
  std::size_t fPos = _prevPos;
  const std::size_t sepLen = strlen(_config._sepField.c_str());
  String::size_type idx = _stream.find(_config._sepField, fPos);
  while (idx != String::npos && idx < _curPos) {
    _fieldsPos.push_back(idx);
    idx += sepLen;
    fPos = idx;
    idx = _stream.find(_config._sepField, fPos);
  }

  if (fPos <= _curPos) {
    _fieldsPos.push_back(_curPos);
  }
}

}  // namespace io
}  // namespace gemini