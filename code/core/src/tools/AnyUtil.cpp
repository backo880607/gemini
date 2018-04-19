#include "tools/AnyUtil.h"

namespace gemini {

class AnyAbstract {
public:
	AnyAbstract(Any& value) : _value(value) {}
	virtual ~AnyAbstract() {}

	virtual Any add(AnyAbstract* rhs) = 0;
	virtual Any sub(AnyAbstract* rhs) = 0;
	virtual Any multiply(AnyAbstract* rhs) = 0;
	virtual Any division(AnyAbstract* rhs) = 0;

public:
	Any& _value;
};
class AnyBoolean final : public AnyAbstract {
public:
	AnyBoolean(Any& value) : AnyAbstract(value) {}

	virtual Any add(AnyAbstract* rhs) override { return nullptr; }
	virtual Any sub(AnyAbstract* rhs) override { return nullptr; }
	virtual Any multiply(AnyAbstract* rhs) override { return nullptr; }
	virtual Any division(AnyAbstract* rhs) override { return nullptr; }
};
class AnyShort : public AnyAbstract {
public:
	virtual Any add(AnyAbstract* rhs) override {
		if (rhs->_value.isType<Short>()) {
			return AnyUtil::cast<Short>(_value) + AnyUtil::cast<Short>(rhs->_value);
		} else if (rhs->_value.isType<UShort>()) {
			return AnyUtil::cast<Short>(_value) + AnyUtil::cast<UShort>(rhs->_value);
		}

		return nullptr;
	 }
};
class AnyDouble : public AnyAbstract {
public:
	virtual Any add(AnyAbstract* rhs) override {
		if (rhs->_value.isType<Short>()) {
			return AnyUtil::cast<Double>(_value) + AnyUtil::cast<Short>(rhs->_value);
		} else if (rhs->_value.isType<UShort>()) {
			return AnyUtil::cast<Double>(_value) + AnyUtil::cast<UShort>(rhs->_value);
		} else if (rhs->_value.isType<Int>()) {
			return AnyUtil::cast<Double>(_value) + AnyUtil::cast<Int>(rhs->_value);
		} else if (rhs->_value.isType<UInt>()) {
			return AnyUtil::cast<Double>(_value) + AnyUtil::cast<UInt>(rhs->_value);
		}

		return nullptr;
	 }
};
class AnyCustom : public AnyAbstract {
public:
	virtual Any add(AnyAbstract* rhs) override {

	}
};
class AnyHandler {
public:
	void init() {

	}
	AnyAbstract* get(const Any& value) { return _values[value._cls->index()]; }
private:
	AnyAbstract* _values[1024];
};
AnyHandler g_anyHandler;

Any AnyUtil::add(const Any& lhs, const Any& rhs)
{
	if (!lhs || !rhs) {
		return nullptr;
	}

	return g_anyHandler.get(lhs)->add(g_anyHandler.get(rhs));
}

Any AnyUtil::sub(const Any& lhs, const Any& rhs)
{
	if (!lhs || !rhs) {
		return nullptr;
	}
	return nullptr;
}

Any AnyUtil::multiply(const Any& lhs, const Any& rhs)
{
	if (!lhs || !rhs) {
		return nullptr;
	}
	return nullptr;
}

Any AnyUtil::division(const Any& lhs, const Any& rhs)
{
	if (!lhs || !rhs) {
		return nullptr;
	}

	return nullptr;
}

}