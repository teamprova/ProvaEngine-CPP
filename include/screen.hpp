#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "shaderprogram.hpp"
#include "game.hpp"
#include "matrix.hpp"

namespace Prova
{
  class Matrix;
  class Vector3;
  class Sprite;
  class ShaderProgram;

  class Screen
  {
    friend class Game;

    public:
      Screen(Game*);
      ShaderProgram* spriteShaderProgram;
      Game* game;
      void BeginDraw();
      void DrawSprite(Sprite&, Vector3);
      void DrawSprite(Sprite&, float, float);
      void Clear(int, int, int);
      void SwapBuffer();
      void GetWidth();
      void GetHeight();
      ~Screen();
    private:
      void InitGL();
      void InitDefaultShader();
      SDL_GLContext _glContext;
      Matrix _transforms;
      int _width;
      int _height;
  };
}