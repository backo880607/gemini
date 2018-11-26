#ifndef GEMINI_IApplication_INCLUDE
#define GEMINI_IApplication_INCLUDE
#include <locale>
#include "Common.h"

namespace gemini {

class Class;
class Field;
class CORE_API IApplication {
 public:
  virtual void init() = 0;
  virtual void uninit() = 0;

  virtual Boolean isFieldStoraged(const Class& cls, const Field& field) = 0;

  virtual const Char* getEnvironment() = 0;
  virtual const Char* getConfigPath() = 0;
  virtual const Char* getTempPath() = 0;

  virtual const std::locale& getLocale() = 0;
  virtual void setLocale(const Char* name) = 0;
  virtual void setLocale(const std::locale& loc) = 0;
};
CORE_API IApplication& getApp();

class CORE_API LocaleSwitch {
 public:
  LocaleSwitch(const Char* name = "c");
  LocaleSwitch(const std::locale& loc);
  ~LocaleSwitch();

 private:
  std::locale _oldLocale;
};

}  // namespace gemini
#endif  // GEMINI_IApplication_INCLUDE