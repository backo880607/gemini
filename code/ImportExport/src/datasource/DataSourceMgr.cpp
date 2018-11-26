#include "../../include/datasource/DataSourceMgr.h"
#include "message/Exception.h"

namespace gemini {
namespace integration {

DataSourceMgr::DataSourceMgr() {}

DataSourceMgr::~DataSourceMgr() {}

DataSourceMgr::dataSource_type DataSourceMgr::getDataSource(
    const Source::SPtr& source) const {
  if (!source.valid()) {
    return nullptr;
  }
  auto iter = _dataSources.find(&source->getClass());
  return iter != _dataSources.end() ? iter->second : nullptr;
}

void DataSourceMgr::registerDataSource(const Class& cls,
                                       dataSource_type dataSource) {
  auto iter = _dataSources.find(&cls);
  THROW_IF(iter != _dataSources.end(), RegisterException, cls.getName(),
           " has registed");
  _dataSources.insert(std::make_pair(&cls, dataSource));
}

}  // namespace integration
}  // namespace gemini