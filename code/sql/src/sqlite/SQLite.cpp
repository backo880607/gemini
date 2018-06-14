#include "../../include/sqlite/SQLite.h"
#include "../../include/sqlite/SQLiteStatement.h"
#include "sqlite3.h"

namespace gemini
{
namespace sql
{

SQLite::SQLite()
    : _pDB(nullptr)
{
}

SQLite::~SQLite()
{
}

Boolean SQLite::open()
{
    return sqlite3_open_v2(getConfig().ip.c_str(), &_pDB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, nullptr) == 0;
}

void SQLite::close()
{
    if (_pDB != nullptr)
    {
        sqlite3_close_v2(_pDB);
        _pDB = nullptr;
    }
}

std::shared_ptr<StatementImpl> SQLite::createStatement()
{
    return std::shared_ptr<StatementImpl>(_pDB != nullptr ? new SQLiteStatement(*this, _pDB) : nullptr);
}

} // namespace sql
} // namespace gemini