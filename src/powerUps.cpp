#include "powerUps.h"
#include <random>
#include <cmath>

PowerUp::PowerUp(std::string powerUp, bool spawnSide){
    this->spawnSide = spawnSide;

    if(powerUp == "HP"){
        powerUpTexture.loadFromFile("Textures/power-up.png");
        powerUpSprite.setTexture(powerUpTexture);
        powerUpSprite.setTextureRect(IntRect(16, 16, 16, 16));
    }
    else if(powerUp == "WALLS"){
        powerUpTexture.loadFromFile("Textures/power-up.png");
        powerUpSprite.setTexture(powerUpTexture);
        powerUpSprite.setTextureRect(IntRect(16, 0, 16, 16));
    }
    else if(powerUp == "INSTA K"){
        powerUpTexture.loadFromFile("Textures/power-up.png");
        powerUpSprite.setTexture(powerUpTexture);
        powerUpSprite.setTextureRect(IntRect(0, 0, 16, 16));
    }
    powerUpSprite.setScale(2.f, 2.f);
    powerUpType = powerUp;
}

PowerUp::~PowerUp(){};

void PowerUp::update(int& spawnTimer, std::unique_ptr<PowerUp>& powerUp, int& instaKillTimer){
    if(spawnTimer < 1500){
        spawnTimer++;
    }
    else if(powerUp == nullptr){       
        spawnTimer = 0;
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> yDistribution(50.f, 400.f);
        int randomSpawn = yDistribution(gen);

        std::uniform_int_distribution<int> sideDistribution(0, 1);
        int randomSide = sideDistribution(gen);

        std::uniform_int_distribution<int> powerUpDistribution(0, 9);
        std::array<int, 10> randomPowerUpArray = {0,0,0,0,0,1,1,1,2,2};

        int randomPowerUp = randomPowerUpArray[powerUpDistribution(gen)];



        if(randomPowerUp == 0){
            if(randomSide == 0){
                powerUp = std::make_unique<PowerUp>("HP", 0);
                powerUp->powerUpSprite.setPosition(0.f - powerUp->powerUpSprite.getGlobalBounds().width, randomSpawn);
            }
            else if(randomSide == 1){
                powerUp = std::make_unique<PowerUp>("HP", 1);
                powerUp->powerUpSprite.setPosition(600.f, randomSpawn);
            }
        }
        else if(randomPowerUp == 1){
            if(randomSide == 0){
                powerUp = std::make_unique<PowerUp>("WALLS", 0);
                powerUp->powerUpSprite.setPosition(0.f - powerUp->powerUpSprite.getGlobalBounds().width, randomSpawn);
            }
            else if(randomSide == 1){
                powerUp = std::make_unique<PowerUp>("WALLS", 1);
                powerUp->powerUpSprite.setPosition(600.f, randomSpawn);
            }
        }
        else if(randomPowerUp == 2){
            if(randomSide == 0){
                powerUp = std::make_unique<PowerUp>("INSTA K", 0);
                powerUp->powerUpSprite.setPosition(0.f - powerUp->powerUpSprite.getGlobalBounds().width, randomSpawn);
            }
            else if(randomSide == 1){
                powerUp = std::make_unique<PowerUp>("INSTA K", 1);
                powerUp->powerUpSprite.setPosition(600.f, randomSpawn);
            }
        }
    }

    if(instaKillTimer != 0){
        instaKillTimer--;
    }
}
void PowerUp::move(RenderWindow& window, std::unique_ptr<PowerUp>& powerUp, std::vector<std::unique_ptr<Bullet> >& playerBullets, std::vector<std::unique_ptr<Wall> >& walls, Player& player, int& instaKillTimer, std::vector<std::unique_ptr<Explosion> >& explosions){
    if(powerUp == nullptr){
        return;
    }
    else{
        if(powerUp->spawnSide == 0){
            powerUp->powerUpSprite.move(3.f, 0.f);
        }
            
        else if(powerUp->spawnSide == 1){
            powerUp->powerUpSprite.move(-3.f, 0.f);
        }
            

        if((powerUp->powerUpSprite.getPosition().x - powerUp->powerUpSprite.getGlobalBounds().width > window.getSize().x && powerUp->spawnSide == 0) ||
            (powerUp->powerUpSprite.getPosition().x + powerUp->powerUpSprite.getGlobalBounds().width < 0 && powerUp->spawnSide == 1)){
                powerUp.reset();
            }
        
        for(size_t i = 0; i < playerBullets.size(); i++){
            if(powerUp != nullptr){
                if(playerBullets[i]->bulletSprite.getGlobalBounds().intersects(powerUp->powerUpSprite.getGlobalBounds())){
                    Explosion::createExplosion(explosions, Vector2f(powerUp->powerUpSprite.getPosition().x + powerUp->powerUpSprite.getGlobalBounds().width / 2, powerUp->powerUpSprite.getPosition().y + powerUp->powerUpSprite.getGlobalBounds().height / 2), false, false, player);
                    if(powerUp->powerUpType == "HP"){
                        player.hp = std::min(player.hp + 3, 10);
                        player.hpBar.setSize(Vector2f(static_cast<float>(player.hp) * 10.f, 20.f));
                    }
                    else if(powerUp->powerUpType == "WALLS"){
                        /*
                        for(int i = 0; i < walls.size(); i++){
                            delete walls[i];
                        }

                        walls.clear();

                        for(int i = 1; i <= 14; i++){
                            Wall* wall= new Wall(i);
                            walls.push_back(wall);
                        }*/

                        for(size_t j = 0; j < walls.size(); j++){
                            if(walls[j]->null == true){
                                walls[j]->null = false;
                                walls[j]->hp = 3;
                            }
                        }
                    }
                    else if(powerUp->powerUpType == "INSTA K"){
                        instaKillTimer = 1000;
                    }

                    powerUp.reset();

                    playerBullets.erase(playerBullets.begin() + i);
                }
            }
            else{
                return;
            }
            
        }
    }
}