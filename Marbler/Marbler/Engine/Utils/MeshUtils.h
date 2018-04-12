#pragma once

#include "../Core/Asset/VMesh.h"

class MeshUtils
{
public:
	MeshUtils();

	static VMesh* CreateCubeGeometry(float width, float height, float depth);
	static VMesh* CreateCylinderGeometry(unsigned int segments, float height, float radius);
	static VMesh* CreateSphereGeometry(unsigned int longitudeSegments, unsigned int latitudeSegments, float radius);

	~MeshUtils();
};

