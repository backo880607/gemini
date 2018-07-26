#ifndef GEMINI_SmartPtr_INCLUDE
#define GEMINI_SmartPtr_INCLUDE
#include "Common.h"

namespace gemini {

template <typename T>
class StoragePool;

template <typename T>
class StorageSystem;

template <typename T>
class StorageNo {
 public:
  typedef T value_type;
  typedef T *pointer;
  typedef EmptyType extract_type;
  typedef const T *const_pointer;
  typedef T *stored_type;

  StorageNo() : _pT(nullptr) {}
  StorageNo(const StorageNo &) : _pT(nullptr) {}
  template <class U>
  StorageNo(const StorageNo<U> &) : _pT(nullptr) {}
  template <class U>
  StorageNo(const StoragePool<U> &) : _pT(nullptr) {}
  template <class U>
  StorageNo(const StorageSystem<U> &) : _pT(nullptr) {}

  void create() {}
  void destroy() {}

  extract_type operator->() const { return _pT; }
  void swap(StorageNo &rhs) { std::swap(_pT, rhs._pT); }

  friend inline pointer getImpl(const StorageNo &sp) { return sp._pT; }
  friend inline const stored_type &getImplRef(const StorageNo &sp) {
    return sp._pT;
  }
  friend inline stored_type &getImplRef(StorageNo &sp) { return sp._pT; }

 private:
  stored_type _pT;
};

template <typename T>
class StorageSystem {
 public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T *stored_type;

  StorageSystem() : _pT(nullptr) {}
  template <class U>
  StorageSystem(const StorageSystem<U> &) : _pT(nullptr) {}
  template <class U>
  StorageSystem(const StorageNo<U> &) : _pT(nullptr) {}
  template <class U>
  StorageSystem(const StoragePool<U> &) : _pT(nullptr) {}
  ~StorageSystem() {}

  void create() { _pT = new value_type; }
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
  void destroy() {
    delete (void *)_pT;
    _pT = nullptr;
  }
#elif GEMINI_OS == GEMINI_OS_LINUX
  void destroy() {
    delete _pT;
    _pT = nullptr;
  }
#elif GEMINI_OS == GEMINI_OS_MAC_OS_X
  void destroy() {
    delete _pT;
    _pT = nullptr;
  }
#endif

  pointer operator->() const { return _pT; }
  pointer operator->() { return _pT; }
  void swap(StorageSystem &rhs) { std::swap(_pT, rhs._pT); }

  friend inline pointer getImpl(const StorageSystem &sp) { return sp._pT; }
  friend inline const stored_type &getImplRef(const StorageSystem &sp) {
    return sp._pT;
  }
  friend inline stored_type &getImplRef(StorageSystem &sp) { return sp._pT; }

 private:
  stored_type _pT;
};

class CORE_API Counter {
  typedef MT_Int value_type;

 private:
  Counter(Counter const &) = delete;
  Counter &operator=(Counter const &) = delete;

 public:
  Counter() {
    _nShareCount = 0;
    _nWeakCount = 0;
  }

  void shareAdd() { ++_nShareCount; }
  Boolean shareRelease() { return (--_nShareCount) == 0; }
  Boolean checkShareCount() const { return _nShareCount != 0; }

  void weakAdd() { ++_nWeakCount; }
  Boolean weakRelease() { return (--_nWeakCount) == 0; }

 private:
  value_type _nShareCount;
  value_type _nWeakCount;
};

template <typename P>
class WeakCounted;

template <typename P>
class RefCounted {
  typedef Counter counter_type;
  template <typename P1>
  friend class WeakCounted;

 public:
  RefCounted() : _pCount(nullptr) {}
  RefCounted(const RefCounted &rhs) : _pCount(rhs._pCount) {}
  template <typename P1>
  RefCounted(const WeakCounted<P1> &rhs)
      : _pCount(reinterpret_cast<const WeakCounted<P1> &>(rhs).validCounter()) {
  }
  template <typename P1>
  RefCounted(const RefCounted<P1> &rhs)
      : _pCount(reinterpret_cast<const RefCounted &>(rhs)._pCount) {}

  void newCount() {
    _pCount = new counter_type();
    assert(_pCount != nullptr);
    _pCount->weakAdd();
  }

  P clone(const P &val) {
    if (_pCount) _pCount->shareAdd();
    return _pCount ? val : nullptr;
  }

  Boolean release(const P &) {
    if (_pCount && _pCount->shareRelease()) {
      if (_pCount->weakRelease()) {
        delete _pCount;
        _pCount = nullptr;
      }
      return true;
    }

    return false;
  }

  P validImpl(const P &val) const { return val; }
  void swap(RefCounted &rhs) { std::swap(_pCount, rhs._pCount); }

  template <typename P1>
  friend class WeakCounted;
  template <typename P1>
  friend class RefCounted;

 private:
  counter_type *_pCount;
};

template <typename P>
class PluginCounted {
 public:
  PluginCounted() {}
  template <typename P1>
  PluginCounted(const PluginCounted<P1> &rhs) {}
  template <typename P1>
  PluginCounted(const RefCounted<P1> &rhs) {}

  void newCount() {}

  P clone(const P &val) {
    if (val != nullptr) val->addRef();
    return val;
  }

  Boolean release(const P &val) {
    if (val != nullptr) return val->release();
    return false;
  }

  P validImpl(const P &val) const { return val; }

  void swap(PluginCounted &rhs) {}
};

template <typename P>
class WeakCounted {
  typedef Counter counter_type;

