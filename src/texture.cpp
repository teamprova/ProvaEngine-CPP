#include <glew.h>
#include <gl.h>
#include <SOIL.h>
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
  Texture* cachedTexture = FetchTexture(path);

  id = cachedTexture->id;
  width = cachedTexture->width;
  height = cachedTexture->height;
}

Texture* Texture::FetchTexture(std::string path)
{
  bool cached = _textureCache.count(path) == 1;

  if(cached)
    return _textureCache[path];

  Texture* texture = _textureCache[path] = new Texture();

  texture->id = SOIL_load_OGL_texture(
    path.c_str(),
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture->width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture->height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  return texture;
}