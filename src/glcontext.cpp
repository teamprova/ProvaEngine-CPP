#include <glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdexcept>
#include "glcontext.hpp"

using namespace Prova;

GLContext::GLContext(void* window)
{
  handle = SDL_GL_CreateContext((SDL_Window*) window);
  
  if(handle == nullptr)
  {
    std::string error(SDL_GetError());
    throw std::runtime_error("Error initializing GL Context: " + error);
  }
  
  if(!gladLoadGL())
  {
    throw std::runtime_error("Failed to initialize glad OpenGL loader");
  }
}

GLContext::~GLContext()
{
  SDL_GL_DeleteContext((SDL_GLContext*) handle);
}