#pragma once

class Pon {
    bool alive_;
    int health_;
    int strength_;

public:
    static const int kDefaultHealth = 50;
    static const int kDefaultStrength = 5;

    Pon();

    void updateHealth(int delta);
    bool isAlive();
};
