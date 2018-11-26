#ifndef GEMINI_SQL_Binder_INCLUDE
#define GEMINI_SQL_Binder_INCLUDE
#include "SQLExport.h"

namespace gemini {
namespace sql {

class StatementImpl;
class GEMINI_SQL_API Binder {
 public:
  /// Binding direction for a parameter.
  enum class Direction { PD_IN, PD_OUT, PD_IN_OUT };

  Binder();
  virtual ~Binder();

  virtual void bind(Boolean &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Char &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Short &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Int &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Long &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Float &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Double &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(String &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(DateTime &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(Duration &value, Direction dir = Direction::PD_IN) = 0;
  virtual void bind(DurationExtend &value,
                    Direction dir = Direction::PD_IN) = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Binder_INCLUDE
