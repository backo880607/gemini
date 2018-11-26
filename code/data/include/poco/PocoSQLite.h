#ifndef GEMINI_SQL_PocoSQLite_INCLUDE
#define GEMINI_SQL_PocoSQLite_INCLUDE
#include "PocoConnection.h"

namespace gemini {
namespace sql {

class PocoSQLite : public PocoConnection {
 public:
  PocoSQLite();
  ~PocoSQLite();

 protected:
  virtual String connector() const override;
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoSQLite_INCLUDE