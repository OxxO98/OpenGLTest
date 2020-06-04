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
    : State(GAME_ACTIVE), Keys(), Mouse(), MouseEvent(), Width(width), Height(height)
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
    MainMenu.Load("MainMenu",this->Width, this->Height);

    GamePage BattlePage;
    BattlePage.Load("BattlePage", this->Width, this->Height);

    this->Pages.push_back(MainMenu);
    this->Pages.push_back(BattlePage);
    this->page = 0;

    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - 200.0f, this->Height - 200.0f);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("background"), "player");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{   
    if (this->State == GAME_ACTIVE)
    {
        if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
            //std::cout << Mouse[0] << Mouse[1] << std::endl;
            if (MouseCollision(*Player)) {
                //std::cout << Player->Size.x << Player->Size.y << std::endl;
                std::cout << "true" << std::endl;
            }
            for (int i = 0; i < Pages[this->page].GameObjs.size(); i++) {
                if (MouseCollision(Pages[this->page].GameObjs[i])) {
                    if (Pages[this->page].GameObjs[i].ID == "fight") {
                        this->State = GAME_WIN;
                        this->page = 1;
                        Pages[this->page].Draw(*Renderer);
                    }
                }
            }
        }
        // move player
        if (this->Keys[GLFW_KEY_W])
        {
            Player->Position.y += cTest("up");
        }
        if (this->Keys[GLFW_KEY_A])
        {
            Player->Position.x -= 10.0f;
        }
        if (this->Keys[GLFW_KEY_S])
        {
            Player->Position.y += cTest("down");
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
    this->Pages[this->page].Draw(*Renderer);
    Player->Draw(*Renderer);
}

unsigned int Game::MouseCollision(GameObject obj) {
    if (obj.Position.x < Mouse.x && Mouse.x < obj.Position.x + obj.Size.x) {
        if (obj.Position.y < Mouse.y && Mouse.y < obj.Position.y + obj.Size.y) {
            return true;
        }
    }
    return false;
}
