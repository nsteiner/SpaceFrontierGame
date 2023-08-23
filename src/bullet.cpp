#include "bullet.h"
#include <iostream>
#include <cmath>

Bullet::Bullet() : currVelocity(0.f, 0.f), maxSpeed(15.f){
    bulletTexture.loadFromFile("Textures/missiles.png");
    IntRect spriteSource(154, 28, 16, 8);
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setTextureRect(spriteSource);
    bulletSprite.setScale(2.f, 2.f);
    bulletSprite.setOrigin(0, spriteSource.height / 2);
}

Bullet::Bullet(int typeOfEnemy) : currVelocity(0.f, 0.f), maxSpeed(20.f){
    bulletTexture.loadFromFile("Textures/missiles.png");
    if(typeOfEnemy == 0){
        IntRect spriteSource(218, 28, 16, 8);
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setTextureRect(spriteSource);
        bulletSprite.setScale(2.f, 2.f);
        bulletSprite.setOrigin(0, spriteSource.height / 2);
        bulletSprite.setRotation(90.f);
        hp = 1;
    }
    else if(typeOfEnemy == 1){
        IntRect spriteSource(218, 28, 16, 8);
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setTextureRect(spriteSource);
        bulletSprite.setOrigin(0, spriteSource.height / 2);
        bulletSprite.setScale(float(1.5), float(1.5));
        bulletSprite.setRotation(90.f);
        hp = 1;
    }
    else if(typeOfEnemy == 2){
        IntRect spriteSource(90, 28, 16, 8);
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setTextureRect(spriteSource);
        bulletSprite.setOrigin(0, spriteSource.height / 2);
        bulletSprite.setScale(3.f, 3.f);
        bulletSprite.setRotation(90.f);
        hp = 5;
    }
    this->typeOfEnemy = typeOfEnemy;
}

Bullet::~Bullet(){};

//players bullets
void Bullet::updatePB(std::vector<std::unique_ptr<Bullet> >& playerBullets, const Player& player, int& playerShootTimer, int& score, const Vector2f& aimDir, const Vector2f& aimDirNorm, RenderWindow& window){
    if(playerShootTimer < 10){
        playerShootTimer++;
    }
    else if(Mouse::isButtonPressed(Mouse::Left) && playerShootTimer >= 5){
        std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>();
        bullet->bulletSprite.setRotation(player.playerSprite.getRotation() - 90);

        bullet->bulletSprite.setPosition(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y);

        bullet->currVelocity = aimDirNorm * bullet->maxSpeed;
        playerBullets.push_back(std::move(bullet));

        playerShootTimer = 0;
    }

    for(size_t i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->bulletSprite.move(playerBullets[i]->currVelocity);
        if(playerBullets[i]->bulletSprite.getPosition().x < 0.f || playerBullets[i]->bulletSprite.getPosition().x > window.getSize().x || playerBullets[i]->bulletSprite.getPosition().y < 27.f || playerBullets[i]->bulletSprite.getPosition().y > window.getSize().y){
            playerBullets.erase(playerBullets.begin() + i);
        }
    }
}

