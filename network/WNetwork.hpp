//
// Created by TheNasCrazy on 16/01/2018.
//

#ifndef NETWORK_WNETWORK_HPP
#define NETWORK_WNETWORK_HPP

#include "INetwork.hpp"
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <vector>

class WNetwork : public INetwork{
private:
    int _fd;
    sockaddr_in _addr;
    WSAData _wsaData;
    std::vector <int> _fdList;
    fd_set _readfds;
    fd_set _writefds;
public:
    WNetwork();
    ~WNetwork();
    virtual int Socket(int af, int type, int protocol);
    virtual int Bind(int fd, struct sockaddr *addr, int addrlen);
    virtual int Listen(int fd, int backlog);
    virtual int Server(int);
    virtual int Client(std::string, int);
    virtual void addSocket(int);
    virtual std::vector<int> getFdList() const;
    virtual int getSocket() const;
    virtual bool waitForReceive(struct timeval *);
    virtual int SendTo(void const *data, size_t size, const sockaddr_in *dest_addr);
    virtual int ReceiveFrom(void * data, unsigned int size, sockaddr_in * dest_addr);
};


#endif //NETWORK_WNETWORK_HPP
