#ifndef POWERUPS_H
#define POWERUPS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "bullet.h"
#include "player.h"
#include "wall.h"
#include "explosion.h"

using namespace sf;


class PowerUp{
    public:
        Texture powerUpTexture;
        Sprite powerUpSprite;
        std::string powerUpType;
        int hp;
        bool spawnSide; //0 - left, 1 - right
        PowerUp(std::string powerUp, bool spawnSide);
        ~PowerUp();

        static void update(int& spawnTimer, std::unique_ptr<PowerUp>& powerUp, int& instaKillTimer);
        static void move(RenderWindow& window, std::unique_ptr<PowerUp>& powerUp, std::vector<std::unique_ptr<Bullet> >& playerBullets, std::vector<std::unique_ptr<Wall> >& walls, Player& player, int& instaKillTimer, std::vector<std::unique_ptr<Explosion> >& explosions);
};


#endif