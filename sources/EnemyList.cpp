#include "../headers/EnemyList.h"

/*************** class Enemy ***********************/

Enemy::Enemy(int posX, int posY, int type)
{
    m_posX = posX;
    m_posY = posY;
    m_type = type;
    m_animation_flag = true;
    m_type = type;

    m_timeStart = clock();

    switch (type) {
        case 0:
            m_life = BIGSPACECRAFT_LIFE;
            break;
        case 1:
            m_life = SPACECRAFT_LIFE;
            break;
        case 2:
            m_life = ASTEROID_LIFE;
            break;
        default:
            m_life = ASTEROID_LIFE;
    }
}

Enemy::~Enemy() {}

bool Enemy::move()
{
    clock_t timeTmp;
    double diff = 0;

    timeTmp = clock();
    diff = ((double)timeTmp - (double)m_timeStart);
    diff /= CLOCKS_PER_SEC;


    if (diff >= (double)ENEMY_SPEED)
    {
        m_timeStart = timeTmp;
        m_posY++;

        m_animation_flag = m_animation_flag ? false : true;

        return true;
    }

    return false;
}

int Enemy::getX()
{
    return m_posX;
}

int Enemy::getY()
{
    return m_posY;
}

void Enemy::setColor(int color)
{
    m_color = color;
}

int Enemy::getColor()
{
    return m_color;
}

bool Enemy::decreaseLife()
{
    if (m_life > 0)
    {
        m_life--;
        return false;
    }

    return true;
}

int Enemy::getType()
{
    return m_type;
}

void Enemy::display()
{
    switch (m_type)
    {
        case 0:
            attron(COLOR_PAIR(2));
            setColor(2);
            if (m_animation_flag)
            {
                    mvprintw(m_posY, m_posX, " {@@} ");
                mvprintw(m_posY + 1, m_posX, " /\"\"\\ ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            else
            {
                    mvprintw(m_posY, m_posX, " {@@} ");
                mvprintw(m_posY + 1, m_posX, "  \\/  ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            break;
        case 1:
            attron(COLOR_PAIR(1));
            setColor(1);
            if (m_animation_flag)
            {
                    mvprintw(m_posY, m_posX, " dOOb ");
                mvprintw(m_posY + 1, m_posX, " ^/\\^ ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            else
            {
                    mvprintw(m_posY, m_posX, " dOOb ");
                mvprintw(m_posY + 1, m_posX, " ~||~ ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            break;
        case 2:
            attron(COLOR_PAIR(3));
            setColor(3);
            if (m_animation_flag)
            {
                    mvprintw(m_posY, m_posX, " /MM\\ ");
                mvprintw(m_posY + 1, m_posX, " |~~| ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            else
            {
                    mvprintw(m_posY, m_posX, " /MM\\ ");
                mvprintw(m_posY + 1, m_posX, " \\~~/ ");
                mvprintw(m_posY + 2, m_posX, "      ");
            }
            break;

        default:
            break;
    }
}

/**************************************************/

/**************** class EnemyList *****************/


EnemyList::EnemyList(int nCol, int type)
{
    m_nCol = nCol;
    m_type = type;
    srand(time(NULL));

    for (int i = 20; i < nCol; i += 10)
    {
        m_enemy_l.push_back(std::move(new Enemy(i, 1, rand() % 3)));
    }
}

EnemyList::~EnemyList()
{
   for (auto enemy : m_enemy_l)
   {
       delete enemy;
   }
}

bool EnemyList::removeFirst()
{
    auto iter = m_enemy_l.begin();
    delete *iter;
    m_enemy_l.pop_front();

    return true;
}

bool EnemyList::removeLast()
{
    auto iter = m_enemy_l.end();
    delete *(--iter);
    m_enemy_l.pop_back();

    return true;
}

bool EnemyList::moveEnemy()
{
    for (auto enemy : m_enemy_l)
    {
        enemy->move();
    }

    return true;
}

void EnemyList::displayEnemy()
{
    for (auto enemy : m_enemy_l)
    {
        enemy->display();
    }
}

bool EnemyList::deleteEnemy(std::list<Enemy *>::iterator& iter)
{
    delete *iter;
    iter = m_enemy_l.erase(iter);
    return true;
}

std::list<Enemy *>::iterator EnemyList::begin()
{
    return m_enemy_l.begin();
}

std::list<Enemy *>::iterator EnemyList::end()
{
    return m_enemy_l.end();
}

/***********************************************/
