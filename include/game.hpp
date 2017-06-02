#pragma once
#include <SDL2/SDL.h>
#include <string>

class Scene;
class Screen;

class Game
{
  friend class Screen;

  public:
    Game(int width, int height, std::string title);
    Scene* scene;
    Screen* screen;
    int FPS = 60;
    void SetTitle(std::string);
    void SwapScene(Scene*);
    void Start(Scene*);
    void Close();
  private:
    void Update();
    SDL_Window* _window;
    bool _running = false;
};