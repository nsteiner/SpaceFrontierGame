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
    window.setFramerateLimit(60);

    Font font;
    if(!font.loadFromFile("Chaviera.otf")){
        throw("Could not fload font");
    }

    Text text;
    text.setFont(font);
    //do stuff to text
    
    while(window.isOpen())
    {
        Event event;

        if(event.type == Event::Closed)
            window.close();
    }

    window.clear();
     
    window.display();

    return 0;
}
*/