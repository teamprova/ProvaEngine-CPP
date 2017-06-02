#pragma once
#include "vector3.hpp"

class Vector3;
class Scene;
class Screen;

class Entity
{
  public:
    Vector3 position;
    Vector3 velocity;
    Scene* scene;
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    virtual void Update();
    virtual void Draw(Screen*);
};