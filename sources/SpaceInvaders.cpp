#include "../headers/SpaceInvaders.h"

SpaceInvaders::SpaceInvaders(int col, int row, int posX, int posY, int h)
{
    m_nCol = col;
    m_nRow = row;

    m_cannon = std::make_unique<Cannon>(posX, posY, col - 1, -1, h);
    m_bullet_list = std::make_unique<BulletList>();
    m_sounds = std::make_unique<SoundEffects>();
}

SpaceInvaders::~SpaceInvaders()
{
    if (!m_enemy_vector.empty())
    {
        for (auto enemyList : m_enemy_vector)
        {
            delete enemyList;
        }
    }
}

void SpaceInvaders::startMessage ()
{
    attron(A_PROTECT);
    attron(COLOR_PAIR(1));
    mvprintw (0, m_nCol / 2 - 33, "                          _                     _               ");
    mvprintw (1, m_nCol / 2 - 33, "                         (_)                   | |              ");
    mvprintw (2, m_nCol / 2 - 33, " ___ _ __   __ _  ___ ___ _ _ ____   ____ _  __| | ___ _ __ ___ ");
    mvprintw (3, m_nCol / 2 - 33, "/ __| '_ \\ / _` |/ __/ _ \\ | '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|");
    mvprintw (4, m_nCol / 2 - 33, "\\__ \\ |_) | (_| | (_|  __/ | | | \\ V / (_| | (_| |  __/ |  \\__ \\");
    mvprintw (5, m_nCol / 2 - 33, "|___/ .__/ \\__,_|\\___\\___|_|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/");
    mvprintw (6, m_nCol / 2 - 33, "    | |                                                         ");
    mvprintw (7, m_nCol / 2 - 33, "    |_|                                                         ");


    attron(COLOR_PAIR(3));
    mvprintw(10, (COLS / 2) - 11, " /MM\\ ");
    mvprintw(11, (COLS / 2) - 11, " |~~| ");
    mvprintw(11, (COLS / 2) - 4, "=  10 points");

    attron(COLOR_PAIR(1));
    mvprintw(13, (COLS / 2) - 11, " dOOb ");
    mvprintw(14, (COLS / 2) - 11, " ~||~ ");
    mvprintw(14, (COLS / 2) - 4, "=  20 points");

    attron(COLOR_PAIR(2));
    mvprintw(16, (COLS / 2) - 11, " {@@} ");
    mvprintw(17, (COLS / 2) - 11, "  \\/  ");
    mvprintw(17, (COLS / 2) - 4, "=  40 points");

    attron(COLOR_PAIR(4));
    mvprintw (20, m_nCol / 2 - 25, "**************************************************");
    mvprintw (21, m_nCol / 2 - 25, "****         press 'ENTER' to start game      ****");
    mvprintw (22, m_nCol / 2 - 25, "****         press 'ESC' to quit              ****");
    mvprintw (23, m_nCol / 2 - 25, "****                                          ****");
    mvprintw (24, m_nCol / 2 - 25, "****              powered by Tyom             ****");
    mvprintw (25, m_nCol / 2 - 25, "**************************************************");
    refresh ();
}

void SpaceInvaders::gameOver()
{
    if (m_score < 0)
        m_score = 0;

    attron(A_PROTECT);
    attron(COLOR_PAIR(4));
    move(0, 0);
    erase();
         mvprintw (11, COLS / 2 - 25, "*************************************************");
         mvprintw (12, COLS / 2 - 25, "*************       GAME OVER        ************");
         mvprintw (13, COLS / 2 - 25, "*************************************************");
         mvprintw (14, COLS / 2 - 25, "****                                         ****");
mvprintw (15, COLS / 2 - 25, "%s%d%s","****               Score :  ", m_score, "               ****");
         mvprintw (16, COLS / 2 - 25, "****                                         ****");
         mvprintw (17, COLS / 2 - 25, "****          press 'ESC' to quit            ****");
         mvprintw (18, COLS / 2 - 25, "****                                         ****");
         mvprintw (19, COLS / 2 - 25, "****            powered by TM N1             ****");
         mvprintw (20, COLS / 2 - 25, "****                                         ****");
         mvprintw (21, COLS / 2 - 25, "*************************************************");

         m_sounds->gameover();
}

