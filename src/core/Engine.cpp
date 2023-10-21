#include "engine.h"

Engine* Engine::s_instance = nullptr;

Properties* props = new Properties("Vegito", 100, 100, 392/4, 72);
Vegito* vegito = new Vegito(props);

bool Engine::Init()
{
    // Initialize the SDL library.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Specify the image formats to initialize for SDL_image.
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

    // Initialize SDL_image with the specified image formats.
    if (IMG_Init(imgFlags) != imgFlags) {
        SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    // Create an SDL window with the specified title, position, and dimensions.
    m_window = SDL_CreateWindow("project_vm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    // Check if the window creation was successful.
    if(m_window == nullptr) {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    // Create an SDL renderer for rendering graphics with hardware acceleration and vsync.
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Check if the renderer creation was successful.
    if(m_renderer == nullptr) {
        SDL_Log("Failed to create renderer : %s", SDL_GetError());
        return false;
    }

    // Load the game map using the MapParser singleton instance.
    if(MapParser::GetInstance()->Load()) {
        std::cout << "Game map loaded successfully." << std::endl;
    } else {
        std::cout << "Failed to load the game map." << std::endl;
    }

    // Retrieve the game map for "Level_1" from the MapParser singleton instance.
    m_levelMap = MapParser::GetInstance()->GetMap("Level_1");

    // Load various textures using the TextureManager singleton instance.
    TextureManager::GetInstance()->Load("plains_day", "assets/images/plains_day.png");
    TextureManager::GetInstance()->Load("vegito_stand", "assets/animations/vegito/vegito_ssj_std.png");
    TextureManager::GetInstance()->Load("vegito_fly", "assets/animations/vegito/vegito_ssj_fly.png");
    TextureManager::GetInstance()->Load("vegito_dash", "assets/animations/vegito/vegito_dash.png");
    TextureManager::GetInstance()->Load("vegito_protects", "assets/animations/vegito/vegito_protects.png");
    TextureManager::GetInstance()->Load("vegito_legs_attack", "assets/animations/vegito/vegito_legs_attack.png");
    TextureManager::GetInstance()->Load("vegito_jump", "assets/animations/vegito/vegito_jump.png");

    // Load music and play it using the SoundsManager singleton instance.
    SoundsManager::GetInstance()->LoadMusic("blazing_blue_fusion", "assets/sounds/music/blazing_blue_fusion.mp3");
    SoundsManager::GetInstance()->PlayMusic("blazing_blue_fusion");

    // Set the camera's target to Vegito's origin for tracking.
    Camera::GetInstance()->SetTarget(vegito->get_origin());

    // Set the engine's running flag to true, indicating that the engine is running.
    return m_isRunning = true;
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
    m_isRunning = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_levelMap->update();
    vegito->update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_RenderClear(m_renderer);

    TextureManager::GetInstance()->Draw("plains_day", 0, 0, SCREEN_WIDTH * 1.5, SCREEN_HEIGHT, 1.0f, 1.0f, 0.1f, SDL_FLIP_NONE);

    m_levelMap->render();

    vegito->draw();

    SDL_RenderPresent(m_renderer);
}

void Engine::Event()
{
    Event::GetInstance()->Listen();
}
