#pragma once
#include "collider2d.hpp"

namespace Prova
{
  class Entity;
  class Vector2;

  class CircleCollider : public Collider2D
  {
    public:
      CircleCollider(Entity* entity, float size);
      float radius;
      void Draw(Screen& screen) override;
    protected:
      Vector2 GetSize() override;
  };
}