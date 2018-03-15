#pragma once
#include "Expression.h"

#include "./function/FunctionMgr.h"
#include "../../public/DateTime.h"

namespace gemini {

class CORE_API Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity) = 0;
	virtual Boolean parse(const Char*& str) = 0;
};

class CORE_API IntCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	Long _value;
	friend class Expression;
};

class CORE_API DoubleCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	Double _value;
	friend class Expression;
};

class CORE_API TextCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	String _value;
};

class CORE_API DateTimeCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	DateTime _value;
};

class CORE_API OperTypeCalculate : public Calculate
{
public: 
	OperTypeCalculate(const String& name);

	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Any getValue(const Any& param1, const Any& param2, const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);
private:
	Function _fun;
};

class CORE_API FieldCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	Any getResult(const EntityObject* entity);

private:
	const Class* _propertyCls;
	const Field* _field;
	std::vector<const Field*> _paths;
};

class CORE_API FunctionCalculate : public Calculate
{
public:
	virtual Any getValue(const EntityObject::SPtr entity);
	virtual Boolean parse(const Char*& str);

private:
	Function _fun;
	std::vector<Expression> _params;
};

}