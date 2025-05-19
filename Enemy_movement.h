//EnemyMovement – strategy šablonas.
//Bazinė klasė MovementStrategy apibrėžia, kaip turi judėti priešas, o konkretūs WalkMovement, TeleportMovement realizuoja specifinį judėjimo būdą.
//Pastovi klasė Enemy deleguoja judėjimo atsakomybę pasirinktai strategijai.

#ifndef ENEMY_MOVEMENT_H
#define ENEMY_MOVEMENT_H

using namespace std;

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

class MovementStrategy {
public:
    virtual ~MovementStrategy() = default;
    
    virtual void move(int& x, int& y, int targetX, int targetY) = 0;
    
    virtual string getName() const = 0;
};

class WalkMovement : public MovementStrategy {
public:
    WalkMovement(int walkSpeed = 1);
    void move(int& x, int& y, int targetX, int targetY) override;
    string getName() const override;

private:
    int walkSpeed;
};

class TeleportMovement : public MovementStrategy {
public:
    TeleportMovement(int cooldown = 5);
    void move(int& x, int& y, int targetX, int targetY) override;
    string getName() const override;

private:
    int cooldown;
    int cooldownTimer;
};

class Enemy {
public:
    Enemy(const string& name = "Enemy", int startX = 0, int startY = 0);
    
    Enemy(unique_ptr<MovementStrategy> movementStrategy, 
          const string& name = "Enemy", 
          int startX = 0, 
          int startY = 0);
    
    void setMovementStrategy(unique_ptr<MovementStrategy> newStrategy);
    
    void update(int targetX, int targetY);
    
    string getInfo() const;
    
    int getX() const;
    int getY() const;
    
    string getCurrentStrategy() const;

private:
    string name;
    int posX;
    int posY;
    unique_ptr<MovementStrategy> strategy;
};

#endif