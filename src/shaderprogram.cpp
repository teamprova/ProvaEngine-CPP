#include <glad.h>
#include <fstream>
#include <string>
#include <cerrno>
#include <stdexcept>
#include <iostream>
#include <string>
#include <list>
#include "shaderprogram.hpp"
#include "color.hpp"
#include "mesh.hpp"
#include "matrix.hpp"
#include "texture.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

using namespace Prova;

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
  glUseProgram(id);

  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetVector3(std::string name, Vector3 vector)
{
  glUseProgram(id);

  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetVector4(std::string name, Vector4 vector)
{
  glUseProgram(id);

  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &vector.x);
}

void ShaderProgram::SetVector4(std::string name, Color color)
{
  glUseProgram(id);

  unsigned int location = GetUniform(name);
  glUniform4fv(location, 1, &color.r);
}

void ShaderProgram::SetMatrix(std::string name, Matrix matrix)
{
  glUseProgram(id);

  unsigned int location = GetUniform(name);
  glUniformMatrix4fv(location, 1, true, &matrix[0][0]);
}

void ShaderProgram::SetTexture(int sampler, Texture texture)
{
  SetTexture(sampler, texture.id);
}

void ShaderProgram::SetTexture(int sampler, unsigned int texture)
{
  glUseProgram(id);

  glActiveTexture(GL_TEXTURE0 + sampler);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void ShaderProgram::SetTexture(std::string name, Texture texture)
{
  SetTexture(name, texture.id);
}

void ShaderProgram::SetTexture(std::string name, unsigned int texture)
{
  glUseProgram(id);
  
  unsigned int location = GetUniform(name);
  glActiveTexture(location);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void ShaderProgram::DrawMesh(DrawMode mode, Mesh& mesh)
{
  glUseProgram(id);
  glBindVertexArray(mesh.VAO);
  glDrawElements((unsigned int) mode, mesh._indexCount, GL_UNSIGNED_INT, NULL);
}

void ShaderProgram::LoadVertexShader(std::string sourceFile)
{
  LoadShader(GL_VERTEX_SHADER, sourceFile);
}

void ShaderProgram::LoadFragmentShader(std::string sourceFile)
{
  LoadShader(GL_FRAGMENT_SHADER, sourceFile);
}

void ShaderProgram::LoadGeometryShader(std::string sourceFile)
{
  LoadShader(GL_GEOMETRY_SHADER, sourceFile);
}

void ShaderProgram::AttachVertexShader(std::string source)
{
  CompileShader(GL_VERTEX_SHADER, source);
}

void ShaderProgram::AttachFragmentShader(std::string source)
{
  CompileShader(GL_FRAGMENT_SHADER, source);
}

void ShaderProgram::AttachGeometryShader(std::string source)
{
  CompileShader(GL_GEOMETRY_SHADER, source);
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

void ShaderProgram::LoadShader(unsigned int shaderType, std::string sourceFile)
{
  // read file as written
  std::ifstream in(sourceFile, std::ios::in | std::ios::binary);

  if (!in)
  {
    std::string error = "Error reading file " + sourceFile + ", Error Code: ";
    error += std::to_string(errno);
    throw std::runtime_error(error);
  }
  
  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();

  CompileShader(shaderType, contents);
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