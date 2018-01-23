#include "../headers/gameEngine.h"

gameEngine::gameEngine()
{
    initscr();
    keypad(stdscr, true);

    // hide cursor
    curs_set(0);
    noecho();
    // non blocking call getch()
    nodelay(stdscr, true);

    start_color();
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);

    srand (time(NULL));

    m_timeStart = clock();

    m_game = std::make_unique<SpaceInvaders>(COLS, LINES, COLS / 2, LINES - 1, 1);
    m_bgmusic = new SoundEffects();
}

gameEngine::~gameEngine()
{
    endwin();
}

void gameEngine::run()
{
    move(0, 0);
    m_game->startMessage();

    // 10 is key value of ENTER and 27 of ESC
    while ((m_action = getch()) != 10)
    {
        if (m_action == 27)
        {
            m_endGame = true;
            break;
        }
    }

    move(0, 0);
    erase();
    m_action = 0;

    // for bg music
    std::thread t1(&SoundEffects::playBgMusic, m_bgmusic);

    while (!m_endGame)
    {
        m_action = getch();

        switch(m_action)
         {
            case ERR:
                 break;

            case KEY_RIGHT:
                m_game->moveRight(2);
                break;

            case KEY_LEFT:
                m_game->moveLeft(2);
                break;

            case (int)' ':
                m_game->shoot();
                break;

            case (int)'z':
                m_game->changeCannonCollor();
                break;

            case 27:
                m_endGame = true;
            break;
        }

        m_game->moveBullet();

        clock_t timeTmp;
        double diff = 0;

        timeTmp = clock();
        diff = ((double)timeTmp - (double)m_timeStart);
        diff /= CLOCKS_PER_SEC;

        if (diff >= (double)ENEMY_CREATING_SPEED)
        {
            m_timeStart = timeTmp;
            m_game->addEnemy();
        }

        m_game->moveEnemies();
        m_game->checkCollision();

        if (m_game->checkCannonCollision())
            m_endGame = true;
        if (m_game->checkScore())
            m_endGame = true;

        m_game->display();

        m_action = 0;
        refresh();
    }

    m_bgmusic->pauseBgMusic();
    m_game->gameOver();
    refresh ();

    // if press ESC then exit
    while ((m_action = getch()) != 27);

    // detach thread
    t1.detach();
    delete m_bgmusic;
}
