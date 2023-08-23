#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "bomberEnemy.h"
#include "menu.h"
#include "strafingEnemy.h"
#include "bossEnemy.h"
#include "wall.h"
#include "explosion.h"
#include "firingAnimation.h"
//#include "powerUps.h"


using namespace sf;

class Bullet{
    public:
        Texture bulletTexture;
        Sprite bulletSprite;
        Vector2f currVelocity;
        float maxSpeed;
        int typeOfEnemy;
        //0 - bomber
        //1 - strafer
        //2 - boss
        int hp;

        Bullet();
        Bullet(int typeOfEnemy);
        ~Bullet();

        static void updatePB(std::vector<std::unique_ptr<Bullet> >& playerBullets, const Player& player, int& playerShootTimer, int& score, const Vector2f& aimDir, const Vector2f& aimDirNorm, RenderWindow& window);
        static void updateEB(std::vector<std::unique_ptr<Bullet> >& enemyBullets, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, RenderWindow& window, Menu& menu, std::vector<std::unique_ptr<Wall> >& walls, std::vector<std::unique_ptr<Bullet> >& playerBullets, const int& instaKillTimer, std::vector<std::unique_ptr<Explosion> >& explosions, std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations);
        static void reset(std::vector<std::unique_ptr<Bullet> >& playerBullets, std::vector<std::unique_ptr<Bullet> >& enemyBullets);
};



#endif