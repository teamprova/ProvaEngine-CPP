#pragma once
#include <SDL2/SDL.h>

class Game;
class Canvas;

class Scene
{
  friend class Game;

  public:
    Game* game;
    bool IsKeyDown(int);
    bool IsKeyUp(int);
  protected:
    virtual void Update() = 0;
    virtual void Draw(Canvas*) = 0;
  private:
    void PreUpdate();
    const Uint8* _keystate;
};