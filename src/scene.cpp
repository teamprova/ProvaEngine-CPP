#include <SDL2/SDL.h>
#include <map>
#include "scene.hpp"
#include "entity.hpp"
#include "screen.hpp"

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
  _entities.push_back(entity);
  entity->scene = this;
}

void Scene::RemoveEntity(Entity* entity)
{
  _entities.remove(entity);
  
  if(entity->scene == this)
    entity->scene = NULL;
}

void Scene::EntityUpdate()
{
  for(Entity* entity : _entities)
  {
    entity->Update();
    entity->position += entity->velocity;
  }
}

void Scene::Update()
{
  EntityUpdate();
}

void Scene::Draw(Screen* screen)
{
  std::multimap<float, Entity*> sorted;

  for(Entity* entity : _entities)
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