#pragma once
#include "../../../public/Any.h"

namespace gemini {

class Function
{
	friend class FunctionMgr;
	typedef Any(*FunCall)(const std::vector<Any>&);
public:
	struct ParamInfo {
		std::set<const Class*> clses;
	};
public:
	Function(FunCall fun = nullptr);
	Boolean valid() const { return _fun != nullptr; }
	Any invoke(std::vector<Any>& params) { return (*_fun)(params); }

private:
	FunCall _fun;
	String _name;
	std::vector<ParamInfo> _params;
	std::set<const Class*> _returnClses;
};

class FunctionMgr
{
public:
	static FunctionMgr& instance() { static FunctionMgr mgr; return mgr; }

	Function getFunction(const String& name);

	void registerFunction(const Char* name, Function::FunCall fun);
private:
	std::map<String, Function> _functions;
};

struct __register_expression_method__ {
	__register_expression_method__(const String& methodName, const String& returnType, const String& paramsType);
};

#define EXPRESSION_METHOD(RETURN_TYPE, METHOD_NAME, ...) \
private:\
	struct __expression_##METHOD_NAME {\
		__expression_##METHOD_NAME() {\
			static gemini::__register_expression_method__ reg(#METHOD_NAME, #RETURN_TYPE, __VA_ARGS__); }\
	} __expression_##METHOD_NAME;\

}