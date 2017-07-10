#pragma once
#include <random>

namespace Prova
{
  class Math
  {
    public:
      static float RandomF(float min, float max);
      static int RandomI(int min, int max);
    private:
      static std::default_random_engine _randomEngine;
      static std::uniform_real_distribution<float> _randomFunction;
  };
}