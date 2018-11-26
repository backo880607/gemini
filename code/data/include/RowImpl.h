#ifndef GEMINI_SQL_RowImpl_INCLUDE
#define GEMINI_SQL_RowImpl_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class RowImpl {
 public:
  RowImpl();
  virtual ~RowImpl();

  virtual Boolean isNull(Int col) = 0;
  virtual Boolean isNull(const String &name) = 0;

  virtual String getText(Int col) = 0;
  virtual String getText(const String &name) = 0;
  virtual Any getValue(Int col) = 0;
  virtual Any getValue(const String &name) = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_RowImpl_INCLUDE