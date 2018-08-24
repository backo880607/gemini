#include "../include/StatementImpl.h"

namespace gemini {
namespace sql {

StatementImpl::StatementImpl(ConnectionImpl &conn)
    : _state(State::ST_INITIALIZED), _conn(conn) {}

StatementImpl::~StatementImpl() {}

void StatementImpl::reset() {
  resetImpl();
  _state = State::ST_INITIALIZED;
  _ostr.clear();
  _ostr.str("");
}

void StatementImpl::compile() {
  std::lock_guard<std::mutex> locker(_mutex);

  if (_state == State::ST_INITIALIZED || _state == State::ST_RESET ||
      _state == State::ST_BOUND) {
    compileImpl();
    _state = State::ST_COMPILED;
  }
}

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
      return "VARCHAR";
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