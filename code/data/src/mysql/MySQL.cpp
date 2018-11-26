#include "../../include/mysql/MySQL.h"
#include "../../include/mysql/MySQLStatement.h"

namespace gemini {
namespace sql {

MySQL::MySQL() {}

MySQL::~MySQL() {}

std::shared_ptr<StatementImpl> MySQL::createStatement() {
  return std::shared_ptr<StatementImpl>(new MySQLStatement(*this));
}

String MySQL::systemDatabase() const { return "information_schema"; }

String MySQL::databaseExisted(const String &databaseName) const {
  return StringUtil::SPrintf("SELECT * FROM information_schema.SCHEMATA where SCHEMA_NAME='%s';", databaseName);
}

String MySQL::createDatabase(const String &databaseName) const {
  return StringUtil::SPrintf("CREATE DATABASE %s default charset utf8 COLLATE utf8_general_ci", databaseName);
}

}  // namespace sql
}  // namespace gemini