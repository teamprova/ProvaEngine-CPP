#include "circlecollider.hpp"
#include "color.hpp"
#include "rect.hpp"
#include "screen.hpp"
#include "vector2.hpp"

using namespace Prova;

CircleCollider::CircleCollider(Entity* entity, float radius)
  : Collider2D(entity)
{
  shape = Shape::Circle;
  this->radius = radius;
}

Vector2 CircleCollider::GetSize()
{
  return Vector2(radius * 2, radius * 2);
}

void CircleCollider::Draw(Screen& screen)
{
  Color color = collisionOccurred ? Color(1, 0, 0) : Color(0, 0, 1);
  Vector3 position = GetPosition();

  // todo
  Rect bounds = GetBounds();
  Vector3 topLeft = bounds.GetTopLeft();
  Vector3 topRight = bounds.GetTopRight();
  Vector3 bottomLeft = bounds.GetBottomLeft();
  Vector3 bottomRight = bounds.GetBottomRight();

  screen.DrawLine(topLeft, topRight, color);
  screen.DrawLine(topRight, bottomRight, color);
  screen.DrawLine(bottomRight, bottomLeft, color);
  screen.DrawLine(bottomLeft, topLeft, color);
  screen.DrawLine(position, position, color);
}