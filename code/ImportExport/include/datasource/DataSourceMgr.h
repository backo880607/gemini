#ifndef GEMINI_INTEGRATION_DataSourceMgr_INCLUDE
#define GEMINI_INTEGRATION_DataSourceMgr_INCLUDE
#include "../../bean/Source.h"

namespace gemini {
namespace integration {

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

  dataSource_type getDataSource(const Source::SPtr &source) const;

  void registerDataSource(const Class &cls, dataSource_type dataSource);

 private:
  std::map<const Class *, dataSource_type> _dataSources;
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_DataSourceMgr_INCLUDE
