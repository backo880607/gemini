#ifndef GEMINI_ReflectMethod_INCLUDE
#define GEMINI_ReflectMethod_INCLUDE
#include "Any.h"

namespace gemini {

// root of all callables
struct __callable__ {
  typedef std::vector<const Class *> arg_list_cls;
  virtual ~__callable__() {}
  virtual int get_args_count() const = 0;
  virtual const arg_list_cls &get_args() const = 0;
  virtual const Class &get_ret_cls() const = 0;
  virtual Any invoke(void *object, const std::vector<Any> &params) const = 0;
};

// joins
#define REF_JOIN(X, Y) REF_DO_JOIN(X, Y)
#define REF_DO_JOIN(X, Y) REF_DO_JOIN2(X, Y)
#define REF_DO_JOIN2(X, Y) X##Y

#define __IF0(E)
#define __IF1(E) _##E
#define __IF2(E) _##E
#define __IF3(E) _##E
#define __IF4(E) _##E
#define __IF5(E) _##E
#define __IF6(E) _##E
#define __IF7(E) _##E
#define __IF8(E) _##E
#define __IF9(E) _##E
#define __IF10(E) _##E
#define __IF11(E) _##E
#define __IF12(E) _##E
#define __IF13(E) _##E
#define __IF14(E) _##E
#define __IF15(E) _##E
#define __IF16(E) _##E
#define __IF17(E) _##E
#define __IF18(E) _##E
#define __IF19(E) _##E
#define __IF20(E) _##E
#define __IF(N, E) __IF##N(E)

// repeaters
#define __REPEAT0(M, C, S)
#define __REPEAT1(M, C, S) _##S M(1)
#define __REPEAT2(M, C, S) \
  __REPEAT1(M, C, S)       \
  _##C M(2)
#define __REPEAT3(M, C, S) \
  __REPEAT2(M, C, S)       \
  _##C M(3)
#define __REPEAT4(M, C, S) \
  __REPEAT3(M, C, S)       \
  _##C M(4)
#define __REPEAT5(M, C, S) \
  __REPEAT4(M, C, S)       \
  _##C M(5)
#define __REPEAT6(M, C, S) \
  __REPEAT5(M, C, S)       \
  _##C M(6)
#define __REPEAT7(M, C, S) \
  __REPEAT6(M, C, S)       \
  _##C M(7)
#define __REPEAT8(M, C, S) \
  __REPEAT7(M, C, S)       \
  _##C M(8)
#define __REPEAT9(M, C, S) \
  __REPEAT8(M, C, S)       \
  _##C M(9)
#define __REPEAT10(M, C, S) \
  __REPEAT9(M, C, S)        \
  _##C M(10)
#define __REPEAT11(M, C, S) \
  __REPEAT10(M, C, S)       \
  _##C M(11)
#define __REPEAT12(M, C, S) \
  __REPEAT11(M, C, S)       \
  _##C M(12)
#define __REPEAT13(M, C, S) \
  __REPEAT12(M, C, S)       \
  _##C M(13)
#define __REPEAT14(M, C, S) \
  __REPEAT13(M, C, S)       \
  _##C M(14)
#define __REPEAT15(M, C, S) \
  __REPEAT14(M, C, S)       \
  _##C M(15)
#define __REPEAT16(M, C, S) \
  __REPEAT15(M, C, S)       \
  _##C M(16)
#define __REPEAT17(M, C, S) \
  __REPEAT16(M, C, S)       \
  _##C M(17)
#define __REPEAT18(M, C, S) \
  __REPEAT17(M, C, S)       \
  _##C M(18)
#define __REPEAT19(M, C, S) \
  __REPEAT18(M, C, S)       \
  _##C M(19)
#define __REPEAT20(M, C, S) \
  __REPEAT19(M, C, S)       \
  _##C M(20)
#define __REPEAT(N, M, C, S, E) __REPEAT##N(M, C, S) __IF##N(E)

#define ___NOTHING__
#define ___COMMA__ ,
#define ___SEMICOLON__ ;
#define __TYPE_ARG__(N) T##N
#define __TEMPLATE_ARG__(N) class T##N
#define __ARG__(N) T##N t##N
#define __PARAM__(N) t##N
#define __PARAM_PTR__(N) &__PARAM__(N)
#define ___TEMPLATE_DECLARE_BEGIN__ template <
#define ___TEMPLATE_BEGIN__ <
#define ___TEMPLATE_END__ >
#define __NOT_VIRTUAL__

// parameter for generating
#define __TYPE_INFO_ARG__(N) \
  this->args_list.push_back(&Class::forType<__TYPE_ARG__(N)>())

#define __TYPE_CAST_ARG__(N) params[N].cast<__TYPE_ARG__(N)>();

// callable that implements the argument capturing and reporting
#define __CALLABLE__ARGS(N)                                                    \
  template <gemini::Int args_size __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,     \
                                           __COMMA__, __NOTHING__)>            \
  struct __callable_args##N##__ : public __callable__ {                        \
    const Class &ret_cls;                                                      \
    arg_list_cls args_list;                                                    \
    __callable_args##N##__(const Class &ret_id)                                \
        : ret_cls(ret_id), args_list() {                                       \
      __REPEAT(N, __TYPE_INFO_ARG__, __SEMICOLON__, __NOTHING__, __NOTHING__); \
    };                                                                         \
    virtual int get_args_count() const { return args_size; }                   \
    virtual const arg_list_cls &get_args() const { return args_list; }         \
    virtual const Class &get_ret_cls() const { return ret_cls; }               \
  }

