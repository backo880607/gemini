#ifndef GEMINI_IO_DataSourceMgr_INCLUDE
#define GEMINI_IO_DataSourceMgr_INCLUDE
#include "Common.h"

namespace gemini {
namespace io {

class DataSource;
class DataSourceMgr final {
  typedef std::shared_ptr<DataSource> dataSource_type;
  DataSourceMgr();

 public:
  ~DataSourceMgr();

  static DataSourceMgr &instance() {
    static DataSourceMgr mgr;
    return mgr;
  }

  dataSource_type getDataSource(const String &name) const;

  void registerDataSource(const String &name, dataSource_type dataSource);

 private:
  std::map<String, dataSource_type> _dataSources;
};

}  // namespace io
}  // namespace gemini
#endif  // GEMINI_IO_DataSourceMgr_INCLUDE
