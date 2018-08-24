#ifndef GEMINI_SQL_SQLServer_INCLUDE
#define GEMINI_SQL_SQLServer_INCLUDE
#include "../odbc/ODBC.h"

namespace gemini {
namespace sql {

class SQLServer : public ODBC {
 public:
  SQLServer();
  ~SQLServer();

  virtual std::shared_ptr<StatementImpl> createStatement() override;

 protected:
  virtual String connectionString() const override;
};

class Access : public SQLServer {
 public:
  Access();
  ~Access();
};

class SQLExcel : public SQLServer {
 public:
  SQLExcel();
  ~SQLExcel();
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLServer_INCLUDE