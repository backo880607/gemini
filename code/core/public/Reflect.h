#ifndef GEMINI_Reflect_INCLUDE
#define GEMINI_Reflect_INCLUDE
#include "SmartPtr.h"

namespace gemini {

enum class RefKind { None, Entity, Vector, Sequence, Set };
class Object;
class BaseEntity;
class Class;
class IList;
class CORE_API Field final {
  Field(const Field &) = delete;
  Field &operator=(const Field &) = delete;

 public:
  Field(const Class &type, Long offset, const Class &cls, const Char *name,
        Int index = 0, RefKind refKind = RefKind::None);
  ~Field();

  Boolean isUserDefined() const { return _offset >= 0; }
  RefKind getRefKind() const { return _refKind; }
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
  void set(SmartPtr<Object> object, const Value &value) const {
    return set<Value>(object.rawPointer(), value);
  }

 private:
  Int _index;
  const Class &_type;
  Long _offset;
  const Class &_class;
  String _name;
  RefKind _refKind;
};
struct CORE_API __register_field__ {
  __register_field__(const Class &type, Long offset, const Class &cls,
                     const Char *name, Int index = 0,
                     RefKind refKind = RefKind::None);
};

template <class Value>
Value Field::get(const Object *object) const {
  return *(const __field_wrap__<Value> *)(((const char *)object) + _offset);
}

template <class Value>
void Field::set(Object *object, const Value &value) const {
  *(__field_wrap__<Value> *)(((char *)object) + _offset) = value;
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

struct HelperHolder {
  virtual String get(const SmartPtr<Object> &object, const Field &field) const {
    return "";
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const {}
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const {}
};
template <typename T>
struct Helper : public HelperHolder {
  static void *create() { return new T; }
  static String getName() { return getNameImpl(typeid(T).name()); }

  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return field.get<T>(object).toString();
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<T>(object, T::valueOf(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<T>(target, field.get<T>(src));
  }
};
template <>
struct Helper<void> : public HelperHolder {
  static void *create() { return nullptr; }
  static String getName() { return "void"; }
};
template <>
struct Helper<Boolean> : public HelperHolder {
  static void *create() { return new Boolean(); }
  static String getName() { return "Boolean"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Boolean>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Boolean>(object, StringUtilBase::convert<Boolean>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Boolean>(target, field.get<Boolean>(src));
  }
};
template <>
struct Helper<Char> : public HelperHolder {
  static void *create() { return new Char(); }
  static String getName() { return "Char"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Char>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Char>(object, StringUtilBase::convert<Char>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Char>(target, field.get<Char>(src));
  }
};
template <>
struct Helper<Short> : public HelperHolder {
  static void *create() { return new Short(); }
  static String getName() { return "Short"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Short>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Short>(object, StringUtilBase::convert<Short>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Short>(target, field.get<Short>(src));
  }
};
template <>
struct Helper<Int> : public HelperHolder {
  static void *create() { return new Int(); }
  static String getName() { return "Int"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Int>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Int>(object, StringUtilBase::convert<Int>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Int>(target, field.get<Int>(src));
  }
};
template <>
struct Helper<Long> : public HelperHolder {
  static void *create() { return new Long(); }
  static String getName() { return "Long"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Long>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Long>(object, StringUtilBase::convert<Long>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Long>(target, field.get<Long>(src));
  }
};
template <>
struct Helper<Float> : public HelperHolder {
  static void *create() { return new Float(); }
  static String getName() { return "Float"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Float>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Float>(object, StringUtilBase::convert<Float>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Float>(target, field.get<Float>(src));
  }
};
template <>
struct Helper<Double> : public HelperHolder {
  static void *create() { return new Double(); }
  static String getName() { return "Double"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<Double>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<Double>(object, StringUtilBase::convert<Double>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<Double>(target, field.get<Double>(src));
  }
};
template <>
struct Helper<String> : public HelperHolder {
  static void *create() { return new String(); }
  static String getName() { return "String"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return field.get<String>(object);
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<String>(object, value);
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<String>(target, field.get<String>(src));
  }
};
template <>
struct Helper<ID> : public HelperHolder {
  static void *create() { return new ID(); }
  static String getName() { return "ID"; }
  virtual String get(const SmartPtr<Object> &object,
                     const Field &field) const override {
    return StringUtilBase::format(field.get<ID>(object));
  }
  virtual void set(const SmartPtr<Object> &object, const Field &field,
                   const Char *value) const override {
    field.set<ID>(object, StringUtilBase::convert<ID>(value));
  }
  virtual void swap(const Field &field, const SmartPtr<Object> &src,
                    const SmartPtr<Object> &target) const override {
    field.set<ID>(target, field.get<ID>(src));
  }
};
template <>
struct Helper<IList> : public HelperHolder {
  static void *create() { return nullptr; }
  static String getName() { return "IList"; }
};
template <typename T, Boolean BEnum>
struct HelperEnum : public HelperHolder {
  static void *create() { return new T; }
  static String getName() { return getNameImpl(typeid(T).name()); }
};
template <typename T>
struct HelperEnum<T, false> : public Helper<T> {};

class CORE_API RegisterPrimaryKey {
 public:
  RegisterPrimaryKey(const Class &cls, const String &primary);
  ~RegisterPrimaryKey();
};
}  // namespace ns_class
class Method;
class EnumHelper;
class CORE_API Class final {
  typedef void *(*PNewInstance)();

  template <typename T, Boolean BObject>
  struct forTypeImpl {
    static String getName() { return ns_class::getNameImpl(typeid(T).name()); }
    static const Class &value() { return T::getClassStatic(); }
  };
  template <typename T>
  struct forTypeImpl<T, false> {
    typedef ns_class::HelperEnum<T, std::is_enum<T>::value> helper_type;
    static String getName() { return helper_type::getName(); }
    static const Class &value() {
      static const Class *cls = nullptr;
      if (cls == nullptr) {
        cls = ns_class::getClassByName(getName());
        if (cls == nullptr) {
          static const Class _class(getName().c_str(), nullptr,
                                    helper_type::create, new helper_type());
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

  Class(const Char *name, const Class *superClass, PNewInstance instance,
        ns_class::HelperHolder *holder);
  ~Class();

  template <typename T>
  static String getName() {
    using type = typename Fetch<T>::type;
    return forTypeImpl<type, std::is_base_of<Object, type>::value>::getName();
  }

  static Int max_limits();
  static Int maxIndex() { return s_maxIndex; }
  Int index() const { return _index; }
  const String &getName() const { return _name; }
  const Class &getSuperClass() const { return *_superClass; }
  Boolean hasSuper() const;
  Boolean isBase(const Class &superCls) const;

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

  Boolean operator==(const Class &rhs) const { return this == &rhs; }
  Boolean operator!=(const Class &rhs) const { return !(*this == rhs); }
  Boolean operator<(const Class &rhs) const { return this < &rhs; }
  Boolean operator>(const Class &rhs) const { return rhs < *this; }
  Boolean operator<=(const Class &rhs) const { return !(*this > rhs); }
  Boolean operator>=(const Class &rhs) const { return !(*this < rhs); }

  Boolean canNewInstance() const { return _instance != nullptr; }
  void *newInstance() const { return (*_instance)(); }

  const Field *getField(const String &name) const;

 private:
  void addField(const Field *field);
  void addMethod(const Method *method);

  Boolean hasField(const String &name) const;

  template <typename FUN>
  void foreach_fields(FUN fun) const {
    for (std::map<String, const Field *>::const_iterator iter = _fields.begin();
         iter != _fields.end(); ++iter) {
      fun(*iter->second);
    }
  }

  const std::vector<const Field *> &getKeyFields() const { return _keyFields; }

  const Method *getMethod(const String &name) const;

  friend class Object;
  friend class DtoBase;
  friend class BaseEntity;
  friend class EnumHelper;
  friend class ClassUtil;
  friend class EntityFactory;
  friend class StringUtil;
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
  ns_class::HelperHolder *_holder;
  PNewInstance _instance;
  String _name;

  std::map<String, const Field *> _fields;
  std::map<String, const Method *> _methods;
  std::vector<const Field *> _keyFields;
};
CORE_API const std::map<String, const Class *const> &geminiAfxEntityClasses();
CORE_API const std::map<String, const Class *const>
    &geminiAfxControllerClasses();

template <class T>
class __field_wrap__ {
 public:
  typedef T value_type;
  typedef typename std::conditional<sizeof(T) <= 8, value_type,
                                    const value_type &>::type const_reference;

  __field_wrap__() : _value() {}
  __field_wrap__(const_reference val) : _value(val) {}
  ~__field_wrap__() {}
  __field_wrap__ &operator=(const_reference val) {
    _value = val;
    return *this;
  }
  operator const_reference() const { return _value; }

 private:
  value_type _value;
};
template <>
class __field_wrap__<String> {
 public:
  typedef String value_type;
  typedef value_type const_reference;

  __field_wrap__() : _value(nullptr) {}
  __field_wrap__(const_reference val) : _value(new Char[val.size()]) {}
  ~__field_wrap__() {
    if (_value != nullptr) delete[] _value;
  }
  __field_wrap__ &operator=(const_reference val) {
    if (_value != nullptr) {
      delete[] _value;
      _value = nullptr;
    }

    const std::size_t size = val.size();
    _value = new Char[size + 1];
    std::memcpy(_value, val.c_str(), size);
    _value[size] = '\0';
    return *this;
  }

  operator const_reference() const { return _value != nullptr ? _value : ""; }

 private:
  Char *_value;
};
class IList;
class CORE_API FieldRefWrapHelper {
 public:
  static SmartPtr<BaseEntity> get(const BaseEntity *entity, Int sign);
  static void set(BaseEntity *entity, Int sign,
                  const SmartPtr<BaseEntity> &relaEntity);
  static const IList &getList(const BaseEntity *entity, Int sign);
};
template <Boolean IsList>
class __field_ref_wrap__ {
 public:
  typedef const IList &const_reference;
  typedef const IList *const_pointer;

 protected:
  __field_ref_wrap__() {}
  ~__field_ref_wrap__() {}

  const_reference get(const BaseEntity *entity, Int sign) {
    return FieldRefWrapHelper::getList(entity, sign);
  }
};
template <>
class __field_ref_wrap__<false> {
 protected:
  __field_ref_wrap__() {}
  ~__field_ref_wrap__() {}

  SmartPtr<BaseEntity> get(BaseEntity *entity, Int sign) {
    return FieldRefWrapHelper::get(entity, sign);
  }

  void set(BaseEntity *entity, Int sign, const SmartPtr<BaseEntity> &val) {
    FieldRefWrapHelper::set(entity, sign, val);
  }
};

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
      #CLASS_NAME, &SUPER_CLASS_NAME::getClassStatic(), create, nullptr);

#define __OFFSET__(C, M) ((gemini::Long)(&((const C *)1024)->M) - 1024)

#define DECLARE_FIELD(FIELD_TYPE, FIELD_NAME)                              \
 public:                                                                   \
  class __field_##FIELD_NAME : public gemini::__field_wrap__<FIELD_TYPE> { \
    typedef gemini::__field_wrap__<FIELD_TYPE> base_type;                  \
                                                                           \
   public:                                                                 \
    __field_##FIELD_NAME() : base_type() {                                 \
      static gemini::__register_field__ reg(                               \
          gemini::Class::forType<FIELD_TYPE>(),                            \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(),          \
          #FIELD_NAME);                                                    \
    }                                                                      \
    ~__field_##FIELD_NAME() {}                                             \
    __field_##FIELD_NAME &operator=(const_reference val) {                 \
      base_type::operator=(val);                                           \
      return *this;                                                        \
    }                                                                      \
    const_reference operator()() {                                         \
      return base_type::operator const_reference();                        \
    }                                                                      \
    const gemini::Field &field() {                                         \
      static const gemini::Field &holder =                                 \
          *getClassStatic().getField(#FIELD_NAME);                         \
      return holder;                                                       \
    }                                                                      \
  } _##FIELD_NAME;                                                         \
  friend class __field_##FIELD_NAME;

#define DECLARE_ENTITY(CLASS_NAME, FIELD_NAME)                                 \
 public:                                                                       \
  class FIELD_NAME : public gemini::__field_ref_wrap__<false> {                \
    typedef gemini::__field_ref_wrap__<false> base_type;                       \
                                                                               \
   public:                                                                     \
    typedef gemini::SmartPtr<CLASS_NAME> const_reference;                      \
    typedef CLASS_NAME value_type;                                             \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index(), gemini::RefKind::Entity);                                   \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    FIELD_NAME &operator=(const_reference val) {                               \
      base_type::set(cur(), index(), val);                                     \
      return *this;                                                            \
    }                                                                          \
    const_reference operator()() { return base_type::get(cur(), index()); }    \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
    const gemini::Field &field() {                                             \
      static const gemini::Field &holder =                                     \
          *getClassStatic().getField(#FIELD_NAME);                             \
      return holder;                                                           \
    }                                                                          \
                                                                               \
   private:                                                                    \
    gemini::BaseEntity *cur() {                                                \
      return (gemini::BaseEntity *)(((const char *)this) -                     \
                                    __OFFSET__(ClassType, _##FIELD_NAME));     \
    }                                                                          \
  } _##FIELD_NAME;

#define DECLARE_VECTOR(CLASS_NAME, FIELD_NAME)                                 \
 public:                                                                       \
  class FIELD_NAME : public gemini::__field_ref_wrap__<true> {                 \
    typedef gemini::__field_ref_wrap__<true> base_type;                        \
                                                                               \
   public:                                                                     \
    typedef CLASS_NAME value_type;                                             \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index(), gemini::RefKind::Vector);                                   \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    const_reference operator()() { return base_type::get(cur(), index()); }    \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
    const gemini::Field &field() {                                             \
      static const gemini::Field &holder =                                     \
          *getClassStatic().getField(#FIELD_NAME);                             \
      return holder;                                                           \
    }                                                                          \
                                                                               \
   private:                                                                    \
    const gemini::BaseEntity *cur() {                                          \
      return (                                                                 \
          const gemini::BaseEntity *)(((const char *)this) -                   \
                                      __OFFSET__(ClassType, _##FIELD_NAME));   \
    }                                                                          \
  } _##FIELD_NAME;

#define DECLARE_SEQUENCE(CLASS_NAME, FIELD_NAME)                               \
 public:                                                                       \
  class FIELD_NAME : public gemini::__field_ref_wrap__<true> {                 \
    typedef gemini::__field_ref_wrap__<true> base_type;                        \
                                                                               \
   public:                                                                     \
    typedef CLASS_NAME value_type;                                             \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index(), gemini::RefKind::Sequence);                                 \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    const_reference operator()() { return base_type::get(cur(), index()); }    \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
    const gemini::Field &field() {                                             \
      static const gemini::Field &holder =                                     \
          *getClassStatic().getField(#FIELD_NAME);                             \
      return holder;                                                           \
    }                                                                          \
                                                                               \
   private:                                                                    \
    const gemini::BaseEntity *cur() {                                          \
      return (                                                                 \
          const gemini::BaseEntity *)(((const char *)this) -                   \
                                      __OFFSET__(ClassType, _##FIELD_NAME));   \
    }                                                                          \
  } _##FIELD_NAME;

#define DECLARE_SET(CLASS_NAME, FIELD_NAME)                                    \
 public:                                                                       \
  class FIELD_NAME : public gemini::__field_ref_wrap__<true> {                 \
    typedef gemini::__field_ref_wrap__<true> base_type;                        \
                                                                               \
   public:                                                                     \
    typedef CLASS_NAME value_type;                                             \
    FIELD_NAME() : base_type() {                                               \
      index();                                                                 \
      static gemini::__register_field__ reg(                                   \
          gemini::Class::forName(#CLASS_NAME),                                 \
          __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, \
          index(), gemini::RefKind::Set);                                      \
    }                                                                          \
    ~FIELD_NAME() {}                                                           \
    const_reference operator()() { return base_type::get(cur(), index()); }    \
    static gemini::Int index() {                                               \
      static const gemini::Int temp = ClassType::s_index++;                    \
      return temp;                                                             \
    }                                                                          \
    const gemini::Field &field() {                                             \
      static const gemini::Field &holder =                                     \
          *getClassStatic().getField(#FIELD_NAME);                             \
      return holder;                                                           \
    }                                                                          \
                                                                               \
   private:                                                                    \
    const gemini::BaseEntity *cur() {                                          \
      return (                                                                 \
          const gemini::BaseEntity *)(((const char *)this) -                   \
                                      __OFFSET__(ClassType, _##FIELD_NAME));   \
    }                                                                          \
  } _##FIELD_NAME;

#define DECLARE_PRIMARY(CLASS_NAME, ...)           \
  gemini::ns_class::RegisterPrimaryKey             \
      gemini_afx_register_primarykey_##CLASS_NAME( \
          CLASS_NAME::getClassStatic(), #__VA_ARGS__);

#define DEFINE_ENUM(enum_type, ...)     \
  enum class enum_type { __VA_ARGS__ }; \
  const gemini::Char gemini_enum_##enum_type[] = #__VA_ARGS__;

#define DEFINE_ENUM_IMPL(enum_type)                                       \
  const gemini::EnumHelper::Register<enum_type> geminiAfxEnum##enum_type( \
      gemini_enum_##enum_type);

}  // namespace gemini
#endif  // GEMINI_Reflect_INCLUDE