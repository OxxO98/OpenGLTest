#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GamePage.h"
#include "GMKL.h"
#include "RenderStorage.h"

#include <iostream>
#include <string>

//C파트
#include "cTest.h"

SpriteRenderer* Renderer;

std::vector<MonsterObject> Monsters[3];
std::vector<EffectObject> Effect;
std::vector<CharacterObject> Characters;

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
    GMKL::loadBackground();
    GMKL::loadResource();
    GMKL::loadCharacter();

    //유저 정보 로드 페이지 로드 전에 할것!
    initUserCharacters();
    initComposition();
    initMonster();

    //페이지 로드
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
    //현재 페이지
    this->page = 0;
}

void Game::Update(float dt)
{
    //여기서 std::cout std::endl을 쓰는건 조금 그렇지 않나.
    if (Pages[this->page].PID == GMKL::BATTLE_PAGE) {
        //Monster Act
        for (int i = 0; i < 3; i++) {
            for (MonsterObject &elem : Monsters[i]) {
                elem.Position.x += aiMonster(elem.data->MID, dt);
            }
        }
        //Character Act
        for (CharacterObject &elem : Characters) {
            elem.data->coolTime += dt;
            if (!Monsters[appointTarget(elem.data->UCID)].empty()) {
                elem.target = &Monsters[appointTarget(elem.data->UCID)].front();
            }
            else {
                elem.target = NULL;
            }
            if (elem.data->coolTime >= 0.5f && elem.target != NULL) {
                Effect.push_back(EffectObject(&elem, appointTarget(elem.data->UCID), GameObject(elem.Position, glm::vec2(18, 19), ResourceManager::GetTexture("attkEffect"), GMKL::toUCIDString(elem.data->UCID))));
                elem.data->coolTime = 0.0f;
            }
        }
        //Effect Act
        for (std::vector<EffectObject>::iterator it = Effect.begin(); it != Effect.end(); it++) {
            it->Position.x += it->UCID->data->attkVelocity * dt;
            if (!Monsters[it->Target].empty()) {
                if (GMKL::isCollision(&(*it), dynamic_cast<GameObject*>(&Monsters[it->Target].front()))) {
                    stageMonster[it->Target].hp -= it->UCID->data->attkPower;
                    std::cout << "충돌" << stageMonster[it->Target].hp << std::endl;
                    it->Destroyed = true;
                    Effect.erase(it);
                    break;
                }
            }
        }
        //Monster Destroyed
        for (int i = 0; i < 3; i++) {
            for (std::vector<MonsterObject>::iterator it = Monsters[i].begin(); it != Monsters[i].end(); it++) {
                if (it->data->hp <= 0 && !it->data->Destroyed) {
                    std::cout << it->data->UMID << "DIE" << std::endl;
                    std::cout << it->ID << "DELETED" << std::endl;
                    it->data->Destroyed = true; //stageMonster에서 Destroyed 처리하기
                    it->Destroyed = true; //gameObjs에서 지우기
                    Monsters[i].erase(it); //Monsters에서 지우기
                    break;
                }
            }
        }
    }
    //std::cout << 1 / dt << std::endl; //FPS
    if (1 / dt < 30) {
        std::cout << "FPS::WARNING" << std::endl;
    }
}

void Game::ProcessInput(float dt)
{   
    if (this->State == GAME_ACTIVE)
    {
        //페이지 별로 수정
        if (Pages[this->page].PID == GMKL::MAIN_PAGE) {
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "RID00000") {
                    this->page = GMKL::STAGE_PAGE;
                }
                if (ID == "RID00001") {
                    this->page = GMKL::COMPOSITION_PAGE;
                }
                if (ID == "RID00002") {
                    this->page = GMKL::LIST_PAGE;
                }
            }
        }
        if(Pages[this->page].PID == GMKL::LIST_PAGE){
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "backwardButton") {
                    if (!GMKL::Event.empty()) {
                        GMKL::Event.pop();
                    }
                    this->page = GMKL::MAIN_PAGE;
                 }
                if (ID.find("UCID") != std::string::npos) {
                    if (!GMKL::Event.empty() && GMKL::Event.front() == "compositionEvent") {
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
                }
                else if (ID.find("setButton") != std::string::npos) {
                    procComposition(GMKL::toID(ID, "setButton"));
                    GMKL::Event.push("compositionEvent");
                    this->page = GMKL::LIST_PAGE;
                }
            }
        }
        if (Pages[this->page].PID == GMKL::STAGE_PAGE) {
            if (MouseEvent[0] == GLFW_MOUSE_BUTTON_LEFT && MouseEvent[1] == GLFW_PRESS) {
                std::string ID = MouseCollision(Pages[this->page].GameObjs);
                if (ID == "stage1-1") {
                    this->page = GMKL::BATTLE_PAGE;
                    //Pages[this->page].Update(GMKL::BATTLE_PAGE); //갑자기 쓸모 없어짐?
                    RenderStorage::GetDataRenderStorage(Monsters, stageMonster, RenderStorage::MONSTER, GMKL::BATTLE_PAGE);
                    RenderStorage::GetDataRenderStorage(&Characters, NULL, RenderStorage::CHARACTER, GMKL::BATTLE_PAGE);
                }
                if (ID == "backwardButton") {
                    this->page = GMKL::MAIN_PAGE;
                }
            }
        }
    }
}

void Game::Render()
{
    //Page Render
    this->Pages[this->page].Draw(*Renderer);
    if (this->page == GMKL::BATTLE_PAGE) {
        for (EffectObject &elem : Effect) {
            if (!elem.Destroyed) {
                elem.Draw(*Renderer);
            }
        }
        for (int i = 0; i < 3; i++) {
            for (MonsterObject &elem : Monsters[i]) {
                if (!elem.Destroyed) {
                    elem.Draw(*Renderer);
                }
            }
        }
        for (CharacterObject &elem : Characters) {
            if (!elem.Destroyed) {
                elem.Draw(*Renderer);
            }
        }
    }
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
