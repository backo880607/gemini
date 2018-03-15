#pragma once
#include "Connection.h"

namespace gemini {
namespace data {

class StatementImpl;
class GEMINI_DATA_API Statement
{
	typedef std::shared_ptr<StatementImpl> impl_type;
public:
	Statement(Connection conn);
	~Statement() {}

	void reset(Connection conn);

	Int execute(Boolean reset = true);

	Boolean initialized();
	Boolean paused();
	Boolean done();

private:
	impl_type _impl;
};

}
}