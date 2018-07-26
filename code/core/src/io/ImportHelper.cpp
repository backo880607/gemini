#include "io/HandlerHelper.h"
#include "io/IOField.h"
#include "io/IOScheme.h"
#include "io/ImportHelper.h"
#include "io/datasource/DataSourceMgr.h"
#include "tools/StringUtil.h"

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
      std::shared_ptr<DataHandler> handler =
          _dataHelper->getHandler(field->getClass(), field->index());
      if (handler) {
        handler->write(entity, field, value);
        continue;
      }
      handler = _dataHelper->getHandler(field->getClass());
      if (handler) {
        handler->write(entity, field, value);
        continue;
      }

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

void ImportHelper::write(EntityObject::SPtr entity, const Field *field,
                         const String &value) {
  const Class &fieldCls = field->getClass();
  if (fieldCls == Class::forType<Boolean>()) {
    field->set(entity, StringUtil::convert<Boolean>(value.c_str()));
  } else if (fieldCls == Class::forType<Short>()) {
    field->set(entity, StringUtil::convert<Short>(value.c_str()));
  } else if (fieldCls == Class::forType<Int>()) {
    field->set(entity, StringUtil::convert<Int>(value.c_str()));
  } else if (fieldCls == Class::forType<Long>()) {
    field->set(entity, StringUtil::convert<Long>(value.c_str()));
  } else if (fieldCls == Class::forType<Float>()) {
    field->set(entity, StringUtil::convert<Float>(value.c_str()));
  } else if (fieldCls == Class::forType<Double>()) {
    field->set(entity, StringUtil::convert<Double>(value.c_str()));
  } else if (fieldCls == Class::forType<String>()) {
    field->set(entity, value);
  } else if (fieldCls.isEnum()) {
    field->set(entity, fieldCls.getEnum(value));
  } else if (fieldCls.isMultiEnum()) {
  }
}

}  // namespace io
}  // namespace gemini