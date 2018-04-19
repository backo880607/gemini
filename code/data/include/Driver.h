#pragma once
#include "../public/Connection.h"

namespace gemini {

namespace data {

class Driver
{
public:
	virtual Connection connect(const String& url) = 0;
	virtual Boolean acceptsURL(const String& url) = 0;

	virtual Int getMajorVersion() = 0;
	virtual Int getMinorVersion() = 0;
};

}
}