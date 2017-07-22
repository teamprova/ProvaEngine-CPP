#include <stdexcept>
#include "spritebatch.hpp"
#include "shaderprogram.hpp"
#include "sprite.hpp"
#include "vector3.hpp"

using namespace Prova;

SpriteBatch::SpriteBatch()
{
  shaderProgram.AttachVertexShader(
    R"(#version 130
    uniform mat4 transforms;
    in vec4 vertexPosition;
    out vec2 position;

    void main() {
      position = vertexPosition.xy;
      gl_Position = transforms * vertexPosition;
    })"
  );

  shaderProgram.AttachFragmentShader(
    R"(#version 130
    uniform sampler2D sprite;
    uniform vec4 clip;
    in vec2 position;
    out vec4 fragmentColor;

    void main() {
      vec2 texPos = vec2(
        clip.x + (position.x) * clip.z,
        clip.y + (position.y) * clip.w
      );

      fragmentColor = texture(sprite, texPos);

      if(fragmentColor.a == 0)
        discard;
    })"
  );

  shaderProgram.Link();


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

void SpriteBatch::BatchSprite(Sprite& sprite, Vector3 position)
{
  if(!_begun)
    throw std::runtime_error("Batch not started");

  sprite.Update();
  
  _spritePrimitives.emplace_back(sprite);
  _positions.emplace_back(position);
}

void SpriteBatch::End()
{
  if(!_begun)
    throw std::runtime_error("Batch not started");

  unsigned int lastTexture = -1;
  int spriteCount = _spritePrimitives.size();
  auto spriteIt = _spritePrimitives.begin();
  auto positionIt = _positions.begin();

  for(int i = 0; i < spriteCount; ++i)
  {
    SpritePrimitive& sprite = *(spriteIt++);
    Vector3& position = *(positionIt++);

    if(sprite.texture.id != lastTexture)
    {
      shaderProgram.SetTexture(0, sprite.texture);
      lastTexture = sprite.texture.id;
    }
    
    DrawSpritePrimitive(sprite, position);
  }

  _begun = false;
}

void SpriteBatch::DrawSpritePrimitive(SpritePrimitive& sprite, Vector3& position)
{
  Matrix model = Matrix::Identity();
  model = model.Scale(sprite.width, sprite.height, 1);
  model = model.Translate(-sprite.origin);
  model = model.Scale(sprite.scale);
  model = model.RotateZ(sprite.angle);
  model = model.Translate(position.x, position.y, position.z);

  shaderProgram.SetMatrix("transforms", _transform * model);
  shaderProgram.SetVector4("clip", sprite.clip);
  shaderProgram.DrawMesh(ShaderProgram::DrawMode::TRIANGLE_FAN, _mesh);
}