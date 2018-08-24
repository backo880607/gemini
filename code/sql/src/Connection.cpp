#include "../include/ConnectionImpl.h"
#include "../include/oracle/Oracle.h"
#include "../include/sqlite/SQLite.h"
#include "../include/sqlserver/SQLServer.h"
#include "../public/Connection.h"

namespace gemini {
namespace sql {

Connection::Connection() {}

Connection::~Connection() {}

Boolean Connection::open() { return _impl ? _impl->open() : false; }

Boolean Connection::open(SQL_TYPE type, const SQLConfig &config) {
  _impl.reset();
  switch (type) {
    case SQL_TYPE::SQLite:
      _impl.reset(new SQLite());
      break;
    case SQL_TYPE::SQLServer:
      _impl.reset(new SQLServer());
      break;
    case SQL_TYPE::Oracle:
      _impl.reset(new Oracle());
      break;
    case SQL_TYPE::Access:
      _impl.reset(new Access());
      break;
    case SQL_TYPE::Excel:
      _impl.reset(new SQLExcel());
      break;
    default:
      return false;
  }
  return _impl ? _impl->open(config) : false;
}

void Connection::close() {
  if (valid()) _impl->close();
}

Boolean Connection::isConnected() {
  return valid() ? _impl->isConnected() : false;
}

Boolean Connection::getAutoCommit() { return _impl->getAutoCommit(); }

void Connection::setAutoCommit(Boolean autoCommit) {
  _impl->setAutoCommit(autoCommit);
}

void Connection::begin() { _impl->begin(); }

void Connection::commit() { _impl->commit(); }

void Connection::rollback() { _impl->rollback(); }

Boolean Connection::canTransact() { return _impl->canTransact(); }

Boolean Connection::isTransaction() { return _impl->isTransaction(); }

int Connection::getTransactionIsolation() {
  return _impl->getTransactionIsolation();
}

void Connection::setTransactionIsolation(Int level) {
  _impl->setTransactionIsolation(level);
}

Boolean Connection::hasTransactionIsolation(Int level) {
  return _impl->hasTransactionIsolation(level);
}

Boolean Connection::isTransactionIsolation(Int level) {
  return _impl->isTransactionIsolation(level);
}

Int Connection::maxStatementLength() { return _impl->maxStatementLength(); }

}  // namespace sql
}  // namespace gemini