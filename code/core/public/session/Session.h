#pragma once
#include "../Object.h"

namespace gemini {

class Security;
class CORE_API Session : public EntityObject {
  class PlaceHolder {
   public:
    PlaceHolder() {}
    virtual ~PlaceHolder() {}
    virtual const std::type_info &type() const = 0;
  };
  template <typename T>
  class Holder : public PlaceHolder {
   public:
    static Int index;
    Holder() {}
    virtual ~Holder() {}
    virtual const std::type_info &type() const { return typeid(T); }

   private:
    friend class Session;
    T _value;
  };

  DECLARE_CLASS(Session, EntityObject)

  DECLARE_FIELD(DateTime, startTime)
  DECLARE_FIELD(DateTime, stopTime)
  DECLARE_FIELD(DateTime, accessTime)
  DECLARE_FIELD(Long, timeout)
  DECLARE_FIELD(Boolean, expired)
  DECLARE_FIELD(String, host)

  template <class T>
  T &get() {
    if (0 == Holder<T>::index) {
      const std::type_info &typeinfo = typeid(T);
      Int i = 0;
      const Int len = (Int)_holders.size();
      for (; i < len; ++i) {
        if (_holders[i]->type() == typeinfo) break;
      }
      if (i == len) {
        _holders.push_back(new Holder<T>());
      }
      Holder<T>::index = i;
    }

    return ((Holder<T> *)_holders[Holder<T>::index])->_value;
  }

  std::shared_ptr<Security> getSecurity() { return _security; }
  void setSecurity(const std::shared_ptr<Security> &security) {
    _security = security;
  }

 private:
  std::vector<PlaceHolder *> _holders;
  std::shared_ptr<Security> _security;
};
template <class T>
Int Session::Holder<T>::index = 0;

}  // namespace gemini