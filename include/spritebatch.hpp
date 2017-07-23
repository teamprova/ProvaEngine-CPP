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
      void BatchString(std::string text, Font& font, Vector3 position);
      void BatchString(std::string text, Font& font, Color color, Vector3 position);
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