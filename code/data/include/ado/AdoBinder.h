#ifndef GEMINI_SQL_AdoBinder_INCLUDE
#define GEMINI_SQL_AdoBinder_INCLUDE
#include "../../public/Binder.h"
#include "AdoCommon.h"

namespace gemini {
namespace sql {

class AdoBinder : public Binder {
 public:
  AdoBinder(ADODB::_CommandPtr stmt);
  ~AdoBinder();

  virtual void bind(Boolean &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Char &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Short &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Int &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Long &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Float &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Double &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(String &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(DateTime &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(Duration &value, Direction dir = Direction::PD_IN) override;
  virtual void bind(DurationExtend &value,
                    Direction dir = Direction::PD_IN) override;

 private:
  ADODB::ParameterDirectionEnum direction(Direction dir);

 private:
  ADODB::_CommandPtr _stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoBinder_INCLUDE