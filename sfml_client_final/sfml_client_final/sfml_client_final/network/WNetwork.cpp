//
// Created by TheNasCrazy on 16/01/2018.
//

#include "WNetwork.hpp"

#pragma comment(lib, "Ws2_32.lib")

WNetwork::WNetwork() {
    WSAStartup(MAKEWORD(2, 2), &_wsaData);
    _fd = this->Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

WNetwork::~WNetwork() {
    closesocket(static_cast<SOCKET>(_fd));
    WSACleanup();
}

int WNetwork::Socket(int af, int type, int protocol) {
    SOCKET server = socket(af, type, protocol);
    if (server == INVALID_SOCKET)
    {
        std::cout << "Erreur initialisation socket : " << WSAGetLastError();
        return -1;
    }
    return (server);
}

int WNetwork::Bind(int fd, struct sockaddr *addr, int addrlen) {
    int res = bind(static_cast<SOCKET>(fd), addr, addrlen);
    if (res != 0) {
        std::cout << "Erreur bind : " << WSAGetLastError();
        return -1;
    }
    return res;
}

int WNetwork::Listen(int fd, int backlog) {
    int res = listen(static_cast<SOCKET>(fd), backlog);
    if (res != 0)
    {
        std::cout << "Erreur listen : " << WSAGetLastError();
        return -1;
    }
    return (res);
}

int WNetwork::Server(int port) {
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(static_cast<u_short>(port));
    _addr.sin_family = AF_INET;
    int res = this->Bind(_fd, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
    if (res == -1)
        return (-1);
    std::cout << "Serveur demarre sur le port " << port << std::endl;
    return (0);
}

int WNetwork::Client(std::string ip, int port) {
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons((uint16_t)port);
    return (0);
}

void WNetwork::addSocket(int fd) {
    _fdList.push_back(fd);
}

std::vector<int> WNetwork::getFdList() const {
    return (_fdList);
}

int WNetwork::getSocket() const {
    return (_fd);
}

bool WNetwork::waitForReceive(struct timeval *time)
{
    FD_ZERO(&_readfds);
    FD_SET(_fd, &_readfds);
    select(_fd + 1, &_readfds, NULL, NULL, time);
    return FD_ISSET(_fd, &_readfds) != 0;
}

int WNetwork::SendTo(void const *data, size_t size, const sockaddr_in *dest_addr) {
    DWORD total;
    DWORD byte;
    WSABUF tmp;

    total = 0;
    byte = 0;
    while (total != size)
    {
        tmp.buf = &((char*)data)[total];
        tmp.len = size - total;
        if (static_cast<int>(WSASendTo(static_cast<SOCKET>(_fd), &tmp, 1, &byte, 0, (SOCKADDR*)dest_addr, sizeof(SOCKADDR), NULL, NULL)) != 0) {
            std::cout << "Erreur send : " << WSAGetLastError() << std::endl;
            return -1;
        }
        total += byte;
    }
    return total;
}

int WNetwork::ReceiveFrom(void *data, unsigned int size, sockaddr_in *dest_addr) {
    DWORD	byte = 0;
    WSABUF tmp;
    DWORD flag = 0;
    socklen_t addrlen = sizeof(sockaddr_in);

    tmp.buf = (char*)data;
    tmp.len = size;
    if (static_cast<int>(WSARecvFrom(this->_fd, &tmp, 1, &byte, &flag, (SOCKADDR*)dest_addr, &addrlen, NULL, NULL)) != 0)
        return -1;
    return static_cast<int>(byte);
}

