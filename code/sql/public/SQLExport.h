#ifndef GEMINI_SQL_SQLExport_INCLUDE
#define GEMINI_SQL_SQLExport_INCLUDE
#include "Core.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_SQL_EXPORTS
#define GEMINI_SQL_API __declspec(dllexport)
#else
#define GEMINI_SQL_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_SQL_API

#endif

namespace gemini {
class Class;
namespace sql {
enum class Types {
  UNKNOW,
  BOOLEAN,
  SHORT,
  INT,
  LONG,
  FLOAT,
  DOUBLE,
  NUMERIC,
  DECIMAL,
  CHAR,
  VARCHAR,
  LONGVARCHAR,
  DATE,
  TIMESTAMP,
  BINARY,
  VARBINARY,
  LONGVARBINARY,
  BLOB,
  CLOB
};
}
}  // namespace gemini

struct GEMINI_SQL_API __register_sql_table_config__ {
  __register_sql_table_config__(const gemini::Class& cls, const char* tblName);
};
struct GEMINI_SQL_API __register_sql_column_config__ {
  __register_sql_column_config__(const gemini::Class& cls, int sign,
                                 gemini::sql::Types columnType);
};
struct GEMINI_SQL_API __register_sql_column_disable__ {
  __register_sql_column_disable__(const gemini::Class& cls, int sign);
};

#define SQL_TABLE_CONFIG(TABLE_NAME)                                           \
  \
private:                                                                       \
  class __sql_table_config {                                                   \
   public:                                                                     \
    __sql_table_config() {                                                     \
      static __register_sql_table_config__ reg(getClassStatic(), #TABLE_NAME); \
    }                                                                          \
    ~__sql_table_config() {}                                                   \
  } _sql##TABLE_NAME;

#define SQL_COLUMN_CONFIG(FIELD_NAME, COLUMN_TYPE)                \
  \
private:                                                          \
  class __sql_column_##FIELD_NAME {                               \
   public:                                                        \
    __sql_column_##FIELD_NAME() {                                 \
      static __register_sql_column_config__ reg(                  \
          getClassStatic(), _##FIELD_NAME::index(), COLUMN_TYPE); \
    }                                                             \
    ~__sql_column_##FIELD_NAME() {}                               \
  } _sql##FIELD_NAME;

#define SQL_COLUMN_DISABLE(FIELD_NAME)                                    \
  \
private:                                                                  \
  class __sql_column_##FIELD_NAME {                                       \
   public:                                                                \
    __sql_column_##FIELD_NAME() {                                         \
      static __register_sql_column_disable__ reg(getClassStatic(),        \
                                                 _##FIELD_NAME::index()); \
    }                                                                     \
    ~__sql_column_##FIELD_NAME() {}                                       \
  } _sql##FIELD_NAME;

#endif  // GEMINI_SQL_SQLExport_INCLUDE