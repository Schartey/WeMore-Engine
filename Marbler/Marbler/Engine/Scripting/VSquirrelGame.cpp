#include "VSquirrelGame.h"

#include <string>

#include "../Core/Components/VCameraComponent.h"
#include "../GUI/Widgets/VTextWidget.h"
#include "../GUI/Widgets/VImageWidget.h"

VGame* VSquirrelGame::Game = 0;

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
			printf("Created Scene %i", id);
			printf("\n");
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
			printf("Active Scene: %s", name.c_str());
			printf("\n");

			bool success = true;
		}
	}

	sq_pushbool(v, success);
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
										printf("Created Actor: %s", Actor->GetName().c_str());
										printf("\n");

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

SQInteger func_loadTexture(HSQUIRRELVM v)
{
	int id = -1;
	const SQChar* name = "";

	if (sq_gettype(v, 2) == OT_STRING && sq_getstring(v, 2, &name) == 0)
	{
		VTexture* Texture = new VTexture(VSquirrelGame::Game->GetTexturePath() + name);
		Texture->Load();

		id = VSquirrelGame::Game->GetObjectPool()->AddTexture(Texture);
		printf("Created Texture: %s", name);
		printf("\n");
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
				VTexture* Texture = VSquirrelGame::Game->GetObjectPool()->GetTexture(id);

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
				VTexture* Texture = VSquirrelGame::Game->GetObjectPool()->GetTexture(id);

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
				PxRigidDynamic* RigidDynamic = dynamic_cast<PxRigidDynamic*>(Actor->GetRigidActor());
				RigidDynamic->setMass(mass);
				sq_pushbool(v, SQTrue); //push the number of arguments as return value
				return 1; //1 because 1 value is returned
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
									printf("Created CameraComponent: %s", CameraComponent->GetName().c_str());
									printf("\n");

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

/*SQInteger func_createParticleComponent(HSQUIRRELVM v)
{
	//Create ParticleComponent
}*/

SQInteger func_setDirectionalLight(HSQUIRRELVM v)
{
	//Set DirectionalLight, cannot be accessed later, just overriden...because too much work that has to be redone anways, directionallight is a mess right now
	VDirectionalLight* DirectionalLight = VSquirrelGame::Game->GetActiveScene()->CreateDirectionalLight(VSquirrelGame::Game->GetConfig()->getValue("brightness", "0.2f").asFloat());

	sq_pushbool(v, SQTrue); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createPointLight(HSQUIRRELVM v)
{
	//This has to be stored in the Object stuff
	VPointLight2* PointLight1 = VSquirrelGame::Game->GetActiveScene()->CreatePointLight("Pointlight1");
	PointLight1->GetLightComponent()->GetPointLight().Ambient = 0.0f;
	PointLight1->GetLightComponent()->GetPointLight().Diffuse = 0.8f;
	PointLight1->GetLightComponent()->GetPointLight().Color = glm::vec3(1.0f, 1.0f, 1.0f);
	PointLight1->GetLightComponent()->GetPointLight().Attenuation = VAttenuation(0.0f, 0.000001f, 0.1f);

	int id = VSquirrelGame::Game->GetObjectPool()->AddSceneObject(PointLight1);

	sq_pushinteger(v, id); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger func_createTextWidget(HSQUIRRELVM v)
{
	//Store this
	VTextWidget* TextWidget = new VTextWidget();
	TextWidget->GetTextElement()->SetText(Text("Hello World", 0.0f, 0.0f, 0.5f, glm::vec3(1, 1, 1)));
	int id = VSquirrelGame::Game->GetGUI()->AddWidget(TextWidget);

	sq_pushinteger(v, id); //push the number of arguments as return value
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
															VMeshComponent* MeshComponent = new VMeshComponent(VSquirrelGame::Game->GetActiveScene(), "FloorMeshComponent");

															VSceneObject* SceneObject = VSquirrelGame::Game->GetObjectPool()->GetSceneObject<VSceneObject>(parentId);

															SceneObject->AddComponent(MeshComponent);

															MeshComponent->LoadMesh(VSquirrelGame::Game->GetModelPath() + mesh);

															if (strcmp(physicsShape, "Sphere"))
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Sphere);
															}
															else if (strcmp(physicsShape, "Box"))
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Box);
															}
															else if (strcmp(physicsShape, "Cylinder"))
															{
																MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
															}
															MeshComponent->SetBPhysics(physics);

															MeshComponent->SetPosition(glm::vec3(posX, posY, posZ));
															MeshComponent->SetRotation(glm::vec3(rotX, rotY, rotZ));
															MeshComponent->SetScale(glm::vec3(scaleX, scaleY, scaleZ));

															id = VSquirrelGame::Game->GetObjectPool()->AddComponent(MeshComponent);
															printf("Created MeshComponent: %s", MeshComponent->GetName().c_str());
															printf("\n");


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
	printf("Loaded actor");
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

	register_global_func(this->v, func_createScene, "createScene");
	register_global_func(this->v, func_setActiveScene, "setActiveScene");
	register_global_func(this->v, func_createActor, "createActor");
	register_global_func(this->v, func_createMeshComponent, "createMeshComponent");
	register_global_func(this->v, func_loadTexture, "loadTexture");
	register_global_func(this->v, func_setMeshMaterial, "setMeshMaterial");
	register_global_func(this->v, func_setMeshTexture, "setMeshTexture");
	register_global_func(this->v, func_setMeshLightTexture, "setMeshLightTexture");
	register_global_func(this->v, func_createCameraComponent, "createCameraComponent");
	register_global_func(this->v, func_attachComponentToSceneObject, "attachComponentToSceneObject");
	register_global_func(this->v, func_setCameraTarget, "setCameraTarget");
	register_global_func(this->v, func_setActorMass, "setActorMass");
	register_global_func(this->v, func_test_parameters, "testParameters");
	register_global_func(this->v, func_setDirectionalLight, "setDirectionalLight");
	register_global_func(this->v, func_createPointLight, "createPointLight");
	register_global_func(this->v, func_createTextWidget, "createTextWidget");
	register_global_func(this->v, func_createImageWidget, "createImageWidget");
}

void VSquirrelGame::OnInitialize()
{
	Game->OnInitialize();

	sq_pushroottable(v);
	sq_pushstring(v, "onInitialize", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse,SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}

VSquirrelGame::~VSquirrelGame()
{
}
