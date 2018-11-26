#ifndef GEMINI_API_MsgTransmit_INCLUDE
#define GEMINI_API_MsgTransmit_INCLUDE
#include <thread>
#include "MsgQueue.h"

namespace gemini {
namespace api {

class MsgTransmit {
  typedef std::shared_ptr<std::thread> thread_type;

 public:
  MsgTransmit(MsgQueue& request, MsgQueue& response);
  ~MsgTransmit();

  /**
   * @brief 启动请求线程和响应线程进行消息传输
   */
  void start();

  /**
   * @brief 停止请求线程和响应线程的消息传输
   */
  void stop();

 private:
  static void proRequest(MsgTransmit* transmit);
  static void proResponse(MsgTransmit* transmit);

 private:
  MsgQueue& _request;           ///< 请求队列
  MsgQueue& _response;          ///< 应答队列
  thread_type _threadRequest;   ///< 请求线程
  thread_type _threadResponse;  ///< 响应线程
};

}  // namespace api
}  // namespace gemini
#endif  // GEMINI_API_MsgTransmit_INCLUDE