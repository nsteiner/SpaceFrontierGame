#!/bin/bash

# Delete the application file 
rm sfml-app

# Compile the source code
clang++ -std=c++17 src/main.cpp src/player.cpp src/bullet.cpp src/enemy.cpp src/menu.cpp src/database.cpp src/wall.cpp src/bomberEnemy.cpp src/enemyUpdate.cpp src/strafingEnemy.cpp src/bossEnemy.cpp src/powerUps.cpp src/explosion.cpp src/firingAnimation.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsqlite3

# Set environment variables
export DYLD_LIBRARY_PATH=/Users/nsteiner25/Desktop/SFML/External\ Libraries/SFML/lib
export DYLD_FRAMEWORK_PATH=/Users/nsteiner25/Desktop/SFML/External\ Libraries/SFML/extlibs

# Run the application
./sfml-app


