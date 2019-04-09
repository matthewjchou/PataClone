#include "../include/pon.h"

void Pon::UpdateHealth(int delta) {
    health_ += delta;

    if (health_ < 0) {
        alive_ = false;
    }
}

bool Pon::IsAlive() {
    return alive_;
}
