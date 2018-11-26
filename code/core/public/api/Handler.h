#ifndef GEMINI_API_Handler_INCLUDE
#define GEMINI_API_Handler_INCLUDE
#include "../Object.h"

namespace gemini {
namespace api {

class CORE_API DataHandler {
 public:
  DataHandler() {}
  virtual ~DataHandler() {}

  virtual String read(Object::SPtr entity, const Field *field) = 0;
  virtual void write(Object::SPtr entity, const Field *field,
                     const String &value) = 0;
};

class CORE_API ObjectHandler {
 public:
  ObjectHandler() : _cls(nullptr) {}
  virtual ~ObjectHandler() {}

  void setClass(const Class &cls) { _cls = &cls; }

  virtual Object::SPtr get(const String &primary) = 0;
  virtual Object::SPtr require(const String &primary) = 0;
  virtual Object::SPtr require();

 protected:
  const Class *_cls;
};

class CORE_API IDEntityHandler : public ObjectHandler {
 public:
  IDEntityHandler();
  ~IDEntityHandler();

  virtual Object::SPtr get(const String &primary) override;
  virtual Object::SPtr require(const String &primary) override;
  virtual Object::SPtr require() override;
};

/*class CORE_API PrimaryKeyHandler : public ObjectHandler {
 public:
  PrimaryKeyHandler();
  ~PrimaryKeyHandler();

  virtual Object::SPtr get(const String &primary) override;
  virtual Object::SPtr require(const String &primary) override;
  virtual Object::SPtr require() override;

  void set(const String& primary, const Object::SPtr& object);

 private:
  std::map<String, Object::SPtr> _cache;
};*/

class CORE_API ValidateHandler {
 public:
  ValidateHandler() {}
  virtual ~ValidateHandler() {}

  virtual Boolean validate(const Field &field, const String &value) = 0;
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_API_Handler_INCLUDE