#ifndef GEMINI_IO_DataSourceMgr_INCLUDE
#define GEMINI_IO_DataSourceMgr_INCLUDE

namespace gemini {
namespace io {

class DataSourceMgr final
{
	DataSourceMgr();
public:
	~DataSourceMgr();

	static DataSourceMgr& instance() { static DataSourceMgr mgr; return mgr; }
};

}
}
#endif // GEMINI_IO_DataSourceMgr_INCLUDE
