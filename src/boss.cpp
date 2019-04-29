#include "../include/boss.hpp"

using namespace patapongame;

Boss::Boss() {

}

Boss::Boss(std::string set_name, size_t set_health, size_t set_strength) {
    name_ = set_name;
    health_ = set_health;
    strength_ = set_strength;
}

std::string Boss::getName() {
    return name_;
}

int Boss::getHealth() {
    return health_;
}

size_t Boss::getStrength() {
    return strength_;
}

bool Boss::takeDamage(size_t attack_strength) {
    health_ -= attack_strength;
    if (health_ <= 0) {
        health_ = 0;
        return false;
    }

    return true;
}


