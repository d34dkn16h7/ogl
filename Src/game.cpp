#include "game.h"


Game* Game::ins;
GameObject* Game::onControl;
bool Game::isOpen,Game::isEditor;
float Game::deltaTime,Game::lastTime,Game::Speed;

int Game::Run()
{
    isOpen = Renderer::Setup(1024,576,GLFW_WINDOW);//isOpen = Renderer::Setup(1280,800,GLFW_FULLSCREEN);
    map.LoadMap("Data/m.mp");
    Input::Init();
    while(isOpen && !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED))
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
    Speed = 5;
    lastTime = glfwGetTime();
    editor.SetTarget(&map);
    isEditor = true;
    Input::Init();
}
void Game::Update()
{
    if(glfwGetKey(GLFW_KEY_HOME))
        isEditor = !isEditor;

    Input::Update();

    if(isEditor)
        editor.Update();
    input();
}
void Game::input()
{
    if(onControl != nullptr)
    {
        if(glfwGetKey('W'))
            onControl->aPosition(Up * Speed * deltaTime);
        if(glfwGetKey('S'))
            onControl->aPosition(Down * Speed * deltaTime);
        if(glfwGetKey('A'))
            onControl->aPosition(Left * Speed * deltaTime);
        if(glfwGetKey('D'))
            onControl->aPosition(Right * Speed * deltaTime);
    }
    if(glfwGetKey(GLFW_KEY_PAUSE))
        map.SaveMap("Data/m.mp");
}
void Game::Timer()
{
    deltaTime = ( glfwGetTime() - lastTime );
    lastTime = glfwGetTime();
}
