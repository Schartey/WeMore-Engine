local marble = null;
local fpsTextWidget = null;
local helpTextWidget = null;
local frustumTextWidget = null;
local objectsCountTextWidget = null;
local goalTextWidget = null;
local game = null;

local box2 = null;

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

	//Walls
	local smallWall = Engine.SmallWall();
	smallWall.SetPosition(0.0, -3.0, -9.0);
	smallWall.SetRotationDeg(0.0, 0.0, 0.0);

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

	//Player
	marble = Engine.Marble();
	marble.SetMass(1.0);
	marble.SetTexture(marbleTexture);
	
	
	local skyboxId = createSkybox();

	setDirectionalLight();
	local pointLightId = createPointLight();
	local imageWidgetId = createImageWidget();

	//TextWidgets
	fpsTextWidget = Engine.TextWidget();

	helpTextWidget = Engine.TextWidget();
	helpTextWidget.SetPosition(0.0, 100.0);
	helpTextWidget.SetText("Help: F1 - Help, F2 - FPS, F3 - WireFrame, F4 - Recompile, F8 - FrustumCulling, Objective - Get to the furthest right red point!");

	frustumTextWidget = Engine.TextWidget();
	frustumTextWidget.SetPosition(75.0, 0.0);
	frustumTextWidget.SetText("FC active!");

	objectsCountTextWidget = Engine.TextWidget();
	objectsCountTextWidget.SetPosition(90.0, 0.0);
	objectsCountTextWidget.ToggleVisibility();

	goalTextWidget = Engine.TextWidget();
	goalTextWidget.SetPosition(300.0, 300.0);
	goalTextWidget.SetText("Goal reached!");
}

function OnTick()
{
	if(marble != null) 
	{
		local position = marble.GetPosition();

		if(!goalTextWidget.GetVisibility() && position.x > 27 && position.x < 28)
		{
			goalTextWidget.ToggleVisibility();
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