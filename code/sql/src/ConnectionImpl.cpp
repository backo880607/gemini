#include "..\include\ConnectionImpl.h"

namespace gemini
{
namespace sql
{

Boolean ConnectionImpl::open(const SQLConfig &config)
{
    _config = config;
    return open();
}

} // namespace sql
} // namespace gemini