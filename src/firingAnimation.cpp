#include "firingAnimation.h"

FiringAnimation::FiringAnimation(int enemyType) : animationClock(){
    firingTexture.loadFromFile("Textures/rocketThruster.png");
    firingSource = IntRect(0, 0, 16, 16);
    firingSprite.setTexture(firingTexture);
    firingSprite.setTextureRect(firingSource);
    firingSprite.setOrigin(0, firingSprite.getGlobalBounds().height / 2);
    firingSprite.setRotation(90.f);
    this->enemyType = enemyType;

    if(enemyType == 0){
        firingSprite.setScale(2.f, 2.f);
    }
    else{
        firingSprite.setScale(1.f, 1.f);
    }
}

FiringAnimation::FiringAnimation(int enemyType, bool enemyDirection) : animationClock(){
    firingTexture.loadFromFile("Textures/rocketThruster.png");
    firingSource = IntRect(0, 0, 16, 16);
    firingSprite.setTexture(firingTexture);
    firingSprite.setTextureRect(firingSource);
    firingSprite.setOrigin(0, firingSprite.getGlobalBounds().height / 2);
    firingSprite.setRotation(90.f);
    this->enemyType = enemyType;
    this->enemyDirection = enemyDirection;

    if(enemyType == 0){
        firingSprite.setScale(2.f, 2.f);
    }
    else{
        firingSprite.setScale(1.f, 1.f);
    }
}

FiringAnimation::~FiringAnimation(){};

void FiringAnimation::createAnimation(std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations, const std::unique_ptr<Enemy>& enemy){
    std::unique_ptr<FiringAnimation> firingAnimation;

    if(dynamic_cast<BossEnemy*>(enemy.get())){
        if(enemy->currentDirection == 0){
            firingAnimation = std::make_unique<FiringAnimation>(0, 1);
        }
        else{
            firingAnimation = std::make_unique<FiringAnimation>(0, 0);
        }
    }
    else if(dynamic_cast<BomberEnemy*>(enemy.get())){
        firingAnimation = std::make_unique<FiringAnimation>(1);
    }
    else if(dynamic_cast<StrafingEnemy*>(enemy.get())){
        if(enemy->spawnSide == 0){
            firingAnimation = std::make_unique<FiringAnimation>(2, 0);
        }
        else{
            firingAnimation = std::make_unique<FiringAnimation>(2, 1);
        }
    }

    firingAnimation->firingSprite.setPosition(enemy->enemySprite.getPosition().x, enemy->enemySprite.getPosition().y + enemy->enemySprite.getGlobalBounds().height / 3);
    
    firingAnimations.push_back(std::move(firingAnimation));
}

void FiringAnimation::update(std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations, std::vector<std::unique_ptr<Explosion> >& explosions){
    for(size_t i = 0; i < firingAnimations.size(); i++){
        for(size_t j = 0; j < explosions.size(); j++){
            if(firingAnimations[i]->firingSprite.getGlobalBounds().intersects(explosions[j]->expSprite.getGlobalBounds())){
                firingAnimations.erase(firingAnimations.begin() + i);
                break;
            }
        }
    }
    for(size_t i = 0; i < firingAnimations.size(); i++){
        if(firingAnimations[i]->enemyType == 0){
            if(firingAnimations[i]->enemyDirection == 0){
                firingAnimations[i]->firingSprite.move(2.f, 0.f);
            }
            else{
                firingAnimations[i]->firingSprite.move(-2.f, 0.f);
            }
        }
        else if(firingAnimations[i]->enemyType == 1){
            firingAnimations[i]->firingSprite.move(0.f, 1.5f);
        }
        else if(firingAnimations[i]->enemyType == 2){
            if(firingAnimations[i]->enemyDirection == 0){
                firingAnimations[i]->firingSprite.move(3.f, 1.f);
            }
            else{
                firingAnimations[i]->firingSprite.move(-3.f, 1.f);
            }
        }

        if(firingAnimations[i]->firingSource.left == 0){
            if(firingAnimations[i]->animationClock.getElapsedTime().asMilliseconds() >= 75.f){
                firingAnimations[i]->firingSource.left += 16;
                firingAnimations[i]->firingSprite.setTextureRect(firingAnimations[i]->firingSource);
                firingAnimations[i]->animationClock.restart();
            }
        }
        else{
            if(firingAnimations[i]->animationClock.getElapsedTime().asMilliseconds() >= 175.f){
                firingAnimations.erase(firingAnimations.begin() + i);
                i--;
            }
        }
        
    }
}