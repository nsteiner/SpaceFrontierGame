#ifndef FIRINGANIMATION_H
#define FIRINGANIMATION_H
#include "bossEnemy.h"
#include "bomberEnemy.h"
#include "strafingEnemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>  

using namespace sf;

class FiringAnimation{
    public:
        Texture firingTexture;
        Sprite firingSprite;
        IntRect firingSource;
        Clock animationClock;
        int enemyType;
        //0 - bossEnemy, 1 - bomberEnemy, 2 - strafingEnemy
        bool enemyDirection;
        //0 - right, 1 - left

        FiringAnimation(int enemyType);
        FiringAnimation(int enemyType, bool enemyDirection);
        ~FiringAnimation();

        static void createAnimation(std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations, const std::unique_ptr<Enemy>& enemy);
        static void update(std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations, std::vector<std::unique_ptr<Explosion> >& explosions);
};


#endif