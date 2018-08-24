#ifndef GEMINI_SQL_MySQL_INCLUDE
#define GEMINI_SQL_MySQL_INCLUDE
#include "../ConnectionImpl.h"

namespace gemini {
namespace sql {

class MySQL : public ConnectionImpl {
 public:
  virtual Boolean open() override;

  virtual void close() override;

 private:
  MYSQL *_impl;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_MySQL_INCLUDE