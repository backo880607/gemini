#ifndef GEMINI_IBaseService_INCLUDE
#define GEMINI_IBaseService_INCLUDE
#include "../Object.h"

namespace gemini {

namespace service {
class CORE_API Wrap {
 public:
  class Holder {
   public:
    virtual ~Holder() {}
    virtual Holder* clone() const = 0;
    virtual const void* get() const = 0;
  };
  template <typename T>
  class HolderImpl : public Holder {
   public:
    HolderImpl(const T* value) : _value(value) {}
    virtual Holder* clone() const { return new HolderImpl<T>(_value); }
    virtual const void* get() const { return _value; }
    friend class Wrap;
    const T* _value;
  };

 public:
  Wrap(std::nullptr_t) : _holder(nullptr) {}
  template <typename T>
  Wrap(const T* value) {
    _holder = new HolderImpl<T>(value);
  }
  Wrap(const Wrap& rhs) {
    _holder = rhs._holder != nullptr ? rhs._holder->clone() : nullptr;
  }
  ~Wrap() {
    if (_holder == nullptr) delete _holder;
  }

  Wrap& operator=(const Wrap& rhs) {
    Wrap(rhs).swap(*this);
    return *this;
  }

  template <class T>
  const T* cast() {
    return static_cast<HolderImpl<T>*>(_holder)->_value;
  }

  const void* get() const {
    return _holder != nullptr ? _holder->get() : nullptr;
  }

 private:
  void swap(Wrap& rhs) { std::swap(_holder, rhs._holder); }

 private:
  Holder* _holder;
};
extern CORE_API Wrap get_service_interface(const String& iName);

}  // namespace service

template <class T>
class ServiceHelper {
 public:
  ServiceHelper() {
    _service =
        service::get_service_interface(ns_class::getNameImpl(typeid(T).name()))
            .cast<T>();
  }
  ~ServiceHelper() {}

  explicit operator Boolean() const { return _service != nullptr; }
  const T* operator->() const { return _service; }

 private:
  const T* _service;
};

#define SERVICE_INTERFACE_METHOD(CLASS_NAME, METHOD_NAME) \
  virtual gemini::Boolean METHOD_NAME(                    \
      const gemini::SmartPtr<CLASS_NAME>& entity) const = 0;

}  // namespace gemini
#endif  // GEMINI_IBaseService_INCLUDE