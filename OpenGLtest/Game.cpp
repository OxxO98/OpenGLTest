/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GamePage.h"

#include <iostream>

SpriteRenderer* Renderer;

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
    
    GamePage MainMenu;
    MainMenu.Load(this->Width, this->Height);

    this->Pages.push_back(MainMenu);
    this->page = 0;
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    //multiple render
    Texture2D sbackground = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(sbackground, glm::vec2(200.0f, 400.0f), glm::vec2(200, 200), 0.0f);
    //Texture2D myTexture = ResourceManager::GetTexture("block");
    //Renderer->DrawSprite(myTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    //this->Pages[this->page].Draw(*Renderer);
}