#include <SDL2/SDL.h>
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

void Scene::AddEntity(Entity& entity)
{
  entities.push_back(&entity);
  entity.scene = this;
  
  _collider2DMap.AddColliders(entity);
}

void Scene::RemoveEntity(Entity& entity)
{
  entities.remove(&entity);
  
  if(entity.scene == this)
    entity.scene = nullptr;
  
  _collider2DMap.RemoveColliders(entity);
}

void Scene::Setup() { }

void Scene::Update()
{
  EntityUpdate();
  Collider2DUpdate();
}

void Scene::Collider2DUpdate()
{
  _collider2DMap.MapColliders();
  _collider2DMap.FindCollisions();
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
  
  if(Debug)
    _collider2DMap.Draw(*game->screen);
}