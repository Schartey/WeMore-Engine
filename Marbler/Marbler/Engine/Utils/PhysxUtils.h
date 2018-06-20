#pragma once

#include "foundation/PxTransform.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"

using namespace physx;
using namespace glm;

class PhysxUtils
{
public:
	PhysxUtils();

	static PxTransform ConvertGTransformToPxTransform(mat4 Transform);
	static PxTransform ConvertGVecQuatToPxTransform(vec3 Position, quat Rotation);
	static void ConvertPxTransformToGVecQuat(PxTransform Transform, vec3 &Position, quat &Rotation);
	static PxQuat ConvertGVecQuatToPxQuat(quat Rotation);
	static PxVec3 ConvertGVec3ToPxVec3(glm::vec3 Vector);
	static glm::vec3 ConvertPxVec3ToGVec3(PxVec3 Vector);
	~PhysxUtils();
};

