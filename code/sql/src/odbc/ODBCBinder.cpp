#include "../../include/odbc/ODBCBinder.h"
#include "../../public/MetaColumn.h"

namespace gemini {
namespace sql {

ODBCBinder::ODBCBinder(SQLHSTMT hstmt, ODBCTypeInfo* typeInfo)
    : _hstmt(hstmt), _typeInfo(typeInfo) {}

ODBCBinder::~ODBCBinder() {}

std::shared_ptr<MetaColumn> ODBCBinder::metaColumn(Int pos) {
  SQLSMALLINT nullable;
  SQLSMALLINT dataType;
  SQLULEN columnSize;
  SQLSMALLINT decDigits;
  static const Int NAME_BUFFER_LENGTH = 2048;
  SQLCHAR name[NAME_BUFFER_LENGTH];
  SQLSMALLINT nameBufferLength;
  SQLULEN size;
  if (ErrorUtil::isError(SQLDescribeCol(
          _hstmt, (SQLUSMALLINT)pos + 1, name, NAME_BUFFER_LENGTH,
          &nameBufferLength, &dataType, &columnSize, &decDigits, &nullable))) {
    return nullptr;
  }

  std::shared_ptr<MetaColumn> meta(new MetaColumn());
  meta->setName((Char*)name);
  meta->setLength(columnSize);
  meta->setPrecision(decDigits);
  meta->setNullable(SQL_NULLABLE == nullable);
  switch (dataType) {
    case SQL_BIT:
      meta->setType(Types::BOOLEAN);
      break;
    case SQL_TINYINT:
      meta->setType(Types::CHAR);
      break;
    case SQL_SMALLINT:
      meta->setType(Types::SHORT);
      break;
    case SQL_INTEGER:
      meta->setType(Types::INT);
      break;
    case SQL_BIGINT:
      meta->setType(Types::LONG);
      break;
    case SQL_REAL:
      meta->setType(Types::FLOAT);
      break;
    case SQL_DOUBLE:
      meta->setType(Types::DOUBLE);
      break;
      THROW(NotSupportedException, "invalid data type: ", dataType);
  }
  return meta;
}

void ODBCBinder::bind(Int pos, const Boolean& val, Direction dir) {
  bindImpl(pos, val, SQL_C_BIT, dir);
}

void ODBCBinder::bind(Int pos, const Char& val, Direction dir) {
  bindImpl(pos, val, SQL_C_TINYINT, dir);
}

void ODBCBinder::bind(Int pos, const Short& val, Direction dir) {
  bindImpl(pos, val, SQL_C_SHORT, dir);
}

void ODBCBinder::bind(Int pos, const Int& val, Direction dir) {
  bindImpl(pos, val, SQL_C_LONG, dir);
}

void ODBCBinder::bind(Int pos, const Long& val, Direction dir) {
  bindImpl(pos, val, SQL_C_SBIGINT, dir);
}

void ODBCBinder::bind(Int pos, const Float& val, Direction dir) {
  bindImpl(pos, val, SQL_C_FLOAT, dir);
}

void ODBCBinder::bind(Int pos, const Double& val, Direction dir) {
  bindImpl(pos, val, SQL_C_DOUBLE, dir);
}

void ODBCBinder::bind(Int pos, const String& val, Direction dir) {
  SQLPOINTER pVal = 0;
  SQLINTEGER size = (SQLINTEGER)val.size();

  if (dir == Direction::PD_IN_OUT || dir == Direction::PD_OUT) {
    getColumnOrParameterSize(pos, size);
    Char* pChar = (Char*)std::calloc(size, sizeof(Char));
    pVal = (SQLPOINTER)pChar;
  } else if (dir == Direction::PD_IN) {
    pVal = (SQLPOINTER)val.c_str();
  } else
    THROW(DataBaseException, "Parameter must be [in] OR [out] bound.");

  SQLLEN lenIn;
  SQLINTEGER colSize = 0;
  SQLSMALLINT decDigits = 0;
  getColSizeAndPrecision(pos, SQL_C_CHAR, colSize, decDigits);
  if (ErrorUtil::isError(SQLBindParameter(_hstmt, (SQLUSMALLINT)pos + 1,
                                          toODBCDirection(dir), SQL_C_CHAR,
                                          SQL_LONGVARCHAR, (SQLUINTEGER)colSize,
                                          0, pVal, (SQLINTEGER)size, &lenIn))) {
    THROW(DataBaseException, "SQLBindParameter(std::string)")
  }
}

void ODBCBinder::bind(Int pos, const DateTime& val, Direction dir) {}

void ODBCBinder::bind(Int pos, const Duration& val, Direction dir) {}

void ODBCBinder::bind(Int pos, const DurationExtend& val, Direction dir) {}

SQLSMALLINT ODBCBinder::toODBCDirection(Direction dir) const {
  switch (dir) {
    case Direction::PD_IN_OUT:
      return SQL_PARAM_INPUT_OUTPUT;
    case Direction::PD_IN:
      return SQL_PARAM_INPUT;
    case Direction::PD_OUT:
      return SQL_PARAM_OUTPUT;
  }
  THROW(NotSupportedException, "Binder not bound (must be [in] OR [out]).")
}

void ODBCBinder::getColumnOrParameterSize(std::size_t pos, SQLINTEGER& size) {
  std::shared_ptr<MetaColumn> meta = metaColumn(pos);
  Int colSize = meta->length();


  SQLSMALLINT dataType;
  SQLULEN columnSize;
  SQLSMALLINT decimalDigits;
  SQLSMALLINT isNullable;
  if (ErrorUtil::isError(SQLDescribeParam(_hstmt, (SQLUSMALLINT)pos + 1,
                                        &dataType, &columnSize,
                                        &decimalDigits, &isNullable))) {
    THROW(DataBaseException, "SQLBindParameter(std::string)")
  }

  Int paramSize = columnSize;
  if (colSize > 0 && paramSize > 0)
    size = colSize < paramSize ? static_cast<SQLINTEGER>(colSize)
                               : static_cast<SQLINTEGER>(paramSize);
  else if (colSize > 0)
    size = static_cast<SQLINTEGER>(colSize);
  else if (paramSize > 0)
    size = static_cast<SQLINTEGER>(paramSize);

  //if (size > _maxFieldSize) size = static_cast<SQLINTEGER>(_maxFieldSize);
}

void ODBCBinder::getColSizeAndPrecision(Int pos, SQLSMALLINT cDataType,
                                        SQLINTEGER& colSize,
                                        SQLSMALLINT& decDigits) {
  if (_typeInfo != nullptr) {
    if (_typeInfo->getColumnSize(cDataType, colSize) &&
        _typeInfo->getDecimalDigits(cDataType, decDigits)) {
      return;
    }
  }

  SQLSMALLINT dataType;
  SQLSMALLINT isNullable;
  SQLULEN columnSize;
  if (!ErrorUtil::isError(SQLDescribeParam(_hstmt, (SQLUSMALLINT)pos + 1,
                                           &dataType, &columnSize, &decDigits,
                                           &isNullable))) {
    colSize = columnSize;
    return;
  }

  static const int NAME_BUFFER_LENGTH = 2048;
  SQLCHAR name[NAME_BUFFER_LENGTH];
  SQLSMALLINT nameBufferLength;
  if (!ErrorUtil::isError(SQLDescribeCol(_hstmt, (SQLUSMALLINT)pos + 1, name,
                                         NAME_BUFFER_LENGTH, &nameBufferLength,
                                         &dataType, &columnSize, &decDigits,
                                         &isNullable))) {
    colSize = columnSize;
    return;
  }

  colSize = 0;
  decDigits = 0;
}

}  // namespace sql
}  // namespace gemini