// define callables
__CALLABLE__ARGS(0);
__CALLABLE__ARGS(1);
__CALLABLE__ARGS(2);
__CALLABLE__ARGS(3);
__CALLABLE__ARGS(4);
__CALLABLE__ARGS(5);
__CALLABLE__ARGS(6);
__CALLABLE__ARGS(7);
__CALLABLE__ARGS(8);
__CALLABLE__ARGS(9);
__CALLABLE__ARGS(10);
__CALLABLE__ARGS(11);
__CALLABLE__ARGS(12);
__CALLABLE__ARGS(13);
__CALLABLE__ARGS(14);
__CALLABLE__ARGS(15);
__CALLABLE__ARGS(16);
__CALLABLE__ARGS(17);
__CALLABLE__ARGS(18);
__CALLABLE__ARGS(19);
__CALLABLE__ARGS(20);

// callable class macro with return type
#define __CALLABLE__(N)                                                      \
  template <class R, class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,        \
                                      __COMMA__, __NOTHING__)>               \
  struct __callable##N##__                                                   \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                 __COMMA__, __NOTHING__)> {  \
    typedef R (C::*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__,          \
                                        __NOTHING__, __NOTHING__));          \
    MethodType method;                                                       \
    __callable##N##__(MethodType m)                                          \
        : __callable_args##N                                                 \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,             \
                          __NOTHING__)>(Class::forType<R>()),                \
          method(m) {}                                                       \
    R invoke(C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__,            \
                                __NOTHING__)) const {                        \
      return (object->*method)(                                              \
          __REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__));      \
    }                                                                        \
    virtual gemini::Any invoke(void *object,                                 \
                               const std::vector<Any> &params) const {       \
      return (((C *)object)->*method)(__REPEAT(                              \
          N, __TYPE_CAST_ARG__, __COMMA__, __NOTHING__, __NOTHING__));       \
    }                                                                        \
  };

// define callables
__CALLABLE__(0);
__CALLABLE__(1);
__CALLABLE__(2);
__CALLABLE__(3);
__CALLABLE__(4);
__CALLABLE__(5);
__CALLABLE__(6);
__CALLABLE__(7);
__CALLABLE__(8);
__CALLABLE__(9);
__CALLABLE__(10);
__CALLABLE__(11);
__CALLABLE__(12);
__CALLABLE__(13);
__CALLABLE__(14);
__CALLABLE__(15);
__CALLABLE__(16);
__CALLABLE__(17);
__CALLABLE__(18);
__CALLABLE__(19);
__CALLABLE__(20);

// callable class macro with return type and const type
#define __CALLABLE_CONST__(N)                                                \
  template <class R, class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,        \
                                      __COMMA__, __NOTHING__)>               \
  struct __callable_const##N##__                                             \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                 __COMMA__, __NOTHING__)> {  \
    typedef R (C::*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__,          \
                                        __NOTHING__, __NOTHING__)) const;    \
    MethodType method;                                                       \
    __callable_const##N##__(MethodType m)                                    \
        : __callable_args##N                                                 \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,             \
                          __NOTHING__)>(Class::forType<R>()),                \
          method(m) {}                                                       \
    R invoke(C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__,            \
                                __NOTHING__)) const {                        \
      return (object->*method)(                                              \
          __REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__));      \
    }                                                                        \
    virtual gemini::Any invoke(void *object,                                 \
                               const std::vector<Any> &params) const {       \
      return (((C *)object)->*method)(__REPEAT(                              \
          N, __TYPE_CAST_ARG__, __COMMA__, __NOTHING__, __NOTHING__));       \
    }                                                                        \
  };

// define const callables
__CALLABLE_CONST__(0);
__CALLABLE_CONST__(1);
__CALLABLE_CONST__(2);
__CALLABLE_CONST__(3);
__CALLABLE_CONST__(4);
__CALLABLE_CONST__(5);
__CALLABLE_CONST__(6);
__CALLABLE_CONST__(7);
__CALLABLE_CONST__(8);
__CALLABLE_CONST__(9);
__CALLABLE_CONST__(10);
__CALLABLE_CONST__(11);
__CALLABLE_CONST__(12);
__CALLABLE_CONST__(13);
__CALLABLE_CONST__(14);
__CALLABLE_CONST__(15);
__CALLABLE_CONST__(16);
__CALLABLE_CONST__(17);
__CALLABLE_CONST__(18);
__CALLABLE_CONST__(19);
__CALLABLE_CONST__(20);

