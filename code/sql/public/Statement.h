#ifndef GEMINI_SQL_Statement_INCLUDE
#define GEMINI_SQL_Statement_INCLUDE
#include "Connection.h"

namespace gemini
{
namespace sql
{

class StatementImpl;
class GEMINI_SQL_API Statement
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

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Statement_INCLUDE