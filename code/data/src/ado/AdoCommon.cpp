#include "../../include/ado/AdoCommon.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace sql {

String AdoError::format(const _com_error& e) {
  String msg = StringUtil::SPrintf("HRESULT: 0x%08lx; Error: %s", e.Error(),
                                   e.ErrorMessage());
  if (e.ErrorInfo()) {
    msg.append("\nSource: ")
        .append(e.Source())
        .append("; Description: ")
        .append(e.Description());
  }

  return msg;
}

}  // namespace sql
}  // namespace gemini