// callable class macro with void return type
#define __CALLABLE_VOID__(N)                                                 \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,      \
                             __NOTHING__)>                                   \
  struct __callable_void##N##__                                              \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                 __COMMA__, __NOTHING__)> {  \
    typedef void (C::*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__,       \
                                           __NOTHING__, __NOTHING__));       \
    MethodType method;                                                       \
    __callable_void##N##__(MethodType m)                                     \
        : __callable_args##N                                                 \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,             \
                          __NOTHING__)>(Class::forType<void>()),             \
          method(m) {}                                                       \
    void invoke(C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__,         \
                                   __NOTHING__)) const {                     \
      (object->*method)(                                                     \
          __REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__));      \
    }                                                                        \
    virtual gemini::Any invoke(void *object,                                 \
                               const std::vector<Any> &params) const {       \
      return nullptr;                                                        \
    }                                                                        \
  };

// define void callables
__CALLABLE_VOID__(0);
__CALLABLE_VOID__(1);
__CALLABLE_VOID__(2);
__CALLABLE_VOID__(3);
__CALLABLE_VOID__(4);
__CALLABLE_VOID__(5);
__CALLABLE_VOID__(6);
__CALLABLE_VOID__(7);
__CALLABLE_VOID__(8);
__CALLABLE_VOID__(9);
__CALLABLE_VOID__(10);
__CALLABLE_VOID__(11);
__CALLABLE_VOID__(12);
__CALLABLE_VOID__(13);
__CALLABLE_VOID__(14);
__CALLABLE_VOID__(15);
__CALLABLE_VOID__(16);
__CALLABLE_VOID__(17);
__CALLABLE_VOID__(18);
__CALLABLE_VOID__(19);
__CALLABLE_VOID__(20);

// callable class macro with void return type and const type
#define __CALLABLE_CONST_VOID__(N)                                           \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,      \
                             __NOTHING__)>                                   \
  struct __callable_const_void##N##__                                        \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                 __COMMA__, __NOTHING__)> {  \
    typedef void (C::*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__,       \
                                           __NOTHING__, __NOTHING__)) const; \
    MethodType method;                                                       \
    __callable_const_void##N##__(MethodType m)                               \
        : __callable_args##N                                                 \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,             \
                          __NOTHING__)>(Class::forType<void>()),             \
          method(m) {}                                                       \
    void invoke(C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__,         \
                                   __NOTHING__)) const {                     \
      (object->*method)(                                                     \
          __REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__));      \
    }                                                                        \
    virtual gemini::Any invoke(void *object,                                 \
                               const std::vector<Any> &params) const {       \
      return nullptr;                                                        \
    }                                                                        \
  };

// define const void callables
__CALLABLE_CONST_VOID__(0);
__CALLABLE_CONST_VOID__(1);
__CALLABLE_CONST_VOID__(2);
__CALLABLE_CONST_VOID__(3);
__CALLABLE_CONST_VOID__(4);
__CALLABLE_CONST_VOID__(5);
__CALLABLE_CONST_VOID__(6);
__CALLABLE_CONST_VOID__(7);
__CALLABLE_CONST_VOID__(8);
__CALLABLE_CONST_VOID__(9);
__CALLABLE_CONST_VOID__(10);
__CALLABLE_CONST_VOID__(11);
__CALLABLE_CONST_VOID__(12);
__CALLABLE_CONST_VOID__(13);
__CALLABLE_CONST_VOID__(14);
__CALLABLE_CONST_VOID__(15);
__CALLABLE_CONST_VOID__(16);
__CALLABLE_CONST_VOID__(17);
__CALLABLE_CONST_VOID__(18);
__CALLABLE_CONST_VOID__(19);
__CALLABLE_CONST_VOID__(20);

// static callable class macro with return type
#define __STATIC_CALLABLE__(N)                                                \
  template <class R __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,       \
                             __NOTHING__)>                                    \
  struct __static_callable##N##__                                             \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__,  \
                                                 __COMMA__, __NOTHING__)> {   \
    typedef R (*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, \
                                     __NOTHING__));                           \
    MethodType method;                                                        \
    __static_callable##N##__(MethodType m)                                    \
        : __callable_args##N                                                  \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,              \
                          __NOTHING__)>(Class::forType<R>()),                 \
          method(m) {}                                                        \
    R invoke(__REPEAT(N, __ARG__, __COMMA__, __NOTHING__,                     \
                      __NOTHING__)) const {                                   \
      return (*method)(                                                       \
          __REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__));       \
    }                                                                         \
    virtual gemini::Any invoke(void *object,                                  \
                               const std::vector<Any> &params) const {        \
      return (*method)(__REPEAT(N, __TYPE_CAST_ARG__, __COMMA__, __NOTHING__, \
                                __NOTHING__));                                \
    }                                                                         \
  };

// static callable classes
__STATIC_CALLABLE__(0)
__STATIC_CALLABLE__(1)
__STATIC_CALLABLE__(2)
__STATIC_CALLABLE__(3)
__STATIC_CALLABLE__(4)
__STATIC_CALLABLE__(5)
__STATIC_CALLABLE__(6)
__STATIC_CALLABLE__(7)
__STATIC_CALLABLE__(8)
__STATIC_CALLABLE__(9)
__STATIC_CALLABLE__(10)
__STATIC_CALLABLE__(11)
__STATIC_CALLABLE__(12)
__STATIC_CALLABLE__(13)
__STATIC_CALLABLE__(14)
__STATIC_CALLABLE__(15)
__STATIC_CALLABLE__(16)
__STATIC_CALLABLE__(17)
__STATIC_CALLABLE__(18)
__STATIC_CALLABLE__(19)
__STATIC_CALLABLE__(20)

