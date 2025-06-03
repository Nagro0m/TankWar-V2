#include "TankCreation.h"
#include "LevelManager.h"


TankCreation::TankCreation(const string& _name, const int _playerCount) : Level(_name)
{
	hud = nullptr;
	menuFirst = CreationMenuData();
	menuSecond = CreationMenuData();
	playerCount = _playerCount <= 0 ? 1 : _playerCount;
	playerCount = _playerCount > 2 ? 2 : _playerCount;
}

void TankCreation::SetupMenuData(const int _playerCount)
{
	if (playerCount == 1)
	{
		LOG(Warning, "TankCreation Menu 1 created !");
		menu.push_back(&menuFirst);
	}
	else if (playerCount == 2)
	{
		LOG(Warning, "TankCreation Menu 2 created !");
		menu.push_back(&menuFirst);
		menu.push_back(&menuSecond);
	}
}

void TankCreation::UpdateTankVisual(const int _playerIndex)
{
	string _suffix = _playerIndex == 1 ? "_1" : "_2";

	

	if (_playerIndex == 1)
	{
		menuFirst.hull->SetTexture("Menu/Tank/Hulls" + _suffix + "/Hull_" + to_string(menuFirst.currentHullIndex + 1));
		menuFirst.turret->SetTexture("Menu/Tank/Weapons" + _suffix + "/Gun_" + to_string(menuFirst.currentTurretIndex + 1));
		menuFirst.track->SetTexture("Menu/Tank/Tracks/Track_" + to_string(menuFirst.currentTrackIndex + 1));
	}
	else
	{
		menuSecond.hull->SetTexture("Menu/Tank/Hulls" + _suffix + "/Hull_" + to_string(menuFirst.currentHullIndex + 1));
		menuSecond.turret->SetTexture("Menu/Tank/Weapons" + _suffix + "/Gun_" + to_string(menuFirst.currentTurretIndex + 1));
		menuSecond.track->SetTexture("Menu/Tank/Tracks/Track_" + to_string(menuFirst.currentTrackIndex + 1));
	}
}

string TankCreation::GetCategoryName(int _index)
{
	switch (_index)
	{
	case 0:
		return "Hull";
	case 1:
		return "Track";
	case 2:
		return "Weapon";
	default:
		return "";
	}
}

void TankCreation::InitLevel()
{
	Super::InitLevel();
	hud = GetGameMode()->GetHUD();
	SetupMenu();
	hud->AddToViewport(menuFirst.canvas);

}

