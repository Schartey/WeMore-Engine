local marble = null;
local fpsTextWidget = null;
local helpTextWidget = null;
local frustumTextWidget = null;
local objectsCountTextWidget = null;
local goalTextWidget = null;
local game = null;

local box2 = null;
local box3 = null;
local smallWall6 = null;
local boostWidget = null;

function OnInitialize()
{
	print("Main initialized!");

	game = Engine.Game();
	
	local sceneId = game.CreateScene("MainScene");
	print("CreatedScene !");

	if(game.SetActiveScene(sceneId))
	{
		print("Successullfy set new ActiveScene!");
	}
	
	//Assets
	local lightMapTexture = Engine.Texture("Lightmap.png");
	local lightMapPlatformTexture = Engine.Texture("PlatformLightmap.png");
	local marbleTexture = Engine.Texture("marble_2.jpg");
	local platformTexture = Engine.Texture("floor13.jpg");
	local boxTexture = Engine.Texture("9452.jpg");
	local platformSpecularTexture = Engine.Texture("floor13s.jpg");
	local boostTexture = Engine.Texture("Widget/boost.png");
	local finishTexture = Engine.Texture("finishline.jpg");
	
	local stoneTexture = Engine.Texture("Rock_6/Rock_6_Tex/Rock_6_d.png");
	local stoneSpecularTexture = Engine.Texture("Rock_6/Rock_6_Tex/Rock_6_s.png");

	// Platforms
	local platform = Engine.Platform();
	platform.SetPosition(0.0, -5.0, 0.0);
	platform.SetTexture(platformTexture);
	//platform.SetLightMapTexture(lightMapPlatformTexture);
	platform.SetSpecularMapTexture(platformSpecularTexture);

	local platform2 = Engine.Platform();
	platform2.SetPosition(20.0, -10.0, 0.0);
	platform2.SetTexture(platformTexture);
	platform2.SetLightMapTexture(lightMapTexture);
	platform2.SetSpecularMapTexture(platformSpecularTexture);

	local platform3 = Engine.Platform();
	platform3.SetPosition(60.0, -10.0, 0.0);
	platform3.SetTexture(platformTexture);
	platform3.SetLightMapTexture(lightMapTexture);
	platform3.SetSpecularMapTexture(platformSpecularTexture);

	local platform4 = Engine.Platform();
	platform4.SetPosition(60.0, -10.0, 24.0);
	platform4.SetTexture(platformTexture);
	platform4.SetLightMapTexture(lightMapTexture);
	platform4.SetSpecularMapTexture(platformSpecularTexture);

	local platform5 = Engine.Platform();
	platform5.SetPosition(20.0, -10.0, 24.0);
	platform5.SetTexture(platformTexture);
	platform5.SetLightMapTexture(lightMapTexture);
	platform5.SetSpecularMapTexture(platformSpecularTexture);

	//Walls
	local smallWall = Engine.SmallWall();
	smallWall.SetPosition(0.0, -3.0, -9.0);
	smallWall.SetRotationDeg(0.0, 0.0, 0.0);

	local smallWall2 = Engine.SmallWall();
	smallWall2.SetPosition(70.0, -8.0, 0.0);
	smallWall2.SetRotationDeg(0.0, 90.0, 0.0);

	local smallWall3 = Engine.SmallWall();
	smallWall3.SetPosition(70.0, -2.0, 0.0);
	smallWall3.SetRotationDeg(0.0, 90.0, 0.0);

	local smallWall4 = Engine.SmallWall();
	smallWall4.SetPosition(70.0, -5.0, 5.55);
	smallWall4.SetScale(4.5, 2.0, 1.0);
	smallWall4.SetRotationDeg(0.0, 90.0, 0.0);

	local smallWall5 = Engine.SmallWall();
	smallWall5.SetPosition(70.0, -5.0, -5.55);
	smallWall5.SetScale(4.5, 2.0, 1.0);
	smallWall5.SetRotationDeg(0.0, 90.0, 0.0);

	smallWall6 = Engine.SmallWall();
	smallWall6.SetPosition(60.0, -5.0, 10.0);
	smallWall6.SetScale(10.0, 5.0, 1.0);
	smallWall6.SetRotationDeg(0.0, 0.0, 0.0);

	local smallWall7 = Engine.SmallWall();
	smallWall7.SetPosition(20.0, -5.0, 10.0);
	smallWall7.SetScale(10.0, 5.0, 1.0);
	smallWall7.SetRotationDeg(0.0, 0.0, 0.0);

	//Boxes
	local box = Engine.Box(false);
	box.SetPosition(20.0, -5.0, 0.0);
	box.SetTexture(boxTexture);

	box2 = Engine.Box(true);
	box2.SetPosition(40.0, -10.0, 0.0);
	box2.SetTexture(boxTexture);
	box2.SetScale(10.0, 1.0, 1.0);
	//box2.RestrictMotionLinear(true, true, true);
	//box2.RestrictMotionAngular(true, false, true);

	box3 = Engine.Box(false);
	box3.SetPosition(69.5, -5.0, 0.0);
	box3.SetTexture(boxTexture);

	local boost = Engine.Box(true);
	boost.SetPosition(65.0, -10.8, 29.0);
	boost.SetTexture(boostTexture);

	local finish = Engine.Box(true);
	finish.SetPosition(15.0, -9.9, 24.0);
	finish.SetScale(1.0, 0.1, 10.0);
	finish.SetTexture(finishTexture);
	setMeshMaterial(finish.meshId, 0.0, 0.0, 0.0, 0.0, 0.0);

	//Stones
	/*local stone = Engine.Stone();
	stone.SetPosition(63.0, -9.5, 26.0);
	stone.SetTexture(stoneTexture);
	stone.SetSpecularMapTexture(stoneSpecularTexture);*/

	//Player
	marble = Engine.Marble();
	marble.SetPosition(0.0, 0.0, 0.0);
	marble.SetMass(1.0);
	marble.SetTexture(marbleTexture);
	
	
	local skyboxId = createSkybox();

	setDirectionalLight();
	local pointLightId = createPointLight(0.1, 0.8, 1.0, 0.09, 0.032, 50.0, 10.0, 1.0, 0.0);
	local pointLightId = createPointLight(0.1, 0.8, 1.0, 0.09, 0.032, 50.0, 65.0, -8.8, 29.0);
	local pointLightId = createPointLight(0.1, 0.8, 1.0, 0.09, 0.032, 50.0, 68.0, -5.0, 0.0);

	//TextWidgets
	fpsTextWidget = Engine.TextWidget();

	helpTextWidget = Engine.TextWidget();
	helpTextWidget.SetPosition(0.0, 100.0);
	helpTextWidget.SetText("Help: F1 - Help, F2 - FPS, F3 - WireFrame, F4 - Recompile, F8 - FrustumCulling, Objective - Get to the finish line!");

	frustumTextWidget = Engine.TextWidget();
	frustumTextWidget.SetPosition(75.0, 0.0);
	frustumTextWidget.SetText("FC active!");

	objectsCountTextWidget = Engine.TextWidget();
	objectsCountTextWidget.SetPosition(200.0, 0.0);
	objectsCountTextWidget.ToggleVisibility();

	goalTextWidget = Engine.TextWidget();
	goalTextWidget.SetPosition(300.0, 300.0);
	goalTextWidget.SetText("Goal reached!");

	//ImageWidgets
	boostWidget = Engine.ImageWidget();
}

function OnTick()
{
	//Marble Runtime
	if(marble != null) 
	{
		local position = marble.GetPosition();

		if(!goalTextWidget.GetVisibility() && position.x < 15 && position.z > 12.0)
		{
			goalTextWidget.ToggleVisibility();
		}

		if(position.x > 64 && position.x < 65 && position.z > 29 && position.z < 30)
		{
			if(!boostWidget.GetVisibility())
			{
				boostWidget.ToggleVisibility();
				marble.SetMovementSpeed(16.0);
				marble.SetMaxSpeed(12.0);
			}
		}

		if(position.y < -50.0)
		{
			marble.SetPosition(0.0, 0.0, 0.0);
		}
	}

	if(fpsTextWidget != null)
	{
		fpsTextWidget.SetText(game.GetFPS().tostring());
	}

	objectsCountTextWidget.SetText("Objects: " + game.GetObjectsCount().tostring());

	local rotation = box2.GetRotationDeg();

	if(rotation.y > 89)
		rotation.y = -90;
	box2.SetRotationDeg(rotation.x, rotation.y + 1.0, rotation.z);

	local position = box3.GetPosition();

	if(position.x > 69.8)
	{
		local wallPosition = smallWall6.GetPosition();

		if(wallPosition.y > -15.0) 
		{
			smallWall6.SetPosition(wallPosition.x, wallPosition.y - 0.1, wallPosition.z);
		}
	}
}

function OnFPS()
{
	fpsTextWidget.ToggleVisibility();
}

function OnHelp()
{
	helpTextWidget.ToggleVisibility();
}

function OnFrustumCulling()
{
	frustumTextWidget.ToggleVisibility();
}