// internal class for registering a method
struct CORE_API __register_method__ {
  __register_method__(__callable__ *cb, const Class &cls,
                      const Class &returnCls, const char *name,
                      const char *args, const char *virt);
};

// internal class for registering a static method
struct CORE_API __register_static_method__ {
  __register_static_method__(__callable__ *cb, const Class *pclass,
                             const char *type, const char *name,
                             const char *args);
};

// void version
#define __STATIC_CALLABLE_VOID__(N)                                           \
  __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __TEMPLATE_DECLARE_BEGIN__,        \
           __TEMPLATE_END__)                                                  \
  struct __static_callable_void##N##__                                        \
      : public __callable_args##N##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__,  \
                                                 __COMMA__, __NOTHING__)> {   \
    typedef void (*MethodType)(__REPEAT(N, __TYPE_ARG__, __COMMA__,           \
                                        __NOTHING__, __NOTHING__));           \
    MethodType method;                                                        \
    __static_callable_void##N##__(MethodType m)                               \
        : __callable_args##N                                                  \
          ##__<N __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__,              \
                          __NOTHING__)>(gemini::Class::forType<void>()),      \
          method(m) {}                                                        \
    void invoke(__REPEAT(N, __ARG__, __COMMA__, __NOTHING__,                  \
                         __NOTHING__)) const {                                \
      (*method)(__REPEAT(N, __PARAM__, __COMMA__, __NOTHING__, __NOTHING__)); \
    }                                                                         \
    virtual gemini::Any invoke(void *object,                                  \
                               const std::vector<Any> &params) const {        \
      (*method)(__REPEAT(N, __TYPE_CAST_ARG__, __COMMA__, __NOTHING__,        \
                         __NOTHING__));                                       \
      return nullptr;                                                         \
    }                                                                         \
  };

__STATIC_CALLABLE_VOID__(0)
__STATIC_CALLABLE_VOID__(1)
__STATIC_CALLABLE_VOID__(2)
__STATIC_CALLABLE_VOID__(3)
__STATIC_CALLABLE_VOID__(4)
__STATIC_CALLABLE_VOID__(5)
__STATIC_CALLABLE_VOID__(6)
__STATIC_CALLABLE_VOID__(7)
__STATIC_CALLABLE_VOID__(8)
__STATIC_CALLABLE_VOID__(9)
__STATIC_CALLABLE_VOID__(10)
__STATIC_CALLABLE_VOID__(11)
__STATIC_CALLABLE_VOID__(12)
__STATIC_CALLABLE_VOID__(13)
__STATIC_CALLABLE_VOID__(14)
__STATIC_CALLABLE_VOID__(15)
__STATIC_CALLABLE_VOID__(16)
__STATIC_CALLABLE_VOID__(17)
__STATIC_CALLABLE_VOID__(18)
__STATIC_CALLABLE_VOID__(19)
__STATIC_CALLABLE_VOID__(20)

// macro of a inline method that accepts a method pointer and creates a callable
// for it
#define __CREATE_CALLABLE__(N)                                               \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,      \
                             __NOTHING__)>                                   \
  static inline __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__, __COMMA__,  \
                                                __COMMA__, __NOTHING__)>     \
      *create(R (C::*method)(                                                \
          __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) { \
    return new __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__, __COMMA__,   \
                                               __COMMA__, __NOTHING__)>(     \
        method);                                                             \
  }

// macro of a inline method that accepts a method pointer and creates a const
// callable for it
#define __CREATE_CALLABLE_CONST__(N)                                           \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,        \
                             __NOTHING__)>                                     \
  static inline __callable_const##N##__<                                       \
      R, C __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>       \
      *create(R (C::*method)(__REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, \
                                      __NOTHING__)) const) {                   \
    return new __callable_const##N##__<                                        \
        R, C __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>(    \
        method);                                                               \
  }

// void version
#define __CREATE_CALLABLE_VOID__(N)                                           \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,       \
                             __NOTHING__)>                                    \
  static inline __callable_void##N##__<C __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                  __COMMA__, __NOTHING__)>    \
      *create(void (C::*method)(                                              \
          __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) {  \
    return new __callable_void##N##__<C __REPEAT(                             \
        N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>(method);         \
  }

// const void version
#define __CREATE_CALLABLE_CONST_VOID__(N)                                    \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,      \
                             __NOTHING__)>                                   \
  static inline __callable_const_void##N##__<C __REPEAT(                     \
      N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>                   \
      *create(void (C::*method)(__REPEAT(N, __TYPE_ARG__, __COMMA__,         \
                                         __NOTHING__, __NOTHING__)) const) { \
    return new __callable_const_void##N##__<C __REPEAT(                      \
        N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>(method);        \
  }

