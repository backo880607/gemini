#ifndef GEMINI_SQL_PocoBinder_INCLUDE
#define GEMINI_SQL_PocoBinder_INCLUDE
#include "../../public/Binder.h"

namespace Poco {
namespace Data {
class Statement;
}
}  // namespace Poco

namespace gemini {
namespace sql {

class PocoBinder : public Binder {
 public:
  PocoBinder(Poco::Data::Statement *stmt);
  ~PocoBinder();

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
  Poco::Data::Statement *_stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoBinder_INCLUDE