#include "api/DataNode.h"
#include "dao/Memory.h"
#include "io/HandlerHelper.h"
#include "io/IOField.h"
#include "io/IOScheme.h"
#include "io/ImportHelper.h"
#include "io/datasource/DataSourceMgr.h"

namespace gemini {
namespace io {

ImportHelper::ImportHelper() {}

ImportHelper::~ImportHelper() {}

void ImportHelper::execute() {
  for (IOScheme::SPtr scheme : _schemes) {
    if (!parseIOScheme(scheme)) {
      break;
    }
  }
}

Boolean ImportHelper::parseIOScheme(SmartPtr<IOScheme> scheme) {
  if (scheme == nullptr) {
    return false;
  }

  _dataSource = DataSourceMgr::instance().getDataSource(scheme->_dataSource);
  if (_dataSource == nullptr) {
    return false;
  }

  std::shared_ptr<EntityHandler> entityHandler =
      _entityHelper->getHandler(Class::forName(scheme->_innerName));
  if (entityHandler == nullptr) {
    return false;
  }
  std::map<Int, const Field *> primaries = parsePrimaries(scheme);
  while (_dataSource->step()) {
    EntityObject::SPtr entity =
        entityHandler->require(obtainPrimary(primaries));
    if (!entity.valid()) {
      continue;
    }

    Int index = 0;
    IList::Iterator iter = scheme->_fields->iterator();
    while (iter.hasNext()) {
      IOField::SPtr ioField = iter.next<IOField>();
      const Field *field = ioField->_field;
      if (field == nullptr) {
        continue;
      }
      String value = obtainValue(index++, field);
      write(entity, field, value);
    }
  }

  return true;
}

std::map<Int, const Field *> ImportHelper::parsePrimaries(
    SmartPtr<IOScheme> scheme) {
  std::map<Int, const Field *> result;
  Int index = 0;
  IList::Iterator iter = scheme->_fields->iterator();
  while (iter.hasNext()) {
    IOField::SPtr field = iter.next<IOField>();
    if (field->_primary) {
      result.insert(std::make_pair(index, field->_field.field()));
    }
    ++index;
  }
  return result;
}

String ImportHelper::obtainValue(Int index, const Field *field) {
  String value = _dataSource->getMatrix() ? _dataSource->getData(index)
                                          : _dataSource->getData(field);
  StringUtil::replace(value, _dataSource->getConfig()._replaceField.c_str(),
                      _dataSource->getConfig()._sepField.c_str());
  StringUtil::replace(value, _dataSource->getConfig()._replaceEntity.c_str(),
                      _dataSource->getConfig()._sepEntity.c_str());

  return value;
}

String ImportHelper::obtainPrimary(
    const std::map<Int, const Field *> &primaries) {
  String value;
  for (auto iter = primaries.begin(); iter != primaries.end(); ++iter) {
    value += obtainValue(iter->first, iter->second);
    value += _dataSource->getConfig()._sepField;
  }
  if (!value.empty()) {
    value.erase(value.size() - _dataSource->getConfig()._sepField.size());
  }

  return std::move(value);
}

DtoParseHelper::DtoParseHelper() {}

DtoParseHelper::~DtoParseHelper() {}

/*void DtoParseHelper::execute() {
  if (_dataSource == nullptr) {
    return;
  }
}*/

Object::SPtr DtoParseHelper::parseObject(const Class &cls,
                                         const DataNode &dataNode) {
  std::shared_ptr<EntityHandler> entityHandler = _entityHelper->getHandler(cls);
  if (entityHandler == nullptr) {
    return nullptr;
  }

  Object::SPtr obj = entityHandler->require("");
  if (!obj.valid()) {
    return nullptr;
  }

  dataNode.foreach ([&](const DataNode &fieldNode) {
    const Field &field = cls.getField(fieldNode.getName());
    if (field.getClass().isBase(Object::getClassStatic())) {
      Object::SPtr relaObj = parseObject(field.getClass(), fieldNode);
      if (relaObj.valid()) {
        field.set(obj, relaObj);
      }
    } else {
      write(obj, &field, fieldNode.getValue());
    }
  });
  return obj;
}

}  // namespace io
}  // namespace gemini