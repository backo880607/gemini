#ifndef GEMINI_NETWORK_IOServicePool_INCLUDE
#define GEMINI_NETWORK_IOServicePool_INCLUDE
#include "Server.h"

namespace gemini {

class IOServicePool final : public noncopyable {
 public:
  typedef boost::asio::io_service service_type;

 private:
  typedef std::shared_ptr<service_type> io_service_sptr;
  typedef std::shared_ptr<service_type::work> work_sptr;
  typedef std::shared_ptr<std::thread> thread_sptr;

 public:
  IOServicePool();
  ~IOServicePool();

  static IOServicePool& instance() {
    static IOServicePool ins;
    return ins;
  }

  /**
   * @brief 启动ioservice池。
   *
   */
  void start();

  /**
   * @brief 停止池中的所有ioservice
   *
   */
  void stop();

  /**
   * @brief 从ioservice池中获取一个ioservice
   * 策略是顺序的依次从ioservice池中取。
   *
   * @return service_type&
   */
  service_type& get_io_service();

 private:
  std::size_t _pool_size;  ///< ioservice池的大小。
  std::size_t _next_io_service;  ///< io_service���л�ȡio_service������
  std::vector<io_service_sptr> _io_services;  ///< io_service��
  std::vector<work_sptr> _work;
  std::vector<thread_sptr> _threads;  ///< �̳߳أ�ÿ���̵߳�������һ��io_service
  std::mutex _mutex;
};

}  // namespace gemini
#endif  // !GEMINI_NETWORK_IOServicePool_INCLUDE
