#include "../../include/datasource/DSExcelCSV.h"
#include "message/Exception.h"
#include "tools/File.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace integration {

DSExcelCSV::DSExcelCSV() {
  setName("excelCSV");
  setMatrix(true);
}

DSExcelCSV::~DSExcelCSV() {}

Boolean DSExcelCSV::validConnection(const Source::SPtr& source,
                                    const String& tblName) {
  return true;
}

Boolean DSExcelCSV::open(const Source::SPtr& source, const String& tblName) {
  //_file.reset(new File(connection.c_str()));
  return _file->open();
}

void DSExcelCSV::close() {
  if (_file) {
    _file->close();
    _file = nullptr;
  }
}

Boolean DSExcelCSV::step() {
  if (_file->isEnd()) {
    return false;
  }

  String rowData = _file->readLine();
  _rowDatas.clear();
  StringUtil::parse<String>(_rowDatas, rowData, _config._sepField.c_str());
  return !_rowDatas.empty();
}

String DSExcelCSV::getData(Int index) {
  THROW_IF(index >= _rowDatas.size(), BoundaryException, index, "out of ",
           (Int)_rowDatas.size())
  return _rowDatas[index];
}

Boolean DSExcelCSV::write(const Field* fd, const String& data) {
  return Boolean();
}

}  // namespace integration
}  // namespace gemini