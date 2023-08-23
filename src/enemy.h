#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "explosion.h"

using namespace sf;

class Enemy{
    public:
        Texture enemyTexture;
        Sprite enemySprite;
        int hp;
        int shootTimer;
        int spawnTimer;
        int spawnSide; //only applies to strafers
        int currentDirection; //only applies to boss enemy
        

        Enemy();
        virtual ~Enemy();

        //create enemies/increase spawn timers/keep track of collisions
        virtual void update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver) = 0;

        //move enemies
        virtual void move() = 0;

        //reset enemies after game ends
        virtual void reset() = 0;
};


#endif