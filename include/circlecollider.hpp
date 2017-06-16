#pragma once
#include "collider2d.hpp"

namespace Prova
{
  class Entity;
  class Vector2;

  class CircleCollider : public Collider2D
  {
    public:
      CircleCollider(Entity*, float);
      float radius;
      void Draw(Screen&) override;
    protected:
      Vector2 GetSize() override;
  };
}