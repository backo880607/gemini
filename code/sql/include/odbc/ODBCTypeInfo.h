#ifndef GEMINI_SQL_TypeInfo_INCLUDE
#define GEMINI_SQL_TypeInfo_INCLUDE
#include "Error.h"

namespace gemini {
namespace sql {

class ODBCTypeInfo {
  struct Data {
    String typeName;
    SQLSMALLINT dataType;
    SQLINTEGER columnSize;
    String literalPrefix;
    String literalSuffix;
    String createParams;
    SQLSMALLINT nullable;
    SQLSMALLINT caseSensitvie;
    SQLSMALLINT searchable;
    SQLSMALLINT unsignedAttribute;
    SQLSMALLINT fixedPrecScale;
    SQLSMALLINT autoUnique;
    String localTypeName;
    SQLSMALLINT minimumScale;
    SQLSMALLINT maximumScale;
    SQLSMALLINT sqlDataType;
    SQLSMALLINT sqlDatetimeSub;
    SQLINTEGER numPrecRadix;
    SQLSMALLINT intervalPrecision;
  };

 public:
  explicit ODBCTypeInfo(SQLHDBC* pHDBC = nullptr);
  ~ODBCTypeInfo();

  Boolean getColumnSize(SQLSMALLINT type, SQLINTEGER& result);
  Boolean getDecimalDigits(SQLSMALLINT type, SQLSMALLINT& result);

 private:
  void init(SQLHDBC pHDBC);

 private:
  std::map<SQLSMALLINT, Data> _typeInfo;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_TypeInfo_INCLUDE