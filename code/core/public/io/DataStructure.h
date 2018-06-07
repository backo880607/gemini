#ifndef GEMINI_IO_DataStructure_INCLUDE
#define GEMINI_IO_DataStructure_INCLUDE
#include "../Object.h"

namespace gemini
{
namespace io
{

struct DataHeader
{
	Int _size;
	Int _version;
	DateTime _time;
};

struct DataConfig
{
	String _sepField;
	String _sepEntity;
	String _replaceField;
	String _replaceEntity;
	const Class *_cls;
	const Field *_field;
};

class DataHandler;
class DataHandlerHelper
{
	typedef std::shared_ptr<DataHandler> handler_type;
public:
	DataHandlerHelper();
	~DataHandlerHelper();

	void registerHandler(const Class& cls, handler_type handler);
	void registerHandler(const Class& cls, Int sign, handler_type handler);

	handler_type getHandler(const Class& cls);
	handler_type getHandler(const Class& cls, Int sign);

private:
	std::map<const Class*, handler_type> _clsHandlers;
	std::map<const Class*, std::vector<handler_type>> _fieldHandlers;
};

} // namespace io
} // namespace gemini
#endif // GEMINI_IO_DataStructure_INCLUDE