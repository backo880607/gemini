#include "Application.h"
#include "Buffer.h"
//#include "Session.h"
#include "tools/LocaleUtil.h"
#include "tools/StringUtil.h"

#include <stdarg.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace gemini {

void StringUtil::to_upper(String& str) {
  boost::to_upper(str, g_app.getLocale());
}

void StringUtil::to_lower(String& str) {
  return boost::to_lower(str, g_app.getLocale());
}

void StringUtil::trim_lift(String& str) {
  boost::trim_left(str, g_app.getLocale());
}

void StringUtil::trim_right(String& str) {
  boost::trim_right(str, g_app.getLocale());
}

void StringUtil::trim(String& str) { boost::trim(str, g_app.getLocale()); }

Boolean StringUtil::starts_with(const Char* str, const Char* test) {
  return boost::starts_with(str, test);
}

Boolean StringUtil::istarts_with(const Char* str, const Char* test) {
  return boost::istarts_with(str, test, g_app.getLocale());
}

Boolean StringUtil::ends_with(const Char* str, const Char* test) {
  return boost::ends_with(str, test);
}

Boolean StringUtil::iends_with(const Char* str, const Char* test) {
  return boost::iends_with(str, test, g_app.getLocale());
}

Boolean StringUtil::contains(const Char* str, const Char* test) {
  return boost::contains(str, test);
}

Boolean StringUtil::icontains(const Char* str, const Char* test) {
  return boost::icontains(str, test, g_app.getLocale());
}

Boolean StringUtil::equals(const Char* str, const Char* test) {
  return boost::equals(str, test);
}

Boolean StringUtil::iequals(const Char* str, const Char* test) {
  return boost::iequals(str, test, g_app.getLocale());
}

Int StringUtil::compare(const Char* str, const Char* test) {
  Char f, l;
  const Char* dst = str;
  const Char* src = test;
  const std::locale& loc = g_app.getLocale();
  do {
    f = *dst;
    l = *src;
    dst++;
    src++;
  } while ((f) && (f == l));
  return (Int)(f - l);
}

Int StringUtil::icompare(const Char* str, const Char* test) {
  Char f, l;
  const Char* dst = str;
  const Char* src = test;
  const std::locale& loc = g_app.getLocale();
  do {
    f = std::tolower(*dst, loc);
    l = std::tolower(*src, loc);
    dst++;
    src++;
  } while ((f) && (f == l));
  return (Int)(f - l);
}

String::size_type StringUtil::ifind_first(const Char* str, const Char* test) {
  return boost::algorithm::ifind_first(str, test, g_app.getLocale()).begin() -
         str;
}

String::size_type StringUtil::ifind_last(const Char* str, const Char* test) {
  return String::size_type();
}

String StringUtil::get_head(const Char* str, const Char* sep) {
  // const String::size_type pos = boost::find();
  return "";
}

String StringUtil::iget_head(const Char* str, const Char* sep) {
  return String();
}

String StringUtil::get_tail(const Char* str, const Char* sep) {
  String origin(str);
  const String::size_type pos = origin.find_last_of(sep);
  return pos != String::npos ? origin.substr(pos + strlen(sep)) : "";
}

String StringUtil::iget_tail(const Char* str, const Char* sep) {
  return String();
}

void StringUtil::erase_all(String& str, const Char* dest) {
  boost::algorithm::erase_all(str, dest);
}

void StringUtil::ierase_all(String& str, const Char* dest) {
  boost::algorithm::ierase_all(str, dest, g_app.getLocale());
}

void StringUtil::erase_first(String& str, const Char* dest) {
  boost::algorithm::erase_first(str, dest);
}

void StringUtil::ierase_first(String& str, const Char* dest) {
  boost::algorithm::ierase_first(str, dest, g_app.getLocale());
}

String StringUtil::fetch_first(String& str, const Char* sep) {
  return String();
}

String StringUtil::fetch_end(String& str, const Char* sep) { return String(); }

const Char* StringUtil::increment(const Char* str) {
  while (*++str != '\0') {
    if ((*str & 0xc0) != 0x80) {
      break;
    }
  }

  return str;
}

const Char* StringUtil::descending(const Char* str) {
  while (--str) {
    if ((*str & 0xc0) != 0x80) {
      break;
    }
  }

  return str;
}

void StringUtil::replace(String& str, const Char* origin, const Char* des) {
  String::size_type lastpos = 0, thispos;
  const String::size_type lLen = strlen(origin);
  const String::size_type rLen = strlen(des);
  while ((thispos = str.find(origin, lastpos)) != String::npos) {
    str.replace(thispos, lLen, des);
    lastpos = thispos + rLen;
  }
}

String StringUtil::SPrintf(const Char* pFormat, ...) {
  va_list argList;
  va_start(argList, pFormat);

  Buffer<Char> buffer(1028);

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#pragma warning(push)
#pragma warning(disable : 4995)
#pragma warning(disable : 4996)
#pragma warning(disable : 28719)
#endif
  vsnprintf(buffer.begin(), 1028, pFormat, argList);
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#pragma warning(pop)
#endif
  va_end(argList);
  return buffer.begin();
}

String StringUtil::getField(const Object::SPtr& object, const Field& field) {
  if (field.getRefKind() != RefKind::None) {
    const BaseEntity* pObject = (const BaseEntity*)object.rawPointer();
    if (field.getRefKind() == RefKind::Entity) {
      BaseEntity::SPtr entity =
          FieldRefWrapHelper::get(pObject, field.index());
      return entity.valid() ? format(entity->getID()) : "";
    }
    const IList& entities = FieldRefWrapHelper::getList(pObject, field.index());
    return join(entities, ";",
                [](BaseEntity::SPtr entity) { return entity->getID(); });
  }
  return field.getType()._holder->get(object, field);
}

void StringUtil::setField(Object::SPtr object, const Field& field,
                          const Char* value) {
  field.getType()._holder->set(object, field, value);
}

std::wstring StringUtil::utf8_to_unicode(const Char* src) {
  return boost::locale::conv::to_utf<wchar_t>(src, "UTF-8");
}

String StringUtil::uuid() {
  boost::uuids::random_generator gen;
  boost::uuids::uuid u = gen();
  return boost::uuids::to_string(u);
}

}  // namespace gemini