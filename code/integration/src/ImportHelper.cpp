#include "../bean/FieldInfo.h"
#include "../bean/Scheme.h"
#include "../include/IntegrationError.h"
#include "../include/datasource/DataSourceMgr.h"
#include "../public/DataSource.h"
#include "../public/ImportHelper.h"
#include "message/Message.h"
#include "tools/ClassUtil.h"
#include "tools/ExpressionUtil.h"

namespace gemini {
namespace integration {

ImportHelper::ImportHelper() {}

ImportHelper::~ImportHelper() {}

void ImportHelper::execute() {
  for (Scheme::SPtr scheme : _schemes) {
    std::shared_ptr<DataSource> ds =
        DataSourceMgr::instance().getDataSource(scheme->_source());
    if (ds == nullptr) {
      Message::error<InvalidDataSource>(scheme->_source()->_name());
      return;
    }
    if (!ds->validConnection(scheme->_source(), scheme->_externName)) {
      return;
    }
    checkKeyFields(scheme);
  }

  for (Scheme::SPtr scheme : _schemes) {
    if (!proIOScheme(scheme)) {
      break;
    }
  }
}

Boolean ImportHelper::proIOScheme(SmartPtr<Scheme> scheme) {
  if (scheme == nullptr) {
    return false;
  }

  _dataSource = DataSourceMgr::instance().getDataSource(scheme->_source());
  if (_dataSource == nullptr) {
    return false;
  }

  std::shared_ptr<IExpression> filter = ExpressionUtil::create(scheme->_filter);

  const Class &cls = Class::forName(scheme->_innerName);
  std::vector<const Field *> keyFields = ClassUtil::getKeyFields(cls);
  while (_dataSource->step()) {
    BaseEntity::SPtr entity = createEntity(cls);

    Int index = 0;
    IList::Iterator iter = scheme->_fields().iterator();
    while (iter.hasNext()) {
      FieldInfo::SPtr ioField = iter.next<FieldInfo>();
      const Field *field = ioField->_field;
      if (field == nullptr) {
        continue;
      }
      // 获取字段值
      String value = obtainValue(index++, field);

      // 校验字段
      std::shared_ptr<api::ValidateHandler> validate =
          getValidateHandler(*field);
      if (validate != nullptr && validate->validate(*field, value)) {
        // 字段值验证不通过
        continue;
      }

      write(entity, field, value);
    }

    if (filter != nullptr && !filter->getBoolean(entity)) {
      continue;
    }

    String primary = checkEntity(keyFields, entity);
    if (primary.empty()) {
      continue;
    }

    sureEntity(entity, primary, scheme);
  }

  return true;
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

void ImportHelper::checkKeyFields(SmartPtr<Scheme> scheme) {
  const Class &cls = Class::forName(scheme->_innerName);
  std::vector<const Field *> keyFields = ClassUtil::getKeyFields(cls);
  for (const Field *keyField : keyFields) {
    FieldInfo::SPtr findField = _cache.getRela<Scheme::fields>(
        scheme, [&](const FieldInfo::SPtr &ioField) {
          return ioField->_field == keyField;
        });

    if (!findField.valid()) {
    }
  }
}

BaseEntity::SPtr ImportHelper::createEntity(const Class &cls) {
  return _cache.createTemp(cls);
}

String ImportHelper::checkEntity(const std::vector<const Field *> &keyFields,
                                 const BaseEntity::SPtr &entity) {
  String primary;
  for (const Field *field : keyFields) {
    String value = StringUtil::getField(entity, *field);
    if (value.empty()) {  // 键值为空
      return "";
    }
    primary += value;
  }

  const Class &cls = entity->getClass();
  std::shared_ptr<EntityData> data = _cache.getData(cls, primary);
  if (data != nullptr && data->imported) {  // 主键重复
    return "";
  }

  return primary;
}

void ImportHelper::sureEntity(BaseEntity::SPtr &entity, const String &primary,
                              SmartPtr<Scheme> scheme) {
  const Class &cls = entity->getClass();
  BaseEntity::SPtr innerEntity = _cache.getEntity(cls, primary);
  if (innerEntity.valid()) {
    if (scheme->_importType == ImportType::ReplaceImport) {
      // entity->_id = innerEntity->getID();
      _cache.insert(cls, primary, entity);
    } else {
      IList::Iterator iter = scheme->_fields().iterator();
      while (iter.hasNext()) {
        FieldInfo::SPtr ioField = iter.next<FieldInfo>();
        const Field *field = ioField->_field;
        if (field == nullptr) {
          continue;
        }
        ClassUtil::swap(*field, entity, innerEntity);
      }
    }
  } else {
    _cache.insert(cls, primary, entity);
  }
}

/*DtoParser::DtoParser() {}

DtoParser::~DtoParser() {}

DataNode DtoParser::getDataNode(const String &value) {
  switch (getDataType()) {
    case DtoParser::DataType::Init:
      break;
    case DtoParser::DataType::Json: {
      Json json(value.c_str());
      return json.getNode();
    }
    case DtoParser::DataType::XML: {
      XML xml(value.c_str());
      return xml.getNode();
    }
    default:
      break;
  }
  THROW(NoSupportException, " error data type")
}

Object::SPtr DtoParser::parseObject(const Class &cls, const String &value) {
  DataNode node = getDataNode(value);
  return parseObject(cls, node);
}

Object::SPtr DtoParser::parseObject(const Class &cls,
                                    const DataNode &dataNode) {
  Object::SPtr obj = nullptr;
  // cls.isBase(BaseEntity::getClassStatic()) ? DaoUtil::createTemp(cls) :
  // cls.newInstance();
  if (!obj.valid()) {
    return nullptr;
  }

  dataNode.foreach ([&](const DataNode &fieldNode) {
    const Field &field = ClassUtil::getField(cls, fieldNode.getName());
    if (field.getType().isBase(Object::getClassStatic())) {
      Object::SPtr relaObj = parseObject(field.getType(), fieldNode);
      if (relaObj.valid()) {
        field.set(obj, relaObj);
      }
    } else {
      write(obj, &field, fieldNode.getValue());
    }
  });
  return obj;
}*/

}  // namespace integration
}  // namespace gemini