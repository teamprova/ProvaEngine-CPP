#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdexcept>
#include "screen.hpp"
#include "vector3.hpp"
#include "sprite.hpp"
#include "shaderprogram.hpp"
#include "game.hpp"
#include "scene.hpp"

Screen::Screen(Game* game)
{
  this->game = game;
  InitGL();
  InitDefaultShader();
}

void Screen::InitGL()
{
  _glContext = SDL_GL_CreateContext(game->_window);
  
  if(_glContext == NULL)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("Error initializing GL Context: " + error);
  }
  
  //Initialize GLEW
  glewExperimental = GL_TRUE; 
  GLenum glewError = glewInit();

  if(glewError != GLEW_OK)
  {
    //const GLubyte can't be used as a c++ string for some reason
    //std::string error(glewGetErrorString(glewError));
    throw std::runtime_error("GLEW Error");// + error;
  }

  //Use Vsync
  if(SDL_GL_SetSwapInterval(1) < 0)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("VSync Error: " + error);
  }
}

void Screen::InitDefaultShader()
{
  spriteShaderProgram = new ShaderProgram();

  spriteShaderProgram->AttachVertexShader(
    "#version 130\n\
    uniform mat4 transforms;\n\
    uniform mat4 model;\n\
    in vec4 vertexPosition;\n\
    out vec2 position;\n\
\n\
    void main() {\n\
      position = vertexPosition.xy;\n\
      gl_Position = transforms * model * vertexPosition;\n\
    }"
  );
  spriteShaderProgram->AttachFragmentShader(
    "#version 130\n\
    uniform sampler2D sprite;\n\
    uniform vec4 clip;\n\
    in vec2 position;\n\
    out vec4 color;\n\
\n\
    void main() {\n\
      vec2 texPos;\n\
      texPos.x = clip.x + (position.x) * clip.z;\n\
      texPos.y = clip.y + (position.y) * clip.w;\n\
      color = texture(sprite, texPos);\n\
    }"
  );
  spriteShaderProgram->Link();
}

void Screen::BeginDraw()
{
  Matrix cameraTransform = game->scene->camera.GetTransform();
  cameraTransform = cameraTransform.Translate(_width / 2, _height / 2, 0);
  _transforms = game->scene->camera.projection * cameraTransform;
}

void Screen::DrawSprite(Sprite* sprite, Vector3 vector)
{
  Screen::DrawSprite(sprite, vector.x, vector.y);
}

void Screen::DrawSprite(Sprite* sprite, float x, float y)
{
  sprite->Update();
  glUseProgram(spriteShaderProgram->id);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  Matrix model = Matrix::Identity();
  model = model.Scale(sprite->width, sprite->height, 1);
  model = model.Translate(-sprite->origin);
  model = model.Scale(sprite->scale);
  model = model.RotateZ(sprite->angle);
  model = model.Translate(x, y, 0);

  spriteShaderProgram->SetMatrix("transforms", _transforms);
  spriteShaderProgram->SetMatrix("model", model);
  spriteShaderProgram->SetTexture("sprite", sprite->texture);
  spriteShaderProgram->SetVector4("clip", Vector4(sprite->_clip));

  // vertex position
  unsigned int vertexPos = spriteShaderProgram->GetAttribute("vertexPosition");
  glEnableVertexAttribArray(vertexPos);
  glBindVertexArray(sprite->mesh.VAO);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
  
  //Disable vertex position
  glDisableVertexAttribArray(vertexPos);
}

void Screen::Clear(int r, int g, int b)
{
  glClearColor(r/255.0f, g/255.0f, b/255.0f, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::SwapBuffer()
{
  SDL_GL_SwapWindow(game->_window);
}

Screen::~Screen()
{
  delete spriteShaderProgram;
  SDL_GL_DeleteContext(_glContext);
}