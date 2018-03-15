#include "../../../include/expression/function/FunctionMgr.h"
#include "../../../include/expression/function/InternalFunction.h"

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

}