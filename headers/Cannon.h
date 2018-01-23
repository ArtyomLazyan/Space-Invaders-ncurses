#ifndef CANNON_H
#define CANNON_H

#include "BulletList.h"

class Cannon
{
private:

    int m_posX;
    int m_posY;

    /* Variable to indicate the max limit untill cannon can move */
    int m_maxLimit;
    /* Variable to indicate the min limit untill cannon can move */
    int m_minLimit;

    /* cannon's height */
    int m_height;

    int m_color;

public:
    Cannon (int posX, int posY, int maxLimit, int minLimit, int height);
    ~Cannon ();

    int getX();
    int getY();
    int getColor();
    void setColor(int color);

    /* Offset which cannon have to move */
    bool moveLeft(int offset);
    bool moveRight(int offset);

    void display();
};

#endif /* ifndef CANNON_H */
