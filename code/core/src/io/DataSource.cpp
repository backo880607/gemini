#include "io/DataSource.h"

namespace gemini {
namespace io {

DataSource::DataSource()
{
	_config._sepField = u8"\t";
	_config._sepEntity = u8"\n";
	//_config._replaceField = u8"▲";
	//_config._replaceEntity = u8"♦";
	_config._cls = nullptr;
	_config._field = nullptr;
}

DataSource::~DataSource()
{

}

}
}