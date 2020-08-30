//
// Created by TheNasCrazy on 15/01/2018.
//

#include "NetworkManager.hpp"

NetworkManager::NetworkManager() {
#ifdef _WIN32
    _network = new WNetwork();
#else
    _network = new UNetwork();
#endif
    _end = false;
    _network->addSocket(_network->getSocket());
}

NetworkManager::~NetworkManager() {
    _end = true;
}

int NetworkManager::init(TypeConnect type, std::string const &ip, int port) {
  int ret = 0;
    _port = port;
    _ip = ip;
    if (type == SERVER)
      ret = _network->Server(_port);
    else if (type == CLIENT)
      ret = _network->Client(_ip, _port);
    _thrd = new std::thread(&NetworkManager::manageNetwork, this);
    return ret;
}

void NetworkManager::manageNetwork(void) {
    struct timeval	time;
    Packet tmp;

    time.tv_sec = 0;
    time.tv_usec = 10;

    while (!isEnd())
    {
        if (_network->waitForReceive(&time))
        {
            int size = _network->ReceiveFrom(&tmp.data, sizeof(PacketData), &tmp.dest);
            if (size > 0)
            {
                addReceivePacketInList(tmp);
            }
        }
        while (getSizeSendList())
        {
            tmp = getSendPacket();
            _network->SendTo(&tmp.data, sizeof(PacketData), &tmp.dest);
        }
    }
}

bool NetworkManager::isEnd(){
    return (_end);
}

void NetworkManager::addSendPacketInList(Packet packet) {
    _sndmtx.lock();
    _packetSendList.push_back(packet);
    _sndmtx.unlock();
}

void NetworkManager::addReceivePacketInList(Packet packet) {
    _rcvmtx.lock();
    _packetReceiveList.push_back(packet);
    _rcvmtx.unlock();
}

int NetworkManager::getSizeSendList() {
    int size = 0;
    _sndmtx.lock();
    size = _packetSendList.size();
    _sndmtx.unlock();
    return (size);
}

int NetworkManager::getSizeReceiveList() {
    int size = 0;
    _rcvmtx.lock();
    size = _packetReceiveList.size();
    _rcvmtx.unlock();
    return (size);
}

Packet NetworkManager::getSendPacket() {
    _sndmtx.lock();
    Packet tmp = _packetSendList[0];
    _packetSendList.erase(_packetSendList.begin());
    _sndmtx.unlock();
    return (tmp);
}

Packet NetworkManager::getReceivePacket() {
    _rcvmtx.lock();
    Packet tmp = _packetReceiveList[0];
    _packetReceiveList.erase(_packetReceiveList.begin());
    _rcvmtx.unlock();
    return (tmp);
}
