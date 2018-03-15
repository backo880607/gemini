#pragma once
#include "../public/DataExport.h"

namespace gemini {
namespace data {

class StatementImpl;
class ResultSetImpl
{
	typedef std::shared_ptr<StatementImpl> stmt_type;
public:
	ResultSetImpl(const stmt_type& stmt);
	virtual ~ResultSetImpl();

private:
	stmt_type _stmt;
};

}
}