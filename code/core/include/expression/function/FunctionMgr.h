#pragma once
#include "../../../public/Any.h"

namespace gemini {

class Function
{
	friend class FunctionMgr;
	typedef Any(*FunCall)(const std::vector<Any>&);

public:
	Function(FunCall fun = nullptr);
	Boolean valid() const { return _fun != nullptr; }
	Any invoke(std::vector<Any>& params) { return (*_fun)(params); }

private:
	FunCall _fun;
};

class FunctionMgr
{
public:
	static FunctionMgr& instance() { static FunctionMgr mgr; return mgr; }

	Function getFunction(const String& name);

	void registerFunction(const Char* name, Function::FunCall fun);
private:
	std::map<String, Function::FunCall> _functions;
};

}