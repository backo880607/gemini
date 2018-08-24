#ifndef GEMINI_Reflect_INCLUDE
#define GEMINI_Reflect_INCLUDE
#include "SmartPtr.h"

namespace gemini {

class Object;
class EntityObject;
class Class;
class IList;
class CORE_API Field final {
  Field(const Field &) = delete;
  Field &operator=(const Field &) = delete;

 public:
  Field(const Class &type, Long offset, const Class &cls, const Char *name,
        Int index = 0, Boolean multiRef = 0);
  ~Field();

  Boolean getMultiRef() const { return _multiRef; }
  const String &getName() const { return _name; }
  const Class &getClass() const { return _class; }
  const Class &getType() const { return _type; }
  Int index() const { return _index; }

  template <class Value>
  Value get(const Object *object) const;
  template <class Value>
  void set(Object *object, const Value &value) const;

  template <class Value>
  Value get(const SmartPtr<Object> &object) const {
    return get<Value>(object.rawPointer());
  }
  template <class Value>
  void set(SmartPtr<Object> &object, const Value &value) const {
    return set<Value>(object.rawPointer(), value);
  }

 private:
  Boolean _multiRef;
  Int _index;
  const Class &_type;
  Long _offset;
  const Class &_class;
  String _name;
};
struct CORE_API __register_field__ {
  __register_field__(const Class &type, Long offset, const Class &cls,
                     const Char *name, Int index = 0, Boolean multiRef = 0);
};

template <class Value>
Value Field::get(const Object *object) const {
  return *(const Value *)(((const char *)object) + _offset);
}

template <class Value>
void Field::set(Object *object, const Value &value) const {
  *(Value *)(((char *)object) + _offset) = value;
}

namespace ns_class {

CORE_API String getNameImpl(const Char *name);
CORE_API const Class *getClassByName(const String &name);

template <class T>
struct remove_cv {
  typedef T type;
};
template <class T>
struct remove_cv<T &> {
  typedef T type;
};
template <class T>
struct remove_cv<const T &> {
  typedef T type;
};
template <class T>
struct remove_cv<T &&> {
  typedef T type;
};
template <class T>
struct remove_cv<const T &&> {
  typedef T type;
};
template <class T>
struct remove_cv<volatile T> {
  typedef T type;
};
template <class T>
struct remove_cv<volatile const T> {
  typedef T type;
};

template <typename T>
struct FetchImpl {
  typedef T type;
};
template <>
struct FetchImpl<Char *> {
  typedef String type;
};

template <typename T>
struct Helper {
  static void *create() { return new T; }
  static String getName() { return getNameImpl(typeid(T).name()); }
};
template <>
struct Helper<void> {
  static void *create() { return nullptr; }
  static String getName() { return "void"; }
};
template <>
struct Helper<Boolean> {
  static void *create() { return new Boolean(); }
  static String getName() { return "Boolean"; }
};
template <>
struct Helper<Char> {
  static void *create() { return new Char(); }
  static String getName() { return "Char"; }
};
template <>
struct Helper<Short> {
  static void *create() { return new Short(); }
  static String getName() { return "Short"; }
};
template <>
struct Helper<Int> {
  static void *create() { return new Int(); }
  static String getName() { return "Int"; }
};
template <>
struct Helper<Long> {
  static void *create() { return new Long(); }
  static String getName() { return "Long"; }
};
template <>
struct Helper<Float> {
  static void *create() { return new Float(); }
  static String getName() { return "Float"; }
};
template <>
struct Helper<Double> {
  static void *create() { return new Double(); }
  static String getName() { return "Double"; }
};
template <>
struct Helper<String> {
  static void *create() { return new String(); }
  static String getName() { return "String"; }
};
template <>
struct Helper<IList> {
  static void *create() { return nullptr; }
  static String getName() { return "IList"; }
};
template <>
struct Helper<const IList &> {
  static void *create() { return nullptr; }
  static String getName() { return "IList"; }
};
}  // namespace ns_class
class Method;
class EnumHelper;
class CORE_API Class final {
  typedef void *(*PNewInstance)();

