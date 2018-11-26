#ifndef GEMINI_SQL_PocoMySQL_INCLUDE
#define GEMINI_SQL_PocoMySQL_INCLUDE
#include "PocoConnection.h"

namespace gemini {
namespace sql {

class PocoMySQL : public PocoConnection {
 public:
  PocoMySQL();
  ~PocoMySQL();

 protected:
  virtual String connector() const override;
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoMySQL_INCLUDE