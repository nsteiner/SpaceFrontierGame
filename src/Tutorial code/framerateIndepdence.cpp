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
    RenderWindow window(VideoMode(600, 480), "Simple Game");
    
    Clock clock;
    float dt;
    float multiplier = 200.f;

    RectangleShape shape;
    shape.setFillColor(Color::White);
    shape.setSize(Vector2f(50.f, 50.f));

    Vector2f currVelocity;
    Vector2f direction;
    float maxVelocity = 25.f;
    float acceleration = 1.f;
    float drag = 0.5f;

    while(window.isOpen())
    {
        Event event;

        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
            window.close();
        }

        dt = clock.restart().asSeconds() * multiplier;


        //update
        //acceleration
        direction = Vector2f(0.f, 0.f); //reset direction every frame

        if(Keyboard::isKeyPressed(Keyboard::A)){
            direction.x = -1.f;

            if(currVelocity.x > -maxVelocity){ //in negative direction
                currVelocity.x += acceleration * direction.x * dt;
            }

        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            direction.x = 1.f;

            if(currVelocity.x < maxVelocity){ 
                currVelocity.x += acceleration * direction.x * dt;
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            direction.y = 1.f;

            if(currVelocity.y < maxVelocity){
                currVelocity.y += acceleration * direction.y * dt;
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            direction.x = -1.f;

            if(currVelocity.y > -maxVelocity){ //in negative direction
                currVelocity.y += acceleration * direction.y * dt;
            }
        }

        //drag
        if(currVelocity.x > 0.f){
            currVelocity.x -= drag  * dt;

            if(currVelocity.x < 0.f){
                currVelocity.x = 0.f; //don't want to get a negative acceleration out of the drag
            }
        }d
        else if(currVelocity.x < 0.f){
            currVelocity.x += drag  * dt;

            if(currVelocity.x > 0.f){
                currVelocity.x = 0.f;
            }
        }
        if(currVelocity.y > 0.f){
            currVelocity.y -= drag * dt;

            if(currVelocity.y < 0.f){
                currVelocity.y = 0.f; //don't want to get a negative acceleration out of the drag
            }
        }
        else if(currVelocity.y < 0.f){
            currVelocity.y += drag * dt;

            if(currVelocity.y > 0.f){
                currVelocity.y = 0.f;
            }
        }

        //final move
        shape.move(currVelocity.x * dt, currVelocity.y * dt);




        window.clear();

        window.draw(shape);
        
        window.display();
            
    }
    */