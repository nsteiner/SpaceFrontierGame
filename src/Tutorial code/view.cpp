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
    RenderWindow window(VideoMode(1920, 1080), "Simple Game");

    View mainView;
    mainView.setSize(1920, 1080);


    RectangleShape player;
    player.setSize(Vector2f(50.f, 50.f));
    player.setPosition(500.f, 500.f);

    RectangleShape UIElement;
    UIElement.setSize(Vector2f(300.f, 20.f));
    
    
    while(window.isOpen())
    {
        Event event;

        if(event.type == Event::Closed)
            window.close();


        //update

        //draw
        window.clear();

    
        //draw stuff
        window.setView(mainView); //when you set this, all positions are in the view
        window.draw(player);


        //draw UI
        window.setView(window.getDefaultView()); //this resets the window so you aren't drawing in the previously created view
        window.draw(UIElement);
        
     
        window.display();
    }

   

    return 0;
}
*/
