#include "stdafx.h"
#include "m_math_additions.h"

CVector3 TransformCPoint(CVector3 u, glm::mat4 M) {
	glm::vec4 v(u.x, u.y, u.z, 1.0);
	glm::vec4 r = M * v;
	return CPoint(r.x, r.y, r.z);
}

glm::mat4 AddRotation(glm::mat4 M, CVector4 axisAngle, CPoint center) {
	if (IsZeroLength(CVector3(axisAngle.i, axisAngle.j, axisAngle.k))) return M;

	glm::vec3 c(center.x, center.y, center.z);
	glm::vec3 axis(axisAngle.i, axisAngle.j, axisAngle.k);
	float angle = axisAngle.s;
	//float angle = axisAngle.s*180.0f/M_PI;

	glm::mat4 T = glm::translate(glm::mat4(), -c);
	glm::mat4 R = glm::rotate(glm::mat4(), angle, axis);
	glm::mat4 TB = glm::translate(glm::mat4(), c);

	return TB * R * T * M;
}

/*float Length(CVector3 v) {
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

bool IsZeroLength(CVector3 v) {
	float sqlen = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return (sqlen < (1e-06 * 1e-06));
}*/

/*Quaternion QuaternionFromAngleAxis(float angle, CVector3 axis) {
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
	Quaternion q;

	float halfAngle = 0.5*angle;
	float fSin = sin(halfAngle);
	q.s = cos(halfAngle);
	q.i = fSin*axis.x;
	q.j = fSin*axis.y;
	q.k = fSin*axis.z;

	return q;
}*/

Quaternion MPQuaternionBetweenVectors(CVector3 start, CVector3 dest, CVector3 fallbackAxis) {
	// Based on Stan Melax's article in Game Programming Gems
	Quaternion q;
	// Copy, since cannot modify local
	CVector3 v0 = Normalize(start);
	CVector3 v1 = Normalize(dest);

	float d = Dot(v0, v1);
	// If dot == 1, vectors are the same
	if (d >= 1.0f) {
		return q;
	}
	if (d < (1e-6f - 1.0f)) {
		if (fallbackAxis != CVector3()) {
			// rotate 180 degrees about the fallback axis
			q = QuaternionFromAngleAxis(M_PI, fallbackAxis);
		} else {
			// Generate an axis
			CVector3 axis = Cross(CVector3(1, 0, 0), v0);
			if (IsZeroLength(axis)) { // pick another if colinear
				axis = Cross(CVector3(0, 1, 0), v0);
			}
			axis = Normalize(axis);
			q = QuaternionFromAngleAxis(M_PI, axis);
		}
	} else {//alpha from dot product, axis from cross product
		float s = sqrtf((1+d)*2);
		float invs = 1 / s;

		CVector3 c = Cross(v0, v1);

		q.i = c.x * invs;
		q.j = c.y * invs;
		q.k = c.z * invs;
		q.s = s * 0.5f;
		QuaternionNormalize(q);
	}

	return q;
}