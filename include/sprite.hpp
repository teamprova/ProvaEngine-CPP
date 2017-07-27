#pragma once
#include <string>
#include "color.hpp"
#include "mesh.hpp"
#include "rect.hpp"
#include "texture.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Sprite
  {
    friend class SpriteBatch;

    public:
      Sprite();
      Sprite(Texture texture);
      Sprite(std::string sheetpath);
      int angle;
      int width;
      int height;
      Texture texture;
      Vector2 origin;
      Vector2 scale;
      Rect clip;
      Color tint;
  };
}