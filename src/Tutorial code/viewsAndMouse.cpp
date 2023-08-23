/*
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>

using namespace sf;

int main()
{
    //game stuff
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF); //don't want to use a literal in the actual game
    float dt;
    Clock dtClock;

    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    Vector2u mousePosGrid;
    Text text;

    text.setCharacterSize(12);
    text.setFillColor(Color::White);
    text.setPosition(Vector2f(20.f, 20.f));
    text.setString("test");


    RenderWindow window(VideoMode(1920, 1080), "Simple Game");

    View view;
    view.setSize(1920.f, 1080.f);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    float viewSpeed = 100.f;


    RectangleShape shape(Vector2f(gridSizeF, gridSizeF));

    
    while(window.isOpen())
    {
        //update dt
        dt = dtClock.restart().asSeconds();

        //update mouse positions
        mousePosScreen = Mouse::getPosition();
        mousePosWindow = Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.f){
            mousePosGrid.x = mousePosView.x / gridSizeF;
        }
        if(mousePosView.y >= 0.f){
            mousePosGrid.y = mousePosView.y / gridSizeF;
        }

        
       
        Event event;

        if(event.type == Event::Closed)
            window.close();

        //update
        //update input
        if(Keyboard::isKeyPressed(Keyboard::A)){
            view.move(-viewSpeed * dt, 0.f);
        }
        else if(Keyboard::isKeyPressed(Keyboard::D)){
            view.move(viewSpeed * dt, 0.f);
        }
        else if(Keyboard::isKeyPressed(Keyboard::W)){
            view.move(0.f, -viewSpeed * dt);
        }
        else if(Keyboard::isKeyPressed(Keyboard::S)){
            view.move(0.f, viewSpeed * dt);
        }

        window.clear();
        window.setView(view);

        //Render game elements
        window.draw(shape);



        window.setView(window.getDefaultView());

        //render UI
        window.draw(text);

        window.display();
    }

    

    return 0;
}
*/