#include "GamePage.h"
#include "RenderStorage.h"

#include <fstream>
#include <sstream>

void GamePage::Load(std::string page, unsigned int pageWidth, unsigned int pageHeight) {
    this->GameObjs.clear();
     
    std::vector<RenderObj> pageData;

    //포인터로 렌더링 데이터만 가져오기
    RenderStorage::LoadRenderStorage(&pageData, page);
    //만약 여기서 게임 데이터를 가져오게 된다면, 적절히 게임 오브젝트에 합성해야함
    //물론 지금 게임 오브젝트에는 렌더링데이터밖에 없고, 만약 오브젝트에 멤버를 추가해야한다면
    //void포인터로 게임 구조체를 할당한다.


    if (true) {
        this->init(pageData, pageWidth, pageHeight);
    }
}


void GamePage::Draw(SpriteRenderer& renderer)
{
    for (GameObject& page : this->GameObjs)
        if (!page.Destroyed)
            page.Draw(renderer);
}

bool GamePage::IsCompleted()
{
    for (GameObject& page : this->GameObjs)
        if (!page.IsSolid && !page.Destroyed)
            return false;
    return true;
}

void GamePage::init(std::vector<RenderObj> pageData, unsigned int pageWidth, unsigned int pageHeight)
{
    for(RenderObj elem : pageData){
        this->GameObjs.push_back(GameObject(
            glm::vec2(elem.Position),
            glm::vec2(elem.Size),
            ResourceManager::GetTexture(elem.TextureID),
            elem.ObjectID
        ));
    }
}