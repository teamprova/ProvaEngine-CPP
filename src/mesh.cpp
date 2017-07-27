#include <glew.h>
#include "mesh.hpp"
#include "shaderprogram.hpp"

using namespace Prova;

Mesh::Mesh()
{
  glGenVertexArrays(1, &VAO);
}

void Mesh::SetVBO(float vertices[], int length, int dimensions)
{
  glBindVertexArray(VAO);
  CreateBuffer(VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
}

void Mesh::SetIBO(unsigned int indexes[], int length)
{
  _indexCount = length;

  glBindVertexArray(VAO);
  CreateBuffer(IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), indexes, GL_STATIC_DRAW);
}

void Mesh::CreateBuffer(unsigned int& buffer)
{
  // delete old buffers
  if(buffer != -1)
    glDeleteBuffers(1, &buffer);
  
  // create a new buffer
  glGenBuffers(1, &buffer);
}

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &VAO);

  if(VBO != -1)
    glDeleteBuffers(1, &VBO);
  if(IBO != -1)
    glDeleteBuffers(1, &IBO);
}