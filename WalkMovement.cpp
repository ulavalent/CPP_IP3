#include "enemy_movement.h"
#include <cmath>

WalkMovement::WalkMovement(int walkSpeed) : walkSpeed(walkSpeed) {
    if (walkSpeed <= 0) {
        throw invalid_argument("Walk speed must be positive");
    }
}

void WalkMovement::move(int& x, int& y, int targetX, int targetY) {
    int dx = targetX - x;
    int dy = targetY - y;
    
    if (dx == 0 && dy == 0) {
        return;
    }
    
    double distance = sqrt(dx * dx + dy * dy);
    double normalizedDx = dx / distance;
    double normalizedDy = dy / distance;
    
    int moveX = static_cast<int>(normalizedDx * walkSpeed);
    int moveY = static_cast<int>(normalizedDy * walkSpeed);
    
    if (moveX == 0 && dx != 0) {
        moveX = (dx > 0) ? 1 : -1;
    }
    if (moveY == 0 && dy != 0) {
        moveY = (dy > 0) ? 1 : -1;
    }
    
    x += moveX;
    y += moveY;
}

string WalkMovement::getName() const {
    return "Walk Movement (Speed: " + to_string(walkSpeed) + ")";
}