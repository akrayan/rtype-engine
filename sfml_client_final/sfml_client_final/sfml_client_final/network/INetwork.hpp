//
// Created by TheNasCrazy on 16/01/2018.
//

#ifndef NETWORK_INETWORK_HPP
#define NETWORK_INETWORK_HPP

#include <vector>
#include <Winsock2.h>
#include <string>

enum TypeConnect {
    SERVER,
    CLIENT
};

struct PacketData {
    unsigned int    index;
    char data[512];
};

struct Packet {
    sockaddr_in dest;
    PacketData data;
};

class INetwork {
public:
    virtual int Socket(int af, int type, int protocol) = 0;
    virtual int Bind(int fd, struct sockaddr *addr, int addrlen) = 0;
    virtual int Listen(int fd, int backlog) = 0;
    virtual int Server(int) = 0;
    virtual int Client(std::string, int) = 0;
    virtual void addSocket(int) = 0;
    virtual std::vector<int> getFdList() const = 0;
    virtual int getSocket() const = 0;
    virtual bool waitForReceive(struct timeval *) = 0;
    virtual int SendTo(void const *data, size_t size, const sockaddr_in *dest_addr) = 0;
    virtual int ReceiveFrom(void * data, unsigned int size, sockaddr_in * dest_addr) = 0;
};

#endif //NETWORK_INETWORK_HPP
