#include "../../include/sqlite/SQLite.h"
#include "../../include/sqlite/SQLiteStatement.h"
#include "sqlite3.h"
#include "tools/File.h"

namespace gemini {
namespace sql {

SQLite::SQLite() : _pDB(nullptr) {}

SQLite::~SQLite() {}

Boolean SQLite::open() {
  FilePath filePath(getConfig().ip.c_str());
  filePath.append((getConfig().database + ".db").c_str());
  std::unique_lock<std::mutex> locker(_mutex);
  return sqlite3_open_v2(
             filePath.string().c_str(), &_pDB,
             SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI,
             nullptr) == 0;
}

void SQLite::close() {
  if (_pDB != nullptr) {
    std::unique_lock<std::mutex> locker(_mutex);
    sqlite3_close_v2(_pDB);
    _pDB = nullptr;
  }
}

std::shared_ptr<StatementImpl> SQLite::createStatement() {
  return std::shared_ptr<StatementImpl>(
      _pDB != nullptr ? new SQLiteStatement(*this, _pDB) : nullptr);
}

Boolean SQLite::getAutoCommit() {
  std::unique_lock<std::mutex> locker(_mutex);
  return (0 != sqlite3_get_autocommit(_pDB));
}

void SQLite::setAutoCommit(Boolean autoCommit) {
  THROW(NotImplementedException,
        "SQLite autocommit is implicit with begin/commit/rollback.");
}

void SQLite::begin() {
  std::unique_lock<std::mutex> locker(_mutex);
  SQLiteStatement tmp(*this, _pDB);
  tmp << "BEGIN DEFERRED";
  tmp.execute();
  _inTransaction = true;
}

void SQLite::commit() {
  std::unique_lock<std::mutex> locker(_mutex);
  SQLiteStatement tmp(*this, _pDB);
  tmp << "COMMIT";
  tmp.execute();
  _inTransaction = false;
}

void SQLite::rollback() {
  std::unique_lock<std::mutex> locker(_mutex);
  SQLiteStatement tmp(*this, _pDB);
  tmp << "ROLLBACK";
  tmp.execute();
  _inTransaction = false;
}

void SQLite::setTransactionIsolation(Int level) {
  THROW_IF(level != TRANSACTION_READ_COMMITTED, ArgumentException)
}

}  // namespace sql
}  // namespace gemini