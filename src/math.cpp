#include <random>
#include "math.hpp"

using namespace Prova;

std::default_random_engine Math::_randomEngine = std::default_random_engine(std::random_device()());
std::uniform_real_distribution<float> Math::_randomFunction = std::uniform_real_distribution<float>(0, 1);

float Math::RandomF(float min, float max)
{
  float range = max - min;
  return _randomFunction(_randomEngine) * range + min;
}

int Math::RandomI(int min, int max)
{
  return (int) RandomF(min, max + 1);
}