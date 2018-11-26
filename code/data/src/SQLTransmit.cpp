#include "../include/SQLTransmit.h"

namespace gemini {
namespace sql {

SQLTransmit::data_type SQLTransmit::s_emptyData;
SQLTransmit::SQLTransmit() {}

SQLTransmit::~SQLTransmit() { stop(); }

void SQLTransmit::start() {
  _threadQueue =
      std::shared_ptr<boost::thread>(new boost::thread(boost::bind(run, this)));
}

void SQLTransmit::stop() {
  wait();
  if (_threadQueue) {
    _threadQueue->interrupt();
    _threadQueue->join();
    _threadQueue = nullptr;
  }
}

void SQLTransmit::wait() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> locker(_mutex);
    if (_datas.empty()) {
      break;
    }
  }
}

void SQLTransmit::push(const data_type& data) {
  if (data.stmts.empty()) {
    return;
  }

  std::unique_lock<std::mutex> locker(_mutex);
  _datas.push(data);
}

SQLTransmit::data_type& SQLTransmit::get() {
  std::unique_lock<std::mutex> locker(_mutex);
  return _datas.empty() ? s_emptyData : _datas.front();
}

void SQLTransmit::pop() {
  std::unique_lock<std::mutex> locker(_mutex);
  _datas.pop();
}

void SQLTransmit::run(SQLTransmit* transmit) {
  do {
    boost::this_thread::interruption_point();
    data_type& data = transmit->get();
    if (data.stmts.empty()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      continue;
    } else if (data.conn.isConnected()) {
      try {
        data.conn.setAutoCommit(false);
        data.conn.begin();
        for (Statement stmt : data.stmts) {
          stmt.execute();
        }
        data.conn.commit();
      } catch (Exception& exc) {
        data.conn.rollback();
      } catch (std::exception& exc) {
        String message = exc.what();
        data.conn.rollback();
	  }
    }
    transmit->pop();
  } while (true);
}

}  // namespace sql
}  // namespace gemini