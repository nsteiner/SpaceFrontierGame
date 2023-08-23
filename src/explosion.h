#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "player.h"

using namespace sf;

class Explosion{
    public:
        Texture expTexture;
        Sprite  expSprite;
        IntRect spriteSource;
        Clock expClock;
        bool playerHit;
        double locationOnPlayer;

        Explosion(bool playerHit);
        ~Explosion();

        static void createExplosion(std::vector<std::unique_ptr<Explosion> >& explosions, const Vector2f& coordinates, const bool& bossEnemyHit, const bool& playerHit, const Player& player);
        static void update(std::vector<std::unique_ptr<Explosion> >& explosions, const Player& player);
};


#endif 