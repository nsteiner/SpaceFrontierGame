#include "wall.h"
#include <iostream>

Wall::Wall(int i){
    wall.setSize(Vector2f(150.f, 25.f));
    hp = 3;
    null = false;
    wall.setOrigin(150.f, 0.f);
    wallTexture.loadFromFile("Textures/wall.png");
    wall.setTexture(&wallTexture);
    wallNumber = i;
    wallColor = wall.getFillColor();
    hitByRocket = false;

};

Wall::~Wall(){};

void Wall::updateWalls(std::vector<std::unique_ptr<Wall> >& walls, std::vector<std::unique_ptr<Enemy> >& enemies, std::vector<std::unique_ptr<Explosion> >& explosions, const Player& player){
    for (size_t j = 0; j < enemies.size(); j++) {
        for (size_t i = 0; i <= 12; i++) {
            if(walls[i]->null == false){
                if (walls[i]->wall.getGlobalBounds().intersects(enemies[j]->enemySprite.getGlobalBounds()) && !walls[i]->hitByRocket) {
                    Explosion::createExplosion(explosions, Vector2f(enemies[j]->enemySprite.getPosition().x, enemies[j]->enemySprite.getPosition().y + enemies[j]->enemySprite.getGlobalBounds().height / 3), false, false, player);
                    enemies.erase(enemies.begin() + j);
                    walls[i]->hp--;
                }
                //set transparency of wall
                if (walls[i]->hp <= 0) {
                    if(walls[i]->hitByRocket){
                        walls[i]->wallColor.a -= 0.0000005;
                        walls[i]->wall.setFillColor(walls[i]->wallColor);
                        if(walls[i]->wallColor.a <= 0){
                            walls[i]->null = true;
                            walls[i]->wall.setPosition(0.f, 0.f);
                        }
                    }
                    else{
                        walls[i]->null = true;
                        walls[i]->wall.setPosition(0.f, 0.f);
                    }
                }
                else if(walls[i]->hp == 1){
                    walls[i]->wallColor.a = 64;
                    walls[i]->wall.setFillColor(walls[i]->wallColor);
                }
                else if(walls[i]->hp == 2){
                    walls[i]->wallColor.a = 128;
                    walls[i]->wall.setFillColor(walls[i]->wallColor);
                }
            } 
        }
    }
}

void Wall::drawWalls(RenderWindow& window, std::vector<std::unique_ptr<Wall> >& walls, const Player& player){
    for(size_t i = 0; i < walls.size(); i++){
        if(walls[i]->null == false){
            if(walls[i]->wallNumber <= 4){
                walls[i]->wall.setPosition(Vector2f(walls[i]->wallNumber * 150.f, 650.f));
                window.draw(walls[i]->wall);
            }
            else if(walls[i]->wallNumber <= 9){
                walls[i]->wall.setPosition(Vector2f((walls[i]->wallNumber - 4) * 150.f - 75.f, 625.f));
                window.draw(walls[i]->wall);
            }
            else{
                walls[i]->wall.setPosition(Vector2f((walls[i]->wallNumber - 9) * 150.f, 600.f));
                window.draw(walls[i]->wall);
            }
        }
        
    }
}

void Wall::reset(std::vector<std::unique_ptr<Wall> >& walls){
    walls.clear();

    for(int i = 1; i <= 14; i++){
        std::unique_ptr<Wall> wall = std::make_unique<Wall>(i);
        walls.push_back(std::move(wall));
    }
}
