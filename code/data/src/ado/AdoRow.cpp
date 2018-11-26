#include "../../include/ado/AdoRow.h"
#include "../../public/SQLException.h"

namespace gemini {
namespace sql {

AdoRow::AdoRow(ADODB::FieldsPtr fields) : _fields(fields) {}

AdoRow::~AdoRow() {}

Boolean AdoRow::isNull(Int col) { return false; }

Boolean AdoRow::isNull(const String &name) { return false; }

String AdoRow::getText(Int col) {
  try {
    return convertImpl(_fields->GetItem((long)col)->GetValue()).toString();
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

String AdoRow::getText(const String &name) {
  try {
    return convertImpl(_fields->GetItem(name.c_str())->GetValue()).toString();
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

Any AdoRow::getValue(Int col) {
  try {
    return convertImpl(_fields->GetItem((long)col)->GetValue());
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

Any AdoRow::getValue(const String &name) {
  try {
    return convertImpl(_fields->GetItem(name.c_str())->GetValue());
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

Any AdoRow::convertImpl(_variant_t &val) { return nullptr; }

}  // namespace sql
}  // namespace gemini