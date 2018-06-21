#include "VFrustum.h"

#include <iostream>


VFrustum::VFrustum()
{
}

void VFrustum::setCamInternals(float angle, float ratio, float nearD, float farD) {

	// store the information
	this->ratio = ratio;
	this->nearD = nearD;
	this->farD = farD;

	// compute width and height of the near section
	tang = glm::tan(glm::radians<float>(angle));
	nearHeight = nearD * tang;
	nearWidth = nearHeight * ratio;
	farHeight = farD * tang;
	farWidth = farHeight * ratio;
}

void VFrustum::setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u) {

	auto Z = glm::normalize(p - l);
	auto X = glm::normalize(glm::cross(u, Z));
	auto Y = glm::cross(Z, X);

	auto nc = p - Z * nearD;
	auto fc = p - Z * farD;

	auto ntl = nc + Y * nearHeight - X * nearWidth;
	auto ntr = nc + Y * nearHeight + X * nearWidth;
	auto nbl = nc - Y * nearHeight - X * nearWidth;
	auto nbr = nc - Y * nearHeight + X * nearWidth;

	auto ftl = fc + Y * farHeight - X * farWidth;
	auto ftr = fc + Y * farHeight + X * farWidth;
	auto fbl = fc - Y * farHeight - X * farWidth;
	auto fbr = fc - Y * farHeight + X * farWidth;

	frustumPlanes[VFC_TOP].set3Points(ntr, ntl, ftl);
	frustumPlanes[VFC_BOTTOM].set3Points(nbl, nbr, fbr);
	frustumPlanes[VFC_LEFT].set3Points(ntl, nbl, fbl);
	frustumPlanes[VFC_RIGHT].set3Points(nbr, ntr, fbr);
	frustumPlanes[VFC_NEARP].set3Points(ntl, ntr, nbr);
	frustumPlanes[VFC_FARP].set3Points(ftr, ftl, fbl);
}

int VFrustum::pointInFrustum(glm::vec3 p) {

	auto result = F_INSIDE;
	for (auto i = 0; i < 6; i++) {

		if (frustumPlanes[i].distance(p) < 0)
		{
			std::cout << i << std::endl;
			return F_OUTSIDE;
		}
	}
	return result;
}

VFrustum::~VFrustum()
{
}
