#ifndef GEMINI_SQL_ResultSetImpl_INCLUDE
#define GEMINI_SQL_ResultSetImpl_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class MetaColumn {
 public:
  MetaColumn();
  explicit MetaColumn(Int position, const String& name = "", Types type = Types::UNKNOW,
                      Int length = 0,
                      Int precision = 0, Boolean nullable = false);
  virtual ~MetaColumn();

  const String& name() const { return _name; }

  Int length() const { return _length; }

  Int precision() const { return _precision; }

  Int position() const { return _position; }

  Types type() const { return _type; }

  Boolean isNullable() const { return _nullable; }

 private:
  String _name;
  Int _length;
  Int _precision;
  Int _position;
  Types _type;
  Boolean _nullable;
};

class RowImpl;
class StatementImpl;
class ResultSetImpl {
 public:
  ResultSetImpl();
  virtual ~ResultSetImpl();

  virtual Boolean valid() const = 0;

  virtual std::shared_ptr<RowImpl> createRow() const = 0;
  virtual Boolean next() = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_ResultSetImpl_INCLUDE