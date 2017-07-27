#pragma once
#include "matrix.hpp"
#include "vector3.hpp"

namespace Prova
{
  class Vector3;

  enum class SortingMethod { Z, Distance };
  enum class Projection { Perspective, Orthographic };

  class Camera
  {
    public:
      Camera();
      Projection projection = Projection::Perspective;
      SortingMethod sortingMethod = SortingMethod::Distance;
      bool useDepthBuffer = true;
      bool resolutionDependent = false;
      float zNear = -100;
      float zFar = 100;
      
      // for orthographic projection and UI
      float width = 1;
      float height = 1;
      // for perspective projection
      float FOV = 90;

      Vector3 scale;
      Vector3 position;
      Vector3 rotation;
      Matrix GetTransform();
      Matrix GetProjection();
      Matrix GetUIMatrix();
  };
}