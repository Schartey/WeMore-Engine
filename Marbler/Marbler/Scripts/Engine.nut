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

class Engine.Platform {
	id = null;
	meshId = null;

    constructor()
    {
		local floorActorId = createActor("FloorActor", true, true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = floorActorId;

		local floorMeshComponentId = createMeshComponent("FloorMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.1, 10.0, floorActorId);
		meshId = floorMeshComponentId;

		//local lightBoxTextureId = loadTexture("Lightmap.png");
		setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 1.0, 1);
		//attachComponentToSceneObject(floorMeshComponentId, floorActorId);
    }
    function SetPosition(x, y, z)
    {
		::print("Setting Position");
        setSceneObjectPosition(id, x, y ,z);
    }

	function SetLightMapTexture(texture)
	{
		setMeshLightTexture(meshId, texture.id);
	}

	function SetTexture(texture)
	{
		setMeshTexture(meshId, texture.id);
	}
}

class Engine.Box {
	id = null;
	meshId = null;

    constructor()
    {
		local boxActorId = createActor("BoxActor", true, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		id = boxActorId;

		local boxMeshComponentId = createMeshComponent("BoxMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, boxActorId);
		meshId = boxMeshComponentId;

		//local lightBoxTextureId = loadTexture("Lightmap.png");
		setMeshMaterial(boxMeshComponentId, 1.0, 1.0, 1.0, 1.0, 1);
		//attachComponentToSceneObject(floorMeshComponentId, floorActorId);
    }
    function SetPosition(x, y, z)
    {
		::print("Setting Position");
        setSceneObjectPosition(id, x, y ,z);
    }

	function SetTexture(texture)
	{
		setMeshTexture(meshId, texture.id);
	}

	function SetLightMapTexture(texture)
	{
		setMeshLightTexture(meshId, texture.id);
	}
}

class Engine.Marble {
	id = null;
	meshId = null;

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
		setMeshMaterial(marbleMeshComponentId, 1.0, 1.0, 1.0, 1.0, 32);
		local cameraComponentId = createCameraComponent("CameraComponent", 0.0, 5.0, 20.0, 0.0, 0.0, 0.0, cameraActorId);
		//attachComponentToSceneObject(cameraComponendId, cameraActorId);
		setCameraTarget(cameraComponentId, marbleMeshComponentId);
		local inputComponentId = createInputComponent("InputComponent", cameraActorId);
		//local particleComponentId = createParticleComponent("ParticleComponent", floorActorId);
    }

	function GetPosition()
	{
		local position = getSceneObjectPosition(id);
		return position;
	}

	function SetTexture(texture)
	{
		setMeshTexture(meshId, texture.id);
	}

	function SetMass(mass)
	{
		setActorMass(id, mass);
	}

    function DoSomething()
    {
        ::print("DoSomething()")
    }
}

class Engine.TextWidget
{
	id = null;
	visibility = false;

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

	function GetVisibility()
	{
		return visibility;
	}

	function ToggleVisibility()
	{
		visibility = !visibility;
		setTextWidgetVisibility(id, visibility);
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
}