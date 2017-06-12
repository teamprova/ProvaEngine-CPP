#pragma once
#include <list>
#include "vector3.hpp"
#include "collider2d.hpp"

class Vector3;
class Scene;
class Screen;
class Collider2D;
class SpacialMap2D;

class Entity
{
  friend class Scene;
  friend class SpacialMap2D;

  public:
    Vector3 position;
    Vector3 velocity;
    Scene* scene;
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    void AddCollider(Collider2D&);
    void RemoveCollider(Collider2D&);
    virtual void Update();
    virtual void Draw(Screen&);
    virtual void OnCollision2D(Collider2D&, Collider2D&);
    ~Entity();
  private:
    std::list<Collider2D*> _2dColliders;
};