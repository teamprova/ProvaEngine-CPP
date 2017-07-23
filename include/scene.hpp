#pragma once
#include <list>
#include "camera.hpp"
#include "collider2d.hpp"
#include "input.hpp"
#include "spacialmap2d.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Camera;
  class Collider2D;
  class Entity;
  class Game;
  class Screen;
  class Vector2;

  class Scene
  {
    friend class Game;
    friend class Entity;

    public:
      Game* game = nullptr;
      Input* input = nullptr;
      bool debug = false;
      Camera camera;
      std::list<Entity*> entities;
      void AddEntity(Entity& entity);
      void RemoveEntity(Entity& entity);
      Entity& FindClosestEntity(Entity& entity);
      Entity& FindClosestEntity(Entity& entity, int tag);
      // runs when the scene is first attached to a game
      virtual void Setup();
      // runs when the scene is attached to a game
      virtual void Start();
      // runs every update tick
      virtual void Update();
      // called by Update
      void Collider2DUpdate();
      // called by Update
      void EntityUpdate();
      virtual void Draw(Screen& screen);
    private:
      bool _setup = false;
      const uint8_t* _keystate;
      SpacialMap2D _collider2DMap;
  };
}