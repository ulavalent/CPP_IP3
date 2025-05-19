#include "enemy_movement.h"

// Įgyvendinimas pastovios klasės Enemy (stabilus aspektas)

Enemy::Enemy(const string& name, int startX, int startY) 
    : name(name), posX(startX), posY(startY) {
    // Numatyta strategija - WalkMovement
    strategy = make_unique<WalkMovement>();
}

Enemy::Enemy(unique_ptr<MovementStrategy> movementStrategy,
             const string& name, 
             int startX, 
             int startY)
    : name(name), posX(startX), posY(startY), strategy(move(movementStrategy)) {
    
    // Jei strategija nenurodyta, sukuriame numatytą
    if (!strategy) {
        throw invalid_argument("Movement strategy cannot be null");
    }
}

void Enemy::setMovementStrategy(unique_ptr<MovementStrategy> newStrategy) {
    if (!newStrategy) {
        throw invalid_argument("Movement strategy cannot be null");
    }
    strategy = move(newStrategy);
}

void Enemy::update(int targetX, int targetY) {
    try {
        strategy->move(posX, posY, targetX, targetY); // polimorfizmas
    } catch (const exception& e) {
        cerr << "Error during movement: " << e.what() << endl;
    }
}

string Enemy::getInfo() const {
    return name + " at position (" + to_string(posX) + ", " 
           + to_string(posY) + ") using " + strategy->getName(); // polimorfizmas
}

string Enemy::getCurrentStrategy() const {
    return strategy->getName(); // polimorfizmas
}

int Enemy::getX() const {
    return posX;
}

int Enemy::getY() const {
    return posY;
}