#ifndef GEMINI_IO_DataStructure_INCLUDE
#define GEMINI_IO_DataStructure_INCLUDE
#include "../DateTime.h"

namespace gemini {
namespace io {

struct DataHeader
{
	UInt _size;
	UInt _version;
	DateTime _time;
};

struct DataConfig
{
	String _sepField;
	String _sepEntity;
	String _replaceField;
	String _replaceEntity;
	const Class* _cls;
	const Field* _field;
};

}
}

#endif // GEMINI_IO_DataStructure_INCLUDE