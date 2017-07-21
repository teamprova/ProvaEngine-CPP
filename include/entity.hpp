#pragma once
#include <list>
#include <set>
#include "collider2d.hpp"
#include "vector3.hpp"

namespace Prova
{
  class Collider2D;
  class Scene;
  class Screen;
  class SpacialMap2D;
  class Vector3;

  class Entity
  {
    friend class Scene;
    friend class SpacialMap2D;

    public:
      Vector3 position;
      Vector3 velocity;
      Scene* scene = nullptr;
      void AddTag(int tag);
      void RemoveTag(int tag);
      bool HasTag(int tag);
      void AddCollider(Collider2D& collider);
      void RemoveCollider(Collider2D& collider);
      virtual void Setup();
      virtual void Update();
      virtual void Draw(Screen& screen);
      virtual void OnCollision2D(Collider2D& collider, Collider2D& hitCollider);
      ~Entity();
    private:
      bool _setup = false;
      std::set<int> _tags;
      std::list<Collider2D*> _2dColliders;
  };
}