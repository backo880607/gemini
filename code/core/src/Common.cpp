#include "../public/Common.h"
#include "../public/DateTime.h"
#include "Application.h"
#include "Session.h"
#include "tools/LocaleUtil.h"

#include <iomanip>
#include <thread>

namespace gemini {

std::ostringstream& StringUtilBase::getOSStream() {
  Session::SPtr session = getSession();
  if (session.valid()) {
    return session->get<LocaleUtil>().getOSS(true);
  }
  return g_app.getDefaultLocal()->getOSS(true);
}

std::istringstream& StringUtilBase::getISStream(const Char* str) {
  Session::SPtr session = getSession();
  if (session.valid()) {
    return session->get<LocaleUtil>().getISS(str);
  }
  return g_app.getDefaultLocal()->getISS(str);
}

String StringUtilBase::format(Float val, Int precision) {
  std::ostringstream& ss = getOSStream();
  ss << std::fixed << std::setprecision(precision) << boost::locale::as::number
     << val;
  return ss.str();
}
String StringUtilBase::format(Double val, Int precision) {
  std::ostringstream& ss = getOSStream();
  ss << std::fixed << std::setprecision(precision) << boost::locale::as::number
     << val;
  return ss.str();
}

String StringUtilBase::formatImpl(Boolean value) {
  std::ostringstream& ss = getOSStream();
  ss << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Short value) {
  std::ostringstream& ss = getOSStream();
  ss << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Int value) {
  std::ostringstream& ss = getOSStream();
  ss << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Long value) {
  std::ostringstream& ss = getOSStream();
  ss << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Float value) {
  std::ostringstream& ss = getOSStream();
  ss << std::fixed << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Double value) {
  std::ostringstream& ss = getOSStream();
  ss << std::fixed << boost::locale::as::number << value;
  return ss.str();
}
String StringUtilBase::formatImpl(Char value) { return String(1, value); }
String StringUtilBase::formatImpl(Char16 value) {
  // return val;
  return "";
}
String StringUtilBase::formatImpl(Char32 value) {
  // return val;
  return "";
}
String StringUtilBase::formatImpl(WChar* value) {
  return boost::locale::conv::utf_to_utf<Char>(value);
}
String StringUtilBase::formatImpl(const WChar* value) {
  return boost::locale::conv::utf_to_utf<Char>(value);
}
String StringUtilBase::formatImpl(ID value) {
  std::ostringstream& ss = getOSStream();
  ss << boost::locale::as::number << value;
  return ss.str();
}

void StringUtilBase::convertImpl(Short& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> boost::locale::as::number >> value;
}
void StringUtilBase::convertImpl(Int& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> boost::locale::as::number >> value;
}
void StringUtilBase::convertImpl(Long& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> boost::locale::as::number >> value;
}
void StringUtilBase::convertImpl(Float& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> std::fixed >> boost::locale::as::number >> value;
}
void StringUtilBase::convertImpl(Double& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> std::fixed >> boost::locale::as::number >> value;
}
void StringUtilBase::convertImpl(Char& value, const Char* str) { value = *str; }
void StringUtilBase::convertImpl(ID& value, const Char* str) {
  std::istringstream& ss = getISStream(str);
  ss >> boost::locale::as::number >> value;
}

void StringUtilBase::convertImpl(Boolean& value, const Char* str,
                                 std::size_t fPos, std::size_t lPos) {}
void StringUtilBase::convertImpl(Short& value, const Char* str,
                                 std::size_t fPos, std::size_t lPos) {}
void StringUtilBase::convertImpl(Int& value, const Char* str, std::size_t fPos,
                                 std::size_t lPos) {}
void StringUtilBase::convertImpl(Long& value, const Char* str, std::size_t fPos,
                                 std::size_t lPos) {}
void StringUtilBase::convertImpl(Float& value, const Char* str,
                                 std::size_t fPos, std::size_t lPos) {}
void StringUtilBase::convertImpl(Double& value, const Char* str,
                                 std::size_t fPos, std::size_t lPos) {}
void StringUtilBase::convertImpl(ID& value, const Char* str, std::size_t fPos,
                                 std::size_t lPos) {}

void SpinMutex::lock() {
  unsigned k = 0;
#ifdef def_TestDeadLock
  YKDateTime dt = YKDateTime::GetLocalTime();
#endif  // def_TestDeadLock
  while (!try_lock()) {
    if (k < 4) {
    }
#if defined(YK_SMT_PAUSE)
    else if (k < 16) {
      YK_SMT_PAUSE
    }
#endif
    else if (k < 32) {
      std::this_thread::yield();
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    ++k;

#ifdef def_TestDeadLock
    if (dt.IsElapsed(def_ElapsedTime)) ::DebugBreak();
#endif  // def_TestDeadLock
  }
}

Boolean SpinMutex::try_lock(Long milliseconds) {
  DateTime dt = DateTime::local();
  while (!try_lock()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (dt.elapsed(milliseconds)) return false;
  }
  return true;
}

}  // namespace gemini