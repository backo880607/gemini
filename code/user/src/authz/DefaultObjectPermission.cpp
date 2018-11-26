#include "../../include/authz/DefaultObjectPermission.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace user {

DefaultObjectPermission::DefaultObjectPermission(const String& value) {
  setParts(value);
}

DefaultObjectPermission::~DefaultObjectPermission() {}

void DefaultObjectPermission::setParts(const String& value) {
  String temp = value;
  StringUtil::trim(temp);
  if (temp.empty()) {
    return;
  }

  _parts.clear();
  StringUtil::parse<String>(temp, u8":", [&](const String& parts) {
    if (parts.empty()) {
      return;
    }

    _parts.push_back(std::set<String>());
    StringUtil::parse<String>(parts, u8",", [&](const String& subPart) {
      _parts.back().insert(subPart);
    });
  });
}

Boolean ContainsAll(const std::set<String>& lhs, const std::set<String>& rhs) {
  for (const String& rValue : rhs) {
    if (lhs.find(rValue) == lhs.end()) {
      return false;
    }
  }

  return true;
}

Boolean DefaultObjectPermission::implies(
    const std::shared_ptr<ObjectPermission>& p) {
  DefaultObjectPermission* dp = (DefaultObjectPermission*)p.get();

  Int i = 0;
  for (const std::set<String>& otherPart : dp->_parts) {
    if (_parts.size() - 1 < i) {
      return true;
    } else {
      const std::set<String>& part = _parts[i];
      if (part.find(u8"*") == part.end() && !ContainsAll(part, otherPart)) {
        return false;
      }
      ++i;
    }
  }

  for (; i < _parts.size(); ++i) {
    const std::set<String>& part = _parts[i];
    if (part.find(u8"*") == part.end()) {
      return false;
    }
  }

  return true;
}

}  // namespace user
}  // namespace gemini
