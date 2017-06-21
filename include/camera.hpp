#pragma once
#include "matrix.hpp"
#include "vector3.hpp"

namespace SortingMethod
{
  enum SortingMethod { Z, Distance };
}

namespace Projection
{
  enum Projection { Perspective, Orthographic };
}

namespace Prova
{
  class Vector3;

  class Camera
  {
    public:
      Camera();
      Projection::Projection projection = Projection::Perspective;
      SortingMethod::SortingMethod sortingMethod = SortingMethod::Distance;
      bool useDepthBuffer = true;
      
      // for orthographic
      int width = 800;
      int height = 600;
      // for perspective
      float FOV = 90;

      float zNear = -100;
      float zFar = 100;
      Vector3 scale;
      Vector3 position;
      Vector3 rotation;
      Matrix GetTransform();
      Matrix GetProjection();
  };
}