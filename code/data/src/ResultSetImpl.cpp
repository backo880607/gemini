#include "../include/ResultSetImpl.h"

namespace gemini {
namespace data {

ResultSetImpl::ResultSetImpl(const stmt_type& stmt)
	: _stmt(stmt)
{
}

ResultSetImpl::~ResultSetImpl()
{

}

}
}