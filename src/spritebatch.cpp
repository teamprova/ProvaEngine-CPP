#include <stdexcept>
#include <string>
#include "spritebatch.hpp"
#include "color.hpp"
#include "font.hpp"
#include "shaderprogram.hpp"
#include "spriteshaderprogram.hpp"
#include "sprite.hpp"
#include "animatedsprite.hpp"
#include "vector3.hpp"

using namespace Prova;

SpriteBatch::SpriteBatch()
{
  static ShaderProgram* defaultShaderProgram = new SpriteShaderProgram();
  shaderProgram = defaultShaderProgram;

  float vertices[] = {
    0, 0, 0, 1,
    1, 0, 0, 1,
    1, 1, 0, 1,
    0, 1, 0, 1
  };

  unsigned int indexes[] = { 0, 1, 2, 3 };

  _mesh.SetIBO(indexes, 4);
  _mesh.SetVBO(vertices, 16, 4);
}

void SpriteBatch::Begin(Matrix transform)
{
  if(_begun)
    throw std::runtime_error("Batch already started");
  
  _spritePrimitives.clear();
  _positions.clear();
  _transform = transform;
  _begun = true;
}

void SpriteBatch::BatchString(std::string text, Vector3 position, Font& font, Color color)
{
  BatchString(text, position, font, color, 1);
}

void SpriteBatch::BatchString(std::string text, Vector3 position, Font& font, Color color, float scale)
{
  Sprite sprite;
  sprite.texture = font.texture;
  sprite.tint = color;
  sprite.scale.x = sprite.scale.y = scale;

  // lower the text to draw from the top left
  position.y -= font.GetMaxHeight();

  for(int i = 0; i < text.size(); ++i)
  {
    int c = text[i];

    if(!font.HasGlyph(c))
      continue;

    Glyph glyph = font.GetGlyph(c);
    sprite.clip = glyph.clip;
    sprite.width = glyph.width;
    sprite.height = glyph.height;

    // lower the sprite to draw from the top left
    glyph.offset.y -= sprite.height;

    BatchSprite(sprite, position + glyph.offset * scale);

    position += glyph.shift * scale;
  }
}

void SpriteBatch::BatchSprite(AnimatedSprite& sprite, Vector3 position)
{
  sprite.Update();

  BatchSprite((Sprite&) sprite, position);
}

void SpriteBatch::BatchSprite(Sprite& sprite, Vector3 position)
{
  if(!_begun)
    throw std::runtime_error("Batch not started");
  
  _spritePrimitives.emplace_back(sprite);
  _positions.emplace_back(position);
}

void SpriteBatch::End()
{
  if(!_begun)
    throw std::runtime_error("Batch not started");

  Color lastTint(1, 1, 1);
  unsigned int lastTexture = -1;
  int spriteCount = _spritePrimitives.size();
  auto spriteIt = _spritePrimitives.begin();
  auto positionIt = _positions.begin();

  // set the inital value for the tint
  shaderProgram->SetVector4("tint", lastTint);

  for(int i = 0; i < spriteCount; ++i)
  {
    Sprite& sprite = *(spriteIt++);
    Vector3& position = *(positionIt++);

    if(sprite.texture.id != lastTexture)
    {
      shaderProgram->SetTexture(0, sprite.texture);
      lastTexture = sprite.texture.id;
    }

    if(sprite.tint != lastTint)
    {
      shaderProgram->SetVector4("tint", sprite.tint);
      lastTint = sprite.tint;
    }
    
    DrawSprite(sprite, position);
  }

  _begun = false;
}

void SpriteBatch::DrawSprite(Sprite& sprite, Vector3& position)
{
  Matrix model = Matrix::Identity();
  model = model.Scale(sprite.width, sprite.height, 1);
  model = model.Translate(-sprite.origin);
  model = model.Scale(sprite.scale);
  model = model.RotateZ(sprite.angle);
  model = model.Translate(position.x, position.y + sprite.height, position.z);

  shaderProgram->SetMatrix("transforms", _transform * model);
  shaderProgram->SetVector4("clip", sprite.clip);
  shaderProgram->DrawMesh(ShaderProgram::DrawMode::TRIANGLE_FAN, _mesh);
}