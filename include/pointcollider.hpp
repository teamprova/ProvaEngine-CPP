#pragma once
#include "collider2d.hpp"

namespace Prova
{
  class Entity;
  class Vector2;

  class PointCollider : public Collider2D
  {
    public:
      PointCollider(Entity*);
      void Draw(Screen&) override;
    protected:
      Vector2 GetSize() override;
  };
}