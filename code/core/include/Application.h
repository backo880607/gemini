#ifndef GEMINI_Application_INCLUDE
#define GEMINI_Application_INCLUDE
#include "../public/IApplication.h"

namespace gemini {

class CORE_API Application final : public IApplication {
 public:
  Application();
  ~Application();

  virtual void init() override;

  const Char *getConfigPath();
  const Char *getDumpPath();

  virtual const std::locale &getLocale() override;
  virtual void setLocale(const Char *name) override;
};
extern CORE_API Application g_app;

}  // namespace gemini
#endif  // GEMINI_Application_INCLUDE