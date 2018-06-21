#pragma once

#include "glm/glm.hpp"

class Plane
{
public:

	glm::vec3 normal, point;
	float d;


	Plane(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3)
	{
		set3Points(v1, v2, v3);
	}
	Plane(void)
	{
		d = 0;
	}
	~Plane()
	{

	}

	void set3Points(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3)
	{
		glm::vec3 aux1, aux2;

		aux1 = v1 - v2;
		aux2 = v3 - v2;

		normal = glm::normalize(glm::cross(aux2, aux1));
		point = v2;

		d = -dot(normal, point);
	}
	void setNormalAndPoint(glm::vec3 normal, glm::vec3 point)
	{

		this->normal = glm::normalize(normal);
		d = -glm::dot(this->normal, point);
	}
	float distance(glm::vec3 &p) const
	{
		return d + glm::dot(normal, p);
	}
};

class VFrustum
{
public:

	enum {
		VFC_TOP = 0,
		VFC_BOTTOM,
		VFC_LEFT,
		VFC_RIGHT,
		VFC_NEARP,
		VFC_FARP
	};


	enum FRUSTUM_COLLISION
	{
		F_OUTSIDE,
		F_INTERSECT,
		F_INSIDE
	};

	Plane frustumPlanes[6];

	glm::vec3 cc; // camera position
	glm::vec3 X, Y, Z; // the camera referential
	float nearD, farD, nearHeight, nearWidth, farHeight, farWidth, ratio, tang;


	VFrustum();
	~VFrustum();

	void setCamInternals(float angle, float ratio, float nearD, float farD);
	void setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u);
	int pointInFrustum(glm::vec3 p);
};

