#include "../../public/message/Exception.h"
#include "../../public/tools/StringUtil.h"

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

thread_local String g_buffer;
char const* Exception::what() const
{
	std::stringstream temp;
	temp.imbue(std::locale("chs_china"));
	temp << _info->throw_file_ << " " << _info->throw_line_ << " " << _info->throw_function_ << "" << getName().c_str() << ":\n";
	for (Any& any : _info->_datas) {
		temp << StringUtil::format(any).c_str();
	}

	g_buffer = temp.str();
	return g_buffer.c_str();
}

}