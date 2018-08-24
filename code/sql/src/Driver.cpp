#include "../include/Driver.h"
#include "IApplication.h"
#include "tools/File.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace sql {
Driver::Driver() {}

Driver::~Driver() {}

Connection Driver::getConn() {
  Connection conn;
  conn.open(_type, _config);
  return conn;
}

void Driver::setType(const String& type) {
  if (StringUtil::icompare(type.c_str(), "SQLite") == 0) {
    _type = SQL_TYPE::SQLite;
  } else if (StringUtil::icompare(type.c_str(), "MySQL") == 0) {
    _type = SQL_TYPE::MySQL;
  } else if (StringUtil::icompare(type.c_str(), "Oracle") == 0) {
    _type = SQL_TYPE::Oracle;
  } else if (StringUtil::icompare(type.c_str(), "SQLServer") == 0) {
    _type = SQL_TYPE::SQLServer;
  } else if (StringUtil::icompare(type.c_str(), "Access") == 0) {
    _type = SQL_TYPE::Access;
  } else if (StringUtil::icompare(type.c_str(), "Excel") == 0) {
    _type = SQL_TYPE::Excel;
  }
}

}  // namespace sql
}  // namespace gemini