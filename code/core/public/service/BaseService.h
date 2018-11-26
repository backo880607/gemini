#ifndef GEMINI_BaseService_INCLUDE
#define GEMINI_BaseService_INCLUDE
#include "IBaseService.h"

namespace gemini {

class CORE_API BaseService : public EntityHelper {};

namespace service {
extern CORE_API void register_service(const String &name,
                                      const BaseService *service);
extern CORE_API void register_interface(const String &name,
                                        const Wrap &service);
}  // namespace service

template <class T, class... I>
class ServiceRegister {
  template <typename... A>
  struct InterfaceHelper {};
  template <class Head, class... Tail>
  struct InterfaceHelper<Head, Tail...> {
    template <class Impl>
    static void registerInterface(const Impl *service) {
      gemini::service::register_interface(
          ns_class::getNameImpl(typeid(Head).name()),
          service::Wrap((const Head *)service));
      InterfaceHelper<Tail...>::registerInterface<Impl>(service);
    }
  };
  template <class Tail>
  struct InterfaceHelper<Tail> {
    template <class Impl>
    static void registerInterface(const Impl *service) {
      gemini::service::register_interface(
          ns_class::getNameImpl(typeid(Tail).name()),
          service::Wrap((const Tail *)service));
    }
  };

 public:
  ServiceRegister() {
    String name = ns_class::getNameImpl(typeid(T).name());
    gemini::service::register_service(name, &_service);
    InterfaceHelper<I...>::registerInterface<T>(&_service);
  }
  ~ServiceRegister() {}

 private:
  T _service;
};

class CORE_API ServiceAutowired {
  ServiceAutowired(const ServiceAutowired &) = delete;
  ServiceAutowired &operator=(const ServiceAutowired &) = delete;

 protected:
  ServiceAutowired(const String &iName);
  virtual ~ServiceAutowired() {}
  friend class ServiceMgr;
  virtual void assign(const void *service) = 0;
};

namespace service {

class callable {
 public:
  virtual Boolean invoke(const BaseService *service,
                         const BaseEntity::SPtr &entity) = 0;
};
template <class SRV, typename FUN>
class callableHolder : public callable {
  FUN _fun;

 public:
  callableHolder(FUN fun) : _fun(fun) {}
  virtual Boolean invoke(const BaseService *service,
                         const BaseEntity::SPtr &entity) override {
    return (((const SRV *)service)->*_fun)(entity);
  }
};
CORE_API void register_service_method_impl(const String &name,
                                           const String &method,
                                           callable *caller);

template <class SRV>
struct __register_service_method__ {
  template <typename FUN>
  __register_service_method__(FUN fun, const String &srvName,
                              const String &methodName) {
    callable *caller = new service::callableHolder<SRV, FUN>(fun);
    register_service_method_impl(srvName, methodName, caller);
  }
};

}  // namespace service

#define SERVICE_AUTOWIRED(I_TYPE, I_NAME)                     \
 public:                                                      \
  class __field_##I_NAME : public gemini::ServiceAutowired {  \
    typedef const I_TYPE *const_reference;                    \
    const_reference _value;                                   \
                                                              \
   public:                                                    \
    __field_##I_NAME() : gemini::ServiceAutowired(#I_TYPE) {} \
    ~__field_##I_NAME() {}                                    \
    const_reference operator->() const { return _value; }     \
    operator const_reference() const { return _value; }       \
                                                              \
   protected:                                                 \
    virtual void assign(const void *service) {                \
      _value = (const_reference)service;                      \
    }                                                         \
  } _##I_NAME;

#define SERVICE_REQUIRED(I_TYPE, I_NAME)                          \
 public:                                                          \
  class __field_##I_NAME {                                        \
    typedef const I_TYPE *const_reference;                        \
    const_reference _value;                                       \
                                                                  \
   public:                                                        \
    __field_##I_NAME() : _value(nullptr) {}                       \
    ~__field_##I_NAME() {}                                        \
    const_reference operator->() {                                \
      sure();                                                     \
      return _value;                                              \
    }                                                             \
    operator const_reference() {                                  \
      sure();                                                     \
      return _value;                                              \
    }                                                             \
                                                                  \
   private:                                                       \
    void sure() {                                                 \
      if (_value == nullptr) {                                    \
        _value = gemini::service::get_service_interface(#I_TYPE); \
      }                                                           \
    }                                                             \
  } _##I_NAME;

#define SERVICE_METHOD(CLASS_NAME, METHOD_NAME)                                \
 private:                                                                      \
  struct __method_##METHOD_NAME {                                              \
    __method_##METHOD_NAME() {                                                 \
      typedef gemini::Boolean (CLASS_NAME##Service::*method_ptr_type)(         \
          const gemini::SmartPtr<CLASS_NAME> &) const;                         \
      method_ptr_type method_ptr = &CLASS_NAME##Service::METHOD_NAME;          \
      static gemini::service::__register_service_method__<CLASS_NAME##Service> \
          reg(method_ptr,                                                      \
              gemini::ns_class::getNameImpl(                                   \
                  typeid(CLASS_NAME##ServiceImpl).name()),                     \
              #METHOD_NAME);                                                   \
    }                                                                          \
  } __method_##METHOD_NAME;                                                    \
                                                                               \
 public:                                                                       \
  virtual gemini::Boolean METHOD_NAME(                                         \
      const gemini::SmartPtr<CLASS_NAME> &entity) const override;

}  // namespace gemini
#endif  // GEMINI_BaseService_INCLUDE