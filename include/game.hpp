#pragma once
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
      Game(std::string title, int width, int height);
      Scene* scene = nullptr;
      Screen* screen = nullptr;
      Input input;
      void SetTitle(std::string title);
      void SetTargetFPS(int target);
      void ToggleFullscreen();
      void SetResizable(bool resizable);
      void SwapScene(Scene* scene);
      void Start(Scene* scene);
      void Close();
    private:
      void Loop();
      void Update();
      void Draw();
      void CleanUp();
      void SetScene(Scene* scene);
      void* _window;
      bool _isFullscreen = false;
      bool _running = false;
      int _targetFPS = 60;
  };
}