#include "Application.h"
#include "entities/FactoryMgr.h"
#include "entities/IocRelation.h"
#include "expression/Calculate.h"
#include "expression/function/FunctionMgr.h"
#include "tools/StringUtil.h"
#include "tools/ClassUtil.h"

namespace gemini {

#define ENDFLG '\0'

Any LongCalculate::getValue(const BaseEntity::SPtr& entity) { return _value; }

Boolean LongCalculate::parse(const Char*& str) { return false; }

Any DoubleCalculate::getValue(const BaseEntity::SPtr& entity) {
  return _value;
}

Boolean DoubleCalculate::parse(const Char*& str) { return false; }

Any TextCalculate::getValue(const BaseEntity::SPtr& entity) { return _value; }

Boolean TextCalculate::parse(const Char*& str) {
  const Char* temp = ++str;
  while (*str != ENDFLG) {
    if (*str == '\'') {
      _value = String(temp, str - temp);
      ++str;
      return true;
    }
    ++str;
  }

  return false;
}

Any DateTimeCalculate::getValue(const BaseEntity::SPtr& entity) {
  return _value;
}

Boolean DateTimeCalculate::parse(const Char*& str) {
  const Char* temp = str;
  while (*str != ENDFLG) {
    if (*str == '#') {
      const String strValue(temp, str - temp);
      //_value = StringUtil::parse
      ++str;
      return true;
    }
    ++str;
  }

  return false;
}

OperTypeCalculate::OperTypeCalculate(const String& name) {
  _method = FunctionMgr::instance().getMethod(name);
}

Any OperTypeCalculate::getValue(const BaseEntity::SPtr& entity) {
  return nullptr;
}

Any OperTypeCalculate::getValue(const Any& param1, const Any& param2,
                                const BaseEntity::SPtr& entity) {
  std::vector<Any> params;
  params.push_back(param1);
  params.push_back(param2);
  return FunctionMgr::instance().invoke(_method, params);
}

Boolean OperTypeCalculate::parse(const Char*& str) { return false; }

Any FieldCalculate::getValue(const BaseEntity::SPtr& entity) {
  if (_field == nullptr) {
    return entity;
  }

  RefKind kind = RefKind::Entity;
  std::vector<Int> signs;
  for (const Field* path : _paths) {
    if (kind == RefKind::Entity) {
      kind = path->getRefKind();
    }
    signs.push_back(path->index());
  }
  if (kind == RefKind::Entity) {
    kind = _field->getRefKind();
  }
  if (kind != RefKind::Entity) {
    signs.push_back(_field->index());
    return IocRelation::getList(entity, signs);
  }
  BaseEntity::SPtr targetEntity = IocRelation::get(entity, signs);
  if (!targetEntity.valid()) {
    return nullptr;
  }

  return getResult(targetEntity.rawPointer());
}

Boolean FieldCalculate::parse(const Char*& str) { return parse(str, nullptr); }

Boolean FieldCalculate::parse(const Char*& str, const Class* propertyCls) {
  _field = nullptr;
  _paths.clear();
  const Char* temp = str;
  while (*str != ENDFLG) {
    if (*str == '.') {
      String name(temp, str - temp);
      if (propertyCls == nullptr) {
        EntityFactory* factory = FactoryMgr::instance().getFactory(name);
        if (factory == nullptr) return false;
        propertyCls = &factory->getEntityClass();
      } else {
        const Field& field = ClassUtil::getField(*propertyCls, name);
        propertyCls = &field.getType();
        _paths.push_back(&field);
      }

      if (propertyCls == nullptr) {
        return false;
      }

      temp = str + 1;
    } else if (!std::isalpha(*str, g_app.getLocale()) &&
               !std::isdigit(*str, g_app.getLocale())) {
      break;
    }
    ++str;
  }

  if (temp < str) {
    String name(temp, str - temp);
    if (propertyCls == nullptr) {
      EntityFactory* factory = FactoryMgr::instance().getFactory(name);
      if (factory == nullptr) return false;
      propertyCls = &factory->getEntityClass();
    } else {
      const Field& field = ClassUtil::getField(*propertyCls, name);
      propertyCls = &field.getType();
      _field = &field;
    }
  }

  return true;
}

Any FieldCalculate::getResult(const BaseEntity* entity) {
  if (entity == nullptr) {
    return nullptr;
  }

  const Class& propertyCls = _field->getType();
  if (propertyCls == Class::forType<Boolean>()) {
    return _field->get<Boolean>(entity);
  } else if (propertyCls == Class::forType<Char>()) {
    return _field->get<Char>(entity);
  } else if (propertyCls == Class::forType<Short>()) {
    return _field->get<Short>(entity);
  } else if (propertyCls == Class::forType<Int>()) {
    return _field->get<Int>(entity);
  } else if (propertyCls == Class::forType<Long>()) {
    return _field->get<Long>(entity);
  } else if (propertyCls == Class::forType<Float>()) {
    return _field->get<Float>(entity);
  } else if (propertyCls == Class::forType<Double>()) {
    return _field->get<Double>(entity);
  } else if (propertyCls == Class::forType<String>()) {
    return _field->get<String>(entity);
  } else if (propertyCls == Class::forType<ID>()) {
    return _field->get<ID>(entity);
  } else if (propertyCls == Class::forType<DateTime>()) {
    return _field->get<DateTime>(entity);
  } else if (propertyCls == Class::forType<Duration>()) {
    return _field->get<Duration>(entity);
  } else if (propertyCls == Class::forType<DurationExtend>()) {
    return _field->get<DurationExtend>(entity);
  } else if (propertyCls.isEnum() || propertyCls.isMultiEnum()) {
    return _field->get<Short>(entity);
  } else if (propertyCls.isBase(Class::forType<BaseEntity>())) {
    return _field->get<BaseEntity::SPtr>(entity);
  }

  return nullptr;
}

Any FunctionCalculate::getValue(const BaseEntity::SPtr& entity) {
  std::vector<Any> params;
  if (_params.empty()) {
    return FunctionMgr::instance().invoke(_method, params);
  }

  std::size_t index = 0;
  Any paramVal = _params[index].getValue(entity);
  if (!paramVal) {
    return nullptr;
  }

  params.push_back(paramVal);
  if (paramVal.getClass().isBase(Class::forType<BaseEntity>())) {
    BaseEntity::SPtr targetEntity = paramVal.cast<BaseEntity::SPtr>();
    for (++index; index < _params.size(); ++index) {
      paramVal = _params[index].getValue(targetEntity);
      if (!paramVal) {
        return nullptr;
      }
      params.push_back(paramVal);
    }
  } else if (paramVal.isType<IList>()) {
    const IList& targetEntities = paramVal.cast<IList>();
    for (++index; index < _params.size(); ++index) {
      if (!_params[index]._hasField) {
        params.push_back(_params[index].getValue(nullptr));
        continue;
      }
    }
  } else {
    if (StringUtil::icompare(_method->getName().c_str(), "if")) {
      return _params[paramVal.cast<Boolean>() ? 1 : 2].getValue(entity);
    } else {
      for (++index; index < _params.size(); ++index) {
        paramVal = _params[index].getValue(entity);
        if (!paramVal) {
          return nullptr;
        }
        params.push_back(paramVal);
      }
    }
  }
  Any result = FunctionMgr::instance().invoke(_method, params);
  if (_fieldCalc != nullptr) {
    return _fieldCalc->getValue(result.cast<BaseEntity::SPtr>());
  }

  return result;
}

Boolean FunctionCalculate::parse(const Char*& str) {
  _fieldCalc = nullptr;
  const Char* temp = str;
  while (*str != ENDFLG && *str != '(') ++str;

  if (*str == ENDFLG) return false;

  String name(temp, str - temp);
  _method = FunctionMgr::instance().getMethod(name);

  std::vector<const Class*> paramClses;
  ++str;
  while (*str != ENDFLG && *str != ')') {
    Expression paramExp;
    if (!paramExp.create(str, true)) return false;

    _params.push_back(paramExp);
    paramClses.push_back(paramExp.getClass());
  }

  if (*str == ENDFLG) return false;

  ++str;
  if (getClass()->isBase(Class::forType<BaseEntity>())) {
    const Char* temp = str;
    while (*temp != ENDFLG) {
      if (*temp == '.') {
        _fieldCalc = new FieldCalculate();
        if (!_fieldCalc->parse(str, getClass())) {
          delete _fieldCalc;
          _fieldCalc = nullptr;
          return false;
        }
      }

      if (!std::isspace(*temp, g_app.getLocale())) {
        break;
      }
      ++temp;
    }
  }

  // 检验参数的有效性
  FunctionMgr::instance().check(_method, paramClses);
  return true;
}

const Class* FunctionCalculate::getClass() {
  Int returnIndex = FunctionMgr::instance().getReturnIndex(_method->getName());
  if (returnIndex <= 0) {
    return &_method->getReturnClass();
  }
  return _params[returnIndex].getClass();
}

Any DurationCalculate::getValue(const BaseEntity::SPtr& entity) {
  return Any();
}

Boolean DurationCalculate::parse(const Char*& str) { return Boolean(); }

Any EnumCalculate::getValue(const BaseEntity::SPtr& entity) { return Any(); }

Boolean EnumCalculate::parse(const Char*& str) { return Boolean(); }

Any BracketCalculate::getValue(const BaseEntity::SPtr& entity) {
  return _exp.getValue(entity);
}

Boolean BracketCalculate::parse(const Char*& str) {
  Node* nd = _exp.create(str, false);
  if (nd == nullptr) {
    return false;
  }

  _exp._root = nd;
  return true;
}
}