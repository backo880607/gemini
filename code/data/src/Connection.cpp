#include "../include/ConnectionImpl.h"
#include "../include/StatementImpl.h"
#include "../include/mysql/MySQL.h"
#include "../include/oracle/Oracle.h"
#include "../include/sqlite/SQLite.h"
#include "../include/sqlserver/SQLServer.h"
#include "../public/Connection.h"
#include "../include/Driver.h"

namespace gemini {
namespace sql {

Connection::Connection() {}

Connection::~Connection() {
  if (valid() && _impl.unique()) {
    if (_impl->getDriver() != nullptr) {
      _impl->getDriver()->pushBack(_impl);
    } else {
      _impl->close();
    }
  }
}

const SQLConfig& Connection::getConfig() const { return _impl->getConfig(); }

Driver* Connection::getDriver() { return _impl->getDriver(); }

void Connection::setDriver(Driver* driver) { _impl->setDriver(driver); }

void Connection::open() { _impl->open(); }

void Connection::open(SQL_TYPE type, const SQLConfig& config) {
  _impl.reset();
  switch (type) {
    case SQL_TYPE::MySQL:
      _impl.reset(new MySQL());
      break;
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
      return;
  }
  _impl->open(config);
  if (!isConnected()) {
    _impl.reset();
  }
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

CheckDatabase::CheckDatabase() {}

CheckDatabase::~CheckDatabase() {}

void CheckDatabase::execute(SQL_TYPE type, const SQLConfig& config) {
  std::shared_ptr<ConnectionImpl> conn;
  switch (type) {
    case SQL_TYPE::MySQL:
      conn.reset(new MySQL());
      break;
    case SQL_TYPE::SQLite:
      conn.reset(new SQLite());
      break;
    case SQL_TYPE::SQLServer:
      conn.reset(new SQLServer());
      break;
    case SQL_TYPE::Oracle:
      conn.reset(new Oracle());
      break;
    case SQL_TYPE::Access:
      conn.reset(new Access());
      break;
    case SQL_TYPE::Excel:
      conn.reset(new SQLExcel());
      break;
    default:
      return;
  }

  SQLConfig systemConfig = config;
  systemConfig.database = conn->systemDatabase();
  conn->open(systemConfig);
  if (!conn->isConnected()) {
    return;
  }
  Long affectRows = 0;
  (*conn->createStatement() << conn->databaseExisted(config.database).c_str())
      .execute(affectRows);

  if (affectRows <= 0) {
    (*conn->createStatement() << conn->createDatabase(config.database).c_str())
        .execute(affectRows);
  }
  conn->close();
}

}  // namespace sql
}  // namespace gemini