// macro to create a static callable
#define __CREATE_STATIC_CALLABLE__(N)                                        \
  template <class R1 __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,     \
                              __NOTHING__)>                                  \
  static inline __static_callable##N##__<R1 __REPEAT(                        \
      N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>                   \
      *create(R1 (*method)(                                                  \
          __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) { \
    return new __static_callable##N##__<R1 __REPEAT(                         \
        N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>(method);        \
  }

#if 0
//void version for 0 params
#define __CREATE_STATIC_CALLABLE_VOID__0                              \
  static inline __static_callable_void0__ *create(void (*method)()) { \
    return new __static_callable_void0__(method);                     \
  }
#endif

// void version
#define __CREATE_STATIC_CALLABLE_VOID__(N)                                   \
  __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __TEMPLATE_DECLARE_BEGIN__,       \
           __TEMPLATE_END__)                                                 \
  static inline __static_callable_void##N##__ __REPEAT(                      \
      N, __TYPE_ARG__, __COMMA__, __TEMPLATE_BEGIN__, __TEMPLATE_END__) *    \
      create(void (*method)(                                                 \
          __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) { \
    return new __static_callable_void##N##__ __REPEAT(                       \
        N, __TYPE_ARG__, __COMMA__, __TEMPLATE_BEGIN__,                      \
        __TEMPLATE_END__)(method);                                           \
  }

// factory method for non-voids
template <class R>
struct __callable_factory__ {
  __CREATE_CALLABLE__(0)
  __CREATE_CALLABLE__(1)
  __CREATE_CALLABLE__(2)
  __CREATE_CALLABLE__(3)
  __CREATE_CALLABLE__(4)
  __CREATE_CALLABLE__(5)
  __CREATE_CALLABLE__(6)
  __CREATE_CALLABLE__(7)
  __CREATE_CALLABLE__(8)
  __CREATE_CALLABLE__(9)
  __CREATE_CALLABLE__(10)
  __CREATE_CALLABLE__(11)
  __CREATE_CALLABLE__(12)
  __CREATE_CALLABLE__(13)
  __CREATE_CALLABLE__(14)
  __CREATE_CALLABLE__(15)
  __CREATE_CALLABLE__(16)
  __CREATE_CALLABLE__(17)
  __CREATE_CALLABLE__(18)
  __CREATE_CALLABLE__(19)
  __CREATE_CALLABLE__(20)
  __CREATE_CALLABLE_CONST__(0)
  __CREATE_CALLABLE_CONST__(1)
  __CREATE_CALLABLE_CONST__(2)
  __CREATE_CALLABLE_CONST__(3)
  __CREATE_CALLABLE_CONST__(4)
  __CREATE_CALLABLE_CONST__(5)
  __CREATE_CALLABLE_CONST__(6)
  __CREATE_CALLABLE_CONST__(7)
  __CREATE_CALLABLE_CONST__(8)
  __CREATE_CALLABLE_CONST__(9)
  __CREATE_CALLABLE_CONST__(10)
  __CREATE_CALLABLE_CONST__(11)
  __CREATE_CALLABLE_CONST__(12)
  __CREATE_CALLABLE_CONST__(13)
  __CREATE_CALLABLE_CONST__(14)
  __CREATE_CALLABLE_CONST__(15)
  __CREATE_CALLABLE_CONST__(16)
  __CREATE_CALLABLE_CONST__(17)
  __CREATE_CALLABLE_CONST__(18)
  __CREATE_CALLABLE_CONST__(19)
  __CREATE_CALLABLE_CONST__(20)
};

// factory method for non-voids
template <>
struct __callable_factory__<void> {
  __CREATE_CALLABLE_VOID__(0)
  __CREATE_CALLABLE_VOID__(1)
  __CREATE_CALLABLE_VOID__(2)
  __CREATE_CALLABLE_VOID__(3)
  __CREATE_CALLABLE_VOID__(4)
  __CREATE_CALLABLE_VOID__(5)
  __CREATE_CALLABLE_VOID__(6)
  __CREATE_CALLABLE_VOID__(7)
  __CREATE_CALLABLE_VOID__(8)
  __CREATE_CALLABLE_VOID__(9)
  __CREATE_CALLABLE_VOID__(10)
  __CREATE_CALLABLE_VOID__(11)
  __CREATE_CALLABLE_VOID__(12)
  __CREATE_CALLABLE_VOID__(13)
  __CREATE_CALLABLE_VOID__(14)
  __CREATE_CALLABLE_VOID__(15)
  __CREATE_CALLABLE_VOID__(16)
  __CREATE_CALLABLE_VOID__(17)
  __CREATE_CALLABLE_VOID__(18)
  __CREATE_CALLABLE_VOID__(19)
  __CREATE_CALLABLE_VOID__(20)
  __CREATE_CALLABLE_CONST_VOID__(0)
  __CREATE_CALLABLE_CONST_VOID__(1)
  __CREATE_CALLABLE_CONST_VOID__(2)
  __CREATE_CALLABLE_CONST_VOID__(3)
  __CREATE_CALLABLE_CONST_VOID__(4)
  __CREATE_CALLABLE_CONST_VOID__(5)
  __CREATE_CALLABLE_CONST_VOID__(6)
  __CREATE_CALLABLE_CONST_VOID__(7)
  __CREATE_CALLABLE_CONST_VOID__(8)
  __CREATE_CALLABLE_CONST_VOID__(9)
  __CREATE_CALLABLE_CONST_VOID__(10)
  __CREATE_CALLABLE_CONST_VOID__(11)
  __CREATE_CALLABLE_CONST_VOID__(12)
  __CREATE_CALLABLE_CONST_VOID__(13)
  __CREATE_CALLABLE_CONST_VOID__(14)
  __CREATE_CALLABLE_CONST_VOID__(15)
  __CREATE_CALLABLE_CONST_VOID__(16)
  __CREATE_CALLABLE_CONST_VOID__(17)
  __CREATE_CALLABLE_CONST_VOID__(18)
  __CREATE_CALLABLE_CONST_VOID__(19)
  __CREATE_CALLABLE_CONST_VOID__(20)
};

