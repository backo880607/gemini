#ifndef GEMINI_NETWORK_Server_INCLUDE
#define GEMINI_NETWORK_Server_INCLUDE
#include "Socket.h"

#include <mutex>

namespace gemini {

class ServerSocket;
class GEMINI_NETWORK_API Server {
 public:
  Server();
  virtual ~Server();

  /**
   * @brief 运行服务
   * @return 是否成功启动服务
   * @retval false 服务启动失败
   * @retval true  服务启动成功
   */
  virtual Boolean start() = 0;

  /**
   * @brief 停止服务
   *
   */
  virtual void stop() = 0;
};

}  // namespace gemini
#endif  // !GEMINI_NETWORK_Server_INCLUDE