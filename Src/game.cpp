#include "game.h"


Game* Game::ins;
bool Game::isOpen;
float Game::deltaTime,Game::lastTime,Game::Speed;

int Game::Run()
{
    isOpen = Renderer::Setup(1024,576,GLFW_WINDOW);//isOpen = Renderer::Setup(1280,800,GLFW_FULLSCREEN);
    map.LoadMap("Data/m.mp");
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
    Input::Init();
}
void Game::Update()
{
    Input::Update();
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

    if(glfwGetKey(GLFW_KEY_LSHIFT))
        Renderer::sCamera()->aPosition(Forward * deltaTime);
    if(glfwGetKey(GLFW_KEY_LCTRL))
        Renderer::sCamera()->aPosition(Backward * deltaTime);
}
void Game::Timer()
{
    deltaTime = ( glfwGetTime() - lastTime );
    lastTime = glfwGetTime();
}
