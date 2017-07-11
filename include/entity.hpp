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
      void AddTag(int);
      void RemoveTag(int);
      bool HasTag(int);
      void AddCollider(Collider2D&);
      void RemoveCollider(Collider2D&);
      virtual void Update();
      virtual void Draw(Screen&);
      virtual void OnCollision2D(Collider2D&, Collider2D&);
      ~Entity();
    private:
      std::set<int> _tags;
      std::list<Collider2D*> _2dColliders;
  };
}