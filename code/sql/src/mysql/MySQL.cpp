#include "MySQL.h"

namespace gemini
{
namespace sql
{

Boolean MySQL::open()
{
    return mysql_real_connect(_impl, _config.ip.c_str(), _config.user.c_str(), _config.password.c_str(),
                              _config.database.c_str(), _config.port, 0, 0) == 0;
}

void MySQL::close()
{
    if (_impl != null)
    {
        mysql_close(_impl);
        _impl = nullptr;
    }
}

} // namespace sql
} // namespace gemini