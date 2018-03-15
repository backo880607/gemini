#pragma once
#include "../public/Connection.h"

#include <sstream>

namespace gemini {
namespace data {

class StatementImpl
{
public:
	enum class State {
		ST_INITIALIZED,
		ST_COMPILED,
		ST_BOUND,
		ST_PAUSED,
		ST_DONE,
		ST_RESET
	};

	StatementImpl(ConnectionImpl& conn);
	virtual ~StatementImpl();

	State getState() const { return _state; }

	void reset();
	Int execute(Boolean = true);

	String toString() const { return _ostr.str(); }

protected:
	virtual Boolean canCompile() const = 0;
	virtual void compileImpl() = 0;

private:
	void compile();

private:
	State _state;
	ConnectionImpl& _conn;
	std::ostringstream	_ostr;
};

}
}