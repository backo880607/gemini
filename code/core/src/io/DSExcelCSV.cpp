#include "io/DSExcelCSV.h"
#include "tools/File.h"
#include "tools/StringUtil.h"

namespace gemini
{
namespace io
{

DSExcelCSV::DSExcelCSV()
{
	setName("excel");
}

DSExcelCSV::~DSExcelCSV()
{
}

Boolean DSExcelCSV::open(const String &connection)
{
	_file.reset(new File(connection.c_str()));
	return _file->open();
}

void DSExcelCSV::close()
{
	if (_file)
	{
		_file->close();
		_file = nullptr;
	}
}

Boolean DSExcelCSV::step()
{
	if (_file->isEnd())
	{
		return false;
	}

	String rowData = _file->readLine();
	_rowDatas.clear();
	StringUtil::parse<String>(_rowDatas, rowData, _config._sepField.c_str());
	return !_rowDatas.empty();
}

String DSExcelCSV::getData(Int index)
{
	if (index >= _rowDatas.size())
	{
	}

	return _rowDatas[index];
}

Boolean DSExcelCSV::write(const Field *fd, const String &data)
{
	return Boolean();
}

} // namespace io
} // namespace gemini