#pragma once
#include "vector2.hpp"
#include "entity.hpp"

class Entity;
class Vector2;
class Rect;

class Collider2D
{
  public:
    enum ColliderShape { Point, Circle, Square };
    
    Collider2D(Entity*);
    virtual bool Intersects(Collider2D*) = 0;
    virtual Vector2 GetSize() = 0;
    Rect GetBounds();
    Vector2 offset;
    Entity* entity;
};