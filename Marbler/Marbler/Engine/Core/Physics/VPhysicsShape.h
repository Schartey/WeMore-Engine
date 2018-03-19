#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include "VPhysics.h"

class VSceneComponent;

class VPhysicsShape
{
public:

	VPhysicsShape();

	void GenerateBasicPhysicsShape(VSceneComponent* SceneComponent, PxBoxGeometry Geometry, PxMaterial* Material);
	
	PxShape* GetShape() { return Shape; }
	void SetTransformationMatrix(glm::mat4 TransformationMatrix);

	~VPhysicsShape();

private:
	VPhysics * Physics;

	VSceneComponent* SceneComponent;

	PxShape* Shape;
};

