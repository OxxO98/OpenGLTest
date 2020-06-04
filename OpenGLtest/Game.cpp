#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GamePage.h"

//C파트
#include "cTest.h"

#include <iostream>

SpriteRenderer* Renderer;
GameObject* Player;

const glm::vec2 PLAYER_SIZE(200.0f, 200.0f);

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    //example code
    ResourceManager::LoadShader("3.3.shader.vs", "3.3.shader.fs", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader2D myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);
    // load textures
    
    //ResourceManager::LoadTexture("img/asdf-sq-512-h.png", true, "block_solid");
    ResourceManager::LoadTexture("img/asdf2-h.png", true, "background");
    ResourceManager::LoadTexture("img/전투.png", true, "fight");
    ResourceManager::LoadTexture("img/편성.png", true, "set");
    ResourceManager::LoadTexture("img/이벤트.png", true, "event");

    GamePage MainMenu;
    MainMenu.Load(this->Width, this->Height);

    this->Pages.push_back(MainMenu);
    this->page = 0;

    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - 200.0f, this->Height - 200.0f);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("background"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{   
    if (this->State == GAME_ACTIVE)
    {
        // move playerboard
        if (this->Keys[GLFW_KEY_W])
        {
            Player->Position.y -= 10.0f;
        }
        if (this->Keys[GLFW_KEY_A])
        {
            Player->Position.x -= 10.0f;
        }
        if (this->Keys[GLFW_KEY_S])
        {
            Player->Position.y += 10.0f;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            Player->Position.x += 10.0f;
        }
    }
}

void Game::Render()
{
    //multiple render
    Texture2D fight = ResourceManager::GetTexture("fight");
    Renderer->DrawSprite(fight, glm::vec2(758.0f, 259.0f), glm::vec2(450, 179), 0.0f);
    Texture2D set = ResourceManager::GetTexture("set");
    Renderer->DrawSprite(set, glm::vec2(780.0f, 457.0f), glm::vec2(225, 105), 0.0f);
    Texture2D event = ResourceManager::GetTexture("event");
    Renderer->DrawSprite(event, glm::vec2(968.0f, 528.0f), glm::vec2(225, 105), 0.0f);
    //Texture2D background = ResourceManager::GetTexture("background");
    //Renderer->DrawSprite(background, glm::vec2(250.0f, 250.0f), glm::vec2(700, 800), 0.0f);
    Player->Draw(*Renderer);
    //this->Pages[this->page].Draw(*Renderer);
}