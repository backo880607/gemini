#ifndef GEMINI_SQL_SQLiteBinder_INCLUDE
#define GEMINI_SQL_SQLiteBinder_INCLUDE
#include "../../public/Binder.h"

extern "C" {
typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini {
namespace sql {

class SQLiteBinder : public Binder {
 public:
  SQLiteBinder(sqlite3_stmt *pStmt);
  ~SQLiteBinder();

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
  void checkReturn(Int rc);

 private:
  sqlite3_stmt *_pStmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_SQLiteBinder_INCLUDE