#include "io/DSStream.h"

namespace gemini
{
namespace io
{
DSStream::DSStream()
{
	setName("stream");
}

DSStream::~DSStream()
{
}

Boolean DSStream::open(const String & connection)
{
	return Boolean();
}

void DSStream::close()
{
}

Boolean DSStream::step()
{
	return Boolean();
}

String DSStream::getData(Int index)
{
	return String();
}

Boolean DSStream::write(const Field * fd, const String & data)
{
	return Boolean();
}

} // namespace io
} // namespace gemini
