#ifndef GEMINI_SQL_AdoRow_INCLUDE
#define GEMINI_SQL_AdoRow_INCLUDE
#include "../RowImpl.h"
#include "AdoCommon.h"

namespace gemini {
namespace sql {

class AdoRow : public RowImpl {
 public:
  AdoRow(ADODB::FieldsPtr fields);
  ~AdoRow();

  virtual Boolean isNull(Int col) override;
  virtual Boolean isNull(const String &name) override;

  virtual String getText(Int col) override;
  virtual String getText(const String &name) override;
  virtual Any getValue(Int col) override;
  virtual Any getValue(const String &name) override;

 private:
  Any convertImpl(_variant_t &val);

 private:
  ADODB::FieldsPtr _fields;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoRow_INCLUDE