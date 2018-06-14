#ifndef GEMINI_SQL_ResultSetImpl_INCLUDE
#define GEMINI_SQL_ResultSetImpl_INCLUDE
#include "../public/SQLExport.h"

namespace gemini
{
namespace sql
{

class StatementImpl;
class ResultSetImpl
{
	typedef std::shared_ptr<StatementImpl> stmt_type;

  public:
	ResultSetImpl(const stmt_type &stmt);
	virtual ~ResultSetImpl();

  private:
	stmt_type _stmt;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_ResultSetImpl_INCLUDE