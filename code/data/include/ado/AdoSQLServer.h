#ifndef GEMINI_SQL_AdoSQLServer_INCLUDE
#define GEMINI_SQL_AdoSQLServer_INCLUDE
#include "Ado.h"

namespace gemini {
namespace sql {

class AdoSQLServer : public Ado {
 public:
  AdoSQLServer();
  ~AdoSQLServer();

 protected:
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoSQLServer_INCLUDE