#include "GamePage.h"
#include "RenderStorage.h"

#include <fstream>
#include <sstream>

void GamePage::Load(std::string page, unsigned int pageWidth, unsigned int pageHeight) {
    this->GameObjs.clear();
    //load from file ? skip
    std::vector<RenderObj> pageData;

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