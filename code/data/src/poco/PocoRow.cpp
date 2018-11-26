#include <Poco/Data/Row.h>
#include <Poco/Data/RowIterator.h>
#include "../../include/poco/PocoRow.h"

namespace gemini {
namespace sql {

PocoRow::PocoRow(Poco::Data::Row *row) : _row(row) {}

PocoRow::~PocoRow() {}

Boolean PocoRow::isNull(Int col) { return false; }

Boolean PocoRow::isNull(const String &name) { return false; }

String PocoRow::getText(Int col) { return _row->get(col).toString(); }

String PocoRow::getText(const String &name) { return (*_row)[name].toString(); }

Any PocoRow::getValue(Int col) { return nullptr; }

Any PocoRow::getValue(const String &name) { return nullptr; }

}  // namespace sql
}  // namespace gemini