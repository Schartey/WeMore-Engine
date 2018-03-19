#include "VPhysicsShape.h"

#include "../Components/VSceneComponent.h"

VPhysicsShape::VPhysicsShape()
{
	Physics = VPhysics::GetInstance();
}

void VPhysicsShape::GenerateBasicPhysicsShape(VSceneComponent* SceneComponent, PxBoxGeometry Geometry, PxMaterial* Material)
{
	Shape = Physics->GetPxPhysics()->createShape(Geometry, *Material);
	if (Shape != nullptr)
	{
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(SceneComponent->GetTransformationMatrix(), scale, rotation, translation, skew, perspective);
		//Shape->setLocalPose(PxTransform(PxVec3(translation.x, translation.y, translation.z), PxQuat(rotation.x, rotation.y, rotation.z, rotation.w)));
	}
}

void VPhysicsShape::SetTransformationMatrix(glm::mat4 TransformationMatrix)
{
	if (Shape != nullptr)
	{
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(TransformationMatrix, scale, rotation, translation, skew, perspective);
		//Shape->setLocalPose(PxTransform(PxVec3(translation.x, translation.y, translation.z), PxQuat(rotation.x, rotation.y, rotation.z, rotation.w)));
	}
}

VPhysicsShape::~VPhysicsShape()
{
}
