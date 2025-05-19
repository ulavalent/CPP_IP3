#include "enemy_movement.h"
#include <cassert>
#include <iostream>
#include <cmath>

class FlyMovement : public MovementStrategy {
public:
    FlyMovement(int flySpeed = 2, int maxHeight = 5);
    
    void move(int& x, int& y, int targetX, int targetY) override;
    
    string getName() const override;
    
    int getCurrentHeight() const;
    void setMaxHeight(int height);
    
private:
    int flySpeed;
    int maxHeight;
    int currentHeight;
};

void testFlyMovement() {
    cout << "Testing FlyMovement implementation...\n";
    
    FlyMovement flyStrategy(2, 4);
    
    // Test initial parameters
    assert(flyStrategy.getCurrentHeight() == 0);
    assert(flyStrategy.getName() == "Fly Movement (Speed: 2, MaxHeight: 4)");
    
    // Test changing maximum height
    flyStrategy.setMaxHeight(6);
    assert(flyStrategy.getName() == "Fly Movement (Speed: 2, MaxHeight: 6)");
    
    // Test movement
    int x = 0, y = 0;
    int targetX = 10, targetY = 0;
    
    // Check if the enemy moves correctly
    // Horizontal movement
    flyStrategy.move(x, y, targetX, targetY);
    assert(x == 2);
    assert(y == 0);
    assert(flyStrategy.getCurrentHeight() > 0);
    
    // Further movement
    flyStrategy.move(x, y, targetX, targetY);
    assert(x == 4); // Move another 2 steps
    
    // Test diagonal movement
    x = 0;
    y = 0;
    targetX = 10;
    targetY = 10;
    
    // Perform several movement steps
    for (int i = 0; i < 3; i++) {
        int oldX = x;
        int oldY = y;
        flyStrategy.move(x, y, targetX, targetY);
        
        // Ensure movement is in the correct direction
        assert(x > oldX);
        assert(y > oldY);
        
        // Check if movement speed is correct
        double distance = sqrt(pow(x - oldX, 2) + pow(y - oldY, 2));
        assert(abs(distance - flyStrategy.getCurrentHeight()/2.0 - 2.0) < 0.5); // Allow a small error margin
    }
    
    // Test if the enemy reaches the target
    x = 9;
    y = 9;
    targetX = 10;
    targetY = 10;
    
    flyStrategy.move(x, y, targetX, targetY);
    assert(x == 10);
    assert(y == 10);
    
    cout << "All FlyMovement tests passed!\n";
}

int main() {
    try {
        testFlyMovement();
        return 0;
    } catch (const exception& e) {
        cerr << "Test failed: " << e.what() << endl;
        return 1;
    }
}