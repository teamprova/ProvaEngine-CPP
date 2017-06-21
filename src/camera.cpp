#include "camera.hpp"

using namespace Prova;

Camera::Camera()
: scale(1,1,1) {}

Matrix Camera::GetTransform()
{
  Matrix transform = Matrix::Identity();
  transform = transform.Translate(-position);
  transform = transform.Scale(scale);
  transform = transform.RotateY(rotation.y);
  transform = transform.RotateX(rotation.x);
  transform = transform.RotateZ(rotation.z);
  
  return transform;
}

Matrix Camera::GetProjection()
{
  if(projection == Projection::Orthographic)
    return Matrix::Ortho(-width/2, width/2, -height/2, height/2, zNear, zFar);
  return Matrix::Perspective(width, height, zNear, zFar, FOV);
}