#pragma once
#include <utility>
#include <list>
#include <set>
#include <vector>
#include "vector4.hpp"
#include "vector2.hpp"
#include "collider2d.hpp"

namespace Prova
{
  class Entity;

  class SpacialMap2D
  {
    friend class Entity;

    public:
      void MapColliders();
      void FindCollisions();
      void ResolveCollisions();
      void AddCollider(Collider2D& collider);
      void AddColliders(Entity& entity);
      void RemoveCollider(Collider2D& collider);
      void RemoveColliders(Entity& entity);
      void Draw(Screen& screen);
    private:
      void MapColliderCorner(Vector2 corner, Collider2D* collider);
      void UpdateBucketSize();
      void UpdateBucketSize(Collider2D& collider);
      Vector2 _bucketSize;
      std::list<Collider2D*> _colliders;
      std::unordered_map<long long int, std::set<Collider2D*>> _map;
      std::vector<std::pair<Collider2D*, Collider2D*>> _collisions;
  };
}