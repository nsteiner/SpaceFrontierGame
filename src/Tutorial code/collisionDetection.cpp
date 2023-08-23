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
    RenderWindow window(VideoMode(800, 600), "Collision Detection");
    window.setFramerateLimit(120);

    float dt;
    Clock dt_clock;

    const float gridSize = 50.f; //used to layout walls

    //player
    const float movementSpeed = 100.f;
    Vector2f velocity;
    RectangleShape player;
    player.setFillColor(Color::Green);
    player.setSize(Vector2f(gridSize, gridSize)); //simple way for collision detection, can use hit boxes later on


    //walls
    std::vector<RectangleShape> walls;

    RectangleShape wall;
    wall.setFillColor(Color::Red);
    wall.setSize(Vector2f(gridSize, gridSize));
    wall.setPosition(gridSize * 5, gridSize * 2);

    walls.push_back(wall);

    //collision
    FloatRect nextPos;


    

    while(window.isOpen())
    {
        dt = dt_clock.restart().asSeconds();

        Event event;

        if(event.type == Event::Closed)
            window.close();

        
        //player movement
        velocity.x = 0.f;
        velocity.y = 0.f;
        if(Keyboard::isKeyPressed(Keyboard::A)){
            velocity.x = -movementSpeed * dt;
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            velocity.x = movementSpeed * dt;
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            velocity.y = movementSpeed * dt;
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            velocity.y = -movementSpeed * dt;
        }

        player.move(velocity);


        //collision with walls
        for(int i = 0; i < walls.size(); i++){
            FloatRect playerBounds = player.getGlobalBounds();
            FloatRect wallBounds = wall.getGlobalBounds();

            nextPos = playerBounds;
            nextPos.left += velocity.x;
            nextPos.top += velocity.y;

            if(wallBounds.intersects(nextPos)){
                //right collision
                if(playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top){
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                //left collision
                else if(playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top){
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                //bottom
                else if(playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left){
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                //top collision
                else if(playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left){
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top + playerBounds.height);
                }                                                                                                                  
            }

        }

        //collision screen


        window.clear();

        window.draw(player);

        for(int i = 0; i < walls.size(); i++){
            window.draw(walls[i]);
        }
     
        window.display();
    }


    return 0;
}
*/