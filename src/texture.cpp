#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad.h>
#include <unordered_map>
#include <string>
#include "texture.hpp"

using namespace Prova;

std::unordered_map<std::string, Texture*> Texture::_textureCache;

Texture::Texture()
{
  id = 0;
  width = 0;
  height = 0;
}

Texture::Texture(unsigned char data[], int width, int height)
{
  this->width = width;
  this->height = height;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(
    GL_TEXTURE_2D,
 	  0,
    GL_RGBA,
    width,
    height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
 	  &data[0]
  );
}

Texture::Texture(std::string path)
{
  Texture& cachedTexture = FetchTexture(path);

  id = cachedTexture.id;
  width = cachedTexture.width;
  height = cachedTexture.height;
}

Texture& Texture::FetchTexture(std::string path)
{
  bool cached = _textureCache.find(path) != _textureCache.end();

  if(cached)
    return *_textureCache[path];

  int width, height, components;
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &components, 4);

  Texture* texture = new Texture(data, width, height);
  _textureCache[path] = texture;

  return *texture;
}