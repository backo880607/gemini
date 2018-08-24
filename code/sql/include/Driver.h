#ifndef GEMINI_SQL_Driver_INCLUDE
#define GEMINI_SQL_Driver_INCLUDE
#include "../public/Connection.h"

namespace gemini {
namespace sql {

class Driver {
 public:
  Driver();
  virtual ~Driver();

  virtual Connection getConn();

  SQL_TYPE getType() { return _type; }
  void setType(SQL_TYPE type) { _type = type; }
  void setType(const String& type);

  SQLConfig& getConfig() { return _config; }

 protected:
  std::vector<Connection>& getConnections() { return _conns; }

 private:
  SQL_TYPE _type;
  SQLConfig _config;
  std::vector<Connection> _conns;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Driver_INCLUDE