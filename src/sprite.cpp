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

Sprite::Sprite(Texture texture)
  : Sprite()
{
  this->texture = texture;
  width = texture.width;
  height = texture.height;
  origin.x = width / 2;
  origin.y = height / 2;
}

Sprite::Sprite(std::string sheetpath)
  : Sprite(Texture(sheetpath)) { }