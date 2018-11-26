#include "../../include/sqlite/SQLiteBinder.h"
#include "sqlite3.h"

namespace gemini {
namespace sql {

SQLiteBinder::SQLiteBinder(sqlite3_stmt *pStmt) : _pStmt(pStmt) {}

SQLiteBinder::~SQLiteBinder() {}

void SQLiteBinder::bind(Boolean &value,
                        Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Char &value, Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Short &value, Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Int &value, Direction dir /* = Direction::PD_IN */) {
  checkReturn(sqlite3_bind_int(_pStmt, 0, value));
}

void SQLiteBinder::bind(Long &value, Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Float &value, Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Double &value, Direction dir /* = Direction::PD_IN */) {
}

void SQLiteBinder::bind(String &value, Direction dir /* = Direction::PD_IN */) {
}

void SQLiteBinder::bind(DateTime &value,
                        Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(Duration &value,
                        Direction dir /* = Direction::PD_IN */) {}

void SQLiteBinder::bind(DurationExtend &value,
                        Direction /* = Direction::PD_IN */) {}

void SQLiteBinder::checkReturn(Int rc) {}

}  // namespace sql
}  // namespace gemini