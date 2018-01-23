#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <list>

#include <memory>

#include "settings.h"

#include "Cannon.h"
#include "BulletList.h"
#include "EnemyList.h"
#include "SoundEffects.h"

class SpaceInvaders
{
private:

    std::unique_ptr<Cannon> m_cannon;
    std::unique_ptr<BulletList> m_bullet_list;
    std::unique_ptr<SoundEffects> m_sounds;

    std::vector< EnemyList* > m_enemy_vector;

    /* Number of screen's colums and rows */
    int m_nCol; // width
    int m_nRow; // height
    int m_score = 0;

public:
    /* Constructor
     * param col Num of screen's columns
     * param row Num of screen's lines
     * param posX Start X cordinate of Cannon
     * param posY Start Y cordinate of Cannon
     */
    SpaceInvaders (int col, int row, int posX, int posY, int h);
    ~SpaceInvaders ();

    /* This method deals to display on screen Cannon bullets and enemies */
    void display();

    /* Move left and right Cannon
     * param offset Offset which Cannon have to move
     *
     * return true If ok
     * return false Otherwise (e.g. Cannon reached right or left side of screen)
     */
    bool moveLeft(int offset);
    bool moveRight(int offset);

    /* Display's start Message */
    void startMessage();
    void gameOver();
    /* Shoot a bullet */
    bool shoot();

    /* Move upward bullets */
    void moveBullet();

    /* Move downward enemies */
    void moveEnemies();

    void sidebar();

    void changeCannonCollor();

    /* Check collision between bullets and enemies
     * (check if first element of bullist and enelist (with same X position) collide)
     */
    bool checkCollision();

    bool checkScore();

    /* Check if there are collision between cannon and enemies */
    bool checkCannonCollision();

    /* Add enemy to enlist */
    bool addEnemy();
};

#endif /* ifndef SPACEINVADERS_H */
