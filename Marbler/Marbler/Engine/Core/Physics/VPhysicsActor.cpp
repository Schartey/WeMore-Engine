#include "VPhysicsActor.h"

#include<glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../VActor.h"

VPhysicsActor::VPhysicsActor()
{
	this->Physics = VPhysics::GetInstance();
}

void VPhysicsActor::CreateRigidBody(VActor* Actor)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(Actor->GetTransformationMatrix(), scale, rotation, translation, skew, perspective);

	this->RigidBody = this->Physics->GetPxPhysics()->createRigidDynamic(PxTransform(PxVec3(translation.x, translation.y, translation.z), PxQuat(rotation.x, rotation.y, rotation.z, rotation.w)));
}
void VPhysicsActor::AttachPhysicsShape(VPhysicsShape* PhysicsShape)
{
	this->RigidBody->attachShape(*PhysicsShape->GetShape());
}

PxRigidDynamic* VPhysicsActor::GetRigidBody()
{
	return this->RigidBody;
}

void VPhysicsActor::SetRigidBody(PxRigidDynamic* RigidBody)
{
	this->RigidBody = RigidBody;
}

glm::mat4 VPhysicsActor::GetTransformation()
{
	PxTransform transform = this->RigidBody->getGlobalPose();

	glm::mat4 glTransform = glm::translate(glm::mat4(glm::toMat4(glm::quat(transform.q.x, transform.q.y, transform.q.z, transform.q.w))), glm::vec3(transform.p.x, transform.p.y, transform.p.z));

	return glTransform;
}

VPhysicsActor::~VPhysicsActor()
{
}
