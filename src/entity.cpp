#include "entity.hpp"
#include "scene.hpp"

bool Entity::IsKeyDown(int key)
{
  return scene->IsKeyDown(key);
}

bool Entity::IsKeyUp(int key)
{
  return scene->IsKeyUp(key);
}

void Entity::Update(){}
void Entity::Draw(Screen* screen){}