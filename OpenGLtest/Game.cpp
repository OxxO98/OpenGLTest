#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GamePage.h"

#include <iostream>
#include <string>

//C파트
#include "cTest.h"

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
    
    //캐릭터 텍스처 불러오기 (졸라 많아질 예정)
    ResourceManager::LoadTexture("img/메인배경.png", false, "mainBackground");
    ResourceManager::LoadTexture("img/전투배경.png", false, "battleBackground");
    ResourceManager::LoadTexture("img/목록배경.png", false, "listBackground");
    ResourceManager::LoadTexture("img/전투.png", true, "fight");
    ResourceManager::LoadTexture("img/편성.png", true, "set");
    ResourceManager::LoadTexture("img/목록.png", true, "list");
    ResourceManager::LoadTexture("img/backwardButton.png", true, "backwardButton");
    ResourceManager::LoadTexture("img/setButton.png", true, "setButton");
    ResourceManager::LoadTexture("img/noneImage.png", true, "CID0");
    ResourceManager::LoadTexture("img/CODEX-잉퀴시티오.png", true, "CID1");
    ResourceManager::LoadTexture("img/CODEX-세라.png", true, "CID2");
    ResourceManager::LoadTexture("img/CODEX-레아르.png", true, "CID3");

    //유저 정보 로드 페이지 로드 전에 할것!
    initUserCharacters();
    initComposition();
    //showUserCharacters();

    //페이지 로드
    GamePage MainMenu;
    MainMenu.Load("MainMenu",this->Width, this->Height);
    GamePage BattlePage;
    BattlePage.Load("BattlePage", this->Width, this->Height);
    GamePage CharactersPage;
    CharactersPage.Load("CharactersPage", this->Width, this->Height);
    GamePage SettingPage;
    SettingPage.Load("SettingPage", this->Width, this->Height);

    this->Pages.push_back(MainMenu);
    this->Pages.push_back(BattlePage);
    this->Pages.push_back(CharactersPage);
    this->Pages.push_back(SettingPage);
    //현재 페이지
    this->page = 0;
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{   
    if (this->State == GAME_ACTIVE)
    {
        //마우스 이벤트
        if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
            for (int i = 0; i < Pages[this->page].GameObjs.size(); i++) {
                if (MouseCollision(Pages[this->page].GameObjs[i])) {
                    if (Pages[this->page].GameObjs[i].ID == "fight") {
                        this->page = 1;
                        Pages[this->page].Draw(*Renderer);
                    }
                    else if (Pages[this->page].GameObjs[i].ID == "list") {
                        this->page = 2;
                        Pages[this->page].Draw(*Renderer);
                    }
                    else if (Pages[this->page].GameObjs[i].ID == "set") {
                        this->page = 3;
                        Pages[this->page].Draw(*Renderer);
                    }
                    else if (Pages[this->page].GameObjs[i].ID == "backwardButton") {
                        this->page = 0;
                        Pages[this->page].Draw(*Renderer);
                    }
                    else if (int pos = Pages[this->page].GameObjs[i].ID.find("setButton") != std::string::npos) {
                        procComposition(std::stoi(Pages[this->page].GameObjs[i].ID.substr(pos + 8)));
                        this->State = GAME_PROC;
                        this->page = 2;
                        Pages[this->page].Draw(*Renderer);
                    }
                }
            }
        }
    }
    if (this->State == GAME_PROC) {
        if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
            if (Pages[this->page].PID == "CharactersPage") {
                for (int i = 0; i < Pages[this->page].GameObjs.size(); i++) {
                    if (MouseCollision(Pages[this->page].GameObjs[i])) {
                        if (int pos = Pages[this->page].GameObjs[i].ID.find("CID") != std::string::npos) {
                            setComposition(procIndex, std::stoi(Pages[this->page].GameObjs[i].ID.substr(pos + 2)));
                            this->State = GAME_ACTIVE;
                            this->page = 3;
                            Pages[this->page].Draw(*Renderer);
                        }
                    }
                }
            }
        }
    }
}

void Game::Render()
{
    //multiple render
    this->Pages[this->page].Draw(*Renderer);
    //Player->Draw(*Renderer);
}

unsigned int Game::MouseCollision(GameObject obj) {
    if (obj.Position.x < Mouse.x && Mouse.x < obj.Position.x + obj.Size.x) {
        if (obj.Position.y < Mouse.y && Mouse.y < obj.Position.y + obj.Size.y) {
            return true;
        }
    }
    return false;
}
