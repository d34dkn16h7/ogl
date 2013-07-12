#include "map.h"
#include "game.h"
#include "input.h"
#include "editor.h"
#include "physics.h"
#include "renderer.h"
#include "gameObject.h"

#include "camera.h"
Game* Game::ins;
GameObject* Game::onControl;
bool Game::isOpen,Game::isEditor;
float Game::deltaTime,Game::lastTime,Game::Speed;

int Game::Run()
{
    Speed = 15;
    isEditor = true;
    editor->SetTargetMap(map);
    map->LoadMap( Settings::mapFile );
    lastTime = glfwGetTime();
    while( (isOpen && !Input::isKey(GLFW_KEY_ESCAPE)) && !glfwWindowShouldClose( Renderer::gWindow() ) )
    {
        glfwPollEvents();
        Update();
        Renderer::Render();
        Timer();
    }
    glfwDestroyWindow( Renderer::gWindow() );
    glfwTerminate();
    return 0;
}

Game::Game() : map( new Map() ) , editor( new Editor() )
{
    ins = this;
    Tools::Settings::LoadSettings();
    isOpen = Renderer::Setup(1024,576);
    Input::Init();
}

void Game::Update() /// Update all
{
    if(  Input::isKey(GLFW_KEY_HOME))
        isEditor = !isEditor;

    Input::Update();
    Physics::UpdateAll();

    if(isEditor)
        editor->Update();

    input();
}

void Game::input() /// Player input - remove it later
{
    if(onControl != nullptr)
    {
        Physics* p = onControl->GetComponent<Physics>();
        if(p != nullptr)
        {
            if(Input::isKey('W'))
                p->Move(Up * Speed * deltaTime);
            if(Input::isKey('S'))
                p->Move(Down * Speed * deltaTime);
            if(Input::isKey('A'))
                p->Move(Left * Speed * deltaTime);
            if(Input::isKey('D'))
                p->Move(Right * Speed * deltaTime);
        }
    }
    if(Input::isKey(GLFW_KEY_PAUSE))
        map->SaveMap("Data/m.mp");
}

void Game::Timer() /// Update deltaTime
{
    deltaTime = ( glfwGetTime() - lastTime );
    lastTime = glfwGetTime();
}
