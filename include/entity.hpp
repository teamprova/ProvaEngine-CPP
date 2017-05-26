#pragma once
#include "vector2.hpp"

class Vector2;
class Scene;
class Canvas;

class Entity
{
  public:
    Vector2 position;
    Vector2 velocity;
    Scene* scene;
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    virtual void Update() = 0;
    virtual void Draw(Canvas*) = 0;
};