#include "explosion.h"
#include <iostream>

Explosion::Explosion(bool playerHit) : expClock(){
    expTexture.loadFromFile("Textures/explosion.png");
    expSprite.setTexture(expTexture);
    spriteSource = IntRect(0, 0, 32, 32);
    expSprite.setTextureRect(spriteSource);
    expSprite.setOrigin(expSprite.getGlobalBounds().width / 2, expSprite.getGlobalBounds().height / 2);
    expSprite.setScale(1.f, 1.f);
    this->playerHit = playerHit;
}

Explosion::~Explosion(){};

void Explosion::createExplosion(std::vector<std::unique_ptr<Explosion> >& explosions, const Vector2f& coordinates, const bool& bossEnemyHit, const bool& playerHit, const Player& player){
    std::unique_ptr<Explosion> explosion = std::make_unique<Explosion>(playerHit);
    if(bossEnemyHit){
        explosion->expSprite.setScale(2.f, 2.f);
    }
    else if(playerHit){
        explosion->locationOnPlayer = (coordinates.x - player.playerSprite.getGlobalBounds().left) / player.playerSprite.getGlobalBounds().width;
    }
    explosion->expSprite.setPosition(coordinates);
    explosions.push_back(std::move(explosion));
}

void Explosion::update(std::vector<std::unique_ptr<Explosion> >& explosions, const Player& player){
    for(size_t i = 0; i < explosions.size(); i++){
        if(explosions[i]->playerHit){
            explosions[i]->expSprite.setPosition(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width * explosions[i]->locationOnPlayer, explosions[i]->expSprite.getPosition().y);
        }
        if(explosions[i]->expClock.getElapsedTime().asMilliseconds() >= 100.f){
            explosions[i]->spriteSource.left += 32;
            explosions[i]->expSprite.setTextureRect(explosions[i]->spriteSource);
            explosions[i]->expClock.restart();
            if(explosions[i]->spriteSource.left >= 256){
                explosions.erase(explosions.begin() + i);
                i--;
            }
        }  
    }
}