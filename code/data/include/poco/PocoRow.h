#ifndef GEMINI_SQL_PocoRow_INCLUDE
#define GEMINI_SQL_PocoRow_INCLUDE
#include "../RowImpl.h"

namespace Poco {
namespace Data {
class Row;
class RowIterator;
}  // namespace Data
}  // namespace Poco

namespace gemini {
namespace sql {

class PocoRow : public RowImpl {
 public:
  PocoRow(Poco::Data::Row *row);
  ~PocoRow();

  virtual Boolean isNull(Int col) override;
  virtual Boolean isNull(const String &name) override;

  virtual String getText(Int col) override;
  virtual String getText(const String &name) override;
  virtual Any getValue(Int col) override;
  virtual Any getValue(const String &name) override;

 private:
  Poco::Data::Row* _row;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoRow_INCLUDE