#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "shaderprogram.hpp"
#include "game.hpp"
#include "matrix.hpp"

namespace Prova
{
  class Color;
  class Matrix;
  class Rect;
  class Sprite;
  class ShaderProgram;
  class Vector3;

  class Screen
  {
    friend class Game;

    public:
      Screen(Game*);
      ShaderProgram* spriteShaderProgram;
      ShaderProgram* flatShaderProgram;
      Game* game;
      int GetWidth();
      int GetHeight();
      void BeginDraw();
      void DrawLine(Color, Vector3, Vector3);
      void DrawLine(Color, Vector2, Vector2);
      void DrawLine(Color, float, float, float, float);
      void DrawRect(Color, Rect);
      void DrawRect(Color, float, float, float, float);
      void DrawSprite(Sprite&, Vector3);
      void DrawSprite(Sprite&, float, float);
      void DrawSprite(Sprite&, float, float, float);
      void Clear(float, float, float);
      void SwapBuffer();
      ~Screen();
    private:
      void InitGL();
      void InitSpriteShader();
      void InitLineShader();
      SDL_GLContext _glContext;
      Matrix _transforms;
      int _width;
      int _height;
  };
}