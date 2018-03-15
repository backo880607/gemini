#pragma once
#include "DataExport.h"

namespace gemini {
namespace data {

struct SQLConfig {
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

enum class SQL_TYPE {
	SQLite,
	MySQL,
	Oracle,
	SQLServer,
	Access,
	Excel,
};

}
}