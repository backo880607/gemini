#include "api/MsgQueue.h"

namespace gemini {
namespace api {

MsgQueue::MsgQueue() {}

MsgQueue::~MsgQueue() {}

void MsgQueue::push(const MsgData& msg) {
  if (!msg.valid()) return;

  std::unique_lock<mutex_type> locker(_mutex);
  _value.push(msg);
}

MsgData MsgQueue::get(Boolean bPop) {
  MsgData msg;
  std::unique_lock<mutex_type> locker(_mutex);
  if (_value.empty()) return msg;

  msg = _value.front();
  if (bPop) _value.pop();

  return msg;
}

void MsgQueue::pop() {
  std::unique_lock<mutex_type> locker(_mutex);
  _value.pop();
}

}  // namespace api
}  // namespace gemini