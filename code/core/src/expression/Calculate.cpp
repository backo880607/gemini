#include "Application.h"
#include "entities/FactoryMgr.h"
#include "entities/IocRelation.h"
#include "expression/Calculate.h"

#include <locale>

namespace gemini {

#define ENDFLG '\0'

Any LongCalculate::getValue(const EntityObject::SPtr& entity) { return _value; }

Boolean LongCalculate::parse(const Char*& str) { return false; }

Any DoubleCalculate::getValue(const EntityObject::SPtr& entity) {
  return _value;
}

Boolean DoubleCalculate::parse(const Char*& str) { return false; }

Any TextCalculate::getValue(const EntityObject::SPtr& entity) { return _value; }

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

Any DateTimeCalculate::getValue(const EntityObject::SPtr& entity) {
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

Any OperTypeCalculate::getValue(const EntityObject::SPtr& entity) {
  return nullptr;
}

Any OperTypeCalculate::getValue(const Any& param1, const Any& param2,
                                const EntityObject::SPtr& entity) {
  std::vector<Any> params;
  params.push_back(param1);
  params.push_back(param2);
  return FunctionMgr::instance().invoke(_method, params);
}

Boolean OperTypeCalculate::parse(const Char*& str) { return false; }

Any FieldCalculate::getValue(const EntityObject::SPtr& entity) {
  if (_propertyCls == nullptr) {
    return nullptr;
  }

  if (_field == nullptr) {
    return entity;
  }

  Boolean multiRef = false;
  std::vector<Int> signs;
  for (const Field* path : _paths) {
    multiRef = path->getMultiRef();
    signs.push_back(path->index());
  }
  if (multiRef) {
    signs.push_back(_field->index());
    return IocRelation::getList(entity, signs);
  }
  EntityObject::SPtr targetEntity = IocRelation::get(entity, signs);
  if (!targetEntity.valid()) {
    return nullptr;
  }

  return getResult(targetEntity.rawPointer());
}

Boolean FieldCalculate::parse(const Char*& str) {
  _isList = false;
  _propertyCls = nullptr;
  _field = nullptr;
  _paths.clear();
  const Char* temp = str;
  while (*str != ENDFLG) {
    if (*str == '.') {
      String name(temp, str - temp);
      if (_propertyCls == nullptr) {
        EntityFactory* factory = FactoryMgr::instance().getFactory(name);
        if (factory == nullptr) return false;
        _propertyCls = &factory->getEntityClass();
      } else {
        const Field& field = _propertyCls->getField(name);
        _propertyCls = &field.getType();
        _paths.push_back(&field);
      }

      if (_propertyCls == nullptr) {
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
    if (_propertyCls == nullptr) {
      EntityFactory* factory = FactoryMgr::instance().getFactory(name);
      if (factory == nullptr) return false;
      _propertyCls = &factory->getEntityClass();
    } else {
      const Field& field = _propertyCls->getField(name);
      _propertyCls = &field.getType();
      _field = &field;
    }
  }

  return true;
}

Any FieldCalculate::getResult(const EntityObject* entity) {
  if (entity == nullptr) {
    return nullptr;
  }

  if (_propertyCls == &Class::forType<Boolean>()) {
    return _field->get<Boolean>(entity);
  } else if (_propertyCls == &Class::forType<Char>()) {
    return _field->get<Char>(entity);
  } else if (_propertyCls == &Class::forType<Short>()) {
    return _field->get<Short>(entity);
  } else if (_propertyCls == &Class::forType<Int>()) {
    return _field->get<Int>(entity);
  } else if (_propertyCls == &Class::forType<Int>()) {
    return _field->get<Int>(entity);
  } else if (_propertyCls == &Class::forType<Long>()) {
    return _field->get<Long>(entity);
  } else if (_propertyCls == &Class::forType<Float>()) {
    return _field->get<Float>(entity);
  } else if (_propertyCls == &Class::forType<Double>()) {
    return _field->get<Double>(entity);
  } else if (_propertyCls == &Class::forType<String>()) {
    return _field->get<String>(entity);
  } else if (_propertyCls->isBase(Class::forType<EntityObject>())) {
    return _field->get<EntityObject::SPtr>(entity);
  }

  return nullptr;
}

Any FunctionCalculate::getValue(const EntityObject::SPtr& entity) {
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
  if (paramVal.getClass().isBase(Class::forType<EntityObject>())) {
    EntityObject::SPtr targetEntity = paramVal.cast<EntityObject::SPtr>();
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
    for (++index; index < _params.size(); ++index) {
      paramVal = _params[index].getValue(entity);
      if (!paramVal) {
        return nullptr;
      }
      params.push_back(paramVal);
    }
  }
  return FunctionMgr::instance().invoke(_method, params);
}

Boolean FunctionCalculate::parse(const Char*& str) {
  const Char* temp = str;
  while (*str != ENDFLG && *str != '(') ++str;

  if (*str == ENDFLG) return false;

  String name(temp, str - temp);
  _method = FunctionMgr::instance().getMethod(name);
  if (_method == nullptr) return false;

  ++str;
  while (*str != ENDFLG && *str != ')') {
    Expression paramExp;
    if (!paramExp.create(str, true)) return false;

    _params.push_back(paramExp);
  }

  if (*str == ENDFLG) return false;

  ++str;
  return true;
}

Any DurationCalculate::getValue(const EntityObject::SPtr& entity) {
  return Any();
}

Boolean DurationCalculate::parse(const Char*& str) { return Boolean(); }

Any EnumCalculate::getValue(const EntityObject::SPtr& entity) { return Any(); }

Boolean EnumCalculate::parse(const Char*& str) { return Boolean(); }

Any BracketCalculate::getValue(const EntityObject::SPtr& entity) {
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