// we only support bdf as of now, may change in the future
#pragma once
#include <map>
#include <string>
#include <vector>
#include "rect.hpp"
#include "texture.hpp"
#include "vector2.hpp"

namespace Prova
{
  class Glyph
  {
    public:
      int encoding;
      int width;
      int height;
      // clip to crop the glyph from the font texture
      Rect clip;
      // offset to render the current glyph
      Vector2 offset;
      // offset to render the next glyph
      Vector2 shift;
  };

  class Font
  {
    typedef std::vector<std::vector<unsigned char>> Bitmap;

    public:
      Font(std::string path);
      std::map<int, Glyph> glyphs;
      Texture texture;
    private:
      void LoadBDF(std::string path);
      Bitmap GetBitmapBDF(std::ifstream& file, int height);
      void StitchTexture(std::vector<Bitmap>& glyphBitmaps, int height);
      void CreateTexture(Bitmap& bitmap, int width, int height);
  };
}