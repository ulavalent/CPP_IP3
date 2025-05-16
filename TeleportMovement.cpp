#include "enemy_movement.h"
#include <cmath>

TeleportMovement::TeleportMovement(int cooldown) 
    : cooldown(cooldown), cooldownTimer(0) {
    if (cooldown < 0) {
        throw invalid_argument("Cooldown cannot be negative");
    }
}

void TeleportMovement::move(int& x, int& y, int targetX, int targetY) {
    if (cooldownTimer > 0) {
        cooldownTimer--;
        return;
    }
    
    int dx = targetX - x;
    int dy = targetY - y;
    double distance = sqrt(dx * dx + dy * dy);
    
    if (distance < 1) {
        return;
    }
    
    x = targetX;
    y = targetY;
    
    cooldownTimer = cooldown;
}

string TeleportMovement::getName() const {
    return "Teleport Movement (Cooldown: " + to_string(cooldown) + ")";
}