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
      Collider2D(Entity* entity);
      Vector2 offset;
      Entity& entity;
      std::set<Collider2D*> collisions;
      bool collisionOccurred = false;
      void AddTag(int);
      void RemoveTag(int);
      bool HasTag(int);
      Vector2 GetPosition();
      Rect GetBounds();
      bool Intersects(Collider2D& collider);
      virtual Vector2 GetSize() = 0;
      virtual void Draw(Screen& screen) = 0;
    protected:
      enum class Shape { Point, Circle, Rectangle, Pixel };

      Shape shape;
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