#ifndef GEMINI_SQL_Binder_INCLUDE
#define GEMINI_SQL_Binder_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class GEMINI_SQL_API Binder {
 public:
  /// Binding direction for a parameter.
  enum class Direction { PD_IN, PD_OUT, PD_IN_OUT };

  Binder();
  virtual ~Binder();

  virtual void bind(Int pos, const Boolean &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Char &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Short &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Int &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Long &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Float &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Double &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const String &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const DateTime &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const Duration &val,
                    Direction dir = Direction::PD_IN) = 0;

  virtual void bind(Int pos, const DurationExtend &val,
                    Direction dir = Direction::PD_IN) = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Binder_INCLUDE
