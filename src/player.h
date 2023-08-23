#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace sf;

class Player {
    public:
        Texture playerTexture;
        Sprite playerSprite;
        int hp;
        RectangleShape hpBar;
        Vector2f currVelocity;
        FloatRect spriteBounds;
        bool isHitThisFrame;
        IntRect spriteSource;

        Player();

        //move player
        void update(RenderWindow& window, sf::Vector2f aimDir, float dt);

        //reset player after game ends/opens game over menu
        void reset(RenderWindow& window, bool& gameOver, bool& menuOpen);
};

#endif