// factory method for static non-voids
template <class R>
struct __static_callable_factory__ {
  __CREATE_STATIC_CALLABLE__(0)
  __CREATE_STATIC_CALLABLE__(1)
  __CREATE_STATIC_CALLABLE__(2)
  __CREATE_STATIC_CALLABLE__(3)
  __CREATE_STATIC_CALLABLE__(4)
  __CREATE_STATIC_CALLABLE__(5)
  __CREATE_STATIC_CALLABLE__(6)
  __CREATE_STATIC_CALLABLE__(7)
  __CREATE_STATIC_CALLABLE__(8)
  __CREATE_STATIC_CALLABLE__(9)
  __CREATE_STATIC_CALLABLE__(10)
  __CREATE_STATIC_CALLABLE__(11)
  __CREATE_STATIC_CALLABLE__(12)
  __CREATE_STATIC_CALLABLE__(13)
  __CREATE_STATIC_CALLABLE__(14)
  __CREATE_STATIC_CALLABLE__(15)
  __CREATE_STATIC_CALLABLE__(16)
  __CREATE_STATIC_CALLABLE__(17)
  __CREATE_STATIC_CALLABLE__(18)
  __CREATE_STATIC_CALLABLE__(19)
  __CREATE_STATIC_CALLABLE__(20)
};

// factory method for static voids
template <>
struct __static_callable_factory__<void> {
  __CREATE_STATIC_CALLABLE_VOID__(0)
  __CREATE_STATIC_CALLABLE_VOID__(1)
  __CREATE_STATIC_CALLABLE_VOID__(2)
  __CREATE_STATIC_CALLABLE_VOID__(3)
  __CREATE_STATIC_CALLABLE_VOID__(4)
  __CREATE_STATIC_CALLABLE_VOID__(5)
  __CREATE_STATIC_CALLABLE_VOID__(6)
  __CREATE_STATIC_CALLABLE_VOID__(7)
  __CREATE_STATIC_CALLABLE_VOID__(8)
  __CREATE_STATIC_CALLABLE_VOID__(9)
  __CREATE_STATIC_CALLABLE_VOID__(10)
  __CREATE_STATIC_CALLABLE_VOID__(11)
  __CREATE_STATIC_CALLABLE_VOID__(12)
  __CREATE_STATIC_CALLABLE_VOID__(13)
  __CREATE_STATIC_CALLABLE_VOID__(14)
  __CREATE_STATIC_CALLABLE_VOID__(15)
  __CREATE_STATIC_CALLABLE_VOID__(16)
  __CREATE_STATIC_CALLABLE_VOID__(17)
  __CREATE_STATIC_CALLABLE_VOID__(18)
  __CREATE_STATIC_CALLABLE_VOID__(19)
  __CREATE_STATIC_CALLABLE_VOID__(20)
};

// callable generator
#define __CALLABLE_GENERATOR__(N)                                        \
  template <class R, class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,    \
                                      __COMMA__, __NOTHING__)>           \
  inline __callable__ *__create_callable__(R (C::*method)(               \
      __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) { \
    return __callable_factory__<R>::create(method);                      \
  }

// const callable generator
#define __CALLABLE_GENERATOR_CONST__(N)                                        \
  template <class R, class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,          \
                                      __COMMA__, __NOTHING__)>                 \
  inline __callable__ *__create_callable__(R (C::*method)(                     \
      __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__)) const) { \
    return __callable_factory__<R>::create(method);                            \
  }

// static callable generator
#define __STATIC_CALLABLE_GENERATOR__(N)                                 \
  template <class R __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,  \
                             __NOTHING__)>                               \
  inline __callable__ *__create_static_callable__(R (*method)(           \
      __REPEAT(N, __TYPE_ARG__, __COMMA__, __NOTHING__, __NOTHING__))) { \
    return __static_callable_factory__<R>::create(method);               \
  }

