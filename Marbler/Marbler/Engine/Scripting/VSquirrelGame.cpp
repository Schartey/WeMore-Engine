#include "VSquirrelGame.h"

#include <string>

#include "../Core/Asset/VTextureCube.h"
#include "../Core/Components/VParticleComponent.h"
#include "../Core/Components/VInputComponent.h"
#include "../Core/Components/VCameraComponent.h"
#include "../GUI/Widgets/VTextWidget.h"
#include "../GUI/Widgets/VImageWidget.h"
#include "../Core/VDebugStatics.h"

VGame* VSquirrelGame::Game = 0;
VLogger* VSquirrelGame::Logger = 0;

SQInteger func_createScene(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	int id = -1;
	if (sq_gettype(v, 2) == OT_STRING)
	{
		const SQChar* name = "";

		if (sq_getstring(v, 2, &name) == 0)
		{
			id = VSquirrelGame::Game->GetObjectPool()->CreateScene(std::string(name));
			VSquirrelGame::Logger->Info("Squirrel", "Created Scene " + id);
			//printf("Created Scene %i", id);
			//printf("\n");
		}
	}
	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setActiveScene(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	bool success = false;

	if (sq_gettype(v, 2) == OT_INTEGER)
	{
		SQInteger id = -1;

		if (sq_getinteger(v, 2, &id) == 0)
		{
			VSquirrelGame::Game->SetActiveScene(VSquirrelGame::Game->GetObjectPool()->GetSceneById(id));
			std::string name = VSquirrelGame::Game->GetActiveScene()->GetName();
			VSquirrelGame::Logger->Info("Squirrel", "Active Scene " + name);
			//printf("Active Scene: %s", name.c_str());
			//printf("\n");

			sq_pushbool(v, true);
			return 1; //1 because 1 value is returned
		}
	}

	sq_pushbool(v, false);
	return 1; //1 because 1 value is returned
}

SQInteger func_createActor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	int id = -1;
	const SQChar* name = "";
	SQBool physics = false;
	SQBool rigidStatic = false;
	//Keep it simple for now, make tables later
	SQFloat posX = 0;
	SQFloat posY = 0;
	SQFloat posZ = 0;
	SQFloat rotX = 0;
	SQFloat rotY = 0;
	SQFloat rotZ = 0;

	bool success = true;

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		if (sq_gettype(v, 3) == OT_BOOL && sq_getbool(v, 3, &physics) == 0)
		{
			if (sq_gettype(v, 4) == OT_BOOL && sq_getbool(v, 4, &rigidStatic) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &posX) == 0)
				{
					if (sq_gettype(v, 6) == OT_FLOAT && sq_getfloat(v, 6, &posY) == 0)
					{
						if (sq_gettype(v, 7) == OT_FLOAT && sq_getfloat(v, 7, &posZ) == 0)
						{
							if (sq_gettype(v, 8) == OT_FLOAT && sq_getfloat(v, 8, &rotX) == 0)
							{
								if (sq_gettype(v, 9) == OT_FLOAT && sq_getfloat(v, 9, &rotY) == 0)
								{
									if (sq_gettype(v, 10) == OT_FLOAT && sq_getfloat(v, 10, &rotZ) == 0)
									{
										VActor* Actor = VSquirrelGame::Game->GetActiveScene()->CreateActor(name);
										Actor->bPhysics = physics;

										if (physics)
										{
											if (rigidStatic)  { 
												Actor->SetRigidStatic();
											}
											else {
												PxRigidDynamic* RigidDynamic = Actor->SetRigidDynamic();
												RigidDynamic->setMass(0.1f);
											}
										}

										Actor->SetPosition(glm::vec3(posX, posY, posZ));
										Actor->SetRotation(glm::vec3(rotX, rotY, rotZ));

										id = VSquirrelGame::Game->GetObjectPool()->AddSceneObject(Actor);
										VSquirrelGame::Logger->Info("Squirrel", "Created Actor: " + Actor->GetName());
										//printf("Created Actor: %s", Actor->GetName().c_str());
										//printf("\n");

									}
								}
							}
						}
					}
				}
			}
		}
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_getSceneObjectPosition(HSQUIRRELVM v)
{
	SQInteger id = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(id);

		sq_pushstring(v, "position", -1); //2
		sq_newtable(v);
		sq_pushstring(v, "x", -1);
		sq_pushfloat(v, SceneObject->GetPosition().x);
		sq_newslot(v, -3, SQTrue);
		sq_pushstring(v, "y", -1);
		sq_pushfloat(v, SceneObject->GetPosition().y);
		sq_newslot(v, -3, SQTrue);
		sq_pushstring(v, "z", -1);
		sq_pushfloat(v, SceneObject->GetPosition().z);
		sq_newslot(v, -3, SQTrue);

		return 1;
	}

	sq_pushinteger(v, -1);
	return 1;
}

