#include "rectcollider.hpp"
#include "color.hpp"
#include "rect.hpp"
#include "screen.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

using namespace Prova;

RectCollider::RectCollider(Entity* entity, float width, float height)
  : Collider2D(entity)
{
  shape = Shape::Rectangle;
  this->width = width;
  this->height = height;
}

Vector2 RectCollider::GetSize()
{
  return Vector2(width, height);
}

void RectCollider::Draw(Screen& screen)
{
  Color color = collisionOccurred ? Color(1, 0, 0) : Color(0, 0, 1);
  Rect bounds = GetBounds();
  Vector3 topLeft = bounds.GetTopLeft();
  Vector3 topRight = bounds.GetTopRight();
  Vector3 bottomLeft = bounds.GetBottomLeft();
  Vector3 bottomRight = bounds.GetBottomRight();

  screen.DrawLine(color, topLeft, topRight);
  screen.DrawLine(color, topRight, bottomRight);
  screen.DrawLine(color, bottomRight, bottomLeft);
  screen.DrawLine(color, bottomLeft, topLeft);
}