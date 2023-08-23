#include "strafingEnemy.h"

StrafingEnemy::StrafingEnemy(): Enemy(){
    enemyTexture.loadFromFile("Textures/ships.png");
    IntRect spriteSource(144, 82, 28, 28);
    enemySprite.setTexture(enemyTexture);
    enemySprite.setTextureRect(spriteSource);
    enemySprite.setOrigin(enemySprite.getGlobalBounds().width / 2, enemySprite.getGlobalBounds().height / 2);
    enemySprite.setRotation(90.f);
    hp = 1;
    shootTimer = 0;
    spawnTimer = 0;
    spawnSide = 0;
}

StrafingEnemy::~StrafingEnemy(){};

void StrafingEnemy::update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver){
    shootTimer++;
    if(spawnTimer < 300){
        spawnTimer++;
    }
    else if(spawnTimer <= 400){
        spawnTimer++;
        if(spawnTimer % 10 == 0){
            std::unique_ptr<Enemy> strafer = std::make_unique<StrafingEnemy>();
            strafer->shootTimer = spawnTimer;
            if(spawnSide == 0){
                strafer->spawnSide = 0;
                strafer->enemySprite.setPosition(25.f, 27.f);
            }
            else{
                strafer->spawnSide = 1;
                strafer->enemySprite.setPosition(575.f, 27.f);
            }
            enemies.push_back(std::move(strafer));

        }
    }
    else if(spawnTimer > 400){
        spawnTimer = 0;
        spawnSide = !spawnSide;
    }
}

void StrafingEnemy::move(){
    shootTimer++;
    if(spawnSide == 0){
        enemySprite.move(3.f, 1.f);
    }
    else{
        enemySprite.move(-3.f, 1.f);
    }
}

void StrafingEnemy::reset(){
    spawnTimer = 0;
    spawnSide = 0;
}