//
// Created by TheNasCrazy on 18/01/2018.
//

#include "NetworkManager.hpp"

int main()
{
    NetworkManager *server = new NetworkManager();
    std::vector<Packet> tmplist;
    Packet tmp;

    server->init(SERVER, "", 4242);
    while (42) {
        while (server->getSizeReceiveList()) {
//            std::cout << server->getSizeReceiveList() << std::endl;
            tmp = server->getReceivePacket();
            std::cout << tmp.data.index << " :" << tmp.data.data << std::endl;
        }
    }
}
