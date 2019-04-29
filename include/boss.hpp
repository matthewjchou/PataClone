#pragma once

#include <string>

namespace patapongame {
    class Boss {
        std::string name_;
        int health_;
        size_t strength_;
    public:
        Boss();
        Boss(std::string set_name, size_t set_health, size_t set_strength);

        std::string getName();
        int getHealth();
        size_t getStrength(); 

        bool takeDamage(size_t attack_strength);
    };
}
