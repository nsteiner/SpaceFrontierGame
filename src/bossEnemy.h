#ifndef BOSSENEMY_H
#define BOSSENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "enemy.h"
#include "player.h"

class BossEnemy: public Enemy{
    public:
    
        BossEnemy();
        virtual ~BossEnemy();

        virtual void update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver);
        virtual void move();
        virtual void reset();
};


#endif