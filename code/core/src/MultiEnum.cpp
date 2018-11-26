#include "MultiEnum.h"
#include "message/Exception.h"

namespace gemini {

MultiEnum::MultiEnum(Short value) : _value((Short)pow(2, value - 1)) {}
MultiEnum::MultiEnum() : _value(0) {}

Boolean MultiEnum::contains(Short value) {
  return (_value | (Short)pow(2, value - 1)) > 0;
}

Boolean MultiEnum::contains(const MultiEnum& rhs) {
  return (_value | rhs._value) == rhs._value;
}

void MultiEnum::operator+=(Short rhs) {
  _value = _value | (Short)pow(2, rhs - 1);
}

void MultiEnum::operator+=(const MultiEnum& rhs) {
  _value = _value | rhs._value;
}

void MultiEnum::operator-=(Short rhs) {
  _value = _value & ~(Short)(pow(2, rhs - 1));
}

void MultiEnum::operator-=(const MultiEnum& rhs) {
  _value = _value & ~rhs._value;
}

Boolean MultiEnum::operator==(const MultiEnum& rhs) {
  return _value == rhs._value;
}

void MultiEnum::operator+=(const Any& rhs) {
  if (rhs.getClass().isEnum()) {
  } else if (rhs.getClass().isMultiEnum()) {
  }

  THROW(OperandException);
}

void MultiEnum::operator-=(const Any& rhs) { THROW(OperandException); }

Boolean MultiEnum::operator==(const Any& rhs) const { THROW(OperandException); }

String MultiEnum::toString() const { return ""; }

Short MultiEnum::add(const Any& rhs) const { THROW(OperandException); }

Short MultiEnum::sub(const Any& rhs) const { THROW(OperandException); }

MultiEnum MultiEnum::valueOf(const Char*) { THROW(OperandException); }

Short MultiEnum::valudOfImpl(const Char* str) { return 0; }

}  // namespace gemini