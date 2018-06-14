#pragma once
#include "../public/Statement.h"
#include "../include/ConnectionImpl.h"
#include "../include/StatementImpl.h"

namespace gemini
{
namespace sql
{

Statement::Statement(Connection conn)
{
	reset(conn);
}

void Statement::reset(Connection conn)
{
	if (conn._impl)
	{
		_impl = conn._impl->createStatement();
	}
}

Int Statement::execute(Boolean reset)
{
	Boolean isDone = done();
	if (initialized() || paused() || isDone)
	{

		if (isDone)
			_impl->reset();
		return _impl->execute(reset);
	}
	return -1;
}

Boolean Statement::initialized()
{
	return _impl->getState() == StatementImpl::State::ST_INITIALIZED;
}

Boolean Statement::paused()
{
	return _impl->getState() == StatementImpl::State::ST_PAUSED;
}

Boolean Statement::done()
{
	return _impl->getState() == StatementImpl::State::ST_DONE;
}

} // namespace sql
} // namespace gemini