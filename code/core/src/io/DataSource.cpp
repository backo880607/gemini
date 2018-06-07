#include "io/DataSource.h"
#include "message/Exception.h"

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

DataHandlerHelper::DataHandlerHelper()
{

}

DataHandlerHelper::~DataHandlerHelper()
{

}

void DataHandlerHelper::registerHandler(const Class& cls, handler_type handler)
{
	auto iter = _clsHandlers.find(&cls);
	THROW_IF(iter != _clsHandlers.end(), RegisterException, cls.getName(), " has registed")
	_clsHandlers.insert(std::make_pair(&cls, handler));
}

void DataHandlerHelper::registerHandler(const Class& cls, Int sign, handler_type handler)
{
	std::vector<handler_type>& handlers = _fieldHandlers[&cls];
	if (handlers.empty())
	{
		handlers.resize(cls.maxIndex());
	}
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(const Class & cls)
{
	auto iter = _clsHandlers.find(&cls);
	return iter != _clsHandlers.end() ? iter->second : nullptr;
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(const Class & cls, Int sign)
{
	auto iter = _fieldHandlers.find(&cls);
	if (iter == _fieldHandlers.end() || iter->second.size() >= sign) {
		return nullptr;
	}
	return iter->second[sign];
}

}
}