#pragma once
#include "collider2d.hpp"

namespace Prova
{
  class Entity;
  class Vector2;

  class RectCollider : public Collider2D
  {
    public:
      RectCollider(Entity*, float, float);
      float width;
      float height;
      void Draw(Screen&) override;
    protected:
      Vector2 GetSize() override;
  };
}