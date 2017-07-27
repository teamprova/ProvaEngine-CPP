#include <glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <stdexcept>
#include "screen.hpp"
#include "color.hpp"
#include "font.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "shaderprogram.hpp"
#include "sprite.hpp"
#include "animatedsprite.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

using namespace Prova;

Screen::Screen(Game* game)
  : glContext(game->_window)
{
  this->game = game;

  InitFlatShader();

  DisableVSync();
  glDepthFunc(GL_LEQUAL);
}

void Screen::InitFlatShader()
{
  flatShaderProgram.AttachVertexShader(
    R"(#version 130
    uniform mat4 projection;
    in vec3 vertexPosition;

    void main() {
      gl_Position = projection * vec4(vertexPosition, 1);
    })"
  );

  flatShaderProgram.AttachFragmentShader(
    R"(#version 130
    uniform vec4 color;
    out vec4 fragmentColor;

    void main() {
      fragmentColor = color;
    })"
  );

  flatShaderProgram.Link();
}

int Screen::GetWidth()
{
  return _width;
}

int Screen::GetHeight()
{
  return _height;
}

void Screen::Resize(int width, int height)
{
  SDL_SetWindowSize((SDL_Window*) game->_window, width, height);
  UpdateResolution(width, height);
}

void Screen::UpdateResolution(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, _width, _height);
}

void Screen::EnableVSync()
{
  if(SDL_GL_SetSwapInterval(1) < 0)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("VSync Error: " + error);
  }
}

void Screen::DisableVSync()
{
  if(SDL_GL_SetSwapInterval(0) < 0)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("VSync Error: " + error);
  }
}

void Screen::BeginDraw()
{
  Camera& camera = game->scene->camera;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  if(camera.useDepthBuffer)
    glEnable(GL_DEPTH_TEST);
  else
    glDisable(GL_DEPTH_TEST);
  
  if(camera.resolutionDependent)
  {
    camera.width = _width;
    camera.height = _height;
  }
  
  _transforms = camera.GetProjection() * camera.GetTransform();
  _UIProjection = camera.GetUIMatrix();

  spriteBatch.Begin(_transforms);
}

void Screen::DrawLine(Color color, Vector3 start, Vector3 end)
{
  float vertices[] = {
    start.x, start.y, start.z,
    end.x, end.y, end.z
  };
  unsigned int indexes[] = { 0, 1 };

  Mesh mesh;
  mesh.SetVBO(vertices, 6, 3);
  mesh.SetIBO(indexes, 2);

  flatShaderProgram.SetMatrix("projection", _transforms);
  flatShaderProgram.SetVector4("color", color);
  flatShaderProgram.DrawMesh(ShaderProgram::DrawMode::LINES, mesh);
}

void Screen::DrawLine(Color color, Vector2 start, Vector2 end)
{
  DrawLine(color, start.x, start.y, end.x, end.y);
}

void Screen::DrawLine(Color color, float x1, float y1, float x2, float y2)
{
  float vertices[] = { x1, y1, 0, x2, y2, 0 };
  unsigned int indexes[] = { 0, 1 };

  Mesh mesh;
  mesh.SetVBO(vertices, 6, 3);
  mesh.SetIBO(indexes, 2);

  flatShaderProgram.SetMatrix("projection", _UIProjection);
  flatShaderProgram.SetVector4("color", color);
  flatShaderProgram.DrawMesh(ShaderProgram::DrawMode::LINES, mesh);
}

void Screen::DrawRect(Color color, Rect rect)
{
  DrawRect(color, rect.left, rect.top, rect.width, rect.height);
}

void Screen::DrawRect(Color color, float x, float y, float width, float height)
{
  float vertices[] = {
    x, y, 0,
    x + width, y, 0,
    x + width, y + height, 0,
    x, y + height, 0
  };
  unsigned int indexes[] = { 0, 1, 2, 3 };

  Mesh mesh;
  mesh.SetVBO(vertices, 12, 3);
  mesh.SetIBO(indexes, 4);

  flatShaderProgram.SetMatrix("projection", _UIProjection);
  flatShaderProgram.SetVector4("color", color);
  flatShaderProgram.DrawMesh(ShaderProgram::DrawMode::LINE_LOOP, mesh);
}

void Screen::DrawString(std::string text, Vector3 position, Font& font, Color color)
{
  spriteBatch.BatchString(text, position, font, color, 1);
}

void Screen::DrawString(std::string text, float x, float y, Font& font, Color color)
{
  spriteBatch.BatchString(text, Vector3(x, y, 0), font, color, 1);
}

void Screen::DrawString(std::string text, float x, float y, float z, Font& font, Color color)
{
  spriteBatch.BatchString(text, Vector3(x, y, z), font, color, 1);
}

void Screen::DrawString(std::string text, Vector3 position, Font& font, Color color, float scale)
{
  spriteBatch.BatchString(text, position, font, color, scale);
}

void Screen::DrawString(std::string text, float x, float y, Font& font, Color color, float scale)
{
  spriteBatch.BatchString(text, Vector3(x, y, 0), font, color, scale);
}

void Screen::DrawString(std::string text, float x, float y, float z, Font& font, Color color, float scale)
{
  spriteBatch.BatchString(text, Vector3(x, y, z), font, color, scale);
}

void Screen::DrawSprite(Sprite& sprite, Vector3 position)
{
  spriteBatch.BatchSprite(sprite, position);
}

void Screen::DrawSprite(Sprite& sprite, float x, float y)
{
  spriteBatch.BatchSprite(sprite, Vector3(x, y, 0));
}

void Screen::DrawSprite(Sprite& sprite, float x, float y, float z)
{
  spriteBatch.BatchSprite(sprite, Vector3(x, y, z));
}

void Screen::DrawSprite(AnimatedSprite& sprite, Vector3 position)
{
  spriteBatch.BatchSprite(sprite, position);
}

void Screen::DrawSprite(AnimatedSprite& sprite, float x, float y)
{
  spriteBatch.BatchSprite(sprite, Vector3(x, y, 0));
}

void Screen::DrawSprite(AnimatedSprite& sprite, float x, float y, float z)
{
  spriteBatch.BatchSprite(sprite, Vector3(x, y, z));
}

void Screen::SetClearColor(float r, float g, float b)
{
  _clearColor = Color(r, g, b);
}

void Screen::SetClearColor(Color color)
{
  _clearColor = color;
}

void Screen::Clear()
{
  glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::SwapBuffer()
{
  spriteBatch.End();
  SDL_GL_SwapWindow((SDL_Window*) game->_window);
}