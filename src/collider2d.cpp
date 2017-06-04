#include "collider2d.hpp"
#include "rect.hpp"
#include "vector2.hpp"

Collider2D::Collider2D(Entity* entity)
{
  this->entity = entity;
}

Rect Collider2D::GetBounds()
{
  Vector2 halfSize = GetSize() / 2;
  Vector2 position(
    offset.x + entity->position.x,
    offset.y + entity->position.y
  );

  return Rect(
    position.x - halfSize.x,
    position.y - halfSize.y,
    position.x + halfSize.x,
    position.y + halfSize.y
  );
}