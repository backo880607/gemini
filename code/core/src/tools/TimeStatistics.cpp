#include "../../public/tools/TimeStatistics.h"
#include "../../public/tools/File.h"

namespace gemini {

TimeStatisticsMgr::TimeStatisticsMgr() {}

TimeStatisticsMgr::~TimeStatisticsMgr() {}

void TimeStatisticsMgr::writeTmStatistics(const String& str) {
  File logger(getPath().c_str());
  if (!logger.open(std::ios_base::out | std::ios_base::app)) return;

  logger.write(str, true);
}

void TimeStatisticsMgr::flushTmStatistics() {
  File logger(getPath().c_str());
  if (!logger.open(std::ios_base::out | std::ios_base::app)) return;

  for (FunTimeStatistics fun : _funStatistics) {
    logger.write(fun(), false);
  }
  logger.flush();
}

String TimeStatisticsMgr::getPath() {
  static String path;
  if (path.empty()) {
    FilePath filePath = FilePath::currentPath().append("LOG");
    if (!filePath.isExist()) filePath.createDirectories();

    filePath.append("TimeStatistics");
    if (!filePath.isExist()) filePath.createDirectories();

    filePath.append("TimeStatistics.txt");
    path = filePath.string();
  }

  return path;
}

}  // namespace gemini