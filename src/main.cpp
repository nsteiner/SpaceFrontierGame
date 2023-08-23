#include <cstdlib>
#include <iostream>
#include "bullet.h"
#include "menu.h"
#include "database.h"
#include "wall.h"
#include "strafingEnemy.h"
#include "enemyUpdate.h"
#include "powerUps.h"
#include "explosion.h"
#include "firingAnimation.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(600.f, 800.f), "Galaga");
    window.setFramerateLimit(60.f);

    Clock clock;
    float dt;
    float multiplier = 200.f;

    //create player
    Player player;
    player.playerSprite.setPosition(window.getSize().x / 2.f, 750.f);

    //create player bullets
    int playerShootTimer = 0;

    std::vector<std::unique_ptr<Bullet> > playerBullets;

    //player bullet direction
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;


    //create enemies
    BomberEnemy bomber;
    StrafingEnemy strafer;
    std::unique_ptr<Enemy> boss;
    int bossSpawnTimer = 0;
    bool bossSpawned = false;
    
    //enemy vector used for moving
    std::vector<std::unique_ptr<Enemy> > enemies;

    //create enemy bullets
    std::vector<std::unique_ptr<Bullet> > enemyBullets;

    
    //menu
    Menu menu;
    bool menuOpen = true;
    bool gameStarted = false;
    bool gameOver = false;

    //player score and hp texts
    int playerScore = 0;
    Text scoreText;
    Text hpText;
    hpText.setFont(menu.menuFont);
    hpText.setString("HP");
    hpText.setCharacterSize(20.f);
    hpText.setPosition(5.f, 2.f);
    scoreText.setFont(menu.menuFont);
    scoreText.setString("SCORE " + std::to_string(playerScore));
    scoreText.setCharacterSize(20.f);
    scoreText.setPosition(300.f, 2.f);

    //set positions of hp bar
    player.hpBar.setPosition(hpText.getGlobalBounds().left + hpText.getGlobalBounds().width + 5.f, 5.f);
    

    //pause "button" in top right
    Text pauseText;
    pauseText.setFont(menu.menuFont);
    pauseText.setFillColor(Color::Red);
    pauseText.setString("PAUSE");
    pauseText.setCharacterSize(20.f);
    pauseText.setPosition(window.getSize().x - pauseText.getGlobalBounds().width - 5.f, 0.f);
    
    //high score elements
    const char* db = "src/highScoreDatabase.db";
    Database::createDB(db);
    Database::createTable(db);
    int highScore = Database::getHighScore(db);
    bool highScoreUpdated = false;

    //update menu (begin game screen)
    menu.update("SPACE FRONTIER", "BEGIN", std::to_string(playerScore), std::to_string(highScore));

    //walls
    std::vector<std::unique_ptr<Wall> > walls;
    walls.reserve(13);
    for(int i = 1; i <= 13; i++){
        std::unique_ptr wall = std::make_unique<Wall>(i);
        walls.push_back(std::move(wall));
    }

    //power ups
    std::unique_ptr<PowerUp> powerUp;
    int powerUpSpawnTimer = 0; 
    int instaKillTimer = 0;

    //explosions
    std::vector<std::unique_ptr<Explosion> > explosions;

    //firing animations
    std::vector<std::unique_ptr<FiringAnimation> > firingAnimations;

    //background
    Texture background;
    background.loadFromFile("Textures/background.png");
    Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(2.f, 2.f);

    while(window.isOpen())
    {
        //if game hasn't begun or high score has been changed, update the highScore variable
        if(!gameStarted || highScoreUpdated){
            highScore = Database::getHighScore(db);
            highScoreUpdated = false;
        }

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        dt = clock.restart().asSeconds() * multiplier;

        if(menuOpen){
            //start/pause menu
            window.clear();
            window.draw(backgroundSprite);
            if(gameOver){
                menu.update("GAME OVER", "PLAY AGAIN", std::to_string(playerScore), std::to_string(highScore));
            }
            else if(gameStarted){
                menu.update("GAME PAUSED", "RESUME", std::to_string(playerScore), std::to_string(highScore));
            }
            menu.draw(window, gameStarted, gameOver);
            window.display();

            //if user presses button, close menu
            if(Mouse::getPosition(window).x > menu.menuButton.getGlobalBounds().left && Mouse::getPosition(window).x < menu.menuButton.getGlobalBounds().left + menu.menuButton.getGlobalBounds().width
                && Mouse::getPosition(window).y > menu.menuButton.getGlobalBounds().top && Mouse::getPosition(window).y < menu.menuButton.getGlobalBounds().top + menu.menuButton.getGlobalBounds().height
                && Mouse::isButtonPressed(Mouse::Left) == true){
                menuOpen = false;
                if(!gameStarted){
                    gameStarted = true;
                }
            }
        }
        else{
            //open pause menu
            if(Mouse::getPosition(window).x > pauseText.getGlobalBounds().left && Mouse::getPosition(window).x < pauseText.getGlobalBounds().left + pauseText.getGlobalBounds().width
                && Mouse::getPosition(window).y > pauseText.getGlobalBounds().top && Mouse::getPosition(window).y < pauseText.getGlobalBounds().top + pauseText.getGlobalBounds().height
                && Mouse::isButtonPressed(Mouse::Left) == true){
                menuOpen = true;
                playerShootTimer = 0;
            }

            //reset menu
            if(gameOver){
                gameOver = false;
                playerScore = 0;
                scoreText.setString("SCORE " + std::to_string(playerScore));
            }

            //update
            //vector updates
            playerCenter = Vector2f(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y - player.playerSprite.getGlobalBounds().height / 2);
            mousePosWindow = Vector2f(Mouse::getPosition(window));
            aimDir = mousePosWindow - playerCenter;
            float length = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
            aimDirNorm = Vector2f(aimDir.x / length, aimDir.y / length);

            //player update
            player.update(window, aimDirNorm, dt); 
            //player bullet update 
            Bullet::updatePB(playerBullets, player, playerShootTimer, playerScore, aimDir, aimDirNorm, window); 

            //power up update
            if(powerUp != nullptr){
                PowerUp::move(window, powerUp, playerBullets, walls, player, instaKillTimer, explosions);
            }
            PowerUp::update(powerUpSpawnTimer, powerUp, instaKillTimer);
        
            //enemy update
            EnemyUpdate::update(window, enemies, player, bomber, strafer, explosions, gameOver);
            if(bossSpawnTimer < 500 && !bossSpawned){
                bossSpawnTimer++;
            }
            else if(bossSpawnTimer >= 500 && !bossSpawned){
                boss = std::make_unique<BossEnemy>();
                bossSpawnTimer = 0;
                bossSpawned = true;
                boss->enemySprite.setPosition(window.getSize().x + boss->enemySprite.getGlobalBounds().width / 2, 27.f + boss->enemySprite.getGlobalBounds().height / 2);
                enemies.push_back(std::move(boss));
            }

            //player bullet/enemy collision
            for(size_t i = 0; i < enemies.size(); i++){
                for(size_t j = 0; j < playerBullets.size(); j++){
                    if(enemies[i]->enemySprite.getGlobalBounds().intersects(playerBullets[j]->bulletSprite.getGlobalBounds())){
                        playerBullets.erase(playerBullets.begin() + j);
                        if(instaKillTimer != 0){
                            enemies[i]->hp -= 10;
                        }
                        else{
                            enemies[i]->hp--;
                        }
                        if(enemies[i]->hp <= 0){
                            if(dynamic_cast<BossEnemy*>(enemies[i].get())){
                                playerScore += 250;
                                Explosion::createExplosion(explosions, Vector2f(enemies[i]->enemySprite.getPosition()), true, false, player);
                                boss.reset();
                                bossSpawned = false;
                            }
                            else if(dynamic_cast<BomberEnemy*>(enemies[i].get())){
                                playerScore += 100;
                                Explosion::createExplosion(explosions, Vector2f(enemies[i]->enemySprite.getPosition()), false, false, player);
                            }
                            else if(dynamic_cast<StrafingEnemy*>(enemies[i].get())){
                                playerScore += 15;
                                Explosion::createExplosion(explosions, Vector2f(enemies[i]->enemySprite.getPosition()), false, false, player);
                            }

                            enemies.erase(enemies.begin() + i);
                            
                            scoreText.setString("SCORE " + std::to_string(playerScore));
                            break;
                        }
                    }
                }
            }
            //enemy movement
            for(size_t i = 0; i < enemies.size(); i++){
                enemies[i]->move();

                if(!dynamic_cast<BossEnemy*>(enemies[i].get())){
                    if(enemies[i]->enemySprite.getGlobalBounds().getPosition().x > window.getSize().x + enemies[i]->enemySprite.getGlobalBounds().width || enemies[i]->enemySprite.getGlobalBounds().getPosition().y > window.getSize().y + enemies[i]->enemySprite.getGlobalBounds().height||
                    enemies[i]->enemySprite.getGlobalBounds().getPosition().x < -enemies[i]->enemySprite.getGlobalBounds().width){
                        enemies.erase(enemies.begin() + i);
                    }
                }
            }

            //explosion update
            Explosion::update(explosions, player);

            FiringAnimation::update(firingAnimations, explosions);
            
            //check to see if any enemies killed player by collision
            if(player.hp <= 0){
                //player reset/game over menu
                player.reset(window, gameOver, menuOpen);
                playerShootTimer = 0;

                //clear bullet vectors
                Bullet::reset(playerBullets, enemyBullets);

                //reset enemies
                bomber.reset();
                strafer.reset();
                bossSpawnTimer = 0;
                bossSpawned = false;

                //wall reset
                Wall::reset(walls);
                
                //Power Up reset
                powerUpSpawnTimer = 0;
                powerUp.reset();        

                //clear enemy vector
                enemies.clear();
                
                //update high score in database if player score is larger
                if (playerScore > highScore) {
                    Database::update(db, playerScore, highScoreUpdated);
                }
 
                //clear explosions vector
                explosions.clear();

                //clear fire animations vector
                firingAnimations.clear();
            }
            
            //enemy bullet update
            Bullet::updateEB(enemyBullets, enemies, player, window, menu, walls, playerBullets, instaKillTimer, explosions, firingAnimations); 

            //check if any enemies killed player by bullet
            if(player.hp <= 0){
                //player reset/game over menu
                player.reset(window, gameOver, menuOpen);
                playerShootTimer = 0;

                //clear bullet vectors
                Bullet::reset(playerBullets, enemyBullets);

                //reset enemies
                bomber.reset();
                strafer.reset();
                bossSpawnTimer = 0;
                bossSpawned = false;

                //wall reset
                Wall::reset(walls);
                
                //Power Up reset
                powerUpSpawnTimer = 0;
                powerUp.reset();

                //clear enemy vector
                enemies.clear();
                
                //update high score in database if player score is larger
                if (playerScore > highScore) {
                    Database::update(db, playerScore, highScoreUpdated);
                }

                //clear explosions vector
                explosions.clear();

                //clear fire animations vector
                firingAnimations.clear();
            }

            //wall update
            Wall::updateWalls(walls, enemies, explosions, player);
            
            //if game is not over, draw game elements
            if(!gameOver){
                //draw
                window.clear();
                window.draw(backgroundSprite); //draw background
                window.draw(pauseText); //draw pause "button"
                window.draw(hpText); //draw "HP: " text
                window.draw(player.hpBar); //draw hp bar
                window.draw(scoreText); //draw score

                if(powerUp != nullptr){
                    window.draw(powerUp->powerUpSprite);
                }

                Wall::drawWalls(window, walls, player); //draw walls
        
                for(size_t i = 0; i < playerBullets.size(); i++){ //draw player bullets
                    window.draw(playerBullets[i]->bulletSprite);
                }  

                window.draw(player.playerSprite); //draw player
                
                for(size_t i = 0; i < enemyBullets.size(); i++){ //draw enemies
                    window.draw(enemyBullets[i]->bulletSprite);
                } 

                for(size_t i = 0; i < enemies.size(); i++){ //draw enemies
                    window.draw(enemies[i]->enemySprite);
                }

                for(size_t i = 0; i < explosions.size(); i++){ //draw enemies
                    window.draw(explosions[i]->expSprite);
                }

                for(size_t i = 0; i < firingAnimations.size(); i++){ //draw enemies
                    window.draw(firingAnimations[i]->firingSprite);
                }
                
                
                window.display();
            }
        }
    }
    return 0;
}
    
