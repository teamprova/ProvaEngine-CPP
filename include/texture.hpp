#pragma once
#include <unordered_map>
#include <string>

namespace Prova
{
  class Texture
  {
    public:
      Texture();
      Texture(unsigned char data[], int width, int height);
      Texture(std::string path);
      unsigned int id;
      int width;
      int height;
    private:
      static std::unordered_map<std::string, Texture*> _textureCache;
      Texture& FetchTexture(std::string path);
  };
}