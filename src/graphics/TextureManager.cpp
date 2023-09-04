#include "TextureManager.h"

#include "Camera.h"

TextureManager* TextureManager::s_instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Failed to load texture : %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_texture_map[id] = texture;

    return true;
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_texture_map[id]);
    m_texture_map.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_texture_map.begin(); it != m_texture_map.end(); it++)
        SDL_DestroyTexture(it->second);

    m_texture_map.clear();
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scale_X = 1.0f, float scale_Y = 1.0f, float scroll_ratio = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_Rect src_rect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition() * scroll_ratio;
    SDL_Rect dst_rect = {int(x -cam.X), y, int(width * scale_X), int(height * scale_Y)};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_texture_map[id], &src_rect, &dst_rect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale_X = 1.0f, float scale_Y= 1.0f)
{
    SDL_Rect src_rect = {width*frame, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dst_rect = {int(x - cam.X), y, int(width * scale_X), int(height * scale_Y)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_texture_map[id], &src_rect, &dst_rect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tileset_id, int tile_size, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dst_rect = {x - int(cam.X), y, tile_size, tile_size};
    SDL_Rect src_rect = {tile_size*frame, tile_size*row, tile_size, tile_size};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_texture_map[tileset_id], &src_rect, &dst_rect, 0, nullptr, flip);
}

bool TextureManager::ParseTexture(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        std::cout << "Failed to load : " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            Load("id", "source");
        }
    }

    return true;
}


