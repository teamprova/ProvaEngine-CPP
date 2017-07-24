#pragma once
#include <list>
#include <string>
#include "font.hpp"
#include "mesh.hpp"
#include "shaderprogram.hpp"
#include "sprite.hpp"
#include "animatedsprite.hpp"
#include "vector3.hpp"

namespace Prova
{
  class AnimatedSprite;
  class Matrix;
  class ShaderProgram;
  class Sprite;
  class Vector3;

  class SpriteBatch
  {
    public:
      SpriteBatch();
      ShaderProgram shaderProgram;
      void Begin(Matrix transform);
      void BatchString(std::string text, Vector3 position, Font& font, Color color);
      void BatchString(std::string text, Vector3 position, Font& font, Color color, float scale);
      void BatchSprite(AnimatedSprite& sprite, Vector3 position);
      void BatchSprite(Sprite& sprite, Vector3 position);
      void End();
    private:
      bool _begun = false;
      std::list<Sprite> _spritePrimitives;
      std::list<Vector3> _positions;
      void DrawSprite(Sprite&, Vector3&);
      Matrix _transform;
      Mesh _mesh;
  };
}