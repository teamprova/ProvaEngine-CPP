#include <SDL2/SDL.h>
#include "scene.hpp"
#include "entity.hpp"
#include "canvas.hpp"

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

void Scene::Draw(Canvas* canvas)
{
  canvas->Clear(0, 0, 0);

  for(Entity* entity : _entities)
    entity->Draw(canvas);

  canvas->SwapBuffer();
}