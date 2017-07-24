#pragma once
#include <string>
#include "color.hpp"
#include "font.hpp"
#include "game.hpp"
#include "glcontext.hpp"
#include "matrix.hpp"
#include "shaderprogram.hpp"
#include "spritebatch.hpp"

namespace Prova
{
  class Color;
  class Font;
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
      Screen(Game* game);
      Game* game;
      GLContext glContext;
      ShaderProgram flatShaderProgram;
      SpriteBatch spriteBatch;
      int GetWidth();
      int GetHeight();
      void EnableVSync();
      void DisableVSync();
      void BeginDraw();
      void DrawLine(Color color, Vector3 start, Vector3 end);
      void DrawLine(Color color, Vector2 start, Vector2 end);
      void DrawLine(Color color, float x1, float y1, float x2, float y2);
      void DrawRect(Color color, Rect rect);
      void DrawRect(Color color, float x, float y, float width, float height);
      void DrawString(std::string text, Vector3 position, Font& font, Color color);
      void DrawString(std::string text, float x, float y, Font& font, Color color);
      void DrawString(std::string text, float x, float y, float z, Font& font, Color color);
      void DrawString(std::string text, Vector3 position, Font& font, Color color, float scale);
      void DrawString(std::string text, float x, float y, Font& font, Color color, float scale);
      void DrawString(std::string text, float x, float y, float z, Font& font, Color color, float scale);
      void DrawSprite(Sprite& sprite, Vector3 position);
      void DrawSprite(Sprite& sprite, float x, float y);
      void DrawSprite(Sprite& sprite, float x, float y, float z);
      void DrawSprite(AnimatedSprite& sprite, Vector3 position);
      void DrawSprite(AnimatedSprite& sprite, float x, float y);
      void DrawSprite(AnimatedSprite& sprite, float x, float y, float z);
      void SetClearColor(float r, float g, float b);
      void SetClearColor(Color color);
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