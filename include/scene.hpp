#pragma once
#include <SDL2/SDL.h>
#include <list>
#include "vector2.hpp"
#include "camera.hpp"
#include "collider2d.hpp"
#include "spacialmap2d.hpp"

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
      Game* game;
      Camera camera;
      std::list<Entity*> entities;
      bool Debug = false;
      void PreUpdate();
      bool IsKeyDown(int);
      bool IsKeyUp(int);
      void AddEntity(Entity&);
      void RemoveEntity(Entity&);
      virtual void Update();
      void Collider2DUpdate();
      void EntityUpdate();
      virtual void Draw(Screen& screen);
    private:
      const Uint8* _keystate;
      SpacialMap2D _collider2DMap;
  };
}