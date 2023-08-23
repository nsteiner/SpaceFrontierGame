#include <random>
#include "bomberEnemy.h"

BomberEnemy::BomberEnemy() : Enemy(){
    enemyTexture.loadFromFile("Textures/ships.png");
    IntRect spriteSource(208, 80, 32, 30);
    enemySprite.setTexture(enemyTexture);
    enemySprite.setTextureRect(spriteSource);
    enemySprite.setOrigin(enemySprite.getGlobalBounds().width / 2, enemySprite.getGlobalBounds().height / 2);
    enemySprite.setRotation(90.f);
    //firingSprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y + enemySprite.getGlobalBounds().height / 2);
    
    hp = 3;
    shootTimer = 0;
    spawnTimer = 0;
}

BomberEnemy::~BomberEnemy(){};

void BomberEnemy::update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver){
    //enemy spawn
    if(spawnTimer < 100){
        spawnTimer++;
    }
    else{
        std::unique_ptr<Enemy> bomber = std::make_unique<BomberEnemy>();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> xDistribution(bomber->enemySprite.getGlobalBounds().width / 2, window.getSize().x - enemySprite.getGlobalBounds().width / 2);

        int randomX = xDistribution(gen);
        bomber->enemySprite.setPosition(randomX, 27.f + bomber->enemySprite.getGlobalBounds().height / 2);
        
        enemies.push_back(std::move(bomber));
        
        spawnTimer = 0;
    }

    for(size_t i = 0; i < enemies.size(); i++){
        //enemy going off screen/collision with player
        if(enemies[i]->enemySprite.getPosition().y >= window.getSize().y){
            enemies.erase(enemies.begin() + i);
            gameOver = true;
        }
        else if(enemies[i]->enemySprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())){
            Explosion::createExplosion(explosions, Vector2f(enemies[i]->enemySprite.getPosition().x, enemies[i]->enemySprite.getPosition().y + enemies[i]->enemySprite.getGlobalBounds().height / 3), false, false, player);
            enemies.erase(enemies.begin() + i);
            
            player.hp -= 2;
            player.hpBar.setSize(Vector2f(static_cast<float>(player.hp) * 10.f, 20.f));
        }
    }
}

void BomberEnemy::move(){
    enemySprite.move(0.f, 1.5f);
}

void BomberEnemy::reset(){
    spawnTimer = 0;
}