#include "../../include/poco/PocoSQLite.h"

#include <Poco/Data/SQLite/Connector.h>

namespace gemini {
namespace sql {

PocoSQLite::PocoSQLite() { Poco::Data::SQLite::Connector::registerConnector(); }

PocoSQLite::~PocoSQLite() {
  Poco::Data::SQLite::Connector::unregisterConnector();
}

String PocoSQLite::connector() const {
  return Poco::Data::SQLite::Connector::KEY;
}

String PocoSQLite::connectionString() const { return getConfig().ip; }

}  // namespace sql
}  // namespace gemini