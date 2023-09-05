#include "SoundsManager.h"

//initialize the instance as a nullptr
SoundsManager* SoundsManager::s_instance = nullptr;

//the constructor of the SoundsManager class initialize the audio
SoundsManager::SoundsManager() {
    if(Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE))
        std::cerr << Mix_GetError() << std::endl;
}

void SoundsManager::PlayMusic(std::string id)
{
    if(Mix_PlayMusic(m_musicMap[id], -1) == -1)
        std::cerr << Mix_GetError() << " : " << id << std::endl;
}

void SoundsManager::LoadMusic(std::string id, std::string source)
{
    Mix_Music* music = Mix_LoadMUS(source.c_str());
    if(music != nullptr)
        m_musicMap[id] = music;
    else
        std::cerr << Mix_GetError() << " : " << source << std::endl;
}

void SoundsManager::PlayEffect(std::string id)
{
    if(Mix_PlayChannel(-1, m_effectMap[id], 0) == -1)
        std::cerr << Mix_GetError() << " : " << id << std::endl;
}

//function that loads a sound effect
void SoundsManager::LoadEffect(std::string id, std::string source)
{
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str()); //load the sound effect in the effect variable
    if(effect != nullptr) //verify if effect is not null
        m_effectMap[id] = effect; //load the effect in the effectMap
    else
        std::cerr << Mix_GetError() << " : " << source << std::endl; //get error message in case there is a problem
}

//function that cleans the
void SoundsManager::Clean()
{
    for(MusicMap::iterator it = m_musicMap.begin(); it != m_musicMap.end(); it++)
        Mix_FreeMusic(it->second);

    for(EffectMap::iterator it = m_effectMap.begin(); it != m_effectMap.end(); it++)
        Mix_FreeChunk(it->second);

    m_musicMap.clear();
    m_effectMap.clear();

    std::cout << "SoundsManager::Clean()" << std::endl;
}
