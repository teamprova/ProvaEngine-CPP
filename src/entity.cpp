#include "entity.hpp"
#include "game.hpp"
#include "scene.hpp"

using namespace Prova;

void Entity::AddTag(int tag)
{
  _tags.emplace(tag);
}

void Entity::RemoveTag(int tag)
{
  _tags.erase(tag);
}

bool Entity::HasTag(int tag)
{
  return _tags.find(tag) != _tags.end();
}

void Entity::AddCollider(Collider2D& collider)
{
  if(scene != nullptr)
    scene->_collider2DMap.AddCollider(collider);
  
  _2dColliders.push_back(&collider);
}

void Entity::RemoveCollider(Collider2D& collider)
{
  if(scene != nullptr)
    scene->_collider2DMap.RemoveCollider(collider);
  
  _2dColliders.remove(&collider);
}

void Entity::Setup(){}
void Entity::Update(){}
void Entity::Draw(Screen& screen){}

void Entity::OnCollision2D(Collider2D& collider, Collider2D& other){}

Entity::~Entity()
{
  for(Collider2D* collider : _2dColliders)
    delete collider;
}