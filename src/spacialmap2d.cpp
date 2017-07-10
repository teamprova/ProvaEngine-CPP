#include "spacialmap2d.hpp"
#include "rect.hpp"

using namespace Prova;

void SpacialMap2D::MapColliders()
{
  for(Collider2D* collider : _colliders)
  {
    // we map the corners to a space,
    // edges don't matter as the buckets are
    // as big as the largest collider
    Rect bounds = collider->GetBounds();
    collider->collisions.clear();

    MapColliderCorner(bounds.GetTopLeft(), collider);
    MapColliderCorner(bounds.GetTopRight(), collider);
    MapColliderCorner(bounds.GetBottomLeft(), collider);
    MapColliderCorner(bounds.GetBottomRight(), collider);
  }
}

void SpacialMap2D::MapColliderCorner(Vector2 corner, Collider2D* collider)
{
  long long int x = corner.y / _bucketSize.x;
  long long int y = corner.y / _bucketSize.y;

  std::set<Collider2D*>& bucket = _map[(x << 32) | y];
  bucket.emplace(collider);
}

void SpacialMap2D::FindCollisions()
{
  // loop through buckets in the spacial map
  for(auto spacialMapIterator : _map)
  {
    auto& bucket = spacialMapIterator.second;

    // test for collision with every collider within the bucket
    for(auto colliderItA = bucket.begin(); colliderItA != bucket.end(); ++colliderItA)
    {
      Collider2D& colliderA = **colliderItA;

      // test with colliders that haven't already been tested with every collider
      // by starting after the current collider being tested
      for(auto colliderItB = colliderItA; ++colliderItB != bucket.end();)
      {
        Collider2D& colliderB = **colliderItB;
        
        // collision occured and hadn't already been noticed
        if(colliderA.Intersects(colliderB) && colliderA.collisions.count(&colliderB) == 0)
        {
          colliderA.collisionOccurred = true;
          colliderB.collisionOccurred = true;
          
          colliderA.entity.OnCollision2D(colliderA, colliderB);
          colliderB.entity.OnCollision2D(colliderB, colliderA);

          colliderA.collisions.emplace(&colliderB);
          colliderB.collisions.emplace(&colliderA);
        }
      }
    }
    
    bucket.clear();
  }

  _map.clear();
}

void SpacialMap2D::Draw(Screen& screen)
{
  for(Collider2D* collider : _colliders)
  {
    collider->Draw(screen);
    collider->collisionOccurred = false;
  }
}

void SpacialMap2D::AddCollider(Collider2D& collider)
{
  _colliders.push_back(&collider);
  
  UpdateBucketSize(collider);
}

void SpacialMap2D::AddColliders(Entity& entity)
{
  for(Collider2D* collider : entity._2dColliders)
  {
    _colliders.push_back(collider);

    UpdateBucketSize(*collider);
  }
}

void SpacialMap2D::RemoveCollider(Collider2D& collider)
{
  _colliders.remove(&collider);

  UpdateBucketSize();
}

void SpacialMap2D::RemoveColliders(Entity& entity)
{
  for(Collider2D* collider : entity._2dColliders)
    _colliders.remove(collider);

  UpdateBucketSize();
}

void SpacialMap2D::UpdateBucketSize()
{
  for(Collider2D* collider : _colliders)
    UpdateBucketSize(*collider);
}

void SpacialMap2D::UpdateBucketSize(Collider2D& collider)
{
  Vector2 size = collider.GetSize();

  if(size.x + 5 > _bucketSize.x)
    _bucketSize.x = size.x + 5;
  if(size.y + 5 > _bucketSize.y)
    _bucketSize.y = size.y + 5;
}