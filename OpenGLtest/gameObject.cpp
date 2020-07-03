#include "gameObject.h"


GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false), ID("none") { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, std::string id, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), ID(id), IsSolid(false), Destroyed(false){ }

GameObject::GameObject(RenderObj object)
    : Position(object.Position), Size(object.Size), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(ResourceManager::GetTexture(object.TextureID)), ID(object.ObjectID), IsSolid(false), Destroyed(false) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

EffectObject::EffectObject()
    : GameObject() { }

EffectObject::EffectObject(CharacterObject* UCID, int Target, GameObject Object)
    : UCID(UCID), Target(Target), GameObject(Object.Position, Object.Size, Object.Sprite, Object.ID, Object.Color, Object.Velocity) { }

MonsterObject::MonsterObject()
    : data(NULL), GameObject() { }

MonsterObject::MonsterObject(Monster* data, GameObject Object)
    : data(data), GameObject(Object.Position, Object.Size, Object.Sprite, Object.ID, Object.Color, Object.Velocity) { }

CharacterObject::CharacterObject()
    : data(NULL), target(NULL), GameObject() { }

CharacterObject::CharacterObject(UserCharacter* data, GameObject Object)
    : data(data), target(NULL), GameObject(Object.Position, Object.Size, Object.Sprite, Object.ID, Object.Color, Object.Velocity) { }
