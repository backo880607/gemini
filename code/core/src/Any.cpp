#include "Any.h"
#include "tools/StringUtil.h"
#include "message/Exception.h"
#include "Object.h"

namespace gemini {

class HolderBoolean : public Any::Holder<Boolean> {
public:
	HolderBoolean(Boolean value) : Any::Holder<Boolean>(value) {}
	virtual PlaceHolder* clone() const { return new HolderBoolean(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const { 
		if (rhs.isType<Boolean>()) { return _value == rhs.cast<Boolean>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const { 
		if (rhs.isType<Boolean>()) { return _value - rhs.cast<Boolean>() < 0 ? true : false; }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderChar : public Any::Holder<Char> {
public:
	HolderChar(Char value) : Any::Holder<Char>(value) {}
	virtual PlaceHolder* clone() const { return new HolderChar(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Char>()) { return _value == rhs.cast<Char>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const { 
		if (rhs.isType<Char>()) { return _value < rhs.cast<Char>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderUChar : public Any::Holder<UChar> {
public:
	HolderUChar(UChar value) : Any::Holder<UChar>(value) {}
	virtual PlaceHolder* clone() const { return new HolderUChar(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Char>()) { return _value == rhs.cast<Char>(); } 
		else if (rhs.isType<UChar>()) { return _value == rhs.cast<UChar>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Char>()) { return _value < rhs.cast<Char>(); }
		else if (rhs.isType<UChar>()) { return _value < rhs.cast<UChar>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderWChar : public Any::Holder<WChar> {
public:
	HolderWChar(WChar value) : Any::Holder<WChar>(value) {}
	virtual PlaceHolder* clone() const { return new HolderWChar(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<WChar>()) { return _value == rhs.cast<WChar>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<WChar>()) { return _value < rhs.cast<WChar>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderChar16 : public Any::Holder<Char16> {
public:
	HolderChar16(Char16 value) : Any::Holder<Char16>(value) {}
	virtual PlaceHolder* clone() const { return new HolderChar16(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Char16>()) { return _value == rhs.cast<Char16>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Char16>()) { return _value < rhs.cast<Char16>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderChar32 : public Any::Holder<Char32> {
public:
	HolderChar32(Char32 value) : Any::Holder<Char32>(value) {}
	virtual PlaceHolder* clone() const { return new HolderChar32(_value); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Char32>()) { return _value == rhs.cast<Char32>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Char32>()) { return _value < rhs.cast<Char32>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderShort : public Any::Holder<Short> {
public:
	HolderShort(Short value) : Any::Holder<Short>(value) {}
	virtual PlaceHolder* clone() const { return new HolderShort(_value); }
	virtual Any operator+ (const Any& rhs) const { 
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else { THROW(OperandException); }
	}
	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<short>()) { return _value == rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<short>()) { return _value < rhs.cast<Short>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderUShort : public Any::Holder<UShort> {
public:
	HolderUShort(UShort value) : Any::Holder<UShort>(value) {}
	virtual PlaceHolder* clone() const { return new HolderUShort(_value); }
	virtual Any operator+ (const Any& rhs) const { 
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else { THROW(OperandException); }
	}
	virtual Boolean operator== (const Any& rhs) const { 
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderInt : public Any::Holder<Int> {
public:
	HolderInt(Int value) : Any::Holder<Int>(value) {}
	virtual PlaceHolder* clone() const { return new HolderInt(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderUInt : public Any::Holder<UInt> {
public:
	HolderUInt(const UInt& value) : Any::Holder<UInt>(value) {}
	virtual PlaceHolder* clone() const { return new HolderUInt(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const { 
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < (UInt)rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < (UInt)rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderLong : public Any::Holder<Long> {
public:
	HolderLong(const Long& value) : Any::Holder<Long>(value) {}
	virtual PlaceHolder* clone() const { return new HolderLong(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value + rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value += rhs.cast<Long>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value - rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value -= rhs.cast<Long>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value * rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value *= rhs.cast<Long>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value / rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value /= rhs.cast<Long>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value == rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value < rhs.cast<Long>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderULong : public Any::Holder<ULong> {
public:
	HolderULong(const Long& value) : Any::Holder<ULong>(value) {}
	virtual PlaceHolder* clone() const { return new HolderLong(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value + rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value + rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value += rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value += rhs.cast<ULong>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value - rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value - rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value -= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value -= rhs.cast<ULong>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value * rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value * rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value *= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value *= rhs.cast<ULong>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value / rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value / rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value /= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value /= rhs.cast<ULong>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value == rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value == rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value < (ULong)rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value < rhs.cast<ULong>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderFloat : public Any::Holder<Float> {
public:
	HolderFloat(const Float& value) : Any::Holder<Float>(value) {}
	virtual PlaceHolder* clone() const { return new HolderFloat(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value + rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value + rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value + rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value += rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value += rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value += rhs.cast<Float>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value - rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value - rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value - rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value -= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value -= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value -= rhs.cast<Float>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value * rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value * rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value * rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value *= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value *= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value *= rhs.cast<Float>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value / rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value / rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value / rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value /= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value /= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value /= rhs.cast<Float>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value == rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value == rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value == rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value < rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value < rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value < rhs.cast<Float>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderDouble : public Any::Holder<Double> {
public:
	HolderDouble(const Double& value) : Any::Holder<Double>(value) {}
	virtual PlaceHolder* clone() const { return new HolderDouble(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value + rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value + rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value + rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value + rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value += rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value += rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value += rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value += rhs.cast<Double>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value - rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value - rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value - rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value - rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value -= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value -= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value -= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value -= rhs.cast<Double>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value * rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value * rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value * rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value * rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value *= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value *= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value *= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value *= rhs.cast<Double>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value / rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value / rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value / rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value / rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value /= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value /= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value /= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value /= rhs.cast<Double>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value == rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value == rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value == rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value == rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value < rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value < rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value < rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value < rhs.cast<Double>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderLDouble : public Any::Holder<LDouble> {
public:
	HolderLDouble(const LDouble& value) : Any::Holder<LDouble>(value) {}
	virtual PlaceHolder* clone() const { return new HolderLDouble(_value); }
	virtual Any operator+ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value + rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value + rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value + rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value + rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value + rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value + rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value + rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value + rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value + rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual void operator+= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value += rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value += rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value += rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value += rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value += rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value += rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value += rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value += rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { _value += rhs.cast<LDouble>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator- (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value - rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value - rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value - rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value - rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value - rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value - rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value - rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value - rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value - rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual void operator-= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value -= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value -= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value -= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value -= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value -= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value -= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value -= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value -= rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { _value -= rhs.cast<LDouble>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator* (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value * rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value * rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value * rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value * rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value * rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value * rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value * rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value * rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value * rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual void operator*= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value *= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value *= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value *= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value *= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value *= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value *= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value *= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value *= rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { _value *= rhs.cast<LDouble>(); }
		else { THROW(OperandException); }
	}
	virtual Any operator/ (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value / rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value / rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value / rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value / rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value / rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value / rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value / rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value / rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value / rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual void operator/= (const Any& rhs) {
		if (rhs.isType<Short>()) { _value /= rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { _value /= rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { _value /= rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { _value /= rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { _value /= rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { _value /= rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { _value /= rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { _value /= rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { _value /= rhs.cast<LDouble>(); }
		else { THROW(OperandException); }
	}

	virtual Boolean operator== (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value == rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value == rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value == rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value == rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value == rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value == rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value == rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value == rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value == rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (rhs.isType<Short>()) { return _value < rhs.cast<Short>(); }
		else if (rhs.isType<UShort>()) { return _value < rhs.cast<UShort>(); }
		else if (rhs.isType<Int>()) { return _value < rhs.cast<Int>(); }
		else if (rhs.isType<UInt>()) { return _value < rhs.cast<UInt>(); }
		else if (rhs.isType<Long>()) { return _value < rhs.cast<Long>(); }
		else if (rhs.isType<ULong>()) { return _value < rhs.cast<ULong>(); }
		else if (rhs.isType<Float>()) { return _value < rhs.cast<Float>(); }
		else if (rhs.isType<Double>()) { return _value < rhs.cast<Double>(); }
		else if (rhs.isType<LDouble>()) { return _value < rhs.cast<LDouble>(); }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderString : public Any::Holder<String> {
public:
	HolderString(const String& value) : Any::Holder<String>(value) {}
	virtual PlaceHolder* clone() const { return new HolderString(_value); }
	virtual Any operator+ (const Any& rhs) const { return _value + rhs.str(); }
	virtual void operator+= (const Any& rhs) { _value += rhs.str(); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const { 
		if (rhs.isType<String>()) { return strcmp(_value.c_str(), rhs.cast<String>().c_str()) == 0; }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const { 
		if (rhs.isType<String>()) { return strcmp(_value.c_str(), rhs.cast<String>().c_str()) < 0; }
		THROW(OperandException);
	}
	virtual String str() const { return StringUtil::format(_value); }
};
class HolderEntityObject : public Any::Holder<SmartPtr<EntityObject>> {
public:
	HolderEntityObject(const SmartPtr<EntityObject>& value) : Any::Holder<SmartPtr<EntityObject>>(value) {}
	virtual PlaceHolder* clone() const { return new HolderEntityObject(_value); }
	virtual const Class& getClass() const { return _value->getClass(); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		if (getClass() == rhs.getClass()) { return _value->getID() == rhs.cast<EntityObject>()->getID(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		if (getClass() == rhs.getClass()) { return _value->getID() < rhs.cast<EntityObject>()->getID(); }
		THROW(OperandException);
	}
	virtual String str() const { THROW(ClassCastException); }
};
class HolderIList : public Any::Holder<const IList&> {
public:
	HolderIList(const IList& value) : Any::Holder<const IList&>(value) {}
	virtual PlaceHolder* clone() const { return new HolderIList(_value); }
	virtual const Class& getClass() const { return Class::forType<IList>(); }
	virtual Any operator+ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator+= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator- (const Any& rhs) const { THROW(OperandException); }
	virtual void operator-= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator* (const Any& rhs) const { THROW(OperandException); }
	virtual void operator*= (const Any& rhs) { THROW(OperandException); }
	virtual Any operator/ (const Any& rhs) const { THROW(OperandException); }
	virtual void operator/= (const Any& rhs) { THROW(OperandException); }
	virtual Boolean operator== (const Any& rhs) const {
		//if (getClass() == rhs.getClass()) { return _value->getID() == rhs.cast<EntityObject>()->getID(); }
		THROW(OperandException);
	}
	virtual Boolean operator< (const Any& rhs) const {
		//if (getClass() == rhs.getClass()) { return _value->getID() < rhs.cast<EntityObject>()->getID(); }
		THROW(OperandException);
	}
	virtual String str() const { THROW(ClassCastException); }
};

Any::Any(const Any& rhs)
	: _holder(rhs._holder != nullptr ? rhs._holder->clone() : nullptr) 
{
}

Any::Any(Any&& rhs)
	: _holder(rhs._holder)
{
	rhs._holder = nullptr;
}

Any::~Any()
{
	if (_holder != nullptr) delete _holder;
}

Any::PlaceHolder* Any::create(Boolean value) {
	return new HolderBoolean(value);
}

Any::PlaceHolder* Any::create(Char value) {
	return new HolderChar(value);
}

Any::PlaceHolder* Any::create(UChar value) {
	return new HolderUChar(value);
}

Any::PlaceHolder* Any::create(WChar value) {
	return new HolderWChar(value);
}

Any::PlaceHolder* Any::create(Char16 value) {
	return new HolderChar16(value);
}

Any::PlaceHolder* Any::create(Char32 value) {
	return new HolderChar32(value);
}

Any::PlaceHolder* Any::create(Short value) {
	return new HolderShort(value);
}

Any::PlaceHolder* Any::create(UShort value) {
	return new HolderUShort(value);
}

Any::PlaceHolder* Any::create(Int value) {
	return new HolderInt(value);
}

Any::PlaceHolder* Any::create(UInt value) {
	return new HolderUInt(value);
}

Any::PlaceHolder* Any::create(Long value) {
	return new HolderLong(value);
}

Any::PlaceHolder* Any::create(ULong value) {
	return new HolderULong(value);
}

Any::PlaceHolder* Any::create(Float value) {
	return new HolderFloat(value);
}

Any::PlaceHolder* Any::create(Double value) {
	return new HolderDouble(value);
}

Any::PlaceHolder* Any::create(LDouble value) {
	return new HolderLDouble(value);
}

Any::PlaceHolder* Any::create(const String& value) {
	return new HolderString(value);
}

Any::PlaceHolder* Any::create(const Char* value) {
	return new HolderString(value);
}

Any::PlaceHolder * Any::create(const SmartPtr<EntityObject>& value)
{
	return new HolderEntityObject(value);
}

Any::PlaceHolder * Any::create(const IList & value)
{
	return new HolderIList(value);
}

Any& Any::operator= (std::nullptr_t rhs) {
	if (_holder != nullptr) {
		delete _holder;
		_holder = nullptr;
	}
	return *this;
}

const Class& Any::getClass() const 
{
	if (!(*this)) {
		THROW(NullPointerException);
	}
	return _holder->getClass(); 
}

Any Any::operator+ (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator+(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator+ : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

Any& Any::operator+= (const Any& rhs) {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

    try {
        _holder->operator+=(rhs);
    } catch (OperandException& exc) {
		throw exc << u8"operator+= : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}

	return *this;
}

Any Any::operator- (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator-(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator- : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

Any& Any::operator-= (const Any& rhs) {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		_holder->operator-=(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator-= : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}

	return *this;
}

Any Any::operator* (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator*(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator* : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

Any& Any::operator*= (const Any& rhs) {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		_holder->operator*=(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator*= : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}

	return *this;
}

Any Any::operator/ (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator/(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator/ : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

Any& Any::operator/= (const Any& rhs) {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		_holder->operator/=(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator/= : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}

	return *this;
}

Boolean Any::operator== (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator==(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator== : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

Boolean Any::operator< (const Any& rhs) const {
	if (!(*this) || !rhs) {
		THROW(NullPointerException);
	}

	try {
		return _holder->operator<(rhs);
	} catch (OperandException& exc) {
		throw exc << u8"operator< : not support type " << getClass().getName() << " or " << rhs.getClass().getName();
	}
}

String Any::str() const
{
	return *this ? _holder->str() : u8"";
}

Any AnyAbstract::operator+(const Any & rhs) const
{
	THROW(OperandException);
}

void AnyAbstract::operator+=(const Any & rhs)
{
	THROW(OperandException);
}

Any AnyAbstract::operator-(const Any & rhs) const
{
	THROW(OperandException);
}

void AnyAbstract::operator-=(const Any & rhs)
{
	THROW(OperandException);
}

Any AnyAbstract::operator*(const Any & rhs) const
{
	THROW(OperandException);
}

void AnyAbstract::operator*=(const Any & rhs)
{
	THROW(OperandException);
}

Any AnyAbstract::operator/(const Any & rhs) const
{
	THROW(OperandException);
}

void AnyAbstract::operator/=(const Any & rhs)
{
	THROW(OperandException);
}

Boolean AnyAbstract::operator==(const Any & rhs) const
{
	THROW(OperandException);
}

Boolean AnyAbstract::operator<(const Any & rhs) const
{
	THROW(OperandException);
}

String AnyAbstract::str() const
{
	THROW(ClassCastException);
}

}