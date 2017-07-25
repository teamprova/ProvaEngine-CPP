#include <glew.h>
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
  
  //Initialize GLEW
  glewExperimental = GL_TRUE; 
  GLenum glewError = glewInit();

  if(glewError != GLEW_OK)
  {
    //const GLubyte can't be used as a c++ string for some reason
    //std::string error(glewGetErrorString(glewError));
    throw std::runtime_error("GLEW Error");// + error;
  }
}

GLContext::~GLContext()
{
  SDL_GL_DeleteContext((SDL_GLContext*) handle);
}