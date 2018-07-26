#include "MultiEnum.h"
#include "message/Exception.h"

namespace gemini {

MultiEnum::MultiEnum(Int value) : _value((Int)pow(2, value - 1)) {}
MultiEnum::MultiEnum() : _value(0) {}

Boolean MultiEnum::contains(Int value) {
  return (_value | (Int)pow(2, value - 1)) > 0;
}

Boolean MultiEnum::contains(const MultiEnum& rhs) {
  return (_value | rhs._value) == rhs._value;
}

void MultiEnum::operator+=(Int rhs) { _value = _value | (Int)pow(2, rhs - 1); }

void MultiEnum::operator+=(const MultiEnum& rhs) {
  _value = _value | rhs._value;
}

void MultiEnum::operator-=(Int rhs) {
  _value = _value & ~(Int)(pow(2, rhs - 1));
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

String MultiEnum::str() const { return ""; }

Int MultiEnum::add(const Any& rhs) const { THROW(OperandException); }

Int MultiEnum::sub(const Any& rhs) const { THROW(OperandException); }

Int MultiEnum::valudOfImpl(const Char* str) { return 0; }

}  // namespace gemini