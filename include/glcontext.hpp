#pragma once

namespace Prova
{
  class GLContext
  {
    public:
      void* handle;
      GLContext(void* window);
      ~GLContext();
  };
}