#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "game.hpp"
#include "matrix.hpp"
#include "shaderprogram.hpp"
#include "spritebatch.hpp"

namespace Prova
{
  class Color;
  class Matrix;
  class Rect;
  class Sprite;
  class SpriteBatch;
  class ShaderProgram;
  class Vector3;

  class Screen
  {
    friend class Game;

    public:
      Screen(Game*);
      Game* game;
      ShaderProgram flatShaderProgram;
      SpriteBatch spriteBatch;
      int GetWidth();
      int GetHeight();
      void EnableVSync();
      void DisableVSync();
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
      void InitFlatShader();
      SDL_GLContext _glContext;
      Matrix _transforms;
      Matrix _2DProjection;
      int _width;
      int _height;
  };
}