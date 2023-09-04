#include "engine.h"
#include "Timer.h"

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->GetIsRunning())
    {
        Engine::GetInstance()->Event();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}