SQInteger func_getSceneObjectRotation(HSQUIRRELVM v)
{
	SQInteger id = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(id);

		glm::vec3 eulerAngles = glm::degrees<float>(glm::eulerAngles(SceneObject->GetRotation()));

		sq_pushstring(v, "rotation", -1); //2
		sq_newtable(v);
		sq_pushstring(v, "x", -1);
		sq_pushfloat(v, eulerAngles.x);
		sq_newslot(v, -3, SQTrue);
		sq_pushstring(v, "y", -1);
		sq_pushfloat(v, eulerAngles.y);
		sq_newslot(v, -3, SQTrue);
		sq_pushstring(v, "z", -1);
		sq_pushfloat(v, eulerAngles.z);
		sq_newslot(v, -3, SQTrue);

		return 1;
	}

	sq_pushinteger(v, -1);
	return 1;
}

SQInteger func_setSceneObjectPosition(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat posx = 0.0f;
	SQFloat posy = 0.0f;
	SQFloat posz = 0.0f;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &posx) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &posy) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &posz) == 0)
				{
					VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(id);

					if (SceneObject != nullptr)
					{
						SceneObject->SetPosition(glm::vec3(posx, posy, posz));

						sq_pushbool(v, true); //push the number of arguments as return value
						return 1; //1 because 1 value is returned
					}
				}
			}
		}
	}

	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setSceneObjectRotationDeg(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat rotx = 0.0f;
	SQFloat roty = 0.0f;
	SQFloat rotz = 0.0f;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &rotx) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &roty) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &rotz) == 0)
				{
					VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(id);

					if (SceneObject != nullptr)
					{
						SceneObject->SetRotationDeg(glm::vec3(rotx, roty, rotz));

						sq_pushbool(v, true); //push the number of arguments as return value
						return 1; //1 because 1 value is returned
					}
				}
			}
		}
	}

	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setMeshComponentScale(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat scaleX = 0.0f;
	SQFloat scaleY = 0.0f;
	SQFloat scaleZ = 0.0f;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &scaleX) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &scaleY) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &scaleZ) == 0)
				{
					VMeshComponent* MeshComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VMeshComponent>(id);

					if (MeshComponent != nullptr)
					{
						MeshComponent->SetScale(glm::vec3(scaleX, scaleY, scaleZ));

						sq_pushbool(v, true); //push the number of arguments as return value
						return 1; //1 because 1 value is returned
					}
				}
			}
		}
	}

	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_loadTexture(HSQUIRRELVM v)
{
	int id = -1;
	const SQChar* name = "";

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		VTexture* Texture = new VTexture(VSquirrelGame::Game->GetTexturePath() + name);
		Texture->Load();

		id = VSquirrelGame::Game->GetObjectPool()->AddTexture(Texture);
		VSquirrelGame::Logger->Info("Squirrel", "Created Texture: " + std::string(name));
		//printf("Created Texture: %s", name);
		//printf("\n");
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setMeshMaterial(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat specularR = 0;
	SQFloat specularG = 0;
	SQFloat specularB = 0;
	SQFloat specularIntensity = 0;
	SQFloat specularPower = 0;
	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VMeshComponent* MeshComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VMeshComponent>(id);
		if (MeshComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &specularR) == 0)
			{
				if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &specularG) == 0)
				{
					if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &specularB) == 0)
					{
						if (sq_gettype(v, 6) == OT_FLOAT && sq_getfloat(v, 6, &specularIntensity) == 0)
						{
							if (sq_gettype(v, 7) == OT_FLOAT && sq_getfloat(v, 7, &specularPower) == 0)
							{
								MeshComponent->GetMaterial()->SetSpecularColor(glm::vec3(specularR, specularG, specularB));
								MeshComponent->GetMaterial()->SetSpecularIntensity(specularIntensity);
								MeshComponent->GetMaterial()->SetSpecularPower(specularPower);

								sq_pushbool(v, SQTrue); //push the number of arguments as return value
								return 1; //1 because 1 value is returned
							}
						}
					}
				}
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setMeshTexture(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQInteger textureId = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VMeshComponent* MeshComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VMeshComponent>(id);
		if (MeshComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_INTEGER && sq_getinteger(v, 3, &textureId) == 0)
			{
				VTexture* Texture = VSquirrelGame::Game->GetObjectPool()->GetTexture(textureId);

				if (Texture != nullptr)
				{
					MeshComponent->GetMaterial()->AddDiffuseTexture(Texture);
					sq_pushbool(v, SQTrue); //push the number of arguments as return value
					return 1; //1 because 1 value is returned
				}

			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setMeshLightTexture(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQInteger textureId = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VMeshComponent* MeshComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VMeshComponent>(id);
		if (MeshComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_INTEGER && sq_getinteger(v, 3, &textureId) == 0)
			{
				VTexture* Texture = VSquirrelGame::Game->GetObjectPool()->GetTexture(textureId);

				if (Texture != nullptr)
				{
					MeshComponent->GetMaterial()->AddLightMapTexture(Texture);
					sq_pushbool(v, SQTrue); //push the number of arguments as return value
					return 1; //1 because 1 value is returned
				}

			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setMeshSpecularTexture(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQInteger textureId = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VMeshComponent* MeshComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VMeshComponent>(id);
		if (MeshComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_INTEGER && sq_getinteger(v, 3, &textureId) == 0)
			{
				VTexture* Texture = VSquirrelGame::Game->GetObjectPool()->GetTexture(textureId);

				if (Texture != nullptr)
				{
					MeshComponent->GetMaterial()->SetSpecularMapTexture(Texture);
					sq_pushbool(v, SQTrue); //push the number of arguments as return value
					return 1; //1 because 1 value is returned
				}

			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setActorMass(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat mass = 0;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VActor* Actor = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VActor>(id);
		if (Actor != nullptr)
		{
			if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &mass) == 0)
			{
				PxRigidActor* RigidActor = Actor->GetRigidActor();
				PxRigidDynamic* RigidDynamic = (PxRigidDynamic*)(Actor->GetRigidActor());
				RigidDynamic->setMass(mass);
				sq_pushbool(v, SQTrue); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setInputMovementSpeed(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat speed = 0.0f;


	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VInputComponent* InputComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VInputComponent>(id);

		if (InputComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &speed) == 0)
			{
				InputComponent->SetMovementSpeed(speed);
				sq_pushbool(v, SQTrue); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setInputJumpForce(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat force = 0.0f;


	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VInputComponent* InputComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VInputComponent>(id);

		if (InputComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &force) == 0)
			{
				InputComponent->SetJumpForce(force);
				sq_pushbool(v, SQTrue); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setInputMaxSpeed(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat maxSpeed = 7.0f;


	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VInputComponent* InputComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VInputComponent>(id);

		if (InputComponent != nullptr)
		{
			if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &maxSpeed) == 0)
			{
				InputComponent->SetMaxSpeed(maxSpeed);
				sq_pushbool(v, SQTrue); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_restrictActorMotionLinear(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQBool rX = false;
	SQBool rY = false;
	SQBool rZ = false;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VActor* Actor = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VActor>(id);
		if (Actor != nullptr)
		{
			if (sq_gettype(v, 3) == OT_BOOL && sq_getbool(v, 3, &rX) == 0)
			{
				if (sq_gettype(v, 4) == OT_BOOL && sq_getbool(v, 4, &rY) == 0)
				{
					if (sq_gettype(v, 5) == OT_BOOL && sq_getbool(v, 5, &rZ) == 0)
					{
						Actor->RestrictMotionLinear(rX, rY, rZ);

						sq_pushbool(v, SQTrue); //push the number of arguments as return value
						return 1; //1 because 1 value is returned
					}
				}
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_restrictActorMotionAngular(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQBool rX = false;
	SQBool rY = false;
	SQBool rZ = false;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VActor* Actor = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VActor>(id);
		if (Actor != nullptr)
		{
			if (sq_gettype(v, 3) == OT_BOOL && sq_getbool(v, 3, &rX) == 0)
			{
				if (sq_gettype(v, 4) == OT_BOOL && sq_getbool(v, 4, &rY) == 0)
				{
					if (sq_gettype(v, 5) == OT_BOOL && sq_getbool(v, 5, &rZ) == 0)
					{
						Actor->RestrictMotionAngular(rX, rY, rZ);

						sq_pushbool(v, SQTrue); //push the number of arguments as return value
						return 1; //1 because 1 value is returned
					}
				}
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_attachComponentToSceneObject(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQInteger sceneComponentId = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VSceneComponent* SceneComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VSceneComponent>(id);
		if (SceneComponent != nullptr)
		{
			if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 3, &sceneComponentId) == 0)
			{
				VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(sceneComponentId);

				if (SceneObject != nullptr)
				{
					SceneObject->AddComponent(SceneComponent);
					sq_pushbool(v, SQTrue); //push the number of arguments as return value
					return 1; //1 because 1 value is returned
				}
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createCameraComponent(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	int id = -1;
	const SQChar* name = "";
	//Keep it simple for now, make tables later
	SQFloat posX = 0;
	SQFloat posY = 0;
	SQFloat posZ = 0;
	SQFloat rotX = 0;
	SQFloat rotY = 0;
	SQFloat rotZ = 0;
	SQInteger parentId = 0;

	bool success = true;

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &posX) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &posY) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &posZ) == 0)
				{
					if (sq_gettype(v, 6) == OT_FLOAT && sq_getfloat(v, 6, &rotX) == 0)
					{
						if (sq_gettype(v, 7) == OT_FLOAT && sq_getfloat(v, 7, &rotY) == 0)
						{
							if (sq_gettype(v, 8) == OT_FLOAT && sq_getfloat(v, 8, &rotZ) == 0)
							{
								if (sq_gettype(v, 9) == OT_INTEGER && sq_getinteger(v, 9, &parentId) == 0)
								{
									VCameraComponent* CameraComponent = new VCameraComponent(VSquirrelGame::Game->GetActiveScene(), name);

									VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(parentId);

									SceneObject->AddComponent(CameraComponent);

									CameraComponent->SetProjectionMatrix(90.0f, VSquirrelGame::Game->GetWindow()->GetWidth(), VSquirrelGame::Game->GetWindow()->GetHeight(), 0.1f, 1000.0f);
									CameraComponent->SetPosition(glm::vec3(posX, posY, posZ));
									CameraComponent->SetRotation(glm::vec3(rotX, rotY, rotZ));

									id = VSquirrelGame::Game->GetObjectPool()->AddComponent(CameraComponent);
									VSquirrelGame::Logger->Info("Squirrel", "Created CameraComponent: " + CameraComponent->GetName());
									//printf("Created CameraComponent: %s", CameraComponent->GetName().c_str());
									//printf("\n");

									VSquirrelGame::Game->GetActiveScene()->SetActiveSceneObject(SceneObject);

									sq_pushinteger(v, id); //push the number of arguments as return value
									return 1; //1 because 1 value is returned
								}
							}
						}
					}
				}
			}
		}
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
	//Create CameraComponent
}

SQInteger func_setCameraTarget(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQInteger sceneComponentId = -1;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		VCameraComponent* CameraComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VCameraComponent>(id);
		if (CameraComponent != nullptr)
		{
			if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 3, &sceneComponentId) == 0)
			{
				VSceneComponent* SceneComponent = VSquirrelGame::Game->GetObjectPool()->GetComponent<VSceneComponent>(sceneComponentId);

				if (SceneComponent != nullptr)
				{
					CameraComponent->SetTarget(SceneComponent);

					sq_pushbool(v, SQTrue); //push the number of arguments as return value
					return 1; //1 because 1 value is returned
				}
			}
		}
	}
	sq_pushbool(v, SQFalse); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setDirectionalLight(HSQUIRRELVM v)
{
	//Set DirectionalLight, cannot be accessed later, just overriden...because too much work that has to be redone anways, directionallight is a mess right now
	VDirectionalLight* DirectionalLight = VSquirrelGame::Game->GetActiveScene()->CreateDirectionalLight(VSquirrelGame::Game->GetConfig()->getValue("brightness", "0.2f").asFloat());

	sq_pushbool(v, SQTrue); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createPointLight(HSQUIRRELVM v)
{
	int id = -1;

	float ambient;
	float diffuse;
	float AttenuationC;
	float AttenuationL;
	float AttenuationE;
	float Scale;
	float posX;
	float posY;
	float posZ;

	if (sq_gettype(v, 2) == OT_FLOAT && sq_getfloat(v, 2, &ambient) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &diffuse) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &AttenuationC) == 0)
			{
				if (sq_gettype(v, 5) == OT_FLOAT && sq_getfloat(v, 5, &AttenuationL) == 0)
				{
					if (sq_gettype(v, 6) == OT_FLOAT && sq_getfloat(v, 6, &AttenuationE) == 0)
					{
						if (sq_gettype(v, 7) == OT_FLOAT && sq_getfloat(v, 7, &Scale) == 0)
						{
							if (sq_gettype(v, 8) == OT_FLOAT && sq_getfloat(v, 8, &posX) == 0)
							{
								if (sq_gettype(v, 9) == OT_FLOAT && sq_getfloat(v, 9, &posY) == 0)
								{
									if (sq_gettype(v, 10) == OT_FLOAT && sq_getfloat(v, 10, &posZ) == 0)
									{
										//This has to be stored in the Object stuff
										VPointLight2* PointLight = VSquirrelGame::Game->GetActiveScene()->CreatePointLight("Pointlight");
										PointLight->GetLightComponent()->GetPointLight().Ambient = ambient;
										PointLight->GetLightComponent()->GetPointLight().Diffuse = diffuse;
										PointLight->GetLightComponent()->GetPointLight().Color = glm::vec3(1.0f, 1.0f, 1.0f);
										PointLight->GetLightComponent()->GetPointLight().Attenuation = VAttenuation(AttenuationC, AttenuationL, AttenuationE);

										PointLight->SetScale(glm::vec3(Scale));
										PointLight->SetPosition(glm::vec3(posX, posY, posZ));

										id = VSquirrelGame::Game->GetObjectPool()->AddSceneObject(PointLight);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createTextWidget(HSQUIRRELVM v)
{
	//Store this
	VTextWidget* TextWidget = new VTextWidget();
	TextWidget->GetTextElement()->SetText(Text("", 0.0f, 0.0f, 0.5f, glm::vec4(1, 1, 1, 1)));
	int id = VSquirrelGame::Game->GetGUI()->AddWidget(TextWidget);

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setTextWidgetText(HSQUIRRELVM v)
{
	SQInteger id = -1;
	const char* text;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_STRING && sq_getstring(v, 3, &text) == 0)
		{
			VTextWidget* TextWidget = (VTextWidget*)VSquirrelGame::Game->GetGUI()->GetWidgetById(id);
			TextWidget->GetTextElement()->GetText()->text = text;

			sq_pushbool(v, true); //push the number of arguments as return value
			return 1; //1 because 1 value is returned
		}
	}
	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setTextWidgetPosition(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQFloat posx;
	SQFloat posy;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_FLOAT && sq_getfloat(v, 3, &posx) == 0)
		{
			if (sq_gettype(v, 4) == OT_FLOAT && sq_getfloat(v, 4, &posy) == 0)
			{
				VTextWidget* TextWidget = (VTextWidget*)VSquirrelGame::Game->GetGUI()->GetWidgetById(id);
				TextWidget->GetTextElement()->GetText()->posX = posx;
				TextWidget->GetTextElement()->GetText()->posY = posy;

				sq_pushbool(v, true); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
			}
		}
	}
	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_setUserWidgetVisibility(HSQUIRRELVM v)
{
	SQInteger id = -1;
	SQBool visibility = false;

	if (sq_gettype(v, 2) == OT_INTEGER && sq_getinteger(v, 2, &id) == 0)
	{
		if (sq_gettype(v, 3) == OT_BOOL && sq_getbool(v, 3, &visibility) == 0)
		{
			VUserWidget* UserWidget = VSquirrelGame::Game->GetGUI()->GetWidgetById(id);
			UserWidget->SetVisibility(visibility);

			sq_pushbool(v, true); //push the number of arguments as return value
			return 1; //1 because 1 value is returned
		}
	}
	sq_pushbool(v, false); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createImageWidget(HSQUIRRELVM v)
{
	//Store this
	VTexture* BoostWidgetTexture = new VTexture(VSquirrelGame::Game->GetTexturePath() + "Widget/boost.png");
	BoostWidgetTexture->Load();

	VImageWidget* ImageWidget = new VImageWidget();
	ImageWidget->GetImageElement()->SetImage(BoostWidgetTexture);
	ImageWidget->GetImageElement()->SetSize(glm::vec2(50.0f, 50.0f));
	ImageWidget->GetImageElement()->SetPosition(glm::vec2(500.0f, 0.0f));
	int id = VSquirrelGame::Game->GetGUI()->AddWidget(ImageWidget);

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createMeshComponent(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	int id = -1;
	const SQChar* name = "";
	const SQChar* mesh = "";
	const SQChar* physicsShape = "";
	SQBool physics = false;
	//Keep it simple for now, make tables later
	SQFloat posX = 0;
	SQFloat posY = 0;
	SQFloat posZ = 0;
	SQFloat rotX = 0;
	SQFloat rotY = 0;
	SQFloat rotZ = 0;
	SQFloat scaleX = 0;
	SQFloat scaleY = 0;
	SQFloat scaleZ = 0;
	SQInteger parentId = 0;

	bool success = true;

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		if (sq_gettype(v, 3) == OT_STRING && sq_getstring(v, 3, &mesh) == 0)
		{
			if (sq_gettype(v, 4) == OT_STRING && sq_getstring(v, 4, &physicsShape) == 0)
			{
				if (sq_gettype(v, 5) == OT_BOOL && sq_getbool(v, 5, &physics) == 0)
				{
					if (sq_gettype(v, 6) == OT_FLOAT && sq_getfloat(v, 6, &posX) == 0)
					{
						if (sq_gettype(v, 7) == OT_FLOAT && sq_getfloat(v, 7, &posY) == 0)
						{
							if (sq_gettype(v, 8) == OT_FLOAT && sq_getfloat(v, 8, &posZ) == 0)
							{
								if (sq_gettype(v, 9) == OT_FLOAT && sq_getfloat(v, 9, &rotX) == 0)
								{
									if (sq_gettype(v, 10) == OT_FLOAT && sq_getfloat(v, 10, &rotY) == 0)
									{
										if (sq_gettype(v, 11) == OT_FLOAT && sq_getfloat(v, 11, &rotZ) == 0)
										{
											if (sq_gettype(v, 12) == OT_FLOAT && sq_getfloat(v, 12, &scaleX) == 0)
											{
												if (sq_gettype(v, 13) == OT_FLOAT && sq_getfloat(v, 13, &scaleY) == 0)
												{
													if (sq_gettype(v, 14) == OT_FLOAT && sq_getfloat(v, 14, &scaleZ) == 0)
													{
														if (sq_gettype(v, 15) == OT_INTEGER && sq_getinteger(v, 15, &parentId) == 0)
														{
															VMeshComponent* MeshComponent = new VMeshComponent(VSquirrelGame::Game->GetActiveScene(), name);

															VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(parentId);

															SceneObject->AddComponent(MeshComponent);

															MeshComponent->LoadMesh(VSquirrelGame::Game->GetModelPath() + mesh);

															if (strcmp(physicsShape, "Sphere") == 0)
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Sphere);
															}
															else if (strcmp(physicsShape, "Box") == 0)
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Box);
															}
															else if (strcmp(physicsShape, "Cylinder") == 0)
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
															}
															MeshComponent->SetBPhysics(physics);

															MeshComponent->SetPosition(glm::vec3(posX, posY, posZ));
															MeshComponent->SetRotation(glm::vec3(rotX, rotY, rotZ));
															MeshComponent->SetScale(glm::vec3(scaleX, scaleY, scaleZ));

															id = VSquirrelGame::Game->GetObjectPool()->AddComponent(MeshComponent);
															VSquirrelGame::Logger->Info("Squirrel", "Created MeshComponent: " + MeshComponent->GetName());
															//printf("Created MeshComponent: %s", MeshComponent->GetName().c_str());
															//printf("\n");


														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createSkybox(HSQUIRRELVM v)
{
	//This has to be stored in the Object stuff
	int id = 0;
	std::string path = VSquirrelGame::Game->GetTexturePath();
	VTextureCube* TextureCube = new VTextureCube(path + "5dim/5dim_bk.tga", path + "5dim/5dim_dn.tga", path + "5dim/5dim_ft.tga", path + "5dim/5dim_lf.tga", path + "5dim/5dim_rt.tga", path + "5dim/5dim_up.tga");
	TextureCube->Load();
	VSkybox* Skybox = VSquirrelGame::Game->GetActiveScene()->CreateSkybox("Skybox", TextureCube);

	id = VSquirrelGame::Game->GetObjectPool()->AddSceneObject(Skybox);

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createInputComponent(HSQUIRRELVM v)
{
	int id = 0;
	const SQChar* name = "";
	SQInteger parentId = 0;

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		if (sq_gettype(v, 3) == OT_INTEGER && sq_getinteger(v, 3, &parentId) == 0)
		{
			VInputComponent* InputComponent = new VInputComponent(VSquirrelGame::Game->GetActiveScene(), name);
			VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(parentId);
			SceneObject->AddComponent(InputComponent);

			id = VSquirrelGame::Game->GetObjectPool()->AddComponent(InputComponent);
		}
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createParticleComponent(HSQUIRRELVM v)
{
	int id = 0;
	const SQChar* name = "";
	SQInteger parentId = 0;

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		if (sq_gettype(v, 3) == OT_INTEGER && sq_getinteger(v, 3, &parentId) == 0)
		{
			VParticleComponent* ParticleComponent = new VParticleComponent(VSquirrelGame::Game->GetActiveScene(), name);
			VParticleDescriptor* ParticleDescriptor = new VParticleDescriptor();
			ParticleDescriptor->Count = 1000;
			ParticleDescriptor->Position = glm::vec3(0, 0, 0);
			ParticleDescriptor->Spread = 5;
			ParticleDescriptor->TTL = 500;
			ParticleDescriptor->Velocity = glm::vec3(0.1f);

			ParticleComponent->SetParticle(ParticleDescriptor);
			ParticleComponent->SetPosition(glm::vec3(0, 3.0f, 0.0f));

			VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(parentId);
			SceneObject->AddComponent(ParticleComponent);

			id = VSquirrelGame::Game->GetObjectPool()->AddComponent(ParticleComponent);
		}
	}

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_getFPS(HSQUIRRELVM v)
{
	float fps = VDebugStatics::GetFPS();

	sq_pushfloat(v, fps);
	return 1;
}

SQInteger func_getObjectsCount(HSQUIRRELVM v)
{
	sq_pushfloat(v, VDebugStatics::Objects);
	return 1;
}

SQInteger func_test_parameters(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
	
	if (sq_gettype(v, 2) == OT_STRING)
	{
		const SQChar* name = "";

		if (sq_getstring(v, 2, &name) == 0)
		{
			VSquirrelGame::Game->GetActiveScene()->CreateActor(std::string(name));
		}
	}
	
	for (SQInteger n = 1; n <= nargs; n++)
	{
		printf("arg %d is ", n);
		switch (sq_gettype(v, n))
		{
		case OT_NULL:
			printf("null");
			break;
		case OT_INTEGER:
			printf("integer");
			break;
		case OT_FLOAT:
			printf("float");
			break;
		case OT_STRING:
			printf("string");
			break;
		case OT_TABLE:
			printf("table");
			break;
		case OT_ARRAY:
			printf("array");
			break;
		case OT_USERDATA:
			printf("userdata");
			break;
		case OT_CLOSURE:
			printf("closure(function)");
			break;
		case OT_NATIVECLOSURE:
			printf("native closure(C function)");
			break;
		case OT_GENERATOR:
			printf("generator");
			break;
		case OT_USERPOINTER:
			printf("userpointer");
			break;
		case OT_CLASS:
			printf("class");
			break;
		case OT_INSTANCE:
			printf("instance");
			break;
		case OT_WEAKREF:
			printf("weak reference");
			break;
		default:
			return sq_throwerror(v, "invalid param"); //throws an exception
		}
	}
	printf("\n");
	sq_pushinteger(v, nargs); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const char *fname)
{
	sq_pushroottable(v);
	sq_pushstring(v, fname, -1);
	sq_newclosure(v, f, 0); //create a new function
	sq_newslot(v, -3, SQFalse);
	sq_pop(v, 1); //pops the root table

	return 1;
}

VSquirrelGame::VSquirrelGame(HSQUIRRELVM v, VGame* Game)
{
	this->v = v;
	this->Game = Game;
	this->Logger = VLogger::GetInstance();

	//Creation
	register_global_func(this->v, func_createScene, "createScene");
	register_global_func(this->v, func_setActiveScene, "setActiveScene");
	register_global_func(this->v, func_createActor, "createActor");
	register_global_func(this->v, func_createMeshComponent, "createMeshComponent");
	register_global_func(this->v, func_createInputComponent, "createInputComponent");
	register_global_func(this->v, func_createParticleComponent, "createParticleComponent");
	register_global_func(this->v, func_createSkybox, "createSkybox");

	//Asset Loading
	register_global_func(this->v, func_loadTexture, "loadTexture");

	//Getter
	register_global_func(this->v, func_getSceneObjectPosition, "getSceneObjectPosition");
	register_global_func(this->v, func_getSceneObjectRotation, "getSceneObjectRotation");
	
	//Setter
	//Material
	register_global_func(this->v, func_setMeshMaterial, "setMeshMaterial");
	register_global_func(this->v, func_setMeshTexture, "setMeshTexture");
	register_global_func(this->v, func_setMeshLightTexture, "setMeshLightTexture");
	register_global_func(this->v, func_setMeshSpecularTexture, "setMeshSpecularTexture");

	//PhysX
	register_global_func(this->v, func_setActorMass, "setActorMass");
	register_global_func(this->v, func_setInputMovementSpeed, "setInputMovementSpeed");
	register_global_func(this->v, func_setInputJumpForce, "setInputJumpForce");
	register_global_func(this->v, func_setInputMaxSpeed, "setInputMaxSpeed");
	register_global_func(this->v, func_restrictActorMotionLinear, "restrictActorMotionLinear");
	register_global_func(this->v, func_restrictActorMotionAngular, "restrictActorMotionAngular");
	
	//Debug
	register_global_func(this->v, func_getFPS, "getFPS");
	register_global_func(this->v, func_getObjectsCount, "getObjectsCount");

	register_global_func(this->v, func_setTextWidgetText, "setTextWidgetText");
	register_global_func(this->v, func_setUserWidgetVisibility, "setUserWidgetVisibility");
	register_global_func(this->v, func_setTextWidgetPosition, "setTextWidgetPosition");
	register_global_func(this->v, func_setSceneObjectPosition, "setSceneObjectPosition");
	register_global_func(this->v, func_setSceneObjectRotationDeg, "setSceneObjectRotationDeg");
	register_global_func(this->v, func_setMeshComponentScale, "setMeshComponentScale");

	register_global_func(this->v, func_createCameraComponent, "createCameraComponent");
	register_global_func(this->v, func_attachComponentToSceneObject, "attachComponentToSceneObject");
	register_global_func(this->v, func_setCameraTarget, "setCameraTarget");
	register_global_func(this->v, func_test_parameters, "testParameters");
	register_global_func(this->v, func_setDirectionalLight, "setDirectionalLight");
	register_global_func(this->v, func_createPointLight, "createPointLight");
	register_global_func(this->v, func_createTextWidget, "createTextWidget");
	register_global_func(this->v, func_createImageWidget, "createImageWidget");
}

void VSquirrelGame::OnInitialize()
{
	this->Game->OnHelpDelegate = std::bind(&VSquirrelGame::OnHelp, this);
	this->Game->OnFPSDelegate = std::bind(&VSquirrelGame::OnFPS, this);
	this->Game->OnFrustumDelegate = std::bind(&VSquirrelGame::OnFrustumCulling, this);

	Game->OnInitialize();

	sq_pushroottable(v);
	sq_pushstring(v, "OnInitialize", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse, SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}

void VSquirrelGame::OnUpdate(double deltaT)
{
	Game->Update(deltaT);

	time += deltaT;

	if (time > 0.02)
	{
		sq_pushroottable(v);
		sq_pushstring(v, "OnTick", -1);
		sq_get(v, -2); //get the function from the root table
		sq_pushroottable(v); //'this' (function environment object)
		sq_call(v, 1, SQFalse, SQFalse);
		sq_pop(v, 2); //pops the roottable and the function
		time = 0;
	}
}

void VSquirrelGame::OnHelp()
{
	sq_pushroottable(v);
	sq_pushstring(v, "OnHelp", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse, SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}

void VSquirrelGame::OnFPS()
{
	sq_pushroottable(v);
	sq_pushstring(v, "OnFPS", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse, SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}


void VSquirrelGame::OnFrustumCulling()
{
	this->Game->ToggleFrustumCulling();
	sq_pushroottable(v);
	sq_pushstring(v, "OnFrustumCulling", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse, SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}

VSquirrelGame::~VSquirrelGame()
{
}
