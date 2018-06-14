#include "../include/ResultSetImpl.h"

namespace gemini
{
namespace sql
{

ResultSetImpl::ResultSetImpl(const stmt_type &stmt)
	: _stmt(stmt)
{
}

ResultSetImpl::~ResultSetImpl()
{
}

} // namespace sql
} // namespace gemini