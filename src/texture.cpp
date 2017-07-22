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
  width = 0;
  height = 0;
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
    0
  );

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture->width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture->height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  return texture;
}