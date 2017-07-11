#include "collider2d.hpp"
#include "pointcollider.hpp"
#include "circlecollider.hpp"
#include "rectcollider.hpp"
//#include "pixelcollider.hpp"
#include "rect.hpp"
#include "vector2.hpp"

using namespace Prova;

Collider2D::Collider2D(Entity* entity)
  : entity(*entity) {}

Vector2 Collider2D::GetPosition()
{
  return Vector2(
    offset.x + entity.position.x,
    offset.y + entity.position.y
  );
}

Rect Collider2D::GetBounds()
{
  Vector2 size = GetSize();
  Vector2 position = GetPosition();

  return Rect(
    position.x - size.x / 2,
    position.y - size.y / 2,
    size.x,
    size.y
  );
}

void Collider2D::AddTag(int tag)
{
  _tags.emplace(tag);
}

void Collider2D::RemoveTag(int tag)
{
  _tags.erase(tag);
}

bool Collider2D::HasTag(int tag)
{
  return _tags.find(tag) != _tags.end();
}

bool Collider2D::Intersects(Collider2D& collider)
{
  Collider2D& colliderA = *this;
  Collider2D& colliderB = collider;

  if(colliderA.shape == Point && colliderB.shape == Point)
    return PointIntersectsPoint((PointCollider&) colliderA, (PointCollider&) colliderB);
  else if(colliderA.shape == Point && colliderB.shape == Circle)
    return PointIntersectsCircle((PointCollider&) colliderA, (CircleCollider&) colliderB);
  else if(colliderA.shape == Point && colliderB.shape == Rectangle)
    return PointIntersectsRect((PointCollider&) colliderA, (RectCollider&) colliderB);

  else if(colliderA.shape == Circle && colliderB.shape == Point)
    return PointIntersectsCircle((PointCollider&) colliderB, (CircleCollider&) colliderA);
  else if(colliderA.shape == Circle && colliderB.shape == Circle)
    return CircleIntersectsCircle((CircleCollider&) colliderA, (CircleCollider&) colliderB);
  
  else if(colliderA.shape == Rectangle && colliderB.shape == Rectangle)
    return RectIntersectsRect((RectCollider&) colliderA, (RectCollider&) colliderB);
  else if(colliderA.shape == Rectangle && colliderB.shape == Point)
    return PointIntersectsRect((PointCollider&) colliderB, (RectCollider&) colliderA);
  
  return false;
}

bool Collider2D::PointIntersectsPoint(PointCollider& pointA, PointCollider& pointB)
{
  return pointA.GetPosition() == pointB.GetPosition();
}

bool Collider2D::PointIntersectsCircle(PointCollider& point, CircleCollider& circle)
{
  float distance = point.GetPosition().DistanceFrom(circle.GetPosition());
  
  return distance <= circle.radius;
}

bool Collider2D::PointIntersectsRect(PointCollider& point, RectCollider& rect)
{
  Vector2 position = point.GetPosition();
  Rect bounds = rect.GetBounds();

  return position.x > bounds.left && position.x < bounds.left + bounds.width &&
         position.y > bounds.top && position.y < bounds.top + bounds.height;
}

//bool Collider2D::PointIntersectsPixel(PointCollider&, PixelCollider&);

bool Collider2D::CircleIntersectsCircle(CircleCollider& circleA, CircleCollider& circleB)
{
  float distance = circleA.GetPosition().DistanceFrom(circleB.GetPosition());

  return distance <= circleA.radius + circleB.radius;
}

//todo
bool Collider2D::CircleIntersectsRect(CircleCollider&, RectCollider&)
{
  return false;
}

//bool Collider2D::CircleIntersectsPixel(CircleCollider&, PixelCollider&);

bool Collider2D::RectIntersectsRect(RectCollider& rectA, RectCollider& rectB)
{
  Vector2 positionA = rectA.GetPosition();
  Vector2 positionB = rectB.GetPosition();

  return positionA.x < positionB.x + rectB.width &&
         positionA.x + rectA.width > positionB.x &&
         positionA.y < positionB.y + rectB.height &&
         positionA.y + rectA.height > positionB.y;
}

//bool Collider2D::RectIntersectsPixel(RectCollider&, PixelCollider&);
//bool Collider2D::PixelIntersectsPixel(PixelCollider&, PixelCollider&);