void SpaceInvaders::sidebar()
{
    attron(A_PROTECT);
    attron(COLOR_PAIR(4));
    for (int i = 0; i < m_nRow; i++)
    {
        mvprintw(i, 18, "|");
    }

    attron(COLOR_PAIR(1));
    mvprintw(1, 0, "^^Space Invaders^^");
    attron(COLOR_PAIR(4));
    mvprintw(4, 2, "%s%d",  "Score : ", m_score);

    mvprintw(6, 2, "Left : Right");
    mvprintw(7, 2,"<--  :  -->");
    mvprintw(9, 2, "SPACE - Shoot");
    mvprintw(11, 2, "Z - Change color");
    mvprintw(13, 2, "ESC - End Game");
}

bool SpaceInvaders::moveLeft(int offset)
{
    if ((m_cannon->getX() - offset - OFFSET_LS) < 0)
        return false;

    return m_cannon->moveLeft(offset);
}

bool SpaceInvaders::moveRight(int offset)
{
    if ((m_cannon->getX() + offset + OFFSET_RS) >= m_nCol)
        return false;

    return m_cannon->moveRight(offset);
}

void SpaceInvaders::display()
{
    // Clean screen
    erase();

    sidebar();

    m_cannon->display();
    m_bullet_list->displayBullet();

    for (auto enemy_list : m_enemy_vector)
    {
        enemy_list->displayEnemy();
    }
}

bool SpaceInvaders::shoot()
{
    m_bullet_list->addBullet(m_cannon->getX(), m_cannon->getY() - 1/* HEIGHT */ - 1, m_cannon->getColor());

    m_sounds->shoot();

    return true;
}

bool SpaceInvaders::addEnemy()
{
    int type = rand() % 3;
    m_enemy_vector.push_back(new EnemyList(m_nCol, type));

    return true;
}

bool SpaceInvaders::checkScore()
{
    if (m_score < 0)
        return true;

    return false;
}

void SpaceInvaders::moveEnemies()
{
    for (auto enemy_list : m_enemy_vector)
    {
        enemy_list->moveEnemy();
    }
}

void SpaceInvaders::moveBullet()
{
    m_bullet_list->moveBullet();
}

bool SpaceInvaders::checkCollision()
{
    for (auto enemy_list : m_enemy_vector)
    {
        for (auto enemy_iter = enemy_list->begin(); enemy_iter != enemy_list->end(); enemy_iter++)
        {
            for (auto bullet_iter = m_bullet_list->begin(); bullet_iter != m_bullet_list->end(); bullet_iter++)
            {
                if ( /* chech collision by enemy width 5 */
                        (
                            ((*enemy_iter)->getX() == (*bullet_iter)->getX())
                            || (((*enemy_iter)->getX() + 1) == (*bullet_iter)->getX())
                            || (((*enemy_iter)->getX() + 2) == (*bullet_iter)->getX())
                            || (((*enemy_iter)->getX() + 3) == (*bullet_iter)->getX())
                            || (((*enemy_iter)->getX() + 4) == (*bullet_iter)->getX())
                            || (((*enemy_iter)->getX() + 5) == (*bullet_iter)->getX())
                        )
                        &&  ((*enemy_iter)->getY() == (*bullet_iter)->getY())
                    )
                {
		    /* if collors are the same */
                    if  ((*enemy_iter)->getColor() == (*bullet_iter)->getColor())
                    {
                        m_bullet_list->removeFirst();
                        m_sounds->hitSHip();
                        /* if life remains then decrease */
                        if ((*enemy_iter)->decreaseLife())
                        {

                            switch((*enemy_iter)->getType())
                            {
                                /* Big Spacecraft */
                                case 0:
                                    m_score += 40;
                                    break;
                                /* Spacecraft */
                                case 1:
                                    m_score += 20;
                                    break;
                                /* Asteroid */
                                case 2:
                                    m_score += 10;
                                    break;
                            }

                            enemy_list->deleteEnemy(enemy_iter);
                            m_sounds->explosion();
                        }
                    }
                    else
                    {
                        m_bullet_list->removeFirst();
                        m_sounds->shootMiss();
                        m_score -= 10;
                    }

                    break;
                }
            }
        }
    }

    return true;
}

bool SpaceInvaders::checkCannonCollision()
{
    for (auto enemy_list : m_enemy_vector)
    {
        for (auto iter = enemy_list->begin(); iter != enemy_list->end(); iter++)
        {
            if ((*iter)->getY() >= (m_cannon->getY() - 2))
            return true;
        }
    }
    return false;
}

void SpaceInvaders::changeCannonCollor()
{
    int color = m_cannon->getColor()+1;

    if (color == 4) color = 1;
    m_cannon->setColor(color);
    m_sounds->changeColor();

}
