#include "../include/pon.hpp"

Pon::Pon() {
    alive_ = true;
    health_ = kDefaultHealth;
    strength_ = kDefaultStrength;
}

int Pon::getHealth() {
    return health_;
}

size_t Pon::getStrength() {
    return strength_;
}

void Pon::updateHealth(int delta) {
    health_ += delta;

    if (health_ < 0) {
        alive_ = false;
    }
}

bool Pon::isAlive() {
    return alive_;
}
