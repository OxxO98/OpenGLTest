#include "GamePage.h"
#include "RenderStorage.h"

#include <fstream>
#include <sstream>

//C파트
//#include "cTest.h"

void GamePage::Load(int page, unsigned int pageWidth, unsigned int pageHeight) {
    this->GameObjs.clear();
    PID = page;
    std::vector<RenderObj> pageData;

    //포인터로 렌더링 데이터만 가져오기
    RenderStorage::LoadRenderStorage(&pageData, page);

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