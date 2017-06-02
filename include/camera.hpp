#pragma once
#include "matrix.hpp"
#include "vector3.hpp"

class Vector3;

class Camera
{
  public:
    Camera();
    Matrix projection = Matrix::Ortho(0, 800, 600, 0, -1, 1);
    Vector3 scale;
    Vector3 position;
    Vector3 rotation;
    Matrix GetTransform();
};