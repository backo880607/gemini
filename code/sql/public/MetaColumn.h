#ifndef GEMINI_SQL_MetaColumn_INCLUDE
#define GEMINI_SQL_MetaColumn_INCLUDE
#include "SQLExport.h"

namespace gemini {
namespace sql {

class MetaColumn {
 public:
  MetaColumn() {}
  ~MetaColumn() {}

  Boolean nullable() const { return _nullable; }
  void setNullable(Boolean nullable) { _nullable = nullable; }

  const String& name() const { return _name; }
  void setName(const String& name) { _name = name; }

  Int length() const { return _length; }
  void setLength(Int length) { _length = length; }

  Int precision() const { return _precision; }
  void setPrecision(Int precision) { _precision = precision; }

  Int position() const { return _position; }
  void setPosition(Int position) { _position = position; }

  Types type() const { return _type; }
  void setType(Types type) { _type = type; }

 private:
  Boolean _nullable;
  String _name;
  Int _length;
  Int _precision;
  Int _position;
  Types _type;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_MetaColumn_INCLUDE