void TankCreation::SetupMenu()
{
	// Canvas
	menuFirst.canvas = hud->SpawnWidget<CanvasWidget>();
	menuFirst.canvas->SetDebugMode(true);
	menuFirst.canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	// Background
	menuFirst.background = hud->SpawnWidget<ImageWidget>(RectangleShapeData(GetWindowSize(), "Menu/BackGround/MenuBackground"), "Menu_Background");
	menuFirst.canvas->AddChild(menuFirst.background);


	// Workbench
	menuFirst.workbench = hud->SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(GetWindowSize().x / 3.0f, GetWindowSize().y / 2), "Menu/SelectMenu"), "Select_Menu");
	menuFirst.workbench->SetZOrder(2);
	menuFirst.canvas->AddChild(menuFirst.workbench);

	menuFirst.track = hud->SpawnWidget<UI::ImageWidget>(RectangleShapeData({ 185, 273 }, "Menu/Tank/Tracks/Track_1"), "Track");
	menuFirst.track->SetZOrder(3);
	menuFirst.canvas->AddChild(menuFirst.track);


	menuFirst.hull = hud->SpawnWidget<UI::ImageWidget>(RectangleShapeData({ 256, 256 }, "Menu/Tank/Hulls_1/Hull_1"), "Hull");
	menuFirst.hull->SetZOrder(4);
	menuFirst.canvas->AddChild(menuFirst.hull);


	menuFirst.turret = hud->SpawnWidget<UI::ImageWidget>(RectangleShapeData({ 94, 212 }, "Menu/Tank/Weapons_1/Gun_1"), "Turret");
	menuFirst.turret->SetZOrder(5);
	menuFirst.canvas->AddChild(menuFirst.turret);


	// Previous Button
	menuFirst.previous = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/LeftArrow"), "Left_Arrow");
	menuFirst.previous->SetZOrder(3);
	menuFirst.previous->BindOnHoverAction([&]() { menuFirst.previous->SetSize(Vector2f(85, 85)); });
	menuFirst.previous->BindOnUnhoverAction([&]() { menuFirst.previous->SetSize(Vector2f(80, 80)); });
	menuFirst.previous->BindOnClickAction([&]()
	{
			switch (menuFirst.currentCategoryIndex)
	{
	case 0:
		menuFirst.currentHullIndex = (menuFirst.currentHullIndex - 1 + 8) % 8;
		break;
	case 1:
		menuFirst.currentTrackIndex = (menuFirst.currentTrackIndex - 1 + 4) % 4;
		break;
	case 2:
		menuFirst.currentTurretIndex = (menuFirst.currentTurretIndex - 1 + 8) % 8;
		break;
	}
	UpdateTankVisual(1);
		});

	menuFirst.canvas->AddChild(menuFirst.previous);

	// Next Button
	menuFirst.next = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/RightArrow"), "Right_Arrow");
	menuFirst.next->SetZOrder(3);
	menuFirst.next->BindOnHoverAction([&]() { menuFirst.next->SetSize(Vector2f(85, 85)); });
	menuFirst.next->BindOnUnhoverAction([&]() { menuFirst.next->SetSize(Vector2f(80, 80)); });
	menuFirst.next->BindOnClickAction([&]()
		{
		switch (menuFirst.currentCategoryIndex)
		{
		case 0:
			menuFirst.currentHullIndex = (menuFirst.currentHullIndex + 1) % 8;
			break;
		case 1:
			menuFirst.currentTrackIndex = (menuFirst.currentTrackIndex + 1) % 4;
			break;
		case 2:
			menuFirst.currentTurretIndex = (menuFirst.currentTurretIndex + 1) % 8;
			break;
		}
		UpdateTankVisual(1);
		});
	menuFirst.canvas->AddChild(menuFirst.next);

	// Select Button
	menuFirst.select = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/Validation"), "Creation_Select");
	menuFirst.select->SetZOrder(3);
	menuFirst.select->BindOnHoverAction([&]() { menuFirst.select->SetSize(Vector2f(85, 85)); });
	menuFirst.select->BindOnUnhoverAction([&]() { menuFirst.select->SetSize(Vector2f(80, 80)); });
	menuFirst.select->BindOnClickAction([&]()
		{
			menuFirst.currentCategoryIndex = (menuFirst.currentCategoryIndex + 1) % 3;
			menuFirst.tankPartText->SetTexture("Menu/TankCreation/" + GetCategoryName(menuFirst.currentCategoryIndex) + "Button");
		});
	menuFirst.canvas->AddChild(menuFirst.select);

	// Quit Button
	menuFirst.quit = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/Cross"), "Creation_Quit");
	menuFirst.quit->SetZOrder(3);
	menuFirst.quit->BindOnHoverAction([&]() { menuFirst.quit->SetSize(Vector2f(85, 85)); });
	menuFirst.quit->BindOnUnhoverAction([&]() { menuFirst.quit->SetSize(Vector2f(80, 80)); });
	menuFirst.quit->BindOnClickAction([&]() { M_LEVEL.SetLevel("MainMenu"); });
	menuFirst.canvas->AddChild(menuFirst.quit);

	// Tank Part Text
	menuFirst.tankPartText = hud->SpawnWidget<ImageWidget>(RectangleShapeData({ 400, 100 }, "Menu/TankCreation/HullButton"), "Creation_TankPartText");
	menuFirst.tankPartText->SetZOrder(3);
	menuFirst.canvas->AddChild(menuFirst.tankPartText);

	/////////
	// Set //
	/////////

	const float _midOfScreenX = GetWindowSize().x / 2.0f;
	const float _midOfScreenY = GetWindowSize().y / 2.0f;

	

	// Workbench
	menuFirst.workbench->SetPosition(Vector2f(GetWindowSize().x / 4, GetWindowSize().y / 2));
	menuFirst.workbench->SetOriginAtMiddle();

	// Previous Button
	menuFirst.previous->SetPosition(Vector2f(GetWindowSize().x / 7, GetWindowSize().y / 2));
	menuFirst.previous->SetOriginAtMiddle();

	// Next Button
	menuFirst.next->SetPosition(Vector2f(GetWindowSize().x / 2.8, GetWindowSize().y / 2));
	menuFirst.next->SetOriginAtMiddle();

	// Select Button
	menuFirst.select->SetPosition(Vector2f(GetWindowSize().x / 4, GetWindowSize().y - GetWindowSize().y / 3));
	menuFirst.select->SetOriginAtMiddle();

	// Quit Button
	menuFirst.quit->SetPosition(Vector2f(GetWindowSize().x - GetWindowSize().x / 10, GetWindowSize().y - GetWindowSize().y / 10));
	menuFirst.quit->SetOriginAtMiddle();

	// Tank Part Text
	menuFirst.tankPartText->SetOriginAtMiddle();
	menuFirst.tankPartText->SetPosition(Vector2f(GetWindowSize().x / 4, GetWindowSize().y/3));

	menuFirst.track->SetOriginAtMiddle();
	menuFirst.track->SetPosition(menuFirst.workbench->GetPosition());
	
	menuFirst.hull->SetOriginAtMiddle();
	menuFirst.hull->SetPosition(menuFirst.workbench->GetPosition());

	menuFirst.turret->SetOriginAtMiddle();
	menuFirst.turret->SetPosition(menuFirst.workbench->GetPosition()- Vector2f(0, 20));


	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////S   E  C  O  N  D   ////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////



	// Workbench
	menuSecond.workbench = hud->SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(GetWindowSize().x / 3.0f, GetWindowSize().y / 2), "Menu/SelectMenu"), "Select_Menu");
	menuSecond.workbench->SetZOrder(2);
	menuFirst.canvas->AddChild(menuSecond.workbench);

	// Previous Button
	menuSecond.previous = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/LeftArrow"), "Left_Arrow");
	menuSecond.previous->SetZOrder(3);
	menuSecond.previous->BindOnHoverAction([&]() { menuSecond.previous->SetSize(Vector2f(85, 85)); });
	menuSecond.previous->BindOnUnhoverAction([&]() { menuSecond.previous->SetSize(Vector2f(80, 80)); });
	menuSecond.previous->BindOnClickAction([&]() {});
	menuFirst.canvas->AddChild(menuSecond.previous);

	// Next Button
	menuSecond.next = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/RightArrow"), "Right_Arrow");
	menuSecond.next->SetZOrder(3);
	menuSecond.next->BindOnHoverAction([&]() { menuSecond.next->SetSize(Vector2f(85, 85)); });
	menuSecond.next->BindOnUnhoverAction([&]() { menuSecond.next->SetSize(Vector2f(80, 80)); });
	menuSecond.next->BindOnClickAction([&]() {});
	menuFirst.canvas->AddChild(menuSecond.next);

	// Select Button
	menuSecond.select = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/Validation"), "Creation_Select");
	menuSecond.select->SetZOrder(3);
	menuSecond.select->BindOnHoverAction([&]() { menuSecond.select->SetSize(Vector2f(85, 85)); });
	menuSecond.select->BindOnUnhoverAction([&]() { menuSecond.select->SetSize(Vector2f(80, 80)); });
	menuSecond.select->BindOnClickAction([&]() {});
	menuFirst.canvas->AddChild(menuSecond.select);

	// Quit Button
	menuSecond.quit = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 80, 80 }, "Menu/TankCreation/Cross"), "Creation_Quit");
	menuSecond.quit->SetZOrder(3);
	menuSecond.quit->BindOnHoverAction([&]() { menuSecond.quit->SetSize(Vector2f(85, 85)); });
	menuSecond.quit->BindOnUnhoverAction([&]() { menuSecond.quit->SetSize(Vector2f(80, 80)); });
	menuSecond.quit->BindOnClickAction([&]() { M_LEVEL.SetLevel("MainMenu"); });
	menuFirst.canvas->AddChild(menuSecond.quit);

	// Tank Part Text
	menuSecond.tankPartText = hud->SpawnWidget<ImageWidget>(RectangleShapeData({ 400, 100 }, "Menu/TankCreation/TrackButton"), "Creation_TankPartText");
	menuSecond.tankPartText->SetZOrder(3);
	menuFirst.canvas->AddChild(menuSecond.tankPartText);

	/////////
	// Set //
	/////////


	// Workbench
	menuSecond.workbench->SetPosition(Vector2f(GetWindowSize().x / 4 + _midOfScreenX, GetWindowSize().y / 2));
	menuSecond.workbench->SetOriginAtMiddle();

	// Previous Button
	menuSecond.previous->SetPosition(Vector2f(GetWindowSize().x / 7 + _midOfScreenX, GetWindowSize().y / 2));
	menuSecond.previous->SetOriginAtMiddle();

	// Next Button
	menuSecond.next->SetPosition(Vector2f(GetWindowSize().x / 2.8 + _midOfScreenX, GetWindowSize().y / 2));
	menuSecond.next->SetOriginAtMiddle();

	// Select Button
	menuSecond.select->SetPosition(Vector2f(GetWindowSize().x / 4 + _midOfScreenX, GetWindowSize().y - GetWindowSize().y / 3));
	menuSecond.select->SetOriginAtMiddle();

	// Quit Button
	menuSecond.quit->SetPosition(Vector2f(GetWindowSize().x - GetWindowSize().x / 10 + _midOfScreenX, GetWindowSize().y - GetWindowSize().y / 10));
	menuSecond.quit->SetOriginAtMiddle();

	// Tank Part Text
	menuSecond.tankPartText->SetPosition(Vector2f(GetWindowSize().x / 4 + _midOfScreenX, GetWindowSize().y / 3));
	menuSecond.tankPartText->SetOriginAtMiddle();
}




void TankCreation::Load()
{
	Super::Load();
}

void TankCreation::Unload()
{
	Super::Unload();
}
