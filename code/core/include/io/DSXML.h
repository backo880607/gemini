#ifndef GEMINI_IO_DSXML_INCLUDE
#define GEMINI_IO_DSXML_INCLUDE
#include "../../public/io/DataSource.h"

namespace gemini {
namespace io {

class DSXML : public DataSource
{
public:
	DSXML();
	~DSXML();
};

class DSXMLFile : public DataSource
{
public:
	DSXMLFile();
	~DSXMLFile();
};

}
}

#endif // GEMINI_IO_DSXML_INCLUDE
