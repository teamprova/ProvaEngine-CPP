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

void Scene::PreUpdate()
{
  _keystate = SDL_GetKeyboardState(NULL);
}

bool Scene::IsKeyDown(int key)
{
  return _keystate[key];
}

bool Scene::IsKeyUp(int key)
{
  return !IsKeyDown(key);
}

void Scene::AddEntity(Entity* entity)
{
  entities.push_back(entity);
  entity->scene = this;
  
  Collider2DMap.AddColliders(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
  entities.remove(entity);
  
  if(entity->scene == this)
    entity->scene = NULL;
  
  Collider2DMap.RemoveColliders(entity);
}

void Scene::Update()
{
  EntityUpdate();
  Collider2DUpdate();
}

void Scene::Collider2DUpdate()
{
  Collider2DMap.MapColliders();
  Collider2DMap.FindCollisions();
}

void Scene::EntityUpdate()
{
  for(Entity* entity : entities)
  {
    entity->Update();
    entity->position += entity->velocity;
  }
}

void Scene::Draw(Screen* screen)
{
  std::multimap<float, Entity*> sorted;

  for(Entity* entity : entities)
  {
    float distance;
    
    if(sortingMethod == SortingMethod::Distance)
      distance = entity->position.DistanceFrom(camera.position);
    else
      distance = camera.position.z - entity->position.z;
    
    sorted.emplace(distance, entity);
  }
 
  screen->Clear(0, 0, 0);

  for(auto it = sorted.rbegin(); it != sorted.rend(); ++it) 
    it->second->Draw(screen);

  screen->SwapBuffer();
}

Scene::~Scene()
{
  for(Entity* entity : entities)
    if(entity->scene == this)
      delete entity;
}