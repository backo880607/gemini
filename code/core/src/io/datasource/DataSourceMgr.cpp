#include "io/datasource/DataSourceMgr.h"
#include "message/Exception.h"

namespace gemini {
namespace io {

DataSourceMgr::DataSourceMgr() {}

DataSourceMgr::~DataSourceMgr() {}

DataSourceMgr::dataSource_type DataSourceMgr::getDataSource(
    const String& name) const {
  auto iter = _dataSources.find(name);
  return iter != _dataSources.end() ? iter->second : nullptr;
}

void DataSourceMgr::registerDataSource(const String& name,
                                       dataSource_type dataSource) {
  auto iter = _dataSources.find(name);
  THROW_IF(iter != _dataSources.end(), RegisterException, name,
           " has registed");
  _dataSources.insert(std::make_pair(name, dataSource));
}

}  // namespace io
}  // namespace gemini