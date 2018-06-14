#ifndef GEMINI_SQL_Driver_INCLUDE
#define GEMINI_SQL_Driver_INCLUDE
#include "../public/Connection.h"

namespace gemini
{

namespace sql
{

class Driver
{
  public:
	virtual Connection connect(const String &url) = 0;
	virtual Boolean acceptsURL(const String &url) = 0;

	virtual Int getMajorVersion() = 0;
	virtual Int getMinorVersion() = 0;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Driver_INCLUDE