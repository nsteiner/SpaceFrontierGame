#include "bossEnemy.h"

BossEnemy::BossEnemy(){
    enemyTexture.loadFromFile("Textures/ships.png");
    IntRect spriteSource(272, 72, 32, 48);
    enemySprite.setTexture(enemyTexture);
    enemySprite.setTextureRect(spriteSource);
    enemySprite.setOrigin(enemySprite.getGlobalBounds().width / 2, enemySprite.getGlobalBounds().height / 2);
    enemySprite.setRotation(90.f);
    enemySprite.setScale(1.5f, 1.5f);
    hp = 10;
    shootTimer = 0;
    spawnTimer = 0;
    currentDirection = 0;
}

BossEnemy::~BossEnemy(){}

void BossEnemy:: update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver){
    
}

void BossEnemy:: move(){
    if(currentDirection == 0){
        enemySprite.move(-2.f, 0.f);
        if(enemySprite.getGlobalBounds().left < 0){
            currentDirection = 1;
        }
    }
    else{
        enemySprite.move(2.f, 0.f);
        if(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width > 600){
            currentDirection = 0;
        }
    }
}

void BossEnemy:: reset(){
    
}