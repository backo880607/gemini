#ifndef GEMINI_SQL_Connection_INCLUDE
#define GEMINI_SQL_Connection_INCLUDE
#include "SQLConfig.h"

namespace gemini
{
namespace sql
{

class ConnectionImpl;
class GEMINI_SQL_API Connection
{
    typedef std::shared_ptr<ConnectionImpl> impl_type;

  public:
    virtual Boolean open();
    virtual Boolean open(const SQLConfig &config);

    virtual void close();

  private:
    friend class Statement;
    impl_type _impl;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Connection_INCLUDE