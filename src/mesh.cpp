#include <GL/glew.h>
#include <GL/gl.h>
#include "mesh.hpp"

Mesh::Mesh()
{
  glGenVertexArrays(1, &VAO);
}

void Mesh::SetVBO(float vertices[], int length, int dimensions)
{
  unsigned int positionAttributeIndex = 0;

  glBindVertexArray(VAO);
  CreateBuffer(&VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(positionAttributeIndex, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
}

void Mesh::SetIBO(unsigned int indexes[], int length)
{
  _indexCount = length;

  glBindVertexArray(VAO);
  CreateBuffer(&IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), indexes, GL_STATIC_DRAW);
}

void Mesh::CreateBuffer(unsigned int* buffer)
{
  // delete old buffers
  if(*buffer == -1)
    glDeleteBuffers(1, buffer);
  
  // create a new buffer
  glGenBuffers(1, buffer);
}