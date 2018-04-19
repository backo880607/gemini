#include "message/Exception.h"
#include "tools/StringUtil.h"

#include <stdarg.h>
#include <sstream>

namespace gemini {
	
Exception::Exception()
	: _info(new exception_error())
{
}

Exception::~Exception()
{
	
}

void Exception::setInfo(char const * curFun, char const * file, int line)
{
	_info->throw_function_ = curFun;
	_info->throw_file_ = file;
	_info->throw_line_ = line;
}

thread_local String tl_exception_buffer;
char const* Exception::what() const
{
	std::stringstream temp;
	temp.imbue(std::locale("chs_china"));
	temp << _info->throw_file_ << " " << _info->throw_line_ << " " << _info->throw_function_ << "" << getName().c_str() << ":\n";
	for (Any& any : _info->_datas) {
		temp << StringUtil::format(any).c_str();
	}

	tl_exception_buffer = temp.str();
	return tl_exception_buffer.c_str();
}

String log_info::detail()
{
	return String();
}

}