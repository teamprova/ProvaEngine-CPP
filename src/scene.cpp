#include <SDL.h>
#include <math.h>
#include <map>
#include "scene.hpp"
#include "entity.hpp"
#include "screen.hpp"
#include "collider2d.hpp"
#include "vector2.hpp"
#include "vector4.hpp"
#include "rect.hpp"

using namespace Prova;

void Scene::EnableDebug()
{
  _debug = true;
}

void Scene::DisableDebug()
{
  _debug = false;
}

bool Scene::IsDebugEnabled()
{
  return _debug;
}

void Scene::AddEntity(Entity& entity)
{
  entities.push_back(&entity);
  entity.scene = this;

  _collider2DMap.AddColliders(entity);

  if(!entity._setup)
  {
    entity.Setup();
    entity._setup = true;
  }

  entity.Start();
}

void Scene::RemoveEntity(Entity& entity)
{
  entities.remove(&entity);
  
  if(entity.scene == this)
    entity.scene = nullptr;
  
  _collider2DMap.RemoveColliders(entity);
}

// finds the closest entity to this entity
Entity& Scene::FindClosestEntity(Entity& myEntity)
{
  float closestDistance = -1;
  Entity* closestEntity = nullptr;

  for(Entity* entity : entities)
  {
    // dont count yourself
    if(entity == &myEntity)
      continue;

    float distance = entity->position.DistanceFrom(myEntity.position);

    if(distance < closestDistance || closestDistance == -1)
    {
      closestDistance = distance;
      closestEntity = entity;
    }
  }

  return *closestEntity;
}

Entity& Scene::FindClosestEntity(Entity& myEntity, int tag)
{
  float closestDistance = -1;
  Entity* closestEntity = nullptr;

  for(Entity* entity : entities)
  {
    // match tags and make sure we aren't matching with self
    if(entity == &myEntity || !entity->HasTag(tag))
      continue;

    float distance = entity->position.DistanceFrom(myEntity.position);

    if(distance < closestDistance || closestDistance == -1)
    {
      closestDistance = distance;
      closestEntity = entity;
    }
  }

  return *closestEntity;
}

void Scene::Setup() { }
void Scene::Start() { }

void Scene::Update()
{
  EntityUpdate();
  Collider2DUpdate();
}

void Scene::Collider2DUpdate()
{
  _collider2DMap.MapColliders();
  _collider2DMap.FindCollisions();
  _collider2DMap.ResolveCollisions();
}

void Scene::EntityUpdate()
{
  for(Entity* entity : entities)
  {
    entity->Update();
    entity->position += entity->velocity;
  }
}

void Scene::Draw(Screen& screen)
{
  std::multimap<float, Entity*> sorted;

  for(Entity* entity : entities)
  {
    float distance;
    
    if(camera.sortingMethod == SortingMethod::Distance)
      distance = entity->position.DistanceFrom(camera.position);
    else
      distance = camera.position.z - entity->position.z;
    
    sorted.emplace(distance, entity);
  }

  for(auto it = sorted.rbegin(); it != sorted.rend(); ++it)
  {
    Entity& entity = *it->second;

    entity.Draw(screen);
  }
  
  if(IsDebugEnabled())
    _collider2DMap.Draw(*game->screen);
}