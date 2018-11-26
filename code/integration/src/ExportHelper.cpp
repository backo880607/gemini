#include "../bean/Scheme.h"
#include "../include/datasource/DataSourceMgr.h"
#include "../public/DataSource.h"
#include "../public/ExportHelper.h"
#include "message/Exception.h"
#include "tools/ExpressionUtil.h"

namespace gemini {
namespace integration {

ExportHelper::ExportHelper() {}

ExportHelper::~ExportHelper() {}

void ExportHelper::execute() {
  for (Scheme::SPtr scheme : _schemes) {
    if (!execute(scheme)) {
      break;
    }
  }
}

Boolean ExportHelper::execute(SmartPtr<Scheme> scheme) {
  Boolean bOK = true;
  try {
    handleScheme(scheme);
  } catch (Exception& exc) {
    bOK = false;
  } catch (std::exception& exc) {
    bOK = false;
  } catch (...) {
    bOK = false;
  }
  return bOK;
}

void ExportHelper::handleScheme(SmartPtr<Scheme> scheme) {
  std::shared_ptr<DataSource> ds =
      DataSourceMgr::instance().getDataSource(scheme->_source());
  if (ds == nullptr) {
    return;
  }
  if (!ds->open(scheme->_source(), scheme->_externName)) {
    return;
  }

  const Class& cls = Class::forName(scheme->_innerName);
  /*const IList& entities = DaoUtil::getList(cls);
  std::shared_ptr<IExpression> expFilter =
      ExpressionUtil::create(scheme->_filter);*/
}

void ExportHelper::execute(const Class& cls) {
  if (_dataSource == nullptr) {
    return;
  }
}

void ExportHelper::execute(const Object::SPtr& object) {}

}  // namespace integration
}  // namespace gemini