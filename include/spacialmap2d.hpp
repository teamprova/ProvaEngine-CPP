#include <list>
#include <set>
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
      void AddCollider(Collider2D&);
      void AddColliders(Entity&);
      void RemoveCollider(Collider2D&);
      void RemoveColliders(Entity&);
      void Draw(Screen&);
    private:
      void MapColliderCorner(Vector2, Collider2D*);
      void UpdateBucketSize();
      void UpdateBucketSize(Collider2D&);
      void ResolveCollisions(std::list<Collider2D>*);
      Vector2 _bucketSize;
      std::list<Collider2D*> _colliders;
      std::unordered_map<long long int, std::set<Collider2D*>> _map;
  };
}