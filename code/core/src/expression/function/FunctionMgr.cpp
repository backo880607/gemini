#include "expression/function/FunctionMgr.h"
#include "expression/function/InternalFunction.h"

namespace gemini {

Function::Function(FunCall fun /* = nullptr */)
	: _fun(fun)
{

}

Function FunctionMgr::getFunction(const String& name)
{
	auto iter = _functions.find(name);
	return iter != _functions.end() ? iter->second : nullptr;
}

void FunctionMgr::registerFunction(const Char* name, Function::FunCall fun)
{
	auto iter = _functions.find(name);
	if (iter != _functions.end()) {

	}

	_functions.insert(std::make_pair(name, fun));
}

__register_expression_method__::__register_expression_method__(const String & methodName, const String & returnType, const String & paramsType)
{

}

}