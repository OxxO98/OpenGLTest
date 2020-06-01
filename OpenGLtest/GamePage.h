#ifndef GAMEPAGE_H
#define GAMEPAGE_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "gameObject.h"
#include "ResourceManager.h"
#include "ResourceManager.h"

class GamePage
{
public:
	//page state equals level state?
	std::vector<GameObject> Pages;
	//constructor
	GamePage() { }
	//load page from file? not in progressing
	void Load(unsigned int pageWidth, unsigned int pageHeight);
	//render Page
	void Draw(SpriteRenderer& render);
	//check compiled
	bool IsCompleted();
private:
	//intialize 
	void init(std::vector<std::vector<unsigned int>> pageData, unsigned int pageWidth, unsigned int pageHeight);
};


#endif