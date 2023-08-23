#include "menu.h"
#include <cstdlib>
Menu::Menu(){
    //RectangleShape menu
    menu.setFillColor(Color::Black);
    menu.setOutlineColor(Color::Red);
    menu.setOutlineThickness(1.f);
    menu.setSize(Vector2f(400.f,400.f));
    menu.setPosition(100.f, 200.f);

    //Text menuText
    menuFont.loadFromFile("Fonts/dash.otf");
    menuText.setFont(menuFont);
    menuText.setFillColor(Color::Red);

    //RectangleShape menuButton
    menuButton.setFillColor(Color::Transparent);
    menuButton.setOutlineColor(Color::Red);
    menuButton.setOutlineThickness(1.f);
    menuButton.setSize(Vector2f(150.f, 50.f));
    menuButton.setOrigin(menuButton.getGlobalBounds().width / 2, menuButton.getGlobalBounds().height / 2);
    menuButton.setPosition(300.f, 525.f);

    //Text menuButtonText;
    menuButtonText.setFont(menuFont);
    menuButtonText.setFillColor(Color::Red);

    scoreText.setFont(menuFont);
    scoreText.setFillColor(Color::Red);

    highScoreText.setFont(menuFont);
    highScoreText.setFillColor(Color::Red);
}

void Menu::update(std::string newMenuText, std::string newMenuButtonText, std::string score, std::string highScore){
    menuText.setString(newMenuText); 
    menuText.setCharacterSize(50.f);
    menuTextBounds = menuText.getLocalBounds();
    menuText.setOrigin(menuTextBounds.left + menuTextBounds.width / 2.f, menuTextBounds.top + menuTextBounds.height / 2.f);
    menuText.setPosition(menu.getPosition().x + menu.getSize().x / 2.f, menu.getPosition().y + menu.getSize().y / 3.f);

    menuButtonText.setString(newMenuButtonText);
    menuButtonText.setCharacterSize(30.f);
    menuButtonTextBounds = menuButtonText.getLocalBounds();
    menuButtonText.setOrigin(menuButtonTextBounds.left + menuButtonTextBounds.width / 2.f, menuButtonTextBounds.top + menuButtonTextBounds.height / 2.f);
    menuButtonText.setPosition(menuButton.getPosition().x, menuButton.getPosition().y);

    scoreText.setString("SCORE " + score);
    scoreText.setCharacterSize(30.f);
    scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreTextBounds.left + scoreTextBounds.width / 2.f, scoreTextBounds.top + scoreTextBounds.height / 2.f);
    scoreText.setPosition(300.f, menuText.getGlobalBounds().top + menuText.getGlobalBounds().height + 50.f);

    highScoreText.setString("HIGH SCORE " + highScore);
    highScoreText.setCharacterSize(30.f);
    highScoreTextBounds = highScoreText.getLocalBounds();
    highScoreText.setOrigin(highScoreTextBounds.left + highScoreTextBounds.width / 2.f, highScoreTextBounds.top + highScoreTextBounds.height / 2.f);
    highScoreText.setPosition(300.f, scoreText.getGlobalBounds().top + scoreText.getGlobalBounds().height + 50.f);
}

void Menu::draw(RenderWindow& window, bool gameStarted, bool gameOver){
    window.draw(menu);
    window.draw(menuText);
    window.draw(menuButton);
    window.draw(menuButtonText);
    if(gameStarted){
        window.draw(scoreText);
    }
    if(!gameStarted || gameOver){
        window.draw(highScoreText);
    }
    
}