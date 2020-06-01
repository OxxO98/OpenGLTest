#include "GamePage.h"

#include <fstream>
#include <sstream>

void GamePage::Load(unsigned int pageWidth, unsigned int pageHeight) {
    //old data clear
    this->Pages.clear();
    //load from file ? skip
    std::vector<std::vector<unsigned int>> pageData;
    
    for (int i = 0; i < 5; i++) {
        std::vector<unsigned int>row;
        for (int i = 0; i < 5; i++) {
            row.push_back(1);
        }
        pageData.push_back(row);
    }
    if (pageData.size() > 0) {
        this->init(pageData, pageWidth, pageHeight);
    }

}


void GamePage::Draw(SpriteRenderer& renderer)
{
    for (GameObject& page : this->Pages)
        if (!page.Destroyed)
            page.Draw(renderer);
}

bool GamePage::IsCompleted()
{
    for (GameObject& page : this->Pages)
        if (!page.IsSolid && !page.Destroyed)
            return false;
    return true;
}

void GamePage::init(std::vector<std::vector<unsigned int>> pageData, unsigned int pageWidth, unsigned int pageHeight)
{
    // calculate dimensions
    unsigned int height = pageData.size();
    unsigned int width = pageData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = pageWidth / static_cast<float>(width), unit_height = pageHeight / height;
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (pageData[y][x] == 1) // solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = true;
                this->Pages.push_back(obj);
            }
            else if (pageData[y][x] > 1)	// non-solid; now determine its color based on level data
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (pageData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (pageData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (pageData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (pageData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Pages.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}