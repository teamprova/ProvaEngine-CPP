#pragma once
#include <set>
#include "entity.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Screen;
  class Entity;
  class Vector2;
  class Rect;
  class RectCollider;
  class CircleCollider;
  class PointCollider;
  //class PixelCollider;

  class Collider2D
  {
    public:
      enum ColliderShape { Point, Circle, Rectangle, Pixel };
      
      Collider2D(Entity*);
      Vector2 offset;
      Entity& entity;
      std::set<Collider2D*> collisions;
      bool collisionOccurred = false;
      void AddTag(int);
      void RemoveTag(int);
      bool HasTag(int);
      Vector2 GetPosition();
      Rect GetBounds();
      bool Intersects(Collider2D&);
      virtual Vector2 GetSize() = 0;
      virtual void Draw(Screen&) = 0;
    protected:
      ColliderShape shape;
    private:
      std::set<int> _tags;
      static bool PointIntersectsPoint(PointCollider&, PointCollider&);
      static bool PointIntersectsCircle(PointCollider&, CircleCollider&);
      static bool PointIntersectsRect(PointCollider&, RectCollider&);
      //static bool PointIntersectsPixel(PointCollider&, PointCollider&);
      static bool CircleIntersectsCircle(CircleCollider&, CircleCollider&);
      static bool CircleIntersectsRect(CircleCollider&, RectCollider&);
      //static bool CircleIntersectsPixel(CircleCollider&, PointCollider&);
      static bool RectIntersectsRect(RectCollider&, RectCollider&);
      //static bool RectIntersectsPixel(RectCollider&, PointCollider&);
  };
}