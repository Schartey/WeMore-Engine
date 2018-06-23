Engine <- {
}

class Engine.Texture {
	id = null;

	constructor(name)
	{
		local lightBoxTextureId = loadTexture(name);
		id = lightBoxTextureId;

	}
}

class Engine.Actor {

	id = null;
	meshId = null;
	
	function GetPosition()
	{
		local position = getSceneObjectPosition(id);
		return position;
	}

	function GetRotationDeg()
	{
		local rotation = getSceneObjectRotation(id);
		return rotation;
	}

    function SetPosition(x, y, z)
    {
		::print("Setting Position");
        setSceneObjectPosition(id, x, y ,z);
    }

	function SetRotationDeg(x,y,z)
	{
		setSceneObjectRotationDeg(id, x, y, z);
	}

	function SetScale(x, y, z)
	{
		setMeshComponentScale(meshId, x, y, z);
	}


	function SetLightMapTexture(texture)
	{
		setMeshLightTexture(meshId, texture.id);
	}

	function SetTexture(texture)
	{
		setMeshTexture(meshId, texture.id);
	}

	function SetSpecularMapTexture(texture)
	{
		::print(texture.id);
		setMeshSpecularTexture(meshId, texture.id);
	}
	
	function SetMass(mass)
	{
		setActorMass(id, mass);
	}

	function RestrictMotionLinear(x, y, z)
	{
		restrictActorMotionLinear(id, x, y, z);
	}

	function RestrictMotionAngular(x, y, z)
	{
		restrictActorMotionAngular(id, x, y, z);
	}
}

class Engine.Platform extends Engine.Actor {
    constructor()
    {
		local floorActorId = createActor("FloorActor", true, true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = floorActorId;

		local floorMeshComponentId = createMeshComponent("FloorMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.1, 10.0, floorActorId);
		meshId = floorMeshComponentId;

		//local lightBoxTextureId = loadTexture("Lightmap.png");
		setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 0.1, 23.0);
		//attachComponentToSceneObject(floorMeshComponentId, floorActorId);
    }
}

class Engine.Box extends Engine.Actor {

    constructor(isStatic)
    {
		local boxActorId = createActor("BoxActor", true, isStatic, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = boxActorId;

		local boxMeshComponentId = createMeshComponent("BoxMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, boxActorId);
		meshId = boxMeshComponentId;

		//local lightBoxTextureId = loadTexture("Lightmap.png");
		setMeshMaterial(boxMeshComponentId, 1.0, 1.0, 1.0, 0.0, 0.0);
		//attachComponentToSceneObject(floorMeshComponentId, floorActorId);
    }
}

class Engine.SmallWall extends Engine.Actor {

    constructor()
    {
		local smallWallActorId = createActor("SmallWallActor", true, true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = smallWallActorId;

		local smallWallMeshComponentId = createMeshComponent("SmallWallMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 2.0, 1.0, smallWallActorId);
		meshId = smallWallMeshComponentId;

		setMeshMaterial(smallWallMeshComponentId, 1.0, 1.0, 1.0, 0.0, 0.0);
    }
}

class Engine.Stone extends Engine.Actor {

    constructor()
    {
		local stoneActorId = createActor("StoneActor", false, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = stoneActorId;

		local stoneMeshComponentId = createMeshComponent("StoneMeshComponentId", "Rock_6/Rock_6.OBJ", "Box", false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, stoneActorId);
		meshId = stoneMeshComponentId;

		//setMeshMaterial(smallWallMeshComponentId, 1.0, 1.0, 1.0, 0.0, 0.0);
    }
}

class Engine.Marble extends Engine.Actor {
	id = null;
	meshId = null;
	inputId = null;

    constructor()
    {
        ::print("Creating Marble")
		
		//Workaround - direct initializiation doesn't work for some reason
		local cameraActorId = createActor("CameraActor", true, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = cameraActorId;
		setActorMass(cameraActorId, 1.0);
		local marbleMeshComponentId = createMeshComponent("MarbleMeshComponent", "marble.obj", "Sphere", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, cameraActorId);
		meshId = marbleMeshComponentId;

		//local marbleTextureId = loadTexture("marble_2.jpg");
		setMeshMaterial(marbleMeshComponentId, 1.0, 1.0, 1.0, 0.4, 2.0);
		local cameraComponentId = createCameraComponent("CameraComponent", 0.0, 5.0, 20.0, 0.0, 0.0, 0.0, cameraActorId);
		//attachComponentToSceneObject(cameraComponendId, cameraActorId);
		setCameraTarget(cameraComponentId, marbleMeshComponentId);
		local inputComponentId = createInputComponent("InputComponent", cameraActorId);
		inputId = inputComponentId;
		//local particleComponentId = createParticleComponent("ParticleComponent", floorActorId);
    }

	function SetMovementSpeed(speed)
	{
		setInputMovementSpeed(inputId, speed);
	}

	function SetJumpForce(force)
	{
		setInputJumpForce(inputId, force);
	}

	function SetMaxSpeed(maxSpeed)
	{
		setInputMaxSpeed(inputId, maxSpeed);
	}
}

class Engine.UserWidget
{
	id = null;
	visibility = false;

	function GetVisibility()
	{
		return visibility;
	}

	function ToggleVisibility()
	{
		::print("test");
		visibility = !visibility;
		setUserWidgetVisibility(id, visibility);
	}
}
class Engine.TextWidget extends Engine.UserWidget
{
	constructor()
	{
		local textWidgetId = createTextWidget();
		id = textWidgetId;
	}

	function SetText(text)
	{
		setTextWidgetText(id, text);
	}

	function SetPosition(posx, posy)
	{
		setTextWidgetPosition(id, posx, posy);
	}
}
class Engine.ImageWidget extends Engine.UserWidget
{
	constructor()
	{
		local imageWidgetId = createImageWidget();
		id = imageWidgetId;
	}
}

class Engine.Game {
	sceneId = null;
	activeScene = null;

	constructor()
	{
		sceneId = -1;
		activeScene = -1;
	}
	
	function CreateScene(scene)
	{
		local id = createScene(scene);
		sceneId = id;
		return id;
	}

	function SetActiveScene(id)
	{
		local success = setActiveScene(id);
		activeScene = id;
		return success;
	}

	function GetFPS()
	{
		local fps = getFPS();
		return fps;
	}

	function GetObjectsCount()
	{
		local objects = getObjectsCount();
		return objects;
	}
}