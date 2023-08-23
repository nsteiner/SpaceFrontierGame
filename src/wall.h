#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "bomberEnemy.h"

using namespace sf;

class Wall{
    public: 
        RectangleShape wall;
        Texture wallTexture;
        int hp;
        FloatRect rectBounds;
        bool null;
        int wallNumber;
        Clock transparencyClock;
        Color wallColor;
        bool hitByRocket;



        Wall(int i);
        ~Wall();

        static void drawWalls(RenderWindow& window, std::vector<std::unique_ptr<Wall> >& walls, const Player& player);
        static void updateWalls(std::vector<std::unique_ptr<Wall> >& walls, std::vector<std::unique_ptr<Enemy> >& enemies, std::vector<std::unique_ptr<Explosion> >& explosions, const Player& player);
        static void reset(std::vector<std::unique_ptr<Wall> >& walls);
};




#endif