#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include <string>
#include <netinet/in.h>
#include "tcpstream.h"

using namespace std;

class TCPAcceptor
{
    int    m_lsd;
    string m_address;
    int    m_port;
    bool   m_listening;

  public:
    TCPAcceptor(int port, const char* address="");
    virtual ~TCPAcceptor();

    int        start();
    TCPStream* accept();

  private:
    TCPAcceptor() {}
};

#endif // TCPACCEPTOR_H
