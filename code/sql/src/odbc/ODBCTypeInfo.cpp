#include "../../include/odbc/ODBCTypeInfo.h"

namespace gemini {
namespace sql {

ODBCTypeInfo::ODBCTypeInfo(SQLHDBC* pHDBC) {
  if (pHDBC != nullptr) init(*pHDBC);
}

ODBCTypeInfo::~ODBCTypeInfo() {}

void ODBCTypeInfo::init(SQLHDBC pHDBC) {
  if (_typeInfo.empty() && pHDBC != nullptr) {
    SQLRETURN rc;
    SQLHSTMT hstmt = SQL_NULL_HSTMT;
    rc = SQLAllocHandle(SQL_HANDLE_STMT, pHDBC, &hstmt);
    //if (!SQL_SUCCEEDED(rc)) throw StatementException(hstmt, "SQLGetData()");

    rc = SQLGetTypeInfo(hstmt, SQL_ALL_TYPES);
    const static Int stringSize = 512;
    if (SQL_SUCCEEDED(rc)) {
      while (SQLFetch(hstmt) != SQL_NO_DATA_FOUND) {
        char typeName[stringSize] = {0};
        char literalPrefix[stringSize] = {0};
        char literalSuffix[stringSize] = {0};
        char createParams[stringSize] = {0};
        char localTypeName[stringSize] = {0};

        Data data;
        SQLLEN ind = 0;
        rc = SQLGetData(hstmt, 1, SQL_C_CHAR, typeName, sizeof(typeName), &ind);
        data.typeName = typeName;
        rc = SQLGetData(hstmt, 2, SQL_C_SSHORT, &data.dataType,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 3, SQL_C_SLONG, &data.columnSize,
                        sizeof(SQLINTEGER), &ind);
        rc = SQLGetData(hstmt, 4, SQL_C_CHAR, literalPrefix,
                        sizeof(literalPrefix), &ind);
        data.literalPrefix = literalPrefix;
        rc = SQLGetData(hstmt, 5, SQL_C_CHAR, literalSuffix,
                        sizeof(literalSuffix), &ind);
        data.literalSuffix = literalSuffix;
        rc = SQLGetData(hstmt, 6, SQL_C_CHAR, createParams,
                        sizeof(createParams), &ind);
        data.createParams = createParams;
        rc = SQLGetData(hstmt, 7, SQL_C_SSHORT, &data.nullable,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 8, SQL_C_SSHORT, &data.caseSensitvie,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 9, SQL_C_SSHORT, &data.searchable,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 10, SQL_C_SSHORT, &data.unsignedAttribute,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 11, SQL_C_SSHORT, &data.fixedPrecScale,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 12, SQL_C_SSHORT, &data.autoUnique,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 13, SQL_C_CHAR, localTypeName,
                        sizeof(localTypeName), &ind);
        data.localTypeName = localTypeName;
        rc = SQLGetData(hstmt, 14, SQL_C_SSHORT, &data.minimumScale,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 15, SQL_C_SSHORT, &data.maximumScale,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 16, SQL_C_SSHORT, &data.sqlDataType,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 17, SQL_C_SSHORT, &data.sqlDatetimeSub,
                        sizeof(SQLSMALLINT), &ind);
        rc = SQLGetData(hstmt, 18, SQL_C_SLONG, &data.numPrecRadix,
                        sizeof(SQLINTEGER), &ind);
        rc = SQLGetData(hstmt, 19, SQL_C_SSHORT, &data.intervalPrecision,
                        sizeof(SQLSMALLINT), &ind);

        _typeInfo.insert(std::make_pair(data.dataType, data));
      }
    }
  }
}

Boolean ODBCTypeInfo::getColumnSize(SQLSMALLINT type, SQLINTEGER& result) {
  std::map<SQLSMALLINT, Data>::iterator iter = _typeInfo.find(type);
  if (iter == _typeInfo.end()) {
    return false;
  }

  result = iter->second.columnSize;
  return true;
}

Boolean ODBCTypeInfo::getDecimalDigits(SQLSMALLINT type, SQLSMALLINT& result) {
  std::map<SQLSMALLINT, Data>::iterator iter = _typeInfo.find(type);
  if (iter == _typeInfo.end()) {
    return false;
  }

  result = iter->second.minimumScale;
  return true;
}

}  // namespace sql
}  // namespace gemini