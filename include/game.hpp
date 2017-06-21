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
      Scene* scene = nullptr;
      Screen* screen = nullptr;
      Input input;
      int FPS = 60;
      void SetTitle(std::string);
      void ToggleFullscreen();
      void SwapScene(Scene*);
      void Start(Scene*);
      void Close();
    private:
      void Loop();
      void Update();
      void Draw();
      void CleanUp();
      SDL_Window* _window;
      bool _isFullscreen = false;
      bool _running = false;
  };
}