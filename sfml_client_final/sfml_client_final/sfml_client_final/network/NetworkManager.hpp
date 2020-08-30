//
// Created by TheNasCrazy on 15/01/2018.
//

#ifndef NETWORK_NETWORKMANAGER_HPP
#define NETWORK_NETWORKMANAGER_HPP
#define READSIZE (4096)

//#include <Winsock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#ifdef _WIN32
 #include "WNetwork.hpp"
#else
#include "UNetwork.hpp"
#endif



class NetworkManager {
private:
    INetwork *_network;
    std::thread *_thrd;
    std::mutex _sndmtx;
    std::mutex _rcvmtx;
    bool _end;
    int _port;
    std::string _ip;
    std::vector<Packet> _packetSendList;
    std::vector<Packet> _packetReceiveList;

public:
    NetworkManager();
    ~NetworkManager();
    int init(TypeConnect, std::string const &, int);
    void manageNetwork(void);
    bool isEnd();
    void addSendPacketInList(Packet);
    std::vector<Packet> getSendPacketList() const;
    void addReceivePacketInList(Packet);
    std::vector<Packet> getReceivePackeList() const;
    int getSizeSendList();
    int getSizeReceiveList();
    Packet getSendPacket();
    Packet getReceivePacket();
 };

#endif //NETWORK_NETWORKMANAGER_HPP
