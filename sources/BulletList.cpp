#include "../headers/BulletList.h"

/*************** class Bullet ***********************/

Bullet::Bullet(int posX, int posY, int color)
{
    m_posX = posX;
    m_posY = posY;
    m_color = color;

    m_timeStart = clock();
}

Bullet::~Bullet() {}

bool Bullet::move()
{

    clock_t timeTmp;
    double diff = 0;

    timeTmp = clock();
    diff = ((double)timeTmp - (double)m_timeStart);
    diff /= CLOCKS_PER_SEC;


    if (diff >= (double)BULLET_SPEED)
    {
        m_timeStart = timeTmp;
        m_posY--;

        return true;
    }

    return false;
}

int Bullet::getX()
{
    return m_posX;
}

int Bullet::getY()
{
    return m_posY;
}

void Bullet::setColor(int color)
{
    m_color = color;
}

int Bullet::getColor()
{
    return m_color;
}

void Bullet::display()
{
    attron(COLOR_PAIR(m_color));
    mvprintw(m_posY, m_posX, "*");
}

/**************************************************/

/**************** class BulletList *****************/

BulletList::BulletList()
{
}

BulletList::~BulletList()
{
   for (auto bullet : m_bullet_l)
   {
       delete bullet;
   }
}

bool BulletList::addBullet(int posX, int posY, int color)
{
    m_bullet_l.push_back(std::move(new Bullet(posX, posY, color)));

    return true;
}

bool BulletList::removeFirst()
{
    auto iter = m_bullet_l.begin();
    delete *iter;
    m_bullet_l.pop_front();

    return true;
}

bool BulletList::removeLast()
{
    auto iter = m_bullet_l.end();
    delete *iter;
    m_bullet_l.pop_back();

    return true;
}

bool BulletList::moveBullet()
{
    if (!m_bullet_l.empty())
    {
        for (auto bullet : m_bullet_l)
        {
            bullet->move();
        }

		// iteratr to the begin of bullet list
        auto begin = m_bullet_l.begin();

        if (((*begin)->getY()) < 0)
            removeFirst();

        return true;
    }

    return false;
}

void BulletList::displayBullet()
{
    if (!m_bullet_l.empty())
    {
        for (auto bullet : m_bullet_l)
        {
            bullet->display();
        }
    }
}

std::list<Bullet *>::iterator BulletList::begin()
{
    return m_bullet_l.begin();
}

std::list<Bullet *>::iterator BulletList::end()
{
    return m_bullet_l.end();
}

/*************************************************/
