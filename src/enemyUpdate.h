#ifndef ENEMYUPDATE_H
#define ENEMYUPDATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "bomberEnemy.h"
#include "player.h"
#include "strafingEnemy.h"
#include "bossEnemy.h"


class EnemyUpdate{
    public:
        static void update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, BomberEnemy& bomberEnemy, StrafingEnemy& strafingEnemy, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver);
};


#endif