// generators
__CALLABLE_GENERATOR__(0)
__CALLABLE_GENERATOR__(1)
__CALLABLE_GENERATOR__(2)
__CALLABLE_GENERATOR__(3)
__CALLABLE_GENERATOR__(4)
__CALLABLE_GENERATOR__(5)
__CALLABLE_GENERATOR__(6)
__CALLABLE_GENERATOR__(7)
__CALLABLE_GENERATOR__(8)
__CALLABLE_GENERATOR__(9)
__CALLABLE_GENERATOR__(10)
__CALLABLE_GENERATOR__(11)
__CALLABLE_GENERATOR__(12)
__CALLABLE_GENERATOR__(13)
__CALLABLE_GENERATOR__(14)
__CALLABLE_GENERATOR__(15)
__CALLABLE_GENERATOR__(16)
__CALLABLE_GENERATOR__(17)
__CALLABLE_GENERATOR__(18)
__CALLABLE_GENERATOR__(19)
__CALLABLE_GENERATOR__(20)
__CALLABLE_GENERATOR_CONST__(0)
__CALLABLE_GENERATOR_CONST__(1)
__CALLABLE_GENERATOR_CONST__(2)
__CALLABLE_GENERATOR_CONST__(3)
__CALLABLE_GENERATOR_CONST__(4)
__CALLABLE_GENERATOR_CONST__(5)
__CALLABLE_GENERATOR_CONST__(6)
__CALLABLE_GENERATOR_CONST__(7)
__CALLABLE_GENERATOR_CONST__(8)
__CALLABLE_GENERATOR_CONST__(9)
__CALLABLE_GENERATOR_CONST__(10)
__CALLABLE_GENERATOR_CONST__(11)
__CALLABLE_GENERATOR_CONST__(12)
__CALLABLE_GENERATOR_CONST__(13)
__CALLABLE_GENERATOR_CONST__(14)
__CALLABLE_GENERATOR_CONST__(15)
__CALLABLE_GENERATOR_CONST__(16)
__CALLABLE_GENERATOR_CONST__(17)
__CALLABLE_GENERATOR_CONST__(18)
__CALLABLE_GENERATOR_CONST__(19)
__CALLABLE_GENERATOR_CONST__(20)
__STATIC_CALLABLE_GENERATOR__(0)
__STATIC_CALLABLE_GENERATOR__(1)
__STATIC_CALLABLE_GENERATOR__(2)
__STATIC_CALLABLE_GENERATOR__(3)
__STATIC_CALLABLE_GENERATOR__(4)
__STATIC_CALLABLE_GENERATOR__(5)
__STATIC_CALLABLE_GENERATOR__(6)
__STATIC_CALLABLE_GENERATOR__(7)
__STATIC_CALLABLE_GENERATOR__(8)
__STATIC_CALLABLE_GENERATOR__(9)
__STATIC_CALLABLE_GENERATOR__(10)
__STATIC_CALLABLE_GENERATOR__(11)
__STATIC_CALLABLE_GENERATOR__(12)
__STATIC_CALLABLE_GENERATOR__(13)
__STATIC_CALLABLE_GENERATOR__(14)
__STATIC_CALLABLE_GENERATOR__(15)
__STATIC_CALLABLE_GENERATOR__(16)
__STATIC_CALLABLE_GENERATOR__(17)
__STATIC_CALLABLE_GENERATOR__(18)
__STATIC_CALLABLE_GENERATOR__(19)
__STATIC_CALLABLE_GENERATOR__(20)

// macro that defines an 'invoke' method with a return type
#define __INVOKE__(N)                                                         \
  template <class R, class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__,         \
                                      __COMMA__, __NOTHING__)>                \
  void invoke(R &result, C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__, \
                                            __NOTHING__)) const {             \
    typedef const __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__, __COMMA__, \
                                                  __COMMA__, __NOTHING__)>    \
        CallableType1;                                                        \
    typedef const __callable_const##N##__<                                    \
        R, C __REPEAT(N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>    \
        CallableType2;                                                        \
    CallableType1 *cb1 = dynamic_cast<CallableType1 *>(_callable);            \
    if (cb1) {                                                                \
      result = cb1->invoke(                                                   \
          object __REPEAT(N, __PARAM__, __COMMA__, __COMMA__, __NOTHING__));  \
      return;                                                                 \
    }                                                                         \
    CallableType2 *cb2 = dynamic_cast<CallableType2 *>(_callable);            \
    if (cb2) {                                                                \
      result = cb2->invoke(                                                   \
          object __REPEAT(N, __PARAM__, __COMMA__, __COMMA__, __NOTHING__));  \
      return;                                                                 \
    }                                                                         \
  }

// macro that defines an 'invoke' method without a return type
#define __INVOKE_VOID__(N)                                                   \
  template <class C __REPEAT(N, __TEMPLATE_ARG__, __COMMA__, __COMMA__,      \
                             __NOTHING__)>                                   \
  void invokeVoid(C *object __REPEAT(N, __ARG__, __COMMA__, __COMMA__,       \
                                     __NOTHING__)) const {                   \
    typedef const __callable_void##N##__<C __REPEAT(                         \
        N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>                 \
        CallableType1;                                                       \
    typedef const __callable_const_void##N##__<C __REPEAT(                   \
        N, __TYPE_ARG__, __COMMA__, __COMMA__, __NOTHING__)>                 \
        CallableType2;                                                       \
    CallableType1 *cb1 = dynamic_cast<CallableType1 *>(_callable);           \
    if (cb1) {                                                               \
      cb1->invoke(                                                           \
          object __REPEAT(N, __PARAM__, __COMMA__, __COMMA__, __NOTHING__)); \
      return;                                                                \
    }                                                                        \
    CallableType2 *cb2 = dynamic_cast<CallableType2 *>(_callable);           \
    if (cb2) {                                                               \
      cb2->invoke(                                                           \
          object __REPEAT(N, __PARAM__, __COMMA__, __COMMA__, __NOTHING__)); \
      return;                                                                \
    }                                                                        \
  }

