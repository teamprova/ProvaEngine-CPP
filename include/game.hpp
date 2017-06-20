#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "input.hpp"

namespace Prova
{
  class Scene;
  class Screen;
  class Input;

  class Game
  {
    friend class Screen;

    public:
      Game(int width, int height, std::string title);
      Scene* scene;
      Screen* screen;
      Input input;
      int FPS = 60;
      void SetTitle(std::string);
      void ToggleFullscreen();
      void SwapScene(Scene*);
      void Start(Scene*);
      void Close();
    private:
      void Update();
      SDL_Window* _window;
      bool _isFullscreen = false;
      bool _running = false;
  };
}