#ifndef GEMINI_SQL_MySQL_INCLUDE
#define GEMINI_SQL_MySQL_INCLUDE
#include "..\..\include\Connection.h"

namespace gemini
{
namespace sql
{

class MySQL : public Connection
{
  public:
    virtual Boolean open() override;

    virtual void close() override;

  private:
    MYSQL *_impl;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_MySQL_INCLUDE