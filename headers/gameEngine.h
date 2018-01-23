#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SpaceInvaders.h"
#include <thread>
#include <memory>

#include "settings.h"

class gameEngine
{
private:

    std::unique_ptr<SpaceInvaders> m_game;
    SoundEffects *m_bgmusic;

    // for keyboard input
    int m_action = 0;
    bool m_endGame = false;
    clock_t m_timeStart;

public:
    gameEngine();
    ~gameEngine();
    void run();
};

#endif /* ifndef GAMEENGINE_H */
