#ifndef GEMINI_SQL_ODBCExtractor_INCLUDE
#define GEMINI_SQL_ODBCExtractor_INCLUDE
#include "../Extractor.h"
#include "ODBCTypeInfo.h"

namespace gemini {
namespace sql {

class ODBCExtractor : public Extractor {
 public:
  ODBCExtractor(SQLHSTMT hstmt);
  ~ODBCExtractor();

  virtual Boolean extract(Int pos, Boolean &value) override;
  virtual Boolean extract(Int pos, Char &value) override;
  virtual Boolean extract(Int pos, Short &value) override;
  virtual Boolean extract(Int pos, Int &value) override;
  virtual Boolean extract(Int pos, Long &value) override;
  virtual Boolean extract(Int pos, Float &value) override;
  virtual Boolean extract(Int pos, Double &value) override;
  virtual Boolean extract(Int pos, String &value) override;
  virtual Boolean extract(Int pos, DateTime &value) override;
  virtual Boolean extract(Int pos, Duration &value) override;
  virtual Boolean extract(Int pos, DurationExtend &value) override;

 private:
  template <typename T>
  Boolean extractImpl(Int pos, T &value, SQLSMALLINT cDataType) {
    std::size_t dataSize = sizeof(T);
    SQLLEN len;
    if (ErrorUtil::isError(SQLBindCol(
            _hstmt, (SQLUSMALLINT)pos + 1, ODBCTypeInfo::sqlDataType(cDataType),
            (SQLPOINTER)&value, (SQLINTEGER)dataSize, &len))) {
      THROW(DataBaseException, "SQLBindCol()")
    }
    return true;
  }

 private:
  SQLHSTMT _hstmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ODBCExtractor_INCLUDE