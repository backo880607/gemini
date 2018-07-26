#ifndef GEMINI_Exception_INCLUDE
#define GEMINI_Exception_INCLUDE
#include "../ReflectMethod.h"

namespace gemini {

class CORE_API log_info {
 public:
  virtual String getName() = 0;

  template <typename T>
  log_info& operator<<(T val) {
    _datas.push_back(val);
    return *this;
  }

  virtual String detail();

 private:
  mutable Char const* throw_function_;
  mutable Char const* throw_file_;
  mutable Int throw_line_;
  Long _dtCreated;
  std::vector<Any> _datas;
  friend class Exception;
};
class CORE_API LOG_INFO : public log_info {
 public:
  virtual String getName() override { return "INFO"; }
};
class CORE_API LOG_WARNING : public log_info {
 public:
  virtual String getName() override { return "WARNING"; }
};
class CORE_API LOG_ERROR : public log_info {
 public:
  virtual String getName() override { return "ERROR"; }
};
class CORE_API LOG_FATAL : public log_info {
 public:
  virtual String getName() override { return "FATAL"; }
};
class CORE_API TIPS_StrongError : public LOG_ERROR {
 public:
  virtual String getName() override { return "STRONGERROR"; }
};
class CORE_API TIPS_WEAK : public LOG_INFO {
 public:
  virtual String getName() override { return "TIPS"; }
};
class CORE_API TIPS_WARNING : public LOG_WARNING {
 public:
  virtual String getName() override { return "WARNINGTIPS"; }
};

class CORE_API Exception : public std::exception {
  class exception_error : public LOG_WARNING {
   public:
    virtual String getName() override { return ""; }
  };

 public:
  Exception();
  ~Exception();

  void setInfo(char const* curFun, char const* file, int line);

  template <typename T>
  Exception& operator<<(T val) {
    *_info << val;
    return *this;
  }

  void setData() {}
  template <class T, class... Args>
  void setData(T head, Args... rest) {
    *_info << head;
    setData(rest...);
  }

  virtual char const* what() const noexcept override;
  String str() const { return what(); }

  virtual String getName() const { return "Exception"; }

 private:
  std::shared_ptr<exception_error> _info;
};

class CORE_API SystemExecption : public Exception {
 public:
  virtual String getName() const override { return "SystemExecption"; }
};
class CORE_API ArithmeticExecption : public Exception {
 public:
  virtual String getName() const override { return "ArithmeticExecption"; }
};
class CORE_API BoundaryException : public Exception {
 public:
  virtual String getName() const override { return "BoundaryException"; }
};
class CORE_API OperandException : public Exception {
 public:
  virtual String getName() const override { return "OperandException"; }
};
class CORE_API NullPointerException : public Exception {
 public:
  virtual String getName() const override { return "NullPointerException"; }
};
class CORE_API ClassCastException : public Exception {
 public:
  virtual String getName() const override { return "ClassCastException"; }
};
class CORE_API FileNotFoundException : public Exception {
 public:
  virtual String getName() const override { return "FileNotFoundException"; }
};
class CORE_API IOException : public Exception {
 public:
  virtual String getName() const override { return "IOException"; }
};
class CORE_API NoSuchFieldException : public Exception {
 public:
  virtual String getName() const override { return "NoSuchFieldException"; }
};
class CORE_API NoSuchMethodException : public Exception {
 public:
  virtual String getName() const override { return "NoSuchMethodException"; }
};
class CORE_API NoSuchElementException : public Exception {
 public:
  virtual String getName() const override { return "NoSuchElementException"; }
};
class CORE_API CircularityException : public Exception {
 public:
  virtual String getName() const override { return "CircularityException"; }
};
class CORE_API NoClassDefException : public Exception {
 public:
  virtual String getName() const override { return "NoClassDefException"; }
};
class CORE_API NoSupportException : public Exception {
 public:
  virtual String getName() const override { return "NoSupportException"; }
};
class CORE_API MatchException : public Exception {
 public:
  virtual String getName() const override { return "MatchException"; }
};
class CORE_API RegisterException : public Exception {
 public:
  virtual String getName() const override { return "RegisterException"; }
};
class CORE_API UnknownException : public Exception {
 public:
  virtual String getName() const override { return "UnknownException"; }
};

#define THROW(ExceptionType, ...)                            \
  {                                                          \
    ExceptionType exc##__LINE__;                             \
    exc##__LINE__.setInfo(__FUNCTION__, __FILE__, __LINE__); \
    exc##__LINE__.setData(__VA_ARGS__);                      \
    throw exc##__LINE__;                                     \
  }

#define THROW_IF(Cond, ExceptionType, ...) \
  if (Cond) THROW(ExceptionType, __VA_ARGS__)

}  // namespace gemini
#endif  // GEMINI_Exception_INCLUDE