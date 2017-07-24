#include <glew.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <string>
#include <stdexcept>
#include <utility>
#include "font.hpp"
#include "rect.hpp"
#include "vector2.hpp"

using namespace Prova;

Font::Font(std::string path)
{
  LoadBDF(path);
}

void Font::LoadBDF(std::string path)
{
  std::ifstream file(path);
  
  if(!file.is_open())
    throw std::runtime_error("Failed to open file: " + path);

  std::vector<Bitmap> bitmaps;
  std::string line, keyword;
  int defaultWidth, defaultHeight, glyphCount;
  int glyphsAdded = 0, totalHeight = 0;
  Vector2 defaultOffset;
  Glyph glyph;

  while(std::getline(file, line))
  {
    std::istringstream words(line);
    std::getline(words, keyword, ' ');

    if(keyword == "STARTCHAR")
    {
      // reset glyph to default
      glyph.offset = defaultOffset;
      glyph.width = defaultWidth;
      glyph.height = defaultHeight;
    }
    else if(keyword == "ENCODING")
    {
      words >> glyph.encoding;
    }
    else if(keyword == "DWIDTH" || keyword == "DWIDTH1")
    {
      words >> glyph.shift.x;
      words >> glyph.shift.y;
    }
    else if(keyword == "BBX")
    {
      words >> glyph.width;
      words >> glyph.height;
      words >> glyph.offset.x;
      words >> glyph.offset.y;
    }
    else if(keyword == "BITMAP")
    {
      Bitmap bitmap = GetBitmapBDF(file, glyph.height);
      bitmaps[glyphsAdded] = bitmap;
    }
    else if(keyword == "ENDCHAR")
    {
      // copy this glyph to the glyph map
      glyphs.emplace(glyph.encoding, glyph);

      // add height to the total for later stitching/compression
      totalHeight += glyph.height;

      ++glyphsAdded;
    }
    // defaults
    else if(keyword == "FONTBOUNDINGBOX")
    {
      words >> defaultWidth;
      words >> defaultHeight;
      words >> defaultOffset.x;
      words >> defaultOffset.y;
    }
    else if(keyword == "CHARS")
    {
      words >> glyphCount;

      bitmaps.resize(glyphCount);
    }
  }

  file.close();
  
  totalHeight = totalHeight / sqrt(glyphCount) + 1;
  StitchTexture(bitmaps, totalHeight);
}

Font::Bitmap Font::GetBitmapBDF(std::ifstream& file, int height)
{
  Bitmap bitmap;
  std::string line;

  for(int i = 0; i < height; ++i)
  {
    if(!std::getline(file, line))
      throw std::runtime_error("Unexpected end of file while reading bitmap");
    
    int bytes = line.size() / 2;
    std::vector<unsigned char> row;
    row.reserve(bytes);

    // convert hex to byte and emplace
    for(int j = 0; j < bytes; ++j)
    {
      unsigned char byte = 0;
      
      for(int k = 0; k < 2; k++)
      {
        byte <<= 4;

        unsigned char c = line[j * 2 + k];

        if(c >= 'A' && c <= 'F')
          byte += c - 'A' + 10;
        else
          byte += c - '0';
      }

      row.emplace_back(byte);
    }

    bitmap.emplace_back(row);
  }

  return bitmap;
}

void Font::StitchTexture(std::vector<Bitmap>& glyphBitmaps, int height)
{
  int top = 0, left = 0, width = 0;
  Bitmap textureBitmap(height);
  auto glyphIt = glyphs.begin();

  for(Bitmap& glyphBitmap : glyphBitmaps)
  {
    int bitmapHeight = glyphBitmap.size();
    int bitmapWidth = glyphBitmap[0].size() * 8;

    // update glyph's clipping
    Glyph& glyph = (glyphIt++)->second;
    glyph.clip.left = left;
    glyph.clip.top = top;

    if(height < top + bitmapHeight)
    {
      // move the placement position to prevent overflow
      left = width;
      top = 0;
    }
    
    // resize the texture if the bitmap is overflowing
    if(width < left + bitmapWidth)
      width = left + bitmapWidth;

    // set texture data
    for(int i = 0; i < bitmapHeight; ++i)
    {
      std::vector<unsigned char>& textureRow = textureBitmap[top + i];
      std::vector<unsigned char>& glyphRow = glyphBitmap[i];

      // add empty space
      textureRow.resize(left * 4, 0);

      // loop through bytes
      for(int i = 0; i < bitmapWidth / 8; ++i)
      {
        unsigned char byte = glyphRow[i];
        
        // loop through bits
        for(int j = 7; j >= 0; --j)
        {
          bool bit = (byte >> j) & 1;

          // Fill the 4 RGBA channels
          for(int k = 0; k < 4; ++k)
            textureRow.emplace_back(bit ? 255 : 0);
        }
      }
    }

    // update position
    top += bitmapHeight;
  }

  // adjust glyph clipping to be percentage based
  // rather than pixel based
  for(auto& it : glyphs)
  {
    Glyph& glyph = it.second;

    glyph.clip.left /= width;
    glyph.clip.top /= height;
    glyph.clip.width = glyph.width / (float) width;
    glyph.clip.height = glyph.height / (float) height;

    glyph.clip.top = 1 - glyph.clip.top;
  }

  CreateTexture(textureBitmap, width, height);
}

void Font::CreateTexture(Bitmap& bitmap, int width, int height)
{
  std::vector<unsigned char> textureData;
  textureData.reserve(width * height * 4);

  // move data to a vector for continuous data
  for(auto it = bitmap.rbegin(); it != bitmap.rend(); ++it) 
  {
    std::vector<unsigned char>& row = *it;

    row.resize(width * 4, 0);
    textureData.insert(textureData.end(), row.begin(), row.end());
  }

  texture = Texture(&textureData[0], width, height);
}