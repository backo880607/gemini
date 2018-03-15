#include "../../include/expression/Calculate.h"
#include "../../include/entities/FactoryMgr.h"
#include "../../include/Application.h"

#include <locale>

namespace gemini {

#define ENDFLG	'\0'

Any IntCalculate::getValue(const EntityObject::SPtr entity)
{
	return _value;
}

Boolean IntCalculate::parse(const Char*& str)
{
	return false;
}

Any DoubleCalculate::getValue(const EntityObject::SPtr entity)
{
	return _value;
}

Boolean DoubleCalculate::parse(const Char*& str)
{
	return false;
}

Any TextCalculate::getValue(const EntityObject::SPtr entity)
{
	return _value;
}

Boolean TextCalculate::parse(const Char*& str)
{
	const Char* temp = ++str;
	while (*str != ENDFLG) {
		if (*str == '\'') {
			_value = String(temp, str - temp);
			++str;
			return true;
		}
		++str;
	}

	return false;
}

Any DateTimeCalculate::getValue(const EntityObject::SPtr entity)
{
	return _value;
}

Boolean DateTimeCalculate::parse(const Char*& str)
{
	const Char* temp = str;
	while (*str != ENDFLG) {
		if (*str == '#') {
			const String strValue(temp, str - temp);
			//_value = StringUtil::parse
			++str;
			return true;
		}
		++str;
	}

	return false;
}

OperTypeCalculate::OperTypeCalculate(const String& name)
{
	_fun = FunctionMgr::instance().getFunction(name);
}

Any OperTypeCalculate::getValue(const EntityObject::SPtr entity)
{
	return nullptr;
}

Any OperTypeCalculate::getValue(const Any& param1, const Any& param2, const EntityObject::SPtr entity)
{
	std::vector<Any> params;
	params.push_back(param1);
	params.push_back(param2);
	return _fun.invoke(params);
}

Boolean OperTypeCalculate::parse(const Char*& str)
{
	return false;
}

Any FieldCalculate::getValue(const EntityObject::SPtr entity)
{
	if (_propertyCls == nullptr) {
		return nullptr;
	}

	if (_field == nullptr) {
		return entity;
	}

	EntityObject::SPtr relaEntity = entity;
	for (const Field* path : _paths) {
		relaEntity = path->get<EntityObject::SPtr>(relaEntity.rawPointer());
		if (relaEntity == nullptr) {
			break;
		}
	}

	return getResult(relaEntity.rawPointer());
}

Boolean FieldCalculate::parse(const Char*& str)
{
	_propertyCls = nullptr;
	_field = nullptr;
	_paths.clear();
	const Char* temp = str;
	while (*str != ENDFLG) {
		if (*str == '.') {
			String name(temp, str - temp);
			if (_propertyCls == nullptr) {
				EntityFactory* factory = FactoryMgr::instance().getFactory(name);
				if (factory == nullptr)
					return false;
				_propertyCls = &factory->getEntityClass();
			} else {
				const Field& field = _propertyCls->getField(name);
				_propertyCls = &field.getType();
				_paths.push_back(&field);
			}

			if (_propertyCls == nullptr) {
				return false;
			}

			temp = str + 1;
		} else if (!std::isalpha(*str, g_app.getLocale()) && !std::isdigit(*str, g_app.getLocale())) {
			break;
		}
		++str;
	}

	if (temp < str) {
		String name(temp, str - temp);
		if (_propertyCls == nullptr) {
			EntityFactory* factory = FactoryMgr::instance().getFactory(name);
			if (factory == nullptr)
				return false;
			_propertyCls = &factory->getEntityClass();
		} else {
			const Field& field = _propertyCls->getField(name);
			_propertyCls = &field.getType();
			_field = &field;
		}
	}

	return true;
}

Any FieldCalculate::getResult(const EntityObject* entity)
{
	if (_propertyCls == &Class::forType<Boolean>()) {
		return entity != nullptr ? _field->get<Boolean>(entity) : false;
	} else if (_propertyCls == &Class::forType<Char>()) {
		return entity != nullptr ? _field->get<Char>(entity) : Char();
	} else if (_propertyCls == &Class::forType<UChar>()) {
		return entity != nullptr ? _field->get<UChar>(entity) : UChar();
	} else if (_propertyCls == &Class::forType<Short>()) {
		return entity != nullptr ? _field->get<Short>(entity) : Short();
	} else if (_propertyCls == &Class::forType<UShort>()) {
		return entity != nullptr ? _field->get<UShort>(entity) : UShort();
	} else if (_propertyCls == &Class::forType<Int>()) {
		return entity != nullptr ? _field->get<Int>(entity) : Int();
	} else if (_propertyCls == &Class::forType<UInt>()) {
		return entity != nullptr ? _field->get<UInt>(entity) : UInt();
	} else if (_propertyCls == &Class::forType<Long>()) {
		return entity != nullptr ? _field->get<Long>(entity) : Long();
	} else if (_propertyCls == &Class::forType<ULong>()) {
		return entity != nullptr ? _field->get<ULong>(entity) : ULong();
	} else if (_propertyCls == &Class::forType<Float>()) {
		return entity != nullptr ? _field->get<Float>(entity) : Float();
	} else if (_propertyCls == &Class::forType<Double>()) {
		return entity != nullptr ? _field->get<Double>(entity) : Double();
	} else if (_propertyCls == &Class::forType<LDouble>()) {
		return entity != nullptr ? _field->get<LDouble>(entity) : LDouble();
	} else if (_propertyCls == &Class::forType<String>()) {
		return entity != nullptr ? _field->get<String>(entity) : String();
	}

	return Any();
}

Any FunctionCalculate::getValue(const EntityObject::SPtr entity)
{
	return nullptr;
}

Boolean FunctionCalculate::parse(const Char*& str)
{
	const Char* temp = str;
	while (*str != ENDFLG && *str != '(')
		++str;

	if (*str == ENDFLG)
		return false;

	String name(temp, str - temp);
	_fun = FunctionMgr::instance().getFunction(name);
	if (!_fun.valid())
		return false;

	++str;
	while (*str != ENDFLG && *str != ')') {
		Expression paramExp;
		if (!paramExp.create(str, true))
			return false;

		_params.push_back(paramExp);
	}

	if (*str == ENDFLG)
		return false;

	++str;
	return true;
}

}