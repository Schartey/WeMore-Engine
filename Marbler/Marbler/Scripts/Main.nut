local marble = null;
local fpsTextWidget = null;
local helpTextWidget = null;
local frustumTextWidget = null;
local goalTextWidget = null;
local game = null;

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
	local marbleTexture = Engine.Texture("marble_2.jpg");
	local platformTexture = Engine.Texture("floor13.jpg");
	local boxTexture = Engine.Texture("9452.jpg");

	// Platforms
	local platform = Engine.Platform();
	platform.SetPosition(0.0, -5.0, 0.0);
	platform.SetTexture(platformTexture);
	platform.SetLightMapTexture(lightMapTexture);

	local platform2 = Engine.Platform();
	platform2.SetPosition(20.0, -10.0, 0.0);
	platform2.SetTexture(platformTexture);
	platform2.SetLightMapTexture(lightMapTexture);

	//Boxes
	local box = Engine.Box();
	box.SetPosition(20.0, -5.0, 0.0);
	box.SetTexture(boxTexture);
	//box.SetLightMapTexture(lightMapTexture);

	//Player
	marble = Engine.Marble();
	marble.SetMass(1.0);
	marble.SetTexture(marbleTexture);
	
	
	//local skyboxId = createSkybox();

	setDirectionalLight();
	local pointLightId = createPointLight();
	local imageWidgetId = createImageWidget();

	//TextWidgets
	fpsTextWidget = Engine.TextWidget();

	helpTextWidget = Engine.TextWidget();
	helpTextWidget.SetPosition(0.0, 100.0);
	helpTextWidget.SetText("Help: F1 - Help, F2 - FPS, F3 - WireFrame, F8 - FrustumCulling, Objective - Get to the furthest right red point!");

	frustumTextWidget = Engine.TextWidget();
	frustumTextWidget.SetPosition(75.0, 0.0);
	frustumTextWidget.SetText("FC active!");

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