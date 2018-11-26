#ifndef GEMINI_SQL_AdoOracle_INCLUDE
#define GEMINI_SQL_AdoOracle_INCLUDE
#include "Ado.h"

namespace gemini {
namespace sql {

class AdoOracle : public Ado {
 public:
  AdoOracle();
  ~AdoOracle();

protected:
  virtual String connectionString() const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoOracle_INCLUDE