#ifndef GEMINI_IO_DSExcelCSV_INCLUDE
#define GEMINI_IO_DSExcelCSV_INCLUDE
#include "../../public/io/DataSource.h"

namespace gemini
{
class File;
namespace io
{

class DSExcelCSV : public DataSource
{
public:
	DSExcelCSV();
	virtual ~DSExcelCSV();

	virtual Boolean open(const String &connection) override;
	virtual void close() override;

	virtual Boolean step() override;
	virtual String getData(Int index) override;

	virtual Boolean write(const Field *fd, const String &data) override;

private:
	std::shared_ptr<File> _file;
	std::vector<String> _rowDatas;
};

} // namespace io
} // namespace gemini
#endif // GEMINI_IO_DSExcelCSV_INCLUDE
