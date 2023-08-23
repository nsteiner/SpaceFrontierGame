#ifndef STRAFINGENEMY_H
#define STRAFINGENEMY_H

#include "enemy.h"
#include "explosion.h"

class StrafingEnemy: public Enemy{
    public:
        StrafingEnemy();
        ~StrafingEnemy();

        virtual void update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver);
        virtual void move();
        virtual void reset();
};

#endif