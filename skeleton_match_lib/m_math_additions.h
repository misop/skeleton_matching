#pragma once
#include <m_math.h>
#include <glm\glm.hpp>

typedef CVector4 Quaternion;
typedef CVector3 CPoint;

CPoint TransformCPoint(CPoint u, glm::mat4 M);
glm::mat4 AddRotation(glm::mat4 M, CVector4 axisAngle, CPoint center);

float Length(CVector3 v);
bool IsZeroLength(CVector3 v);

float QuaternionNorm(Quaternion q);
Quaternion QuaternionNormalize(Quaternion q);
Quaternion QuaternionFromAngleAxis(float angle, CVector3 axis);
Quaternion MPQuaternionBetweenVectors(CVector3 start, CVector3 dest, CVector3 fallbackAxis = CVector3());