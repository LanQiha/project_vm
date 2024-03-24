#include "engine.h"

#include "MapHandler.h"
#include "Camera.h"

#include "SoundsManager.h"
#include "ObjectFactory.h"

#include "GameObject.h"

#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"

#include "Timer.h"

#include "Vegito.h"


Engine* Engine::s_instance = nullptr;

Properties* props = new Properties("vegito", 100, 100, 392/4, 72);
Vegito* vegito = new Vegito(props);

//GameObject* vegito = ObjectFactory::GetInstance()->CreateObject("Vegito", props);


bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(imgFlags) != imgFlags)
    {
        SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("project_vm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_window == nullptr)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == nullptr)
    {
        SDL_Log("Failed to create renderer : %s", SDL_GetError());
        return false;
    }

    if(MapParser::get_instance()->load())
    {
        std::cout << "Map loaded." << std::endl;
    }

    m_level_map = MapParser::get_instance()->get_map("level_1");

    // TextureManager::GetInstance()->ParseTexture("textures.tmx");

    TextureManager::GetInstance()->Load("plains_day", "assets/images/plains_day.png");
    TextureManager::GetInstance()->Load("vegito_stand", "assets/animations/vegito/vegito_ssj_std.png");
    TextureManager::GetInstance()->Load("vegito_fly", "assets/animations/vegito/vegito_ssj_fly.png");
    TextureManager::GetInstance()->Load("vegito_dash", "assets/animations/vegito/vegito_dash.png");
    TextureManager::GetInstance()->Load("vegito_protects", "assets/animations/vegito/vegito_protects.png");
    TextureManager::GetInstance()->Load("vegito_legs_attack", "assets/animations/vegito/vegito_legs_attack.png");
    TextureManager::GetInstance()->Load("vegito_jump", "assets/animations/vegito/vegito_jump.png");

    SoundsManager::GetInstance()->LoadMusic("verdant", "assets/sounds/music/blazing_blue_fusion.mp3");
    SoundsManager::GetInstance()->PlayMusic("verdant");

    Camera::GetInstance()->SetTarget(vegito->get_origin());

    return m_is_running = true;
}

void Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SoundsManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_is_running = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_level_map->update();
    vegito->update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_RenderClear(m_renderer);

    TextureManager::GetInstance()->Draw("plains_day", 0, 0, SCREEN_WIDTH * 1.5, SCREEN_HEIGHT, 1.0f, 1.0f, 0.1f, SDL_FLIP_NONE);

    m_level_map->render();

    vegito->draw();

    SDL_RenderPresent(m_renderer);
}

void Engine::Event()
{
    Event::GetInstance()->Listen();
}
