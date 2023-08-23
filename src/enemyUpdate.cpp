#include "enemyUpdate.h"

void EnemyUpdate::update(RenderWindow& window, std::vector<std::unique_ptr<Enemy> >& enemies, Player& player, BomberEnemy& bomberEnemy, StrafingEnemy& strafingEnemy, std::vector<std::unique_ptr<Explosion> >& explosions, bool& gameOver){
    bomberEnemy.update(window, enemies, player, explosions, gameOver);
    strafingEnemy.update(window, enemies, player, explosions, gameOver);
}
