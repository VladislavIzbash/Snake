#pragma once

#include "Network.h"
#include "../Object.h"


class NetworkLocal: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;

    void initObjectList(std::map<unsigned int, IObject>& object_list) override;
};