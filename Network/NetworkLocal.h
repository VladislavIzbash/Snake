#pragma once

#include "Network.h"
#include "../GameObject.h"


class NetworkLocal: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;

    void initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list) override;

    void update(std::vector<std::unique_ptr<GameObject>>& object_list) override;
};