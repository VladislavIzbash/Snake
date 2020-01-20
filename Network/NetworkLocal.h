#pragma once

#include "Network.h"
#include "../Object.h"


class NetworkLocal: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;

    void initObjectList(std::vector<std::unique_ptr<IObject>>& object_list) override;
};