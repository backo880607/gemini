#ifndef GEMINI_SQL_AdoResultSet_INCLUDE
#define GEMINI_SQL_AdoResultSet_INCLUDE
#include "../ResultSetImpl.h"
#include "AdoCommon.h"

namespace gemini {
namespace sql {

class AdoResultSet : public ResultSetImpl {
 public:
  AdoResultSet(ADODB::_RecordsetPtr recordSet);
  ~AdoResultSet();

  virtual Long rowCount() const override;
  virtual Int columnCount() const override;

  virtual String columnName(Int pos) const override;


  virtual std::shared_ptr<RowImpl> createRow() const override;
  virtual Boolean next() override;

 private:
  ADODB::_RecordsetPtr _recordSet;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoResultSet_INCLUDE