#ifndef GEMINI_LICENSE_LocaleKey_INCLUDE
#define GEMINI_LICENSE_LocaleKey_INCLUDE
#include "../public/LicenseExport.h"
#include "Object.h"

namespace gemini {
namespace license {

class LocaleKey : public EntityObject {
  DECLARE_CLASS(LocaleKey, EntityObject)

  DECLARE_FIELD(Boolean, valid)
  DECLARE_FIELD(Boolean, renew)
  DECLARE_FIELD(String, createTime)
  DECLARE_FIELD(String, updateTime)
  DECLARE_FIELD(String, deadTime)

  DECLARE_FIELD(String, diskSerialNo)
  DECLARE_FIELD(String, macAddr)
  DECLARE_FIELD(String, osName)
  DECLARE_FIELD(String, randomCode)

  DECLARE_FIELD(String, companyName)
  DECLARE_FIELD(String, address)
  DECLARE_FIELD(String, corporate)
  DECLARE_FIELD(String, contacts)

  DECLARE_FIELD(Int, maxUsers)
  DECLARE_FIELD(Int, maxConcurrency)
};

}  // namespace license
}  // namespace gemini
#endif  // GEMINI_LICENSE_LocaleKey_INCLUDE