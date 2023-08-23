#ifndef BOMBERENEMY_H
#define BOMBERENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "enemy.h"
#include "player.h"
#include "explosion.h"

using namespace sf;

class BomberEnemy: public Enemy{
    public:
        BomberEnemy();
        virtual ~BomberEnemy();

        virtual void update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver);
        virtual void move();
        virtual void reset();
};



#endif