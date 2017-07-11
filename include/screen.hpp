#pragma once
#include <string>
#include "color.hpp"
#include "game.hpp"
#include "glcontext.hpp"
#include "matrix.hpp"
#include "shaderprogram.hpp"
#include "spritebatch.hpp"

namespace Prova
{
  class Color;
  class GLContext;
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
      GLContext glContext;
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
      void SetClearColor(float, float, float);
      void SetClearColor(Color);
      void Clear();
      void SwapBuffer();
    private:
      void InitGL();
      void InitFlatShader();
      Matrix _transforms;
      Matrix _2DProjection;
      Color _clearColor;
      int _width;
      int _height;
  };
}