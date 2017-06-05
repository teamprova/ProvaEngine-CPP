#pragma once
#include <SDL2/SDL.h>
#include <list>
#include "vector2.hpp"
#include "camera.hpp"
#include "collider2d.hpp"

class Game;
class Screen;
class Entity;
class Camera;
class Collider2D;
class Vector2;


class Scene
{
  friend class Entity;

  public:
    enum SortingMethod { Z, Distance };

    Game* game;
    Camera camera;
    std::list<Entity*> entities;
    SortingMethod sortingMethod = SortingMethod::Distance;
    void PreUpdate();
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    virtual void Update();
    void Collider2DUpdate();
    void EntityUpdate();
    virtual void Draw(Screen* screen);
    ~Scene();
  private:
    void UpdateBucketSize2D();
    void UpdateBucketSize2D(Collider2D*);
    const Uint8* _keystate;
    std::list<Collider2D*> _2dColliders;
    Vector2 _bucketSize2d;
};