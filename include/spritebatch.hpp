#pragma once
#include <list>
#include <string>
#include "font.hpp"
#include "mesh.hpp"
#include "shaderprogram.hpp"
#include "spriteprimitive.hpp"
#include "sprite.hpp"
#include "vector3.hpp"

namespace Prova
{
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
      void BatchSprite(Sprite& sprite, Vector3 position);
      void BatchSprite(SpritePrimitive& sprite, Vector3 position);
      void End();
    private:
      bool _begun = false;
      std::list<SpritePrimitive> _spritePrimitives;
      std::list<Vector3> _positions;
      void DrawSpritePrimitive(SpritePrimitive&, Vector3&);
      Matrix _transform;
      Mesh _mesh;
  };
}