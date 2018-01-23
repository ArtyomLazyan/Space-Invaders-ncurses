#include "../headers/Cannon.h"

Cannon::Cannon(int posX, int posY, int maxLimit, int minLimit, int height)
{
    m_posX = posX;
    m_posY = posY;

    int color = 1 + (rand() % 3);
    m_color = color;

    m_maxLimit = maxLimit;
    m_minLimit = minLimit;

    m_height = height;
}

Cannon::~Cannon() {}

bool Cannon::moveLeft(int offset)
{
    if ((m_posX - offset) < m_minLimit)
        return false;

    m_posX -= offset;
    return true;
}

bool Cannon::moveRight(int offset)
{
    if ((m_posX + offset) > m_maxLimit)
        return false;

    m_posX += offset;
    return true;
}

int Cannon::getX()
{
    return m_posX;
}

int Cannon::getY()
{
    return m_posY;
}

int Cannon::getColor()
{
    return m_color;
}

void Cannon::setColor(int color)
{
    m_color = color;
}

void Cannon::display()
{
    //Print cannon
    attron(COLOR_PAIR(m_color));
    mvprintw(m_posY - 1, m_posX, "^");
    mvprintw(m_posY, m_posX - 1, "###");
}
