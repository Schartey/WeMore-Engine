function onInitialize()
{
	print("Main initialized!");

	local id = createScene("MainScene");

	print("ID: " + id);
	local success = setActiveScene(id);

	if(success)
	{
		print("Successullfy set new ActiveScene!");
	}
	local floorActorId = createActor("FloorActor", true, true, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0);
	local floorMeshComponentId = createMeshComponent("FloorMeshComponent", "box.fbx", "Box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.1, 10.0, floorActorId);
	local lightBoxTextureId = loadTexture("Lightmap.png");
	setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 1.0, 1);
	setMeshLightTexture(floorMeshComponentId, lightBoxTextureId);
	//attachComponentToSceneObject(floorMeshComponentId, floorActorId);

	local cameraActorId = createActor("CameraActor", true, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	//setActorMass(cameraActorId, 1.0);
	local marbleMeshComponentId = createMeshComponent("MarbleMeshComponent", "marble.obj", "Sphere", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, cameraActorId);
	local marbleTextureId = loadTexture("marble_2.jpg");
	setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 1.0, 32);
	setMeshTexture(floorMeshComponentId, marbleTextureId);
	local cameraComponentId = createCameraComponent("CameraComponent", 0.0, 5.0, 20.0, 0.0, 0.0, 0.0, cameraActorId);
	//attachComponentToSceneObject(cameraComponendId, cameraActorId);
	setCameraTarget(cameraComponentId, marbleMeshComponentId);
	
	setDirectionalLight();
	local pointLightId = createPointLight();
	local textWidgetId = createTextWidget();
	local imageWidgetId = createImageWidget();
}
