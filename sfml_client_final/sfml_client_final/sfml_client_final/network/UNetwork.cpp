//
// Created by thenascrazy on 24/01/18.
//

#include <unistd.h>
#include "UNetwork.hpp"

UNetwork::UNetwork() {
    _fd = this->Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

UNetwork::~UNetwork() {
    close(_fd);
}

int UNetwork::Socket(int af, int type, int protocol) {
    int server = socket(af, type, protocol);
    if (server == -1)
    {
        std::cout << "Erreur initialisation socket : " << server;
        return -1;
    }
    return (server);
}

int UNetwork::Bind(int fd, struct sockaddr *addr, int addrlen) {
    int res = bind(fd, addr, addrlen);
    if (res != 0) {
        std::cout << "Erreur bind : " << res;
        return -1;
    }
    return res;
}

int UNetwork::Listen(int fd, int backlog) {
    int res = listen(fd, backlog);
    if (res != 0)
    {
        std::cout << "Erreur listen : ";
        return -1;
    }
    return (res);
}

int UNetwork::Server(int port) {
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(static_cast<u_short>(port));
    _addr.sin_family = AF_INET;
    int res = this->Bind(_fd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
    if (res == -1)
        return (-1);
    std::cout << "Serveur demarre sur le port " << port << std::endl;
    return (0);
}

int UNetwork::Client(std::string ip, int port) {
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons((uint16_t)port);
    return (0);
}

void UNetwork::addSocket(int fd) {
    _fdList.push_back(fd);
}

std::vector<int> UNetwork::getFdList() const {
    return (_fdList);
}

int UNetwork::getSocket() const {
    return (_fd);
}

bool UNetwork::waitForReceive(struct timeval *time)
{
    FD_ZERO(&_readfds);
    FD_SET(_fd, &_readfds);
    select(_fd + 1, &_readfds, NULL, NULL, time);
    return FD_ISSET(_fd, &_readfds) != 0;
}

int UNetwork::SendTo(void const *data, size_t size, const sockaddr_in *dest_addr) {
    int pos = 0;

    while ((pos += sendto(this->_fd, &((char*)data)[pos], size - pos, 0, (sockaddr*)dest_addr, sizeof(sockaddr_in))) != (int)size && pos != -1);
    return (pos);
}

int UNetwork::ReceiveFrom(void *data, unsigned int size, sockaddr_in *dest_addr) {
    socklen_t len = sizeof(sockaddr_in);
    return (static_cast<int>(recvfrom(this->_fd, data, size, 0, (sockaddr *)dest_addr, &len)));
}