 public:
  WeakCounted() : _pCount(nullptr) {}
  WeakCounted(const WeakCounted &rhs) : _pCount(rhs._pCount) {}
  template <typename P1>
  WeakCounted(const RefCounted<P1> &rhs)
      : _pCount(reinterpret_cast<const WeakCounted &>(rhs)._pCount) {}
  template <typename P1>
  WeakCounted(const WeakCounted<P1> &rhs)
      : _pCount(reinterpret_cast<const WeakCounted &>(rhs)._pCount) {}

  void newCount() {}

  P clone(const P &val) {
    if (_pCount) _pCount->weakAdd();
    return val;
  }

  Boolean release(const P &) {
    if (_pCount && _pCount->weakRelease()) {
      delete _pCount;
      _pCount = nullptr;
    }

    return false;
  }

  counter_type *validCounter() const {
    if (_pCount && _pCount->checkShareCount()) return _pCount;

    return nullptr;
  }

  P validImpl(const P &val) const {
    if (_pCount && _pCount->checkShareCount()) return val;

    return nullptr;
  }
  void swap(WeakCounted &rhs) { std::swap(_pCount, rhs._pCount); }

  template <typename P1>
  friend class RefCounted;

 private:
  counter_type *_pCount;
};

template <typename T, template <typename> class OwnershipPolicy = RefCounted,
          template <class> class MemoryPolicy = StorageSystem>
class SmartPtr : public MemoryPolicy<T>,
                 public OwnershipPolicy<typename MemoryPolicy<T>::pointer> {
  typedef MemoryPolicy<T> MP;
  typedef OwnershipPolicy<typename MP::pointer> OP;

 public:
  typedef typename MP::pointer pointer;
  typedef typename MP::const_pointer const_pointer;
  typedef typename MP::value_type value_type;

  void wrapRawPointer(pointer p) {
    OP::newCount();
    getImplRef(*this) = OP::clone(p);
  }

 public:
  SmartPtr() {}

  explicit SmartPtr(Boolean bNew) {
    if (bNew) {
      MP::create();
      OP::newCount();
      OP::clone(getImplRef(*this));
    }
  }
  SmartPtr(std::nullptr_t rhs) {
    rhs = nullptr;
    SmartPtr temp;
    temp.swap(*this);
  }

  SmartPtr(const SmartPtr &rhs) : MP(rhs), OP(rhs) {
    getImplRef(*this) = OP::clone(getImplRef(rhs));
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  SmartPtr(const SmartPtr<T1, OP1, MP1> &rhs) : MP(rhs), OP(rhs) {
    getImplRef(*this) = OP::clone(reinterpret_cast<pointer>(getImpl(rhs)));
  }

  SmartPtr &operator=(const SmartPtr &rhs) {
    SmartPtr temp(rhs);
    temp.swap(*this);
    return *this;
  }

  SmartPtr &operator=(std::nullptr_t rhs) {
    rhs = nullptr;
    SmartPtr temp;
    temp.swap(*this);
    return *this;
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  SmartPtr &operator=(const SmartPtr<T1, OP1, MP1> &rhs) {
    SmartPtr temp(rhs);
    temp.swap(*this);
    return *this;
  }

  ~SmartPtr() {
    if (OP::release(getImpl(*reinterpret_cast<MP *>(this)))) MP::destroy();
  }

  inline friend Boolean operator==(const SmartPtr &lhs, const_pointer rhs) {
    return lhs.validImpl(getImpl(lhs)) == rhs;
  }

  inline friend Boolean operator==(const_pointer lhs, const SmartPtr &rhs) {
    return rhs == lhs;
  }

  inline friend Boolean operator!=(const SmartPtr &lhs, const_pointer rhs) {
    return !(lhs == rhs);
  }

  inline friend Boolean operator!=(const_pointer lhs, const SmartPtr &rhs) {
    return rhs != lhs;
  }

  inline friend Boolean operator<(const SmartPtr &lhs, const_pointer rhs) {
    return lhs.validImpl(getImpl(lhs)) < rhs;
  }

  inline friend Boolean operator<(const_pointer lhs, const SmartPtr &rhs) {
    return lhs < rhs.validImpl(getImpl(rhs));
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  inline Boolean operator==(const SmartPtr<T1, OP1, MP1> &rhs) const {
    return *this == rhs.validImpl(getImpl(rhs));
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  inline Boolean operator!=(const SmartPtr<T1, OP1, MP1> &rhs) const {
    return !(*this == rhs);
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  inline Boolean operator<(const SmartPtr<T1, OP1, MP1> &rhs) const {
    return *this < rhs.validImpl(getImpl(rhs));
  }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  inline bool operator>(const SmartPtr<T1, OP1, MP1> &rhs) const {
    return *this > rhs.validImpl(getImpl(rhs));
  }

  inline Boolean valid() const {
    return OP::validImpl(getImpl(*this)) != nullptr;
  }

  pointer operator->() { return MP::operator->(); }
  pointer operator->() const { return MP::operator->(); }

  ID getID() const { return valid() ? getImpl(*this)->getID() : 0; }

  template <typename T1, template <typename> class OP1,
            template <class> class MP1>
  Boolean compare(const SmartPtr<T1, OP1, MP1> &rhs) const {
    ID result = getID() - rhs.getID();
    return result != 0 ? (result < 0 ? -1 : 1) : 0;
  }

 private:
  pointer rawPointer() { return getImpl(*this); }
  const_pointer rawPointer() const { return getImpl(*this); }

  void swap(SmartPtr &rhs) {
    OP::swap(rhs);
    MP::swap(rhs);
  }

  friend class Field;
  friend class FieldCalculate;
};

}  // namespace gemini
#endif  // GEMINI_SmartPtr_INCLUDE