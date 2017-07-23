#include "pointcollider.hpp"
#include "color.hpp"
#include "screen.hpp"
#include "vector2.hpp"

using namespace Prova;

PointCollider::PointCollider(Entity* entity)
  : Collider2D(entity)
{
  shape = Shape::Point;
}

Vector2 PointCollider::GetSize()
{
  return Vector2(1, 1);
}

void PointCollider::Draw(Screen& screen)
{
  Color color = collisionOccurred ? Color(1, 0, 0) : Color(0, 0, 1);
  Vector3 position = GetPosition();

  screen.DrawLine(color, position, position);
}