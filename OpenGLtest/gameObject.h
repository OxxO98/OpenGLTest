#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "cTest.h"
#include "RenderObj.h"
#include "ResourceManager.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    std::string ID;
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, std::string id, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    GameObject(RenderObj object);
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
};

class MonsterObject : public GameObject {
public :
    Monster* data;

    MonsterObject();
    MonsterObject(Monster* data, GameObject Object);
};

class CharacterObject : public GameObject {
public :
    UserCharacter* data;
    MonsterObject* target;

    CharacterObject();
    CharacterObject(UserCharacter* data, GameObject object);
};

class EffectObject : public GameObject {
public:
    CharacterObject* UCID;
    int Target;

    EffectObject();
    EffectObject(CharacterObject* UCID, int Target, GameObject Object);
};

#endif