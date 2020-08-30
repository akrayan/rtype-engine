//
// Created by thenascrazy on 24/01/18.
//

#ifndef NETWORK_UNETWORK_HPP
#define NETWORK_UNETWORK_HPP

#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "INetwork.hpp"

class UNetwork : public INetwork {
private:
    int _fd;
    sockaddr_in _addr;
    std::vector <int> _fdList;
    fd_set _readfds;
    fd_set _writefds;
public:
    UNetwork();
    ~UNetwork();
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


#endif //NETWORK_UNETWORK_HPP
