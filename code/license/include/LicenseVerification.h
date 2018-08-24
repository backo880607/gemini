#ifndef GEMINI_LICENSE_LicenseVerification_INCLUDE
#define GEMINI_LICENSE_LicenseVerification_INCLUDE
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <string>

namespace gemini {
namespace license {

class LocaleKey;
class AuthorizeCheck {
 public:
  AuthorizeCheck();
  ~AuthorizeCheck();

  static AuthorizeCheck& instance() {
    static AuthorizeCheck obj;
    return obj;
  }

  void Start();
  void Stop();

  int GetTimeSpan() const { return m_timeSpan; }
  boost::mutex& GetMutex() { return _mutex; }

  static std::shared_ptr<LocaleKey> Verify();

 private:
  static void CheckImpl();

  void Check();

 private:
  int m_timeSpan;
  std::shared_ptr<boost::thread> m_thread;
  boost::mutex _mutex;
  boost::asio::steady_timer m_checkTimer;
};

}  // namespace license
}  // namespace gemini
#endif  // GEMINI_LICENSE_LicenseVerification_INCLUDE