  template <typename T, Boolean BEntity>
  struct forTypeImpl {
    static const Class &value() { return T::getClassStatic(); }
  };
  template <typename T>
  struct forTypeImpl<T, false> {
    static const Class &value() {
      static const Class *cls = nullptr;
      if (cls == nullptr) {
        cls = ns_class::getClassByName(ns_class::Helper<T>::getName());
        if (cls == nullptr) {
          static const Class _class(ns_class::Helper<T>::getName().c_str(),
                                    nullptr, ns_class::Helper<T>::create);
          if (std::is_enum<T>::value) {
            const_cast<Class &>(_class)._isEnum = true;
          }
          cls = &_class;
		}
	  }
      return *cls;
    }
  };

  Class(const Class &rhs) = delete;
  Class &operator=(const Class &rhs) = delete;

 public:
  template <typename T>
  struct Fetch {
    using type = typename ns_class::FetchImpl<
        typename ns_class::remove_cv<T>::type>::type;
  };

  Class(const Char *name, const Class *superClass, PNewInstance instance);
  ~Class();

  template <typename T>
  static String getName() {
    return ns_class::Helper<typename Fetch<T>::type>::getName();
  }

  static Int max_limits();
  static Int maxIndex() { return s_maxIndex; }
  Int index() const { return _index; }
  const String &getName() const { return _name; }
  const Class &getSuperClass() const { return *_superClass; }
  Boolean hasSuper() const;
  Boolean isBase(const Class &cls) const;

  Boolean isEnum() const { return _isEnum; }
  Boolean isMultiEnum() const;
  Int getEnum(const String &name) const;

  operator Int() const { return _index; }

  static const Class &forName(const String &name);
  template <typename T>
  static const Class &forType() {
    using type = typename Fetch<T>::type;
    return forTypeImpl<type, std::is_base_of<Object, type>::value>::value();
  }

  const Field &getField(const String &name) const;

  template <typename FUN>
  void foreach_fields(FUN fun) const {
    for (std::map<String, const Field *>::const_iterator iter = _fields.begin();
         iter != _fields.end(); ++iter) {
      fun(iter->second);
    }
  }

  const Method &getMethod(const String &name) const;

  Boolean operator==(const Class &rhs) const { return this == &rhs; }
  Boolean operator!=(const Class &rhs) const { return !(*this == rhs); }
  Boolean operator<(const Class &rhs) const { return this < &rhs; }
  Boolean operator>(const Class &rhs) const { return rhs < *this; }
  Boolean operator<=(const Class &rhs) const { return !(*this > rhs); }
  Boolean operator>=(const Class &rhs) const { return !(*this < rhs); }

  void *newInstance() const { return (*_instance)(); }

 private:
  void addField(const Field *field);
  void addMethod(const Method *method);

  friend class Object;
  friend class DtoBase;
  friend class EntityObject;
  friend class EnumHelper;
  template <typename, Boolean>
  friend struct forTypeImpl;
  friend struct __register_field__;
  friend struct __register_method__;

 private:
  static Int s_maxIndex;
  Boolean _isEnum;
  Int _index;
  const EnumHelper *_enumHelper;
  const Class *_superClass;
  PNewInstance _instance;
  String _name;

  std::map<String, const Field *> _fields;
  std::map<String, const Method *> _methods;
};
CORE_API const std::map<String, const Class *const> &geminiAfxEntityClasses();
CORE_API const std::map<String, const Class *const>
    &geminiAfxControllerClasses();

template <class T>
class Property {
 protected:
  typedef T value_type;
  typedef typename std::conditional<sizeof(T) <= 8, value_type,
                                    const value_type &>::type const_reference;

  Property() : _value() {}
  Property(const_reference val) : _value(val) {}
  ~Property() {}
  Property &operator=(const_reference val) {
    _value = val;
    return *this;
  }
  operator const_reference() { return _value; }

 private:
  value_type _value;
};
template <>
class Property<String> {
 protected:
  typedef String value_type;
  typedef value_type const_reference;

  Property() : _value(nullptr) {}
  Property(const_reference val) : _value(new Char[val.size()]) {}
  ~Property() {
    if (_value != nullptr) delete[] _value;
  }
  Property &operator=(const_reference val) {
    if (_value != nullptr) {
      delete[] _value;
      _value = nullptr;
    }

    _value = new Char[val.size()];
    std::memcpy(_value, val.c_str(), val.size());
    return *this;
  }

