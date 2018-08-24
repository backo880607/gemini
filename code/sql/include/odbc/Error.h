#ifndef GEMINI_SQL_Error_INCLUDE
#define GEMINI_SQL_Error_INCLUDE
#include "../../public/SQLException.h"
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <Windows.h>
#endif
#include <sqlext.h>

namespace gemini {
namespace sql {

template <typename H, SQLSMALLINT handleType>
class Error {
  static const unsigned int SQL_STATE_SIZE = SQL_SQLSTATE_SIZE + 1;
  static const unsigned int SQL_MESSAGE_LENGTH = SQL_MAX_MESSAGE_LENGTH + 1;
  static const unsigned int SQL_NAME_LENGTH = 128;
  static const String DATA_TRUNCATED;

  struct ErrorFields {
    SQLCHAR sqlState[SQL_STATE_SIZE];
    SQLCHAR message[SQL_MESSAGE_LENGTH];
    SQLINTEGER nativeError;
  };

 public:
  explicit Error(const H& handle) : _handle(handle) {
    std::memset(_connectionName, 0, sizeof(_connectionName));
    std::memset(_serverName, 0, sizeof(_serverName));
    diagnostics();
  }

  ~Error() {}

  Int count() const { return (Int)_fields.size(); }

  String connectionName() const { return String((Char*)_connectionName); }

  String serverName() const { return String((Char*)_serverName); }

  const Error& diagnostics() {
    ErrorFields df;
    SQLSMALLINT count = 1;
    SQLSMALLINT messageLength = 0;
    static const String none = "None";
    static const String na = "Not applicable";

    reset();

    while (!isError(SQLGetDiagRec(handleType, _handle, count, df.sqlState,
                                  &df.nativeError, df.message,
                                  SQL_MESSAGE_LENGTH, &messageLength))) {
      if (1 == count) {
        // success of the following two calls is optional
        // (they fail if connection has not been established yet
        //  or return empty string if not applicable for the context)
        if (isError(SQLGetDiagField(handleType, _handle, count,
                                    SQL_DIAG_CONNECTION_NAME, _connectionName,
                                    sizeof(_connectionName), &messageLength))) {
          std::size_t len = sizeof(_connectionName) > none.length()
                                ? none.length()
                                : sizeof(_connectionName) - 1;
          std::memcpy(_connectionName, none.c_str(), len);
        } else if (0 == _connectionName[0]) {
          std::size_t len = sizeof(_connectionName) > na.length()
                                ? na.length()
                                : sizeof(_connectionName) - 1;
          std::memcpy(_connectionName, na.c_str(), len);
        }

        if (isError(SQLGetDiagField(handleType, _handle, count,
                                    SQL_DIAG_SERVER_NAME, _serverName,
                                    sizeof(_serverName), &messageLength))) {
          std::size_t len = sizeof(_serverName) > none.length()
                                ? none.length()
                                : sizeof(_serverName) - 1;
          std::memcpy(_serverName, none.c_str(), len);
        } else if (0 == _serverName[0]) {
          std::size_t len = sizeof(_serverName) > na.length()
                                ? na.length()
                                : sizeof(_serverName) - 1;
          std::memcpy(_serverName, na.c_str(), len);
        }
      }

      _fields.push_back(df);

      std::memset(df.sqlState, 0, SQL_STATE_SIZE);
      std::memset(df.message, 0, SQL_MESSAGE_LENGTH);
      df.nativeError = 0;

      ++count;
    }

    return *this;
  }

  String toString(Int index) const {
    if ((index < 0) || (index > (count() - 1))) return "";

    return StringUtil::SPrintf(
        "===========================\n"
        "ODBC Diagnostic record #%d:\n"
        "===========================\n"
        "SQLSTATE = %s\nNative Error Code = %ld\n%s\n\n",
        index + 1, (const Char*)(_fields[index].sqlState),
        _fields[index].nativeError, (const Char*)(_fields[index].message));
  }

  String toString() const {
    String str = StringUtil::SPrintf("Connection:%s\nServer:%s\n",
                                     connectionName(), serverName());

    for (Int i = 0; i < count(); ++i) {
      str.append(toString(i));
    }
    return str;
  }

  void reset() { _fields.clear(); }

  Boolean isError(SQLRETURN rc) { return (0 != (rc & (~1))); }

 private:
  const H& _handle;
  SQLCHAR _connectionName[SQL_NAME_LENGTH];
  SQLCHAR _serverName[SQL_NAME_LENGTH];
  std::vector<ErrorFields> _fields;
};
typedef Error<SQLHENV, SQL_HANDLE_ENV> EnvironmentError;
typedef Error<SQLHDBC, SQL_HANDLE_DBC> ConnectionError;
typedef Error<SQLHSTMT, SQL_HANDLE_STMT> StatementError;
typedef Error<SQLHSTMT, SQL_HANDLE_DESC> DescriptorError;

class ErrorUtil {
 public:
  static Boolean isError(SQLRETURN rc);
  static void checkError(SQLHDBC hdbc, SQLRETURN rc);
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_Error_INCLUDE