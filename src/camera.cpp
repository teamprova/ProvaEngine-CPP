#include "camera.hpp"

Camera::Camera()
 : scale(1,1,1) {}

Matrix Camera::GetTransform()
{
  Matrix transform = Matrix::Identity();
  transform = transform.Scale(scale);
  transform = transform.Translate(position);
  transform = transform.RotateY(rotation.y);
  transform = transform.RotateX(rotation.x);
  transform = transform.RotateZ(rotation.z);
  
  return transform;
}