/** The Method class represents an object's method.
 */
class CORE_API Method {
 public:
  /// destructor
  ~Method();

  /** invokes a method that has a result
  @param result optional variable to store the result (if the method is
  non-void)
  @param object object to execute the method of
  @param t1...tn parameters of the invocation
  @exception IllegalAccessError if the method is not public
  @exception TypeMismatchError if the method has different arguments than
  the ones passed to it
  */
  __INVOKE__(0)
  __INVOKE__(1)
  __INVOKE__(2)
  __INVOKE__(3)
  __INVOKE__(4)
  __INVOKE__(5)
  __INVOKE__(6)
  __INVOKE__(7)
  __INVOKE__(8)
  __INVOKE__(9)
  __INVOKE__(10)
  __INVOKE__(11)
  __INVOKE__(12)
  __INVOKE__(13)
  __INVOKE__(14)
  __INVOKE__(15)
  __INVOKE__(16)
  __INVOKE__(17)
  __INVOKE__(18)
  __INVOKE__(19)
  __INVOKE__(20)

  /** invokes a method that 'returns' void
  @param object object to execute the method of
  @param t1...tn parameters of the invocation
  @exception IllegalAccessError if the method is not public
  @exception TypeMismatchError if the method has different arguments than
  the ones passed to it
  */
  __INVOKE_VOID__(0)
  __INVOKE_VOID__(1)
  __INVOKE_VOID__(2)
  __INVOKE_VOID__(3)
  __INVOKE_VOID__(4)
  __INVOKE_VOID__(5)
  __INVOKE_VOID__(6)
  __INVOKE_VOID__(7)
  __INVOKE_VOID__(8)
  __INVOKE_VOID__(9)
  __INVOKE_VOID__(10)
  __INVOKE_VOID__(11)
  __INVOKE_VOID__(12)
  __INVOKE_VOID__(13)
  __INVOKE_VOID__(14)
  __INVOKE_VOID__(15)
  __INVOKE_VOID__(16)
  __INVOKE_VOID__(17)
  __INVOKE_VOID__(18)
  __INVOKE_VOID__(19)
  __INVOKE_VOID__(20)

  const Class &getClass() const { return _class; }
  const String &getName() const { return _name; }
  const Class &getReturnClass() const { return _callable->get_ret_cls(); }
  const std::vector<const Class *> &getArgsClass() const {
    return _callable->get_args();
  }

  Any invoke(void *object, const std::vector<Any> &params) const {
    return _callable->invoke(object, params);
  }

 private:
  // default constructor
  Method(const Class &cls, const char *name, const char *args);
  void set_callable(__callable__ *cb);

  __callable__ *_callable;
  const Class &_class;
  String _name;
  friend class Class;
  friend struct __register_method__;
};

// declares a method
#define __METHOD__(VIRTUAL, RETURN_TYPE, METHOD_NAME, METHOD_ARGS, LINE)    \
 private:                                                                   \
  struct REF_JOIN(__method_##METHOD_NAME##__, LINE) {                       \
    REF_JOIN(__method_##METHOD_NAME##__, LINE)                              \
    () {                                                                    \
      typedef RETURN_TYPE(ClassType::*method_ptr_type) METHOD_ARGS;         \
      method_ptr_type method_ptr = &ClassType::METHOD_NAME;                 \
      static gemini::__register_method__ reg(                               \
          __create_callable__(method_ptr), getClassStatic(),                \
          gemini::Class::forName(#RETURN_TYPE), #METHOD_NAME, #METHOD_ARGS, \
          #VIRTUAL);                                                        \
    }                                                                       \
  } REF_JOIN(__method_##METHOD_NAME##__, LINE);                             \
  friend struct REF_JOIN(__method_##METHOD_NAME##__, LINE);                 \
                                                                            \
 public:                                                                    \
  VIRTUAL RETURN_TYPE METHOD_NAME METHOD_ARGS

/** The METHOD macro is used to declare a reflected method.
@param ACCESS_ATTR access attribute (public, protected or private)
@param RETURN_TYPE the return type of the method
@param METHOD_NAME name of the method
@param METHOD_ARGS the method's arguments enclosed in parentheses
*/
#define METHOD(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  __METHOD__(__NOT_VIRTUAL__, RETURN_TYPE, METHOD_NAME, METHOD_ARGS, __LINE__)
#define METHOD_N(NUM, ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  __METHOD__(__NOT_VIRTUAL__, RETURN_TYPE, METHOD_NAME, METHOD_ARGS, NUM)
#define METHOD0(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(0, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD1(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(1, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD2(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(2, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD3(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(3, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD4(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(4, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD5(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(5, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD6(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(6, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD7(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(7, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD8(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(8, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD9(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(9, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD10(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(10, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD11(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(11, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD12(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(12, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD13(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(13, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD14(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(14, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD15(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(15, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD16(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(16, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD17(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(17, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD18(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(18, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD19(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(19, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)
#define METHOD20(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD_N(20, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)

}  // namespace gemini
#endif  // GEMINI_ReflectMethod_INCLUDE
