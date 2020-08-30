//
// Created by TheNasCrazy on 18/01/2018.
//

#include <iostream>
#include <cstring>
#include <string>
#include "NetworkManager.hpp"

int main()
{
    NetworkManager *client = new NetworkManager();
    Packet tmp;
    std::string data;

    client->init(CLIENT, "127.0.0.1", 4343);
    tmp.data.index = 1;
    inet_pton(AF_INET, "127.0.0.1", &tmp.dest.sin_addr);
    tmp.dest.sin_family = AF_INET;
    tmp.dest.sin_port = htons(4242);
    while (42)
    {
        data.erase();
        std::getline(std::cin, data);
        std::strcpy(tmp.data.data, data.c_str());
        client->addSendPacketInList(tmp);
        std::cout << client->getSizeSendList() << std::endl;
    }
}
