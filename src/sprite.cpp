#include "sprite.hpp"
#include "texture.hpp"
#include "vector2.hpp"

using namespace Prova;

Sprite::Sprite()
{
  clip.left = 0;
  clip.top = 0;
  clip.width = 1;
  clip.height = 1;
  scale.x = 1;
  scale.y = 1;
}

Sprite::Sprite(std::string sheetpath, int width, int height)
  : texture(sheetpath)
{
  this->width = width;
  this->height = height;
  clip.left = 0;
  clip.top = 0;
  clip.width = width / (float) texture.width;
  clip.height = height / (float) texture.height;
  origin.x = width / 2;
  origin.y = height / 2;
  scale.x = 1;
  scale.y = 1;
}