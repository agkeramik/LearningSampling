#ifndef TCPCONNECTOR_H
#define TCPCONNECTOR_H

#include "tcpstream.h"

class TCPConnector
{
public:
   TCPStream* connect(int port, const char* server);

 private:
   int resolveHostName(const char* host, struct in_addr* addr);
};

#endif // TCPCONNECTOR_H
