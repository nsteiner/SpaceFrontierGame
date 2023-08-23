#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>  

using namespace sf;

class Menu{
    public:
        RectangleShape menu;
        Font menuFont;
        Text menuText;
        RectangleShape menuButton;
        Text menuButtonText;
        FloatRect menuTextBounds;
        FloatRect menuButtonTextBounds;
        Text scoreText;
        FloatRect scoreTextBounds;
        Text highScoreText;
        FloatRect highScoreTextBounds;

        Menu();

        void update(std::string menuText, std::string menuButtonText, std::string score, std::string highScore);

        void draw(RenderWindow& window, bool gameStarted, bool gameOver);
    
};


#endif