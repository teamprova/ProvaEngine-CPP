#pragma once
#include <list>
#include "shaderprogram.hpp"
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
      void BatchSprite(Sprite& sprite, Vector3 position);
      void End();
    private:
      bool _begun = false;
      std::list<Sprite*> _sprites;
      std::list<Vector3> _positions;
      void DrawSprite(Sprite&, Vector3&);
      Matrix _transform;
  };
}