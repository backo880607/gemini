#ifndef GEMINI_IO_DataSource_INCLUDE
#define GEMINI_IO_DataSource_INCLUDE
#include "DataStructure.h"

namespace gemini {
namespace io {

class CORE_API DataSource
{
public:
	DataSource();
	virtual ~DataSource();

	const String& getName() const { return _name; }
	void setName(const String& name) { _name = name; }

	virtual Boolean open(const String& connection) = 0;
	virtual void close() = 0;

	virtual Boolean step() = 0;
	virtual String getData(Int index) = 0;

	virtual Boolean write(const Field* fd, const String& data) = 0;

protected:
	String _name;
	DataHeader _header;
	DataConfig _config;
};

}
}
#endif // GEMINI_IO_DataSource_INCLUDE
