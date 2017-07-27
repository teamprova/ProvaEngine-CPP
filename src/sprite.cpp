#include "sprite.hpp"
#include "texture.hpp"
#include "vector2.hpp"

using namespace Prova;

Sprite::Sprite()
  : angle(0),
    clip(0, 0, 1, 1),
    scale(1, 1),
    tint(1, 1, 1)
{ }

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