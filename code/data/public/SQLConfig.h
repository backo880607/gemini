#ifndef GEMINI_SQL_SQLConfig_INCLUDE
#define GEMINI_SQL_SQLConfig_INCLUDE
#include "SQLException.h"

namespace gemini {
namespace sql {

struct SQLConfig {
  Boolean autoCreate;
  String ip;
  Int port;
  String username;
  String password;
  String database;
  String scheme;
  Int connectionTimeout;
  Int readTimeout;
  Int writeTimeout;
  Int maxTotal;  ///< 最大连接数
};

enum class SQL_TYPE {
  SQLite,
  MySQL,
  Oracle,
  SQLServer,
  Access,
  Excel,
};

static const Int TRANSACTION_READ_UNCOMMITTED = 0x00000001L;
static const Int TRANSACTION_READ_COMMITTED = 0x00000002L;
static const Int TRANSACTION_REPEATABLE_READ = 0x00000004L;
static const Int TRANSACTION_SERIALIZABLE = 0x00000008L;

class Driver;
}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_SQLConfig_INCLUDE