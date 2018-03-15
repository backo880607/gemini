#include "../../public/tcp/TCPServerConnection.h"

namespace gemini {

TCPServerConnection::TCPServerConnection()
{
}

TCPServerConnection::~TCPServerConnection()
{
}

Boolean TCPServerConnection::execute(const MsgData & msg)
{
	return Boolean();
}

void TCPServerConnection::close()
{
}

Boolean TCPServerConnection::proHeartBeatTimeout()
{
	return Boolean();
}

}