#include "../public/Connection.h"
#include "../include/ConnectionImpl.h"

namespace gemini
{
namespace sql
{

Boolean Connection::open()
{
	return _impl ? _impl->open() : false;
}

Boolean Connection::open(const SQLConfig &config)
{
	return _impl ? _impl->open(config) : false;
}

void Connection::close()
{
	if (_impl)
	{
		_impl->close();
	}
}

} // namespace sql
} // namespace gemini