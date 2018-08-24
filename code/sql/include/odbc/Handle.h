#ifndef GEMINI_SQL_Handle_INCLUDED
#define GEMINI_SQL_Handle_INCLUDED
#include "Error.h"

namespace gemini {
namespace sql {

template <typename H, SQLSMALLINT handleType>
class Handle {
 public:
  Handle(SQLHDBC hdbc) : _hdbc(hdbc), _handle(0) {
    THROW_IF(ErrorUtil::isError(SQLAllocHandle(handleType, _hdbc, &_handle)),
             DataBaseException, "Could not allocate handle: ", handleType);
  }

  ~Handle() {
    try {
      SQLFreeHandle(handleType, _handle);
    } catch (...) {
    }
  }

  operator const H&() const { return handle(); }
  const H& handle() const { return _handle; }

 private:
  Handle(const Handle&) {}
  const Handle& operator=(const Handle&) { return *this; }

  SQLHDBC _hdbc;
  H _handle;

  friend class ODBCStatement;
};
typedef Handle<SQLHSTMT, SQL_HANDLE_STMT> StatementHandle;
typedef Handle<SQLHDESC, SQL_HANDLE_DESC> DescriptorHandle;

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_Handle_INCLUDED