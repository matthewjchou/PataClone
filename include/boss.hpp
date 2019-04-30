#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include <string>

namespace patapongame {
    class Boss {
        std::string name_;
        int health_;
        int max_health_;
        size_t strength_;

        ofImage image_;
        ofImage icon_;

        ofxBox2dRect hitbox_;

    public:
        Boss();
        Boss(std::string set_name, size_t set_health, size_t set_strength, std::string image_name);

        std::string getName();
        int getHealth();
        int getMaxHealth();
        size_t getStrength(); 
        ofImage & getImage();
        ofImage & getIcon();
        ofxBox2dRect & getHitbox();

        bool takeDamage(int attack_strength);
    };
}
