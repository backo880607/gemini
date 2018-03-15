#include "..\include\ConnectionImpl.h"

namespace gemini {
namespace data {

Boolean ConnectionImpl::open(const SQLConfig& config)
{
    _config = config;
    return open();
}

}
}