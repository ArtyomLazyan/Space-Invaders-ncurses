#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include <ctime>
#include <list>
#include <cstdlib>
#include <ncurses.h>

#include "settings.h"

class Enemy
{
public:
    int m_posX;
    int m_posY;
    int m_type;
    int m_life;
    int m_color;
    bool m_animation_flag;


    /* Start time of bullet's life */
    clock_t m_timeStart;

    Enemy(int posX, int posY, int type);
    ~Enemy();

    bool move();
    int getX();
    int getY();
    void setColor(int color);
    int getColor();
    bool decreaseLife();
    void display();
    int getType();
};

/************** EnemyList *************/
class EnemyList
{
private:
    int m_nCol;
    int m_type;

    std::list<Enemy *> m_enemy_l;

public:
    EnemyList(int nCol, int type);
    ~EnemyList();

    /* Remove the first list's element */
    bool removeFirst();
    bool removeLast();
    bool moveEnemy();
    bool shootBomb();
    void displayEnemy();
    int getY();

    /* Move to begining the iterator and return
     * return NULL if is reached end of list
     */
    std::list<Enemy *>::iterator begin();
    /* Advance iterator to the next element and return or NULL */
    std::list<Enemy *>::iterator end();

    /* Delete a bullet from EnemyList
     * retrun true if it's deleted
     */
    bool deleteEnemy(std::list<Enemy *>::iterator& iter);

};

#endif /* ifndef BULLETLIST_H */
