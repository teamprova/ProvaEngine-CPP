#pragma once
#include <SDL2/SDL.h>
#include <list>
#include "camera.hpp"

class Game;
class Screen;
class Entity;
class Camera;


class Scene
{
  public:
    enum SortingMethod { Z, Distance };

    Game* game;
    Camera camera;
    SortingMethod sortingMethod = SortingMethod::Distance;
    void PreUpdate();
    bool IsKeyDown(int);
    bool IsKeyUp(int);
    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    void EntityUpdate();
    virtual void Update();
    virtual void Draw(Screen* screen);
  private:
    const Uint8* _keystate;
    std::list<Entity*> _entities;
};