#include "camera.hpp"

using namespace Prova;

Camera::Camera()
: scale(1,1,1) {}

Matrix Camera::GetTransform()
{
  Matrix transform = Matrix::Identity();
  transform = transform.Scale(scale);
  transform = transform.Translate(-position);
  transform = transform.RotateY(rotation.y);
  transform = transform.RotateX(rotation.x);
  transform = transform.RotateZ(rotation.z);
  transform = transform.Translate(width / 2, height / 2, 0);
  
  return transform;
}

Matrix Camera::GetProjection()
{
  if(projection == Projection::Orthographic)
    return Matrix::Ortho(0, width, 0, height, -1, 1000);
  return Matrix::Perspective(width, height, 90);
}