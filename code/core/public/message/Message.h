#ifndef GEMINI_Message_INCLUDE
#define GEMINI_Message_INCLUDE
#include "../Object.h"
#include "Exception.h"

namespace gemini {

class CORE_API StrongErrorException : public Exception {
  virtual String getName() const override { return "StrongError"; }
};
class CORE_API Message : public EntityObject {
  DECLARE_CLASS(Message, EntityObject)
 public:
  enum class Type { Debug, Info, Warning, Error, Fatal };

  template <class T, typename... ARGS>
  static void debug(ARGS... args) {
    create<T>(Type::Debug, args...);
  }

  template <class T, typename... ARGS>
  static void info(ARGS... args) {
    create<T>(Type::Info, args...);
  }

  template <class T, typename... ARGS>
  static void warning(ARGS... args) {
    create<T>(Type::Warning, args...);
  }

  template <class T, typename... ARGS>
  static void error(ARGS... args) {
    create<T>(Type::Error, args...);
  }

  template <class T, typename... ARGS>
  static void fatal(ARGS... args) {
    create<T>(Type::Fatal, args...);
  }

  template <class T, typename... ARGS>
  static Message::SPtr strong_error(ARGS... args) {
    Message::SPtr msg = createTemp<T>(Type::Error, args...);
    THROW(StrongErrorException, msg);
    return msg;
  }

  template <class T, typename... ARGS>
  static Message::SPtr tips(ARGS... args) {
    Message::SPtr msg = createTemp<T>(Type::Info, args...);
    return msg;
  }

  template <class T, typename... ARGS>
  static Message::SPtr warning_tips(ARGS... args) {
    Message::SPtr msg = createTemp<T>(Type::Warning, args...);
    return msg;
  }

 private:
  static void putArgs(log_info& msg) {}
  template <typename T>
  static void putArgs(log_info& msg, T arg) {
    msg << arg;
  }
  template <typename T, typename... ARGS>
  static void putArgs(log_info& msg, T arg, ARGS... args) {
    msg << arg;
    putArgs(msg, args...);
  }

  template <class T, typename... ARGS>
  static Message::SPtr create(Type type, ARGS... args) {
    T msg;
    putArgs(msg, args...);
    return createImpl(type, msg);
  }
  template <class T, typename... ARGS>
  static Message::SPtr createTemp(Type type, ARGS... args) {
    T msg;
    putArgs(msg, args...);
    return createImpl(type, msg, true);
  }
  static Message::SPtr createImpl(Type type, log_info& msg,
                                  Boolean bTemp = false);

  Type getType() const { return (const Type&)_type; }
  const String& getName() const { return (const String&)_name; }
  const String& getDetail() const { return (const String&)_detail; }

 private:
  DECLARE_FIELD(Type, type)
  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, detail)
};

}  // namespace gemini

#endif  // GEMINI_Message_INCLUDE