//enemy bullets
void Bullet::updateEB(std::vector<std::unique_ptr<Bullet> >& enemyBullets, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, RenderWindow& window, Menu& menu, std::vector<std::unique_ptr<Wall> >& walls, std::vector<std::unique_ptr<Bullet> >& playerBullets, const int& instaKillTimer, std::vector<std::unique_ptr<Explosion> >& explosions, std::vector<std::unique_ptr<FiringAnimation> >& firingAnimations){
    for(size_t i = 0; i < enemies.size(); i++){
        if(dynamic_cast<BomberEnemy*>(enemies[i].get())){
            if((enemies[i]->shootTimer >= 100 && enemies[i]->shootTimer % 100 == 0) || enemies[i]->shootTimer == 10){
                std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(0);
                bullet->bulletSprite.setPosition(enemies[i]->enemySprite.getPosition().x, enemies[i]->enemySprite.getPosition().y + enemies[i]->enemySprite.getGlobalBounds().width / 4);
                enemyBullets.push_back(std::move(bullet));

                FiringAnimation::createAnimation(firingAnimations, enemies[i]);
                enemies[i]->shootTimer++;
            }
            else{
                enemies[i]->shootTimer++;
            }
        }
        else if(dynamic_cast<StrafingEnemy*>(enemies[i].get())){
            if(enemies[i]->shootTimer % 450 == 0){
                std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(1);
                bullet->bulletSprite.setPosition(enemies[i]->enemySprite.getPosition().x, enemies[i]->enemySprite.getPosition().y + enemies[i]->enemySprite.getGlobalBounds().width / 4);
                enemyBullets.push_back(std::move(bullet));

                FiringAnimation::createAnimation(firingAnimations, enemies[i]);
            }
        }
        else if(dynamic_cast<BossEnemy*>(enemies[i].get())){
            if(enemies[i]->shootTimer == 200){
                std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(2);
                bullet->bulletSprite.setPosition(enemies[i]->enemySprite.getPosition().x, enemies[i]->enemySprite.getPosition().y + enemies[i]->enemySprite.getGlobalBounds().width / 4);
                enemyBullets.push_back(std::move(bullet));
                enemies[i]->shootTimer = 0;

                FiringAnimation::createAnimation(firingAnimations, enemies[i]);
            }
            else{
                enemies[i]->shootTimer++;
            }
        }
    }

    for(size_t i = 0; i < enemyBullets.size(); i++){
        bool bulletCollidedWithWall = false;

        if(enemyBullets[i]->typeOfEnemy == 0){
            enemyBullets[i]->bulletSprite.move(0.f, 10.f);
            if(enemyBullets[i]->bulletSprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())){
                if(enemyBullets[i]->bulletSprite.getPosition().y > player.playerSprite.getPosition().y){
                    Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, player.playerSprite.getGlobalBounds().top + 2 * player.playerSprite.getGlobalBounds().height / 3), false, true, player);
                }
                else{
                    Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 3), false, true, player);
                }
                enemyBullets.erase(enemyBullets.begin() + i);
                player.hp--;
                player.hpBar.setSize(Vector2f(static_cast<float>(player.hp) * 10.f, 20.f));
            }
            else if(enemyBullets[i]->bulletSprite.getPosition().y >= window.getSize().y){
                enemyBullets.erase(enemyBullets.begin() + i);
            }
        }
        else if(enemyBullets[i]->typeOfEnemy == 1){
            enemyBullets[i]->bulletSprite.move(0.f, 5.f);
            if(enemyBullets[i]->bulletSprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())){
                if(enemyBullets[i]->bulletSprite.getPosition().y > player.playerSprite.getPosition().y){
                    Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, player.playerSprite.getGlobalBounds().top + 2 * player.playerSprite.getGlobalBounds().height / 3), false, true, player);
                }
                else{
                    Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 3), false, true, player);
                }
                enemyBullets.erase(enemyBullets.begin() + i);
                player.hp--;
                player.hpBar.setSize(Vector2f(static_cast<float>(player.hp) * 10.f, 20.f));
            }
            else if(enemyBullets[i]->bulletSprite.getPosition().y >= window.getSize().y){
                enemyBullets.erase(enemyBullets.begin() + i);
            }
        }
        else if(enemyBullets[i]->typeOfEnemy == 2){
            enemyBullets[i]->bulletSprite.move(0.f, 1.f);

            //collision with walls
            size_t j;
            for(j = 0; j < walls.size(); j++){
                if(walls[j]->null == false){
                    if(enemyBullets[i]->bulletSprite.getGlobalBounds().intersects(walls[j]->wall.getGlobalBounds()) && !walls[j]->hitByRocket){
                        bulletCollidedWithWall = true;
                        break;
                    }
                }
            }
            if (bulletCollidedWithWall) {
                Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, enemyBullets[i]->bulletSprite.getPosition().y + enemyBullets[i]->bulletSprite.getGlobalBounds().height), false, false, player);
                enemyBullets.erase(enemyBullets.begin() + i);
                walls[j]->hp -= 3;
                walls[j]->hitByRocket = true;
            }

            //collision with player
            if(enemyBullets[i]->bulletSprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())){
                Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, enemyBullets[i]->bulletSprite.getPosition().y + enemyBullets[i]->bulletSprite.getGlobalBounds().height), false, true, player);
                enemyBullets.erase(enemyBullets.begin() + i);
                player.hp -= 3;
                player.hpBar.setSize(Vector2f(static_cast<float>(player.hp) * 10.f, 20.f));
            }
            else if(enemyBullets[i]->bulletSprite.getPosition().y >= window.getSize().y){
                enemyBullets.erase(enemyBullets.begin() + i);
            }

            //collision with player bullets
            for(size_t j = 0; j < playerBullets.size(); j++){
                if(enemyBullets[i]->bulletSprite.getGlobalBounds().intersects(playerBullets[j]->bulletSprite.getGlobalBounds())){
                    playerBullets.erase(playerBullets.begin() + j);
                    if(instaKillTimer > 0){
                        enemyBullets[i]->hp -= 10;
                    }
                    else{
                        enemyBullets[i]->hp--;
                    }
                    
                    if(enemyBullets[i]->hp <= 0){
                        Explosion::createExplosion(explosions, Vector2f(enemyBullets[i]->bulletSprite.getPosition().x, enemyBullets[i]->bulletSprite.getPosition().y + enemyBullets[i]->bulletSprite.getGlobalBounds().height / 2), false, false, player);
                        enemyBullets.erase(enemyBullets.begin() + i);
                        break;
                    }
                }
            }
        }
    }
}

void Bullet::reset(std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet> >& enemyBullets){
    playerBullets.clear();
    enemyBullets.clear();
}