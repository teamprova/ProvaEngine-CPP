#pragma once
#include "vector2.hpp"
#include "entity.hpp"

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
      bool collisionOccurred = false;
      bool Intersects(Collider2D&);
      Vector2 GetPosition();
      virtual Vector2 GetSize() = 0;
      Rect GetBounds();
      virtual void Draw(Screen&) = 0;
    protected:
      ColliderShape shape;
    private:
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