  operator const_reference() { return _value; }

 private:
  Char *_value;
};
class IList;
enum class RefType { Entity, Vector, List, Set };
class CORE_API PropertyRefHelp {
 public:
  static SmartPtr<EntityObject> get(const EntityObject *entity, Int sign);
  static void set(EntityObject *entity, Int sign,
                  const SmartPtr<EntityObject> &relaEntity);
  static const IList &getList(const EntityObject *entity, Int sign);
};
template <class T, RefType Type>
class PropertyRef {
 public:
  typedef const IList &const_reference;
  typedef const IList *const_pointer;
  typedef T value_type;

 protected:
  PropertyRef() {}
  ~PropertyRef() {}

  const_reference get(const EntityObject *entity, Int sign) {
    // return *((const IList*)(entity->_relations[sign]));
    return PropertyRefHelp::getList(entity, sign);
  }
};
template <class T>
class PropertyRef<T, RefType::Entity> {
 public:
  typedef SmartPtr<T> const_reference;
  typedef T value_type;

 protected:
  PropertyRef() {}
  ~PropertyRef() {}

  const_reference get(EntityObject *entity, Int sign) {
    return PropertyRefHelp::get(entity, sign);
  }

  void set(EntityObject *entity, Int sign, const_reference val) {
    PropertyRefHelp::set(entity, sign, val);
  }
};

template <class T>
class Sign {
 public:
  static Int index;
};
template <class T>
Int Sign<T>::index = 0;

class CORE_API EnumHelper {
 public:
  template <typename T>
  struct Register {
    Register(const Char *enumTypes) {
      const Class &cls = Class::forType<T>();
      static EnumHelper helper(cls);
      helper.SplitEnumString(enumTypes);
      const_cast<Class &>(cls)._enumHelper = &helper;
    }
  };

 public:
  EnumHelper(const Class &cls) : _class(cls) {}
  ~EnumHelper() {}

  const Class &getClass() const { return _class; }
  Int valueOf(const String &value) const;

 private:
  void SplitEnumString(const char *str);

 private:
  const Class &_class;
  std::map<String, Int> _info;
};

#define DECLARE_CLASS(CLASS_NAME, SUPER_CLASS_NAME)                           \
 private:                                                                     \
  typedef CLASS_NAME ClassType;                                               \
  static void *create() { return new CLASS_NAME; }                            \
  static const gemini::Class _class;                                          \
                                                                              \
 protected:                                                                   \
  CLASS_NAME() {}                                                             \
  static gemini::Int s_index;                                                 \
  virtual gemini::Int signMaxIndex() override { return ClassType::s_index; }  \
                                                                              \
 public:                                                                      \
  typedef gemini::SmartPtr<ClassType> SPtr;                                   \
  typedef gemini::SmartPtr<ClassType, gemini::WeakCounted, gemini::StorageNo> \
      WPtr;                                                                   \
  virtual ~CLASS_NAME() {}                                                    \
  static const gemini::Class &getClassStatic() { return CLASS_NAME::_class; } \
  virtual const gemini::Class &getClass() const override {                    \
    return CLASS_NAME::_class;                                                \
  }

#define DECLARE_ABSTRACT_CLASS(CLASS_NAME, SUPER_CLASS_NAME)                  \
 private:                                                                     \
  typedef CLASS_NAME ClassType;                                               \
  static void *create() { return nullptr; }                                   \
  static const gemini::Class _class;                                          \
                                                                              \
 protected:                                                                   \
  CLASS_NAME() {}                                                             \
  static gemini::Int s_index;                                                 \
  virtual gemini::Int signMaxIndex() override { return ClassType::s_index; }  \
                                                                              \
 public:                                                                      \
  typedef gemini::SmartPtr<ClassType> SPtr;                                   \
  typedef gemini::SmartPtr<ClassType, gemini::WeakCounted, gemini::StorageNo> \
      WPtr;                                                                   \
  virtual ~CLASS_NAME() {}                                                    \
  static const gemini::Class &getClassStatic() { return CLASS_NAME::_class; } \
  virtual const gemini::Class &getClass() const override {                    \
    return CLASS_NAME::_class;                                                \
  }

#define DECLARE_CLASS_IMPL(CLASS_NAME, SUPER_CLASS_NAME)       \
  gemini::Int CLASS_NAME::s_index = SUPER_CLASS_NAME::s_index; \
  const gemini::Class CLASS_NAME::_class(                      \
      #CLASS_NAME, &SUPER_CLASS_NAME::getClassStatic(), create);

#define __OFFSET__(C, M) ((gemini::Long)(&((const C *)1024)->M) - 1024)

#define DECLARE_FIELD(FIELD_TYPE, FIELD_NAME)                        \
 public:                                                             \
  class __field_##FIELD_NAME : public gemini::Property<FIELD_TYPE> { \
    typedef gemini::Property<FIELD_TYPE> base_type;                  \
                                                                     \
   public:                                                           \
    __field_##FIELD_NAME() : base_type() {                           \
      static gemini::__register_field__ reg(                         \
          gemini::Class::forType<FIELD_TYPE>(),                      \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(),    \
          #FIELD_NAME);                                              \
    }                                                                \
    ~__field_##FIELD_NAME() {}                                       \
    __field_##FIELD_NAME &operator=(const_reference val) {           \
      base_type::operator=(val);                                     \
      return *this;                                                  \
    }                                                                \
    operator const_reference() {                                     \
      return base_type::operator const_reference();                  \
    }                                                                \
    const gemini::Field *field() {                                   \
      static const gemini::Field *holder =                           \
          &getClassStatic().getField(#FIELD_NAME);                   \
      return holder;                                                 \
    }                                                                \
  } _##FIELD_NAME;                                                   \
  friend class __field_##FIELD_NAME;

#define DECLARE_ENTITY(CLASS_NAME, FIELD_NAME)                                 \
 public:                                                                       \
  class FIELD_NAME                                                             \
      : public gemini::PropertyRef<CLASS_NAME, gemini::RefType::Entity> {      \
    typedef gemini::PropertyRef<CLASS_NAME, gemini::RefType::Entity>           \
        base_type;                                                             \
                                                                               \
   public:                                                                     \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index());                                                            \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    FIELD_NAME &operator=(const_reference val) {                               \
      base_type::set(cur(), index(), val);                                     \
      return *this;                                                            \
    }                                                                          \
    operator const_reference() { return base_type::get(cur(), index()); }      \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
                                                                               \
   private:                                                                    \
    gemini::EntityObject *cur() {                                              \
      return (gemini::EntityObject *)(((const char *)this) -                   \
                                      __OFFSET__(ClassType, _##FIELD_NAME));   \
    }                                                                          \
  } _##FIELD_NAME;

#define DECLARE_VECTOR(CLASS_NAME, FIELD_NAME)                                 \
 public:                                                                       \
  class FIELD_NAME                                                             \
      : public gemini::PropertyRef<CLASS_NAME, gemini::RefType::Vector> {      \
    typedef gemini::PropertyRef<CLASS_NAME, gemini::RefType::Vector>           \
        base_type;                                                             \
                                                                               \
   public:                                                                     \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index(), true);                                                      \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    operator const_reference() { return base_type::get(cur(), index()); }      \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
                                                                               \
    const_pointer operator->() { return &(const_reference)(*this); }           \
                                                                               \
   private:                                                                    \
    const gemini::EntityObject *cur() {                                        \
      return (                                                                 \
          const gemini::EntityObject *)(((const char *)this) -                 \
                                        __OFFSET__(ClassType, _##FIELD_NAME)); \
    }                                                                          \
  } _##FIELD_NAME;

#define DEFINE_ENUM(enum_type, ...)     \
  enum class enum_type { __VA_ARGS__ }; \
  const gemini::Char gemini_enum_##enum_type[] = #__VA_ARGS__;

#define DEFINE_ENUM_IMPL(enum_type)                                       \
  const gemini::EnumHelper::Register<enum_type> geminiAfxEnum##enum_type( \
      gemini_enum_##enum_type);

}  // namespace gemini
#endif  // GEMINI_Reflect_INCLUDE