#ifndef SOUNDSMANAGER_H
#define SOUNDSMANAGER_H

#include <iostream>
#include <string>
#include <map>

#include <SDL2/SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048

using MusicMap = std::map <std::string, Mix_Music*>;
using EffectMap = std::map <std::string, Mix_Chunk*>;


class SoundsManager
{
    public:
        inline static SoundsManager* GetInstance()
        {
            return s_instance = (s_instance != nullptr)? s_instance : new SoundsManager();
        }

        void PlayMusic(std::string id);
        void LoadMusic(std::string id, std::string source);

        void PlayEffect(std::string id);
        void LoadEffect(std::string id, std::string source);

        void Clean();

    private:
        SoundsManager();
        static SoundsManager* s_instance;

        MusicMap m_music_map;
        EffectMap m_effect_map;
};

#endif // SOUNDSMANAGER_H
