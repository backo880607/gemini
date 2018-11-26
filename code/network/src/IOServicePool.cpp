#include "../include/IOServicePool.h"

namespace gemini {
namespace network {

IOServicePool::IOServicePool() : _pool_size(4), _next_io_service(0) {}

IOServicePool::~IOServicePool() { stop(); }

void IOServicePool::start() {
  std::unique_lock<std::mutex> lock(_mutex);
  for (std::size_t i = 0; i < _pool_size; ++i) {
    io_service_sptr ios(new boost::asio::io_service);
    _io_services.push_back(ios);
    _work.push_back(work_sptr(new boost::asio::io_service::work(*ios)));

    std::shared_ptr<std::thread> thread(
        new std::thread(boost::bind(&boost::asio::io_service::run, ios)));
    _threads.push_back(thread);
  }

  _next_io_service = 0;
}

void IOServicePool::stop() {
  std::unique_lock<std::mutex> lock(_mutex);
  for (std::size_t i = 0; i < _io_services.size(); ++i) {
    _io_services[i]->stop();
  }

  for (std::size_t i = 0; i < _threads.size(); ++i) {
    _threads[i]->join();
  }
  _threads.clear();
  _work.clear();
  _io_services.clear();
}

IOServicePool::service_type& IOServicePool::get_io_service() {
  std::unique_lock<std::mutex> lock(_mutex);
  service_type& io_service = *_io_services[_next_io_service];
  ++_next_io_service;
  if (_next_io_service == _io_services.size()) _next_io_service = 0;

  return io_service;
}

}  // namespace network
}  // namespace gemini