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

void Entity::AddCollider(Collider2D* collider)
{
  if(scene != NULL)
    scene->Collider2DMap.AddCollider(collider);
  
  _2dColliders.push_back(collider);
}

void Entity::RemoveCollider(Collider2D* collider)
{
  if(scene != NULL)
    scene->Collider2DMap.RemoveCollider(collider);
  
  _2dColliders.remove(collider);
}

void Entity::Update(){}
void Entity::Draw(Screen* screen){}

void Entity::OnCollision2D(Collider2D* collider, Collider2D* other){}

Entity::~Entity()
{
  for(Collider2D* collider : _2dColliders)
    delete collider;
}