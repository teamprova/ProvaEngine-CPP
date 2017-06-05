#include <SDL2/SDL.h>
#include <math.h>
#include <map>
#include <set>
#include <unordered_map>
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
  
  for(Collider2D* collider : entity->_2dColliders)
  {
    UpdateBucketSize2D(collider);
    _2dColliders.push_back(collider);
  }
}

void Scene::RemoveEntity(Entity* entity)
{
  entities.remove(entity);
  
  if(entity->scene == this)
    entity->scene = NULL;
  
  for(Collider2D* collider : entity->_2dColliders)
    _2dColliders.remove(collider);
  
  UpdateBucketSize2D();
}

void Scene::Update()
{
  EntityUpdate();
  Collider2DUpdate();
}

void Scene::Collider2DUpdate()
{
  std::unordered_map<Vector4, std::set<Collider2D*>> spacialMap;

  for(Collider2D* collider : _2dColliders)
  {
    // we map the corners to a space,
    // edges don't matter as the buckets are
    // as big as the largest collider
    Rect bounds = collider->GetBounds();

    // todo:
    Vector2 key;
    key.x = key.x / _bucketSize2d.x;
    key.y = key.y / _bucketSize2d.y;

    // it might make sense to floor the
    // key vector, but our hash function
    // converts our vectors dimensions to
    // integers anyway
    spacialMap[key].emplace(collider);
  }

  // loop through spacial map
  for(auto spacialMapIterator : spacialMap)
    // test for collision within each mapped space
    for(Collider2D* colliderA : spacialMapIterator.second)
      for(Collider2D* colliderB : spacialMapIterator.second)
        if(colliderA != colliderB && colliderA->Intersects(colliderB))
          colliderA->entity->OnCollision2D(colliderA, colliderB);
}

void Scene::UpdateBucketSize2D()
{
  for(Collider2D* collider : _2dColliders)
    UpdateBucketSize2D(collider);
}

void Scene::UpdateBucketSize2D(Collider2D* collider)
{
  Vector2 size = collider->GetSize();

  if(size.x > _bucketSize2d.x)
    _bucketSize2d.x = size.x;
  if(size.x > _bucketSize2d.y)
    _bucketSize2d.y = size.y;
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