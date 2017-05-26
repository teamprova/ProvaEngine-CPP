#pragma once
#include <SDL2/SDL.h>
#include <list>

class Game;
class Canvas;
class Entity;

class Scene
{
  public:
    Game* game;
    void PreUpdate();
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    void EntityUpdate();
    virtual void Update();
    virtual void Draw(Canvas*);
  private:
    const Uint8* _keystate;
    std::list<Entity*> _entities;
};