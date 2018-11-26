#include "../include/ConnectionImpl.h"
//#include "../include/Extractor.h"
#include "../include/StatementImpl.h"

namespace gemini {
namespace sql {

StatementImpl::StatementImpl(ConnectionImpl& conn)
    : _conn(&conn), _binder(nullptr) {}

StatementImpl::~StatementImpl() {
  if (_binder != nullptr) {
    delete _binder;
  }
}

const SQLConfig& StatementImpl::getConfig() const { return _conn->getConfig(); }

String StatementImpl::getColumnType(Types type) {
  switch (type) {
    case Types::BOOLEAN:
      return "BIT";
    case Types::CHAR:
      return "TINYINT";
    case Types::SHORT:
      return "SMALLINT";
    case Types::INT:
      return "INT";
    case Types::LONG:
      return "BIGINT";
    case Types::FLOAT:
      return "REAL";
    case Types::DOUBLE:
      return "DOUBLE";
    case Types::VARCHAR:
      return "VARCHAR(255)";
    case Types::LONGVARCHAR:
      return "CLOB";
    case Types::DATE:
      return "DATE";
    case Types::TIMESTAMP:
      return "TIMESTAMP";
    case Types::BINARY:
      return "";
    case Types::VARBINARY:
      return "";
    case Types::LONGVARBINARY:
      return "";
    case Types::BLOB:
      return "BLOB";
    case Types::CLOB:
      return "CLOB";
  }

  THROW(NotSupportedException)
}

}  // namespace sql
}  // namespace gemini