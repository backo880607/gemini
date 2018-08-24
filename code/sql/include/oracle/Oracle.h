#ifndef GEMINI_SQL_Oracle_INCLUDE
#define GEMINI_SQL_Oracle_INCLUDE
#include "../odbc/ODBC.h"

namespace gemini {
namespace sql {

class Oracle : public ODBC {
 public:
  Oracle();
  ~Oracle();

 protected:
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_Oracle_INCLUDE