#include "player.h"
#include <cmath>


Player::Player() : hp(20), currVelocity(0.f, 0.f){
    hpBar.setFillColor(Color::Red);
    hpBar.setSize(Vector2f(static_cast<float>(hp) * 10.f, 20.f));
    
    playerTexture.loadFromFile("Textures/player.png");
    spriteSource = IntRect(60, 115, 380, 270);
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(spriteSource);

    spriteBounds = playerSprite.getGlobalBounds();
    playerSprite.setScale(0.2f, 0.2f);
    playerSprite.setOrigin(spriteSource.width / 2.f, spriteSource.height / 2.f);
}

void Player::update(RenderWindow& window, Vector2f aimDir, float dt){
        playerSprite.setRotation(atan2(aimDir.y, aimDir.x) * (180 / 3.14159265) + 90);

        //keyboard movements
        if(Keyboard::isKeyPressed(Keyboard::A) & !Keyboard::isKeyPressed(Keyboard::D)){
            currVelocity.x = -5.f;
        }
        else if(Keyboard::isKeyPressed(Keyboard::D) & !Keyboard::isKeyPressed(Keyboard::A)){
            currVelocity.x = 5.f;
        }
        else{
            currVelocity.x = 0.f;
        }
        playerSprite.move(currVelocity * dt);

        //collisions
        if(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 > window.getSize().x){
            playerSprite.setPosition(window.getSize().x - playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y);
        }
        else if(playerSprite.getPosition().x - playerSprite.getGlobalBounds().width / 2 < 0){
            playerSprite.setPosition(playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y);
        }
}

void Player::reset(RenderWindow& window, bool& gameOver, bool& menuOpen){
    //player update
    hp = 10;
    hpBar.setSize(Vector2f(static_cast<float>(hp) * 20.f, 20.f));
    playerSprite.setPosition(window.getSize().x / 2.f, window.getSize().y - playerSprite.getGlobalBounds().height / 2);    //player
    playerSprite.setRotation(90);

    //game over menu
    gameOver = true;
    menuOpen = true;
}