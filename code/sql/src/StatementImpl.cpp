#include "../include/StatementImpl.h"

namespace gemini
{
namespace sql
{

StatementImpl::StatementImpl(ConnectionImpl &conn)
	: _state(State::ST_INITIALIZED), _conn(conn)
{
}

StatementImpl::~StatementImpl()
{
}

void StatementImpl::reset()
{
}

Int StatementImpl::execute(Boolean)
{
	do
	{
		compile();
	} while (canCompile());

	return 0;
}

void StatementImpl::compile()
{
	if (_state == State::ST_INITIALIZED ||
		_state == State::ST_RESET ||
		_state == State::ST_BOUND)
	{
		compileImpl();
		_state = State::ST_COMPILED;
	}
}

} // namespace sql
} // namespace gemini