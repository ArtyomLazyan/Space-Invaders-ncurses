#ifndef BULLETLIST_H
#define BULLETLIST_H

#include <ctime>
#include <list>
#include <ncurses.h>
#include <cstdlib>

#include "settings.h"

class Bullet
{
public:
    int m_posX;
    int m_posY;
    int m_color;

    /* Start time of bullet's life */
    clock_t m_timeStart;

    Bullet(int posX, int posY, int color);
    ~Bullet();

    bool move();
    int getX();
    int getY();
    void setColor(int color);
    int getColor();
    void display();
};

class BulletList
{
private:
	/* List contains Bullet objecst */
    std::list<Bullet *> m_bullet_l;

public:
    BulletList();
    ~BulletList();

    /* Add a bullet at the end of list */
    bool addBullet(int posX, int posY, int color);
    /* Remove the first list's element */
    bool removeFirst();
    bool removeLast();
    bool moveBullet();
    void displayBullet();
    int getY();

    /* Move to begining the iterator and return
     * return NULL if is reached end of list
     */
    std::list<Bullet *>::iterator begin();
    /* Advance iterator to the next element and return or NULL */
    std::list<Bullet *>::iterator end();
};

#endif /* ifndef BULLETLIST_H */
