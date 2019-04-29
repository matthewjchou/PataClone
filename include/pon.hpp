#pragma once

#include <string>

class Pon {
    bool alive_;
    int health_;
    size_t strength_;

public:
    static const int kDefaultHealth = 500;
    static const size_t kDefaultStrength = 50;

    Pon();

    int getHealth();
    size_t getStrength();

    void updateHealth(int delta);
    bool isAlive();


};
