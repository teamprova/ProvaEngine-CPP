#pragma once
#include <SDL2/SDL.h>
#include <string>

class Scene;
class Canvas;

class Game
{
  public:
    Game(int width, int height, std::string title);
    int FPS = 30;
    void SetTitle(std::string);
    void SwapScene(Scene*);
    void Start(Scene*);
    void Close();
  private:
    void Update();
    Scene* _scene;
    SDL_Window* _window;
    Canvas* _canvas;
    bool _running = false;
};