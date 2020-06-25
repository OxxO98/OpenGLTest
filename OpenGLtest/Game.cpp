#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GamePage.h"
#include "GMKL.h"

#include <iostream>
#include <string>

//C��Ʈ
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
    
    //ĳ���� �ؽ�ó �ҷ����� (���� ������ ����)
    ResourceManager::LoadTexture("img/���ι��.png", false, "mainBackground");
    ResourceManager::LoadTexture("img/�������.png", false, "battleBackground");
    ResourceManager::LoadTexture("img/��Ϲ��.png", false, "listBackground");
    ResourceManager::LoadTexture("img/�����������.png", false, "stageBackground");

    ResourceManager::LoadTexture("img/����.png", true, "stageButton");
    ResourceManager::LoadTexture("img/��.png", true, "compositionButton");
    ResourceManager::LoadTexture("img/�δ�.png", true, "listButton");
    ResourceManager::LoadTexture("img/���.png", true, "gattyaButton");
    ResourceManager::LoadTexture("img/����.png", true, "healButton");
    ResourceManager::LoadTexture("img/����.png", true, "kenkyuButton"); //�߸� ����

    ResourceManager::LoadTexture("img/backwardButton.png", true, "backwardButton");
    ResourceManager::LoadTexture("img/setButton.png", true, "setButton");
    ResourceManager::LoadTexture("img/stage1-1.png", true, "stage1-1");

    ResourceManager::LoadTexture("img/noneImage.png", true, "CID0");
    ResourceManager::LoadTexture("img/CODEX-������Ƽ��.png", true, "CID1");
    ResourceManager::LoadTexture("img/CODEX-����.png", true, "CID2");
    ResourceManager::LoadTexture("img/CODEX-���Ƹ�.png", true, "CID3");

    //���� ���� �ε� ������ �ε� ���� �Ұ�!
    initUserCharacters();
    initComposition();

    //������ �ε�
    GamePage MainMenu;
    MainMenu.Load(GMKL::MAIN_PAGE,this->Width, this->Height);
    GamePage StagePage;
    StagePage.Load(GMKL::STAGE_PAGE, this->Width, this->Height);
    GamePage CharactersPage;
    CharactersPage.Load(GMKL::LIST_PAGE, this->Width, this->Height);
    GamePage SettingPage;
    SettingPage.Load(GMKL::COMPOSITION_PAGE, this->Width, this->Height);
    GamePage BattlePage;
    BattlePage.Load(GMKL::BATTLE_PAGE, this->Width, this->Height);

    this->Pages.push_back(MainMenu);
    this->Pages.push_back(CharactersPage);
    this->Pages.push_back(StagePage);
    this->Pages.push_back(SettingPage);
    this->Pages.push_back(BattlePage);
    //���� ������
    this->page = 0;
}

void Game::Update(float dt)
{
    //���⼭ std::cout std::endl�� ���°� ���� �׷��� �ʳ�.
}

void Game::ProcessInput(float dt)
{   
    if (this->State == GAME_ACTIVE)
    {
        //������ ���� ����
        if (Pages[this->page].PID == GMKL::MAIN_PAGE) {
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "RID00001") {
                    this->page = GMKL::LIST_PAGE;
                    Pages[this->page].Draw(*Renderer);
                }
                if (ID == "RID00002") {
                    this->page = GMKL::STAGE_PAGE;
                    Pages[this->page].Draw(*Renderer);
                }
                if (ID == "RID00005") {
                    this->page = GMKL::COMPOSITION_PAGE;
                    Pages[this->page].Draw(*Renderer);
                }
            }
        }
        if(Pages[this->page].PID == GMKL::LIST_PAGE){
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "backwardButton") {
                    GMKL::Event.pop();
                    this->page = GMKL::MAIN_PAGE;
                    Pages[this->page].Draw(*Renderer);
                 }
                if (ID.find("UCID") != std::string::npos) {
                    if (GMKL::Event.front() == "compositionEvent") {
                        setComposition(procIndex, GMKL::toUCID(ID));
                        GMKL::Event.pop();
                        this->page = GMKL::COMPOSITION_PAGE;
                        Pages[this->page].Load(GMKL::COMPOSITION_PAGE, this->Width, this->Height);
                    }
                }
            }
        }
        if (Pages[this->page].PID == GMKL::COMPOSITION_PAGE) {
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "backwardButton") {
                    this->page = GMKL::MAIN_PAGE;
                    Pages[this->page].Draw(*Renderer);
                }
                else if (ID.find("setButton") != std::string::npos) {
                    procComposition(GMKL::toID(ID, "setButton"));
                    GMKL::Event.push("compositionEvent");
                    this->page = GMKL::LIST_PAGE;
                    Pages[this->page].Draw(*Renderer);
                }
            }
        }
        if (Pages[this->page].PID == GMKL::STAGE_PAGE) {
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "stage1-1") {
                    this->page = GMKL::BATTLE_PAGE;
                    Pages[this->page].Load(GMKL::BATTLE_PAGE, this->Width, this->Height);
                }
                if (ID == "backwardButton") {
                    this->page = GMKL::MAIN_PAGE;
                    Pages[this->page].Draw(*Renderer);
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

std::string Game::MouseCollision(std::vector<GameObject> obj) {
    for (int i = 0; i < obj.size(); i++) {
        if (obj[i].ID == "none") {
            continue;
        }
        if (obj[i].Position.x < Mouse.x && Mouse.x < obj[i].Position.x + obj[i].Size.x) {
            if (obj[i].Position.y < Mouse.y && Mouse.y < obj[i].Position.y + obj[i].Size.y) {
                std::cout << obj[i].ID << std::endl;
                MouseEvent[1] = GLFW_RELEASE;
                return obj[i].ID;
            }
        }
    }
    return "undefined";
}
