#include "enemy_movement.h"
#include <memory>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void drawField(const vector<Enemy>& enemies, int playerX, int playerY, int width = 20, int height = 10) {
    vector<vector<char>> field(height, vector<char>(width, '.'));
    
    if (playerX >= 0 && playerX < width && playerY >= 0 && playerY < height) {
        field[playerY][playerX] = 'P';
    }
    
    for (size_t i = 0; i < enemies.size(); i++) {
        int x = enemies[i].getX();
        int y = enemies[i].getY();
        
        if (x >= 0 && x < width && y >= 0 && y < height) {
            if (enemies[i].getCurrentStrategy().find("Walk") != string::npos) {
                field[y][x] = 'W';
            } else if (enemies[i].getCurrentStrategy().find("Teleport") != string::npos) {
                field[y][x] = 'T';
            } else {
                field[y][x] = 'E';
            }
        }
    }
    
    for (const auto& row : field) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

int main() {
    cout << "Enemy Movement - Strategy Design Pattern Demonstration" << endl;
    cout << "----------------------------------------------" << endl;
    
    try {
        vector<Enemy> enemies;
        
        enemies.push_back(Enemy("Walker", 2, 2));
        
        auto teleporter = make_unique<TeleportMovement>(3);
        enemies.push_back(Enemy(move(teleporter), "Teleporter", 8, 8));
        
        auto fastWalker = make_unique<WalkMovement>(2);
        enemies.push_back(Enemy(move(fastWalker), "Fast Walker", 15, 3));
        
        int playerX = 10;
        int playerY = 5;
        
        cout << "Starting simulation..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        
        for (int step = 0; step < 10; step++) {
            clearScreen();
            cout << "Step " << (step + 1) << endl;
            
            for (auto& enemy : enemies) {
                enemy.update(playerX, playerY); // polimorfizmas
                cout << enemy.getInfo() << endl; // polimorfizmas
            }
            
            cout << "\nField display (P = Player, W = Walker, T = Teleporter):" << endl;
            drawField(enemies, playerX, playerY);
            
            if (step == 4) {
                cout << "\nChanging strategies..." << endl;
                
                enemies[0].setMovementStrategy(make_unique<TeleportMovement>(2));
                
                enemies[1].setMovementStrategy(make_unique<WalkMovement>(3));
            }
            
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        
        cout << "\nSimulation complete!" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}