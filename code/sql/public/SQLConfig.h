#ifndef GEMINI_SQL_SQLConfig_INCLUDE
#define GEMINI_SQL_SQLConfig_INCLUDE
#include "SQLExport.h"

namespace gemini
{
namespace sql
{

struct SQLConfig
{
	String ip;
	UInt port;
	String user;
	String password;
	String database;
	String Schema;
	UInt connectionTimeout;
	UInt readTimeout;
	UInt writeTimeout;
};

enum class SQL_TYPE
{
	SQLite,
	MySQL,
	Oracle,
	SQLServer,
	Access,
	Excel,
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_SQLConfig_INCLUDE