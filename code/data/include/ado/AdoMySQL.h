#ifndef GEMINI_SQL_AdoMySQL_INCLUDE
#define GEMINI_SQL_AdoMySQL_INCLUDE
#include "Ado.h"

namespace gemini {
namespace sql {

class AdoMySQL : public Ado {
 public:
  AdoMySQL();
  ~AdoMySQL();

 protected:
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoMySQL_INCLUDE