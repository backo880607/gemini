#ifndef GEMINI_SQL_PocoSQLServer_INCLUDE
#define GEMINI_SQL_PocoSQLServer_INCLUDE
#include "PocoConnection.h"

namespace gemini {
namespace sql {

class PocoSQLServer : public PocoConnection {
 public:
  PocoSQLServer();
  ~PocoSQLServer();

 protected:
  virtual String connector() const override;
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoSQLServer_INCLUDE