#include "MultiEnum.h"
#include "Reflect.h"
#include "controller/BaseController.h"
#include "dao/BaseDao.h"
#include "entities/IocRelation.h"
#include "message/Exception.h"
#include "propagate/Propagate.h"

namespace gemini {

Field::Field(const Class &type, Long offset, const Class &cls, const Char *name,
             Int index /* = 0 */, RefKind refKind /* = RefKind::None */)
    : _refKind(refKind),
      _index(index),
      _type(type),
      _offset(offset),
      _class(cls),
      _name(name) {}

Field::~Field() {}

__register_field__::__register_field__(const Class &type, Long offset,
                                       const Class &cls, const Char *name,
                                       Int index /* = 0 */,
                                       RefKind refKind /* = RefKind::None */) {
  const Field *field = new Field(type, offset, cls, name, index, refKind);
  const_cast<Class &>(cls).addField(field);
}

Method::Method(const Class &cls, const char *name, const char *args)
    : _class(cls), _name(name) {}

Method::~Method() {}

void Method::set_callable(__callable__ *cb) { _callable = cb; }

__register_method__::__register_method__(__callable__ *cb, const Class &cls,
                                         const Class &returnCls,
                                         const char *name, const char *args,
                                         const char *virt) {
  Method *method = new Method(cls, name, args);
  method->set_callable(cb);
  const_cast<Class &>(cls).addMethod(method);
}

__register_static_method__::__register_static_method__(__callable__ *cb,
                                                       const Class *pclass,
                                                       const char *type,
                                                       const char *name,
                                                       const char *args) {
  // StaticMethod* method = new StaticMethod(pclass, type, name, args);
  //(const_cast<Class *>(pclass))->_addStaticMethod(method, cb);
}

class ClassManager final {
  ClassManager(const ClassManager &) = delete;
  ClassManager &operator=(const ClassManager &) = delete;

 public:
  ClassManager() {}
  ~ClassManager() {}

  void registerClass(const Class &cls) {
    if (cls.isBase(BaseEntity::getClassStatic())) {
      _classEntity.insert(std::make_pair(cls.getName(), &cls));
    } else if (cls.isBase(BaseController::getClassStatic())) {
      _classController.insert(std::make_pair(cls.getName(), &cls));
    } else if (cls.isBase(BaseDao::getClassStatic())) {
      _classDao.insert(std::make_pair(cls.getName(), &cls));
    }

    THROW_IF(_classAll.find(cls.getName()) != _classAll.end(),
             RegisterException, cls.getName(), " has registered!")
    _classAll.insert(std::make_pair(cls.getName(), &cls));
  }

  const Class *forName(const String &name) {
    auto iter = _classAll.find(name);
    return iter != _classAll.end() ? iter->second : nullptr;
  }

  const std::map<String, const Class *const> &getEntityClasses() const {
    return _classEntity;
  }
  const std::map<String, const Class *const> &getControllerClasses() const {
    return _classController;
  }

 private:
  std::map<String, const Class *const> _classAll;
  std::map<String, const Class *const> _classEntity;
  std::map<String, const Class *const> _classController;
  std::map<String, const Class *const> _classDao;
};
ClassManager &geminiAfxGetClassManager() {
  static ClassManager manager;
  return manager;
}
const std::map<String, const Class *const> &geminiAfxEntityClasses() {
  return geminiAfxGetClassManager().getEntityClasses();
}
const std::map<String, const Class *const> &geminiAfxControllerClasses() {
  return geminiAfxGetClassManager().getControllerClasses();
}

SmartPtr<BaseEntity> FieldRefWrapHelper::get(const BaseEntity *entity,
                                               Int sign) {
  return entity->_relations[sign]->get();
}
void FieldRefWrapHelper::set(BaseEntity *entity, Int sign,
                             const SmartPtr<BaseEntity> &relaEntity) {
  SmartPtr<BaseEntity> entitySPtr;
  entitySPtr.wrapRawPointer(entity);
  IocRelation::set(entitySPtr, sign, relaEntity);
}
const IList &FieldRefWrapHelper::getList(const BaseEntity *entity, Int sign) {
  return *((const IList *)(entity->_relations[sign]));
}

namespace ns_class {

String getNameImpl(const Char *name) {
  const Char *pLastSlash = strrchr(name, ':');
  if (pLastSlash == nullptr) {
    pLastSlash = strrchr(name, ' ');
  }
  return pLastSlash != nullptr ? pLastSlash + 1 : name;
}

const Class *getClassByName(const String &name) {
  return geminiAfxGetClassManager().forName(name);
}

RegisterPrimaryKey::RegisterPrimaryKey(const Class &cls,
                                       const String &primary) {}

RegisterPrimaryKey::~RegisterPrimaryKey() {}

}  // namespace ns_class

Int Class::s_maxIndex = 0;
Class::Class(const Char *name, const Class *superClass, PNewInstance instance,
             ns_class::HelperHolder *holder)
    : _isEnum(false),
      _index(s_maxIndex++),
      _enumHelper(nullptr),
      _superClass(superClass),
      _holder(holder),
      _instance(instance),
      _name(name) {
  geminiAfxGetClassManager().registerClass(*this);
}

Class::~Class() {}

Int Class::max_limits() { return 1024; }

Boolean Class::hasSuper() const { return _superClass != nullptr; }

Boolean Class::isBase(const Class &superCls) const {
  const Class *temp = this;
  while (temp->hasSuper()) {
    temp = &temp->getSuperClass();
    if (*temp == superCls) {
      return true;
    }
  }
  return false;
}

Boolean Class::isMultiEnum() const {
  return getSuperClass() == Class::forType<MultiEnum>();
}

Int Class::getEnum(const String &name) const {
  THROW_IF(!isEnum(), MatchException, name, "is not enum")
  THROW_IF(_enumHelper == nullptr, RegisterException, name, " not registed")
  return _enumHelper->valueOf(name);
}

const Class &Class::forName(const String &name) {
  const Class *cls = geminiAfxGetClassManager().forName(name);
  THROW_IF(cls == nullptr, RegisterException, name, " has not registered!")
  return *cls;
}

const Field *Class::getField(const String &name) const {
  std::map<String, const Field *>::const_iterator iter = _fields.find(name);
  return iter != _fields.end() ? iter->second : nullptr;
}

Boolean Class::hasField(const String &name) const {
  return _fields.find(name) != _fields.end();
}

void Class::addField(const Field *field) {
  std::map<String, const Field *>::iterator iter =
      _fields.find(field->getName());
  THROW_IF(iter != _fields.end(), RegisterException, field->getName(),
           " has existed in class ", getName())
  _fields.insert(std::make_pair(field->getName(), field));
}

const Method *Class::getMethod(const String &name) const {
  std::map<String, const Method *>::const_iterator iter = _methods.find(name);
  return iter != _methods.end() ? iter->second : nullptr;
}

void Class::addMethod(const Method *method) {
  std::map<String, const Method *>::iterator iter =
      _methods.find(method->getName());
  THROW_IF(iter != _methods.end(), RegisterException, method->getName(),
           " has existed in class ", getName());
  _methods.insert(std::make_pair(method->getName(), method));
}

Int EnumHelper::valueOf(const String &value) const {
  std::map<String, Int>::const_iterator iter = _info.find(value);
  THROW_IF(iter == _info.end(), NoSuchElementException, value);
  return iter->second;
}

void EnumHelper::SplitEnumString(const char *str) {
  /*const char * p = str;
          Int index = 0;
          while (std::isspace(*p)) p++;
          while (*p != '\0') {
                  const char* temp = p;
                  while (*p == '_' || std::isdigit(*p) || std::isalpha(*p)) p++;
                  String name(temp, p - temp);
                  while (std::isspace(*p)) p++;

                  if (*p == '\0') {
                          s_info.insert(std::make_pair(name, index++));
                          break;
                  }

                  if (*p == '=') {
                          p++;
                          while (std::isspace(*p)) p++;
                          temp = p;
                          while (std::isdigit(*p)) p++;
                          String value(temp, p - temp);
                          index = StringUtil::convert<Int>(value.c_str());
                          while (std::isspace(*p)) p++;
                  }

                  if (*p == ',') {
                          s_info.insert(std::make_pair(name, index++));
                  }
                  p++;

                  while (std::isspace(*p)) p++;
          }*/
}

}  // namespace gemini