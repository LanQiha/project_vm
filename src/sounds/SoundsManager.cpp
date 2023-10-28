#include "SoundsManager.h"

SoundsManager* SoundsManager::s_instance = nullptr;

SoundsManager::SoundsManager()
{
    if(Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE))
        std::cerr << Mix_GetError() << std::endl;
}

void SoundsManager::PlayMusic(std::string id)
{
    if(Mix_PlayMusic(m_music_map[id], -1) == -1)
        std::cerr << Mix_GetError() << " : " << id << std::endl;
}

void SoundsManager::LoadMusic(std::string id, std::string source)
{
    Mix_Music* music = Mix_LoadMUS(source.c_str());
    if(music != nullptr)
        m_music_map[id] = music;
    else
        std::cerr << Mix_GetError() << " : " << source << std::endl;
}

void SoundsManager::PlayEffect(std::string id)
{
    if(Mix_PlayChannel(-1, m_effect_map[id], 0) == -1)
        std::cerr << Mix_GetError() << " : " << id << std::endl;
}

void SoundsManager::LoadEffect(std::string id, std::string source)
{
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if(effect != nullptr)
        m_effect_map[id] = effect;
    else
        std::cerr << Mix_GetError() << " : " << source << std::endl;
}

void SoundsManager::Clean()
{
    for(MusicMap::iterator it = m_music_map.begin(); it != m_music_map.end(); it++)
        Mix_FreeMusic(it->second);

    for(EffectMap::iterator it = m_effect_map.begin(); it != m_effect_map.end(); it++)
        Mix_FreeChunk(it->second);

    m_music_map.clear();
    m_effect_map.clear();

    std::cout << "SoundsManager::Clean()" << std::endl;
}
