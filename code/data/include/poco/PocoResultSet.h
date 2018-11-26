#ifndef GEMINI_SQL_PocoResultSet_INCLUDE
#define GEMINI_SQL_PocoResultSet_INCLUDE
#include "../ResultSetImpl.h"

namespace Poco {
namespace Data {
class RecordSet;
class Statement;
}
}  // namespace Poco

namespace gemini {
namespace sql {

class PocoResultSet : public ResultSetImpl {
 public:
  PocoResultSet(Poco::Data::Statement& stmt);
  ~PocoResultSet();

  virtual Long rowCount() const override;
  virtual Int columnCount() const override;

  virtual String columnName(Int pos) const override;

  virtual std::shared_ptr<RowImpl> createRow() const override;
  virtual Boolean next() override;

 private:
  Poco::Data::RecordSet* _recordSet;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoResultSet_INCLUDE