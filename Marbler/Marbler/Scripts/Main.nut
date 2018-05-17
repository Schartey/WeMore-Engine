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
	local floorActorId = createActor("FloorActor", true, true, 0.0, -10.0, 0.0, 0.0, 45.0, 0.0);
	local floorMeshComponentId = createMeshComponent("FloorMeshComponent", "box.fbx", "box", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.1, 10.0);
	local lightBoxTextureId = createTexture("Lightmap.png");
	setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 1.0, 1);
	setMeshLightTexture(floorMeshComponentId, lightBoxTextureId);
	attachComponentToSceneObject(floorMeshComponentId, floorActorId);

	local cameraActorId = createActor("CameraActor", true, false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	setActorMass(cameraActorId, 1.0f);
	local marbleMeshComponentId = createMeshComponent("MarbleMeshComponent", "marble.obj", "sphere", true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
	local marbleTextureId = createTexture("marble_2.jpg");
	setMeshMaterial(floorMeshComponentId, 1.0, 1.0, 1.0, 1.0, 32);
	setMeshTexture(floorMeshComponentId, marbleTextureId);
	local cameraComponentId = createCameraComponent("CameraComponent", true, 0.0, 5.0, 20.0, 0.0, 0.0, 0.0);
	attachComponentToSceneObject(cameraComponendId, cameraActorId);
	setCameraTarget(cameraComponentId, marbleMeshComponentId);
}
