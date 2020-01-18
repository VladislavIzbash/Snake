#pragma once

#include "INetwork.h"


class NetworkLocal: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;
};