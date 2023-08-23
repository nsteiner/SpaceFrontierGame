/*
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>

using namespace sf;

class Bullet{
    public:
        CircleShape shape;
        Vector2f currVelocity;
        float maxSpeed;

        Bullet(float radius = 5.f) : currVelocity(0.f, 0.f), maxSpeed(15.f)
        {
            this->shape.setFillColor(Color::Red);
            this->shape.setRadius(radius);
        }
};

int main()
{
    RenderWindow window(VideoMode(600, 480), "360 Shooter");
    window.setFramerateLimit(60);

    CircleShape player(25.f);
    player.setFillColor(Color::White);


    //players
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    //get these to get the following direction
    Vector2f aimDir;
    Vector2f aimDirNorm;


    //bullets
    Bullet b1;

    std::vector<Bullet> bullets;

    //enemy
    RectangleShape enemy;

    
    while(window.isOpen())
    {
        Event event;

        if(event.type == Event::Closed)
            window.close();


        //update
        //vectors
        playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius()); 
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        //line between player and mouse position
        float length = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm = Vector2f(aimDir.x / length, aimDir.y / length);

        //player
        if(Keyboard::isKeyPressed(Keyboard::A)){
            player.move(-10.f, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            player.move(10.f, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            player.move(0.f, 10.f);
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            player.move(0.f, -10.f);
        }


        //shooting
        if(Mouse::isButtonPressed(Mouse::Left)){
            b1.shape.setPosition(playerCenter);
            b1.currVelocity = aimDirNorm * b1.maxSpeed;

            bullets.push_back(Bullet(b1));
        }

        for(size_t i = 0; i < bullets.size(); i++){
            bullets[i].shape.move(bullets[i].currVelocity);

            if(bullets[i].shape.getPosition().x < 0 || bullets[i].getPosition().x > window.getSize().x || bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y){
                bullets.erase(bullet.begin() + i);
            }       
        }




        window.clear();

        window.draw(player);

        for(size_t i = 0; i < bullets.size(); i++){
            window.draw(bullets[i].shape);
        }
        
        window.display();

 
    }   

    
    return 0;
}
*/