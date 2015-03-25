#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include "stream.h"

using namespace std;

class TCPStream:public Stream
{
    int     m_sd;
    string  m_peerIP;
    int     m_peerPort;

  public:
    friend class TCPAcceptor;
    friend class TCPConnector;

    virtual ~TCPStream();

    virtual ssize_t send(const char* buffer, size_t len);
    virtual ssize_t receive(char* buffer, size_t len);

    string getPeerIP();
    int getPeerPort();

  private:
    TCPStream(int sd, struct sockaddr_in* address);
    TCPStream();
    TCPStream(const TCPStream& stream);
};







#endif
