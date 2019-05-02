#include "../include/boss.hpp"

using namespace patapongame;

Boss::Boss() {

}

Boss::Boss(std::string set_name, size_t set_health, size_t set_strength, std::string image_name) {
    name_ = set_name;
    health_ = set_health;
    max_health_ = set_health;
    strength_ = set_strength;
    image_.load(image_name);
    icon_.load(image_name);
    hitbox_.setPhysics(3, 0, 1);
}

std::string Boss::getName() {
    return name_;
}

int Boss::getHealth() {
    return health_;
}

int Boss::getMaxHealth() {
    return max_health_;
}

size_t Boss::getStrength() {
    return strength_;
}

ofImage & Boss::getImage() {
    return image_;
}

ofImage & Boss::getIcon() {
    return icon_;
}

ofxBox2dRect & Boss::getHitbox() {
    return hitbox_;
}

bool Boss::takeDamage(int attack_strength) {
    std::cout << "AUGMENTED DAMAGE: " << std::to_string(attack_strength) << std::endl;

    std::cout << "HEALTH BEFORE ATTACK: " << std::to_string(health_) << std::endl;

    health_ -= attack_strength;
    std::cout << "HEALTH AFTER ATTACK: " << std::to_string(health_) << std::endl;
    if (health_ <= 0) {
        health_ = 0;
        return false;
    }

    return true;
}


