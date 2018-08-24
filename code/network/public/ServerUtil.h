#ifndef GEMINI_NETWORK_ServerUtil_INCLUDE
#define GEMINI_NETWORK_ServerUtil_INCLUDE
#include "NetworkExport.h"

namespace gemini {

class GEMINI_NETWORK_API ServerUtil {
 public:
  static Boolean startTCPServer();
  static void stopTCPServer();

  static Boolean startHTTPServer();
  static void stopHTTPServer();
};

}  // namespace gemini
#endif  // GEMINI_NETWORK_ServerUtil_INCLUDE
