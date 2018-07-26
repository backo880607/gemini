#include "api/MsgTransmit.h"

namespace gemini {

MsgTransmit::MsgTransmit(MsgQueue& request, MsgQueue& response)
    : _request(request), _response(response) {}

MsgTransmit::~MsgTransmit() { stop(); }

void MsgTransmit::start() {
  _threadRequest = thread_type(new std::thread(proRequest, this));
  _threadResponse = thread_type(new std::thread(proResponse, this));
}

void MsgTransmit::stop() {
  if (_threadRequest) {
    //_threadRequest->interrupt();
    _threadRequest->join();
    _threadRequest = nullptr;
  }

  if (_threadResponse) {
    //_threadResponse->interrupt();
    _threadResponse->join();
    _threadResponse = nullptr;
  }
}

void MsgTransmit::proRequest(MsgTransmit* transmit) {
  do {
    MsgData msg = transmit->_request.get();
    if (msg.valid()) {
      transmit->_response.push(msg);
    }

    transmit->_request.pop();
  } while (true);
}

void MsgTransmit::proResponse(MsgTransmit* transmit) {}

}  // namespace gemini