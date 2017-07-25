#include "spriteshaderprogram.hpp"

using namespace Prova;

SpriteShaderProgram::SpriteShaderProgram()
{
  AttachVertexShader(
    R"(#version 130
    uniform mat4 transforms;
    in vec4 vertexPosition;
    out vec2 position;

    void main() {
      position = vertexPosition.xy;
      gl_Position = transforms * vertexPosition;
    })"
  );

  AttachFragmentShader(
    R"(#version 130
    uniform sampler2D sprite;
    uniform vec4 clip;
    uniform vec4 tint;

    in vec2 position;
    out vec4 fragmentColor;

    void main() {
      vec2 texPos = vec2(
        clip.x + (position.x) * clip.z,
        clip.y + (position.y) * clip.w
      );

      fragmentColor = texture(sprite, texPos) * tint;

      if(fragmentColor.a == 0)
        discard;
    })"
  );

  Link();
}