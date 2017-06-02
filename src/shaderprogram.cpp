#include <GL/glew.h>
#include <GL/glu.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <list>
#include "shaderprogram.hpp"
#include "matrix.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

ShaderProgram::ShaderProgram()
{
  id = glCreateProgram();
}

unsigned int ShaderProgram::GetAttribute(std::string name)
{
  unsigned int location = glGetAttribLocation(id, name.c_str());

  if(location == -1)
    throw std::runtime_error("Couldn't find attribute: " + name);
  return location;
}

unsigned int ShaderProgram::GetUniform(std::string name)
{
  unsigned int location = glGetUniformLocation(id, name.c_str());

  if(location == -1)
    throw std::runtime_error("Couldn't find uniform: " + name);
  return location;
}

void ShaderProgram::SetVector2(std::string name, Vector2 vector)
{
  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetVector3(std::string name, Vector3 vector)
{
  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetVector4(std::string name, Vector4 vector)
{
  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetMatrix(std::string name, Matrix matrix)
{
  unsigned int location = GetUniform(name);
  glUniformMatrix4fv(location, 1, true, &matrix[0][0]);
}

void ShaderProgram::SetTexture(int sampler, unsigned int texture)
{
  glActiveTexture(GL_TEXTURE0 + sampler);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void ShaderProgram::SetTexture(std::string name, unsigned int texture)
{
  unsigned int location = GetUniform(name);
  glActiveTexture(location);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void ShaderProgram::AttachVertexShader(std::string source)
{
  CompileShader(GL_VERTEX_SHADER, source);
}

void ShaderProgram::AttachFragmentShader(std::string source)
{
  CompileShader(GL_FRAGMENT_SHADER, source);
}

void ShaderProgram::Link()
{
  glLinkProgram(id);

  //Check for errors
  int programSuccess;
  glGetProgramiv(id, GL_LINK_STATUS, &programSuccess);

  if(programSuccess == true)
    return;

  PrintProgramLog();
  throw std::runtime_error("Error linking program");
}

void ShaderProgram::PrintProgramLog()
{
  int infoLogLength = 0;
  int maxLength = 0;
  
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
  
  char* infoLog = new char[maxLength];
  
  glGetProgramInfoLog(id, maxLength, &infoLogLength, infoLog);
  
  if(infoLogLength > 0)
    std::cout << infoLog << "\n";
  
  delete[] infoLog;
}

void ShaderProgram::CompileShader(unsigned int shaderType, std::string source)
{
  GLuint shader = glCreateShader(shaderType);

  const GLchar* shaderSource[] = { source.c_str() };

  glShaderSource(shader, 1, shaderSource, NULL);
  glCompileShader(shader);

  int successfulCompilation;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &successfulCompilation);

  if(successfulCompilation != true)
  {
    PrintShaderLog(shader);
    throw std::runtime_error("Unable to compile shader");
  }

  glAttachShader(id, shader);

  _shaders.push_back(shader);
}

void ShaderProgram::PrintShaderLog(unsigned int shader)
{
  int infoLogLength = 0;
  int maxLength = 0;
  
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
  
  char* infoLog = new char[maxLength];
  
  glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

  if(infoLogLength > 0)
    std::cout << infoLog << "\n";

  delete[] infoLog;
}

ShaderProgram::~ShaderProgram()
{
  for(auto shader : _shaders)
  {
    glDetachShader(id, shader);
	  glDeleteShader(shader);
  }

	glDeleteProgram(id);
}