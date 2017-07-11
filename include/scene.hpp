#pragma once
#include <list>
#include "camera.hpp"
#include "collider2d.hpp"
#include "input.hpp"
#include "spacialmap2d.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Game;
  class Screen;
  class Entity;
  class Camera;
  class Collider2D;
  class Vector2;

  class Scene
  {
    friend class Entity;

    public:
      Game* game = nullptr;
      Input* input = nullptr;
      Camera camera;
      std::list<Entity*> entities;
      bool Debug = false;
      void AddEntity(Entity&);
      void RemoveEntity(Entity&);
      virtual void Setup();
      virtual void Update();
      void Collider2DUpdate();
      void EntityUpdate();
      virtual void Draw(Screen& screen);
    private:
      const uint8_t* _keystate;
      SpacialMap2D _collider2DMap;
  };
}