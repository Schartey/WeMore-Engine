#include "PhysxUtils.h"

PhysxUtils::PhysxUtils()
{
}

PxTransform PhysxUtils::ConvertGTransformToPxTransform(glm::mat4 Transform)
{
	glm::vec3 scale;
	glm::quat Rotation;
	glm::vec3 Translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(Transform, scale, Rotation, Translation, skew, perspective);

	return PxTransform(PxVec3(Translation.x, Translation.y, Translation.z), PxQuat(Rotation.x, Rotation.y, Rotation.z, Rotation.w));
}

PxTransform PhysxUtils::ConvertGVecQuatToPxTransform(vec3 Position, quat Rotation)
{
	return PxTransform(PxVec3(Position.x, Position.y, Position.z), PxQuat(Rotation.x, Rotation.y, Rotation.z, Rotation.w));
}

void PhysxUtils::ConvertPxTransformToGVecQuat(PxTransform Transform, vec3 &Position, quat &Rotation)
{
	Position.x = Transform.p.x;
	Position.y = Transform.p.y;
	Position.z = Transform.p.z;

	Rotation.x = Transform.q.x;
	Rotation.y = Transform.q.y;
	Rotation.z = Transform.q.z;
	Rotation.w = Transform.q.w;
}

PxVec3 PhysxUtils::ConvertGVec3ToPxVec3(glm::vec3 Vector)
{
	return PxVec3(Vector.x, Vector.y, Vector.z);
}


PhysxUtils::~PhysxUtils()
{
}
