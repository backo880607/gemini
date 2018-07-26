#include "io/ExportHelper.h"
#include "io/IOProject.h"
#include "io/IOScheme.h"
#include "io/ImportHelper.h"
#include "io/controller/IOController.h"

namespace gemini {
DECLARE_CLASS_IMPL(IOController, BaseController)
void IOController::executeProject(ID projectID) {
  io::ImportHelper helper;
  io::IOProject::SPtr ioProject = get<io::IOProject>(projectID);
  IList::Iterator iter = ioProject->_schemes->iterator();
  while (iter.hasNext()) {
    io::IOScheme::SPtr ioScheme = iter.next<io::IOScheme>();
    if (ioScheme->_type == io::IOSchemeType::None) {
      continue;
    }

    if (ioScheme->_type == io::IOSchemeType::Export) {
    } else {
      helper.execute();
    }
  }
}
}  // namespace gemini