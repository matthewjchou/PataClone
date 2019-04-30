#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include <string>

namespace patapongame {
    class Boss {
        std::string name_;
        int health_;
        size_t strength_;

        ofImage image_;
        ofxBox2dRect hitbox_;
    public:
        Boss();
        Boss(std::string set_name, size_t set_health, size_t set_strength, std::string image_name);

        std::string getName();
        int getHealth();
        size_t getStrength(); 
        ofImage & getImage();
        ofxBox2dRect & getHitbox();

        bool takeDamage(size_t attack_strength);
    };
}
