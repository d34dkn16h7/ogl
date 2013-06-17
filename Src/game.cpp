#include "gui.h"
#include "game.h"
#include "input.h"
#include "physics.h"
#include "renderer.h"

Game* Game::ins;
GameObject* Game::onControl;
bool Game::isOpen,Game::isEditor;
float Game::deltaTime,Game::lastTime,Game::Speed;

int Game::Run()
{
    isOpen = Renderer::Setup(1024,576,GLFW_WINDOW);//isOpen = Renderer::Setup(1280,800,GLFW_FULLSCREEN);
    map.LoadMap("Data/m.mp");
    Input::Init();
    while(isOpen && !Input::isKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED))
    {
        Update();
        Renderer::Render();
        Timer();
    }
    glfwTerminate();
    return 0;
}
Game::Game()
{
    ins = this;
    Speed = 15;
    lastTime = glfwGetTime();
    editor.SetTargetMap(&map);
    isEditor = true;
    Input::Init();
}
void Game::Update()
{
    if(glfwGetKey(GLFW_KEY_HOME))
        isEditor = !isEditor;

    Input::Update();
    Physics::UpdateAll();

    if(isEditor)
        editor.Update();

    input();
}
void Game::input()
{
    if(onControl != nullptr)
    {
        Physics* p = (Physics*)onControl->GetComponent(ComponentType::C_Physics);
        if(Input::isKey('W'))
            p->Move(Up * Speed * deltaTime);
        if(Input::isKey('S'))
            p->Move(Down * Speed * deltaTime);
        if(Input::isKey('A'))
            p->Move(Left * Speed * deltaTime);
        if(Input::isKey('D'))
            p->Move(Right * Speed * deltaTime);
    }
    if(Input::isKey(GLFW_KEY_PAUSE))
        map.SaveMap("Data/m.mp");
}
void Game::Timer()
{
    deltaTime = ( glfwGetTime() - lastTime );
    lastTime = glfwGetTime();
}
