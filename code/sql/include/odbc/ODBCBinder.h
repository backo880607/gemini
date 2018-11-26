#ifndef GEMINI_SQL_ODBCBinder_INCLUDE
#define GEMINI_SQL_ODBCBinder_INCLUDE
#include "../Binder.h"
#include "ODBCTypeInfo.h"

namespace gemini {
namespace sql {

class MetaColumn;
class ODBCBinder : public Binder {
 public:
  ODBCBinder(SQLHSTMT hstmt, ODBCTypeInfo *typeInfo);
  ~ODBCBinder();

  std::shared_ptr<MetaColumn> metaColumn(Int pos);

  virtual void bind(Int pos, const Boolean &val, Direction dir) override;
  virtual void bind(Int pos, const Char &val, Direction dir) override;
  virtual void bind(Int pos, const Short &val, Direction dir) override;
  virtual void bind(Int pos, const Int &val, Direction dir) override;
  virtual void bind(Int pos, const Long &val, Direction dir) override;
  virtual void bind(Int pos, const Float &val, Direction dir) override;
  virtual void bind(Int pos, const Double &val, Direction dir) override;
  virtual void bind(Int pos, const String &val, Direction dir) override;
  virtual void bind(Int pos, const DateTime &val, Direction dir) override;
  virtual void bind(Int pos, const Duration &val, Direction dir) override;
  virtual void bind(Int pos, const DurationExtend &val, Direction dir) override;

 private:
  SQLSMALLINT toODBCDirection(Direction dir) const;
  void getColumnOrParameterSize(std::size_t pos, SQLINTEGER &size);
  void getColSizeAndPrecision(Int pos, SQLSMALLINT cDataType,
                              SQLINTEGER &colSize, SQLSMALLINT &decDigits);

  template <typename T>
  void bindImpl(Int pos, T &val, SQLSMALLINT cDataType, Direction dir) {
    SQLINTEGER colSize = 0;
    SQLSMALLINT decDigits = 0;
    getColSizeAndPrecision(pos, cDataType, colSize, decDigits);

    if (ErrorUtil::isError(SQLBindParameter(
            _hstmt, (SQLUSMALLINT)pos + 1, toODBCDirection(dir), cDataType,
            ODBCTypeInfo::sqlDataType(cDataType), colSize, decDigits,
            (SQLPOINTER)&val, 0, 0))) {
      THROW(DataBaseException, "SQLBindParameter(std::string)")
    }
  }

 private:
  SQLHSTMT _hstmt;
  ODBCTypeInfo *_typeInfo;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ODBCBinder_INCLUDE