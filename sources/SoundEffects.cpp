#include "../headers/SoundEffects.h"

SoundEffects::SoundEffects()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (m_flags != (m_result = Mix_Init(m_flags)))
	{
        printf("Could not initialize mixer (result: %d).\n", m_result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    m_music = Mix_LoadMUS(MP3_PATH);
    m_shoot = Mix_LoadWAV(SHOOT_PATH);
    m_explosion = Mix_LoadWAV(EXPLOSION_PATH);
    m_gameover = Mix_LoadWAV(GAMEOVER_PATH);
    m_shootMiss = Mix_LoadWAV(SHOOTMISS_PATH);
    m_hitShip = Mix_LoadWAV(HITSHIP_PATH);
    m_changeColor = Mix_LoadWAV(CHANGECOLOR_PATH);
}

SoundEffects::~SoundEffects()
{
    Mix_FreeMusic(m_music);
    Mix_FreeChunk(m_shoot);
    Mix_FreeChunk(m_explosion);
    Mix_FreeChunk(m_gameover);
    Mix_FreeChunk(m_shootMiss);
    Mix_FreeChunk(m_hitShip);
    Mix_FreeChunk(m_changeColor);

    Mix_CloseAudio();
    SDL_Quit();
}

void SoundEffects::playBgMusic()
{
    Mix_PlayMusic(m_music, 1);
    while (!SDL_QuitRequested()) {
            SDL_Delay(250);
    }
}

void SoundEffects::pauseBgMusic()
{
    Mix_PauseMusic();
}

void SoundEffects::shoot()
{
    Mix_PlayChannel(-1, m_shoot, 0);
}

void SoundEffects::explosion()
{
    Mix_PlayChannel(-1, m_explosion, 0);
}

void SoundEffects::gameover()
{
    Mix_PlayChannel(-1, m_gameover, 0);
}

void SoundEffects::hitSHip()
{
    Mix_PlayChannel(-1, m_hitShip, 0);
}

void SoundEffects::shootMiss()
{
    Mix_PlayChannel(-1, m_shootMiss, 0);
}

void SoundEffects::changeColor()
{
    Mix_PlayChannel(-1, m_changeColor, 0);
}
