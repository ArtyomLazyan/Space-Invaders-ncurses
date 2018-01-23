#ifndef SOUNDEFECTS_H
#define SOUNDEFECTS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "ncurses.h"

class SoundEffects
{
    const char *MP3_PATH = "../sounds/bgMusic.wav";
    const char *SHOOT_PATH = "../sounds/shoot.wav";
    const char *EXPLOSION_PATH = "../sounds/explosion.wav";
    const char *GAMEOVER_PATH = "../sounds/gameOver.wav";
    const char *HITSHIP_PATH = "../sounds/hitAlien.wav";
    const char *SHOOTMISS_PATH = "../sounds/dontHit.wav";
    const char *CHANGECOLOR_PATH = "../sounds/changeCannonColor.wav";

    int m_result = 0;
    int m_flags = MIX_INIT_MP3;

    Mix_Music *m_music;
    Mix_Chunk *m_shoot;
    Mix_Chunk *m_explosion;
    Mix_Chunk *m_gameover;
    Mix_Chunk *m_hitShip;
    Mix_Chunk *m_shootMiss;
    Mix_Chunk *m_changeColor;

public:
    SoundEffects();
    void playBgMusic();
    void pauseBgMusic();
    void shoot();
    void explosion();
    void gameover();
    void hitSHip();
    void shootMiss();
    void changeColor();

    ~SoundEffects();
};

#endif
