#include "MainMenuLevel.h"
#include "LevelManager.h"

MainMenuLevel::MainMenuLevel(const string& _name) : Level(_name)
{
	hud = nullptr;
	menu = MenuData();
	option = OptionsMenuData();
	music = SpawnSample<MusicSample>("BackgroundMusic", MP3);
	music->SetLoop(true);
	music->Stop();
}

void MainMenuLevel::SetupMenu()
{
	//////////
	// INIT //
	//////////

	// Canvas
	menu.canvas = hud->SpawnWidget<CanvasWidget>();
	menu.canvas->SetDebugMode(true);
	menu.canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	// Background
	menu.background = hud->SpawnWidget<ImageWidget>(RectangleShapeData(GetWindowSize(), "Menu/BackGround/MenuBackground"), "Menu_Background");
	menu.canvas->AddChild(menu.background);

	// Logo
	menu.logo = hud->SpawnWidget<ImageWidget>(RectangleShapeData({ 873.0f, 279.0f }, "Menu/TitleWithTank"), "Menu_Logo");
	menu.logo->SetZOrder(2);
	menu.canvas->AddChild(menu.logo);

	// SelectMenu
	menu.selectMenu = hud->SpawnWidget<ImageWidget>(RectangleShapeData({ 873.0f, 279.0f }, "Menu/SelectMenu"), "Menu_SelectMenu");
	menu.selectMenu->SetZOrder(2);
	menu.canvas->AddChild(menu.selectMenu);

	Vector2f _buttonSize = Vector2f(GetWindowSize().x / 6.4f, GetWindowSize().y / 10.8);
	Vector2f _buttonSizeOn = Vector2f(_buttonSize * 1.02f);
	


	// solo Button
	menu.solo = hud->SpawnWidget<ButtonWidget>(RectangleShapeData(_buttonSize, "Menu/Button/ButtonSolo"), "ButtonSolo");
	menu.solo->SetZOrder(3);
	menu.solo->BindOnHoverAction([&]() { menu.solo->SetSize(Vector2f(330, 110));  });
	menu.solo->BindOnUnhoverAction([&]() { menu.solo->SetSize(Vector2f(300, 100));  });
	//menu.play->BindOnClickAction([&]() { M_LEVEL.SetLevel(new CyberCafeLevel("cyber"));  });
	menu.canvas->AddChild(menu.solo);

	// duo Button
	menu.duo = hud->SpawnWidget<ButtonWidget>(RectangleShapeData(_buttonSize, "Menu/Button/ButtonDuo"), "ButtonDuo");
	menu.duo->SetZOrder(3);
	menu.duo->BindOnHoverAction([&]() { menu.duo->SetSize(Vector2f(330, 110));  });
	menu.duo->BindOnUnhoverAction([&]() { menu.duo->SetSize(Vector2f(300, 100));  });
	//menu.play->BindOnClickAction([&]() { M_LEVEL.SetLevel(new CyberCafeLevel("cyber"));  });
	menu.canvas->AddChild(menu.duo);

	// Options Button
	menu.options = hud->SpawnWidget<ButtonWidget>(RectangleShapeData(_buttonSize, "Menu/Button/ButtonSettings"), "ButtonSettings");
	menu.options->SetZOrder(3);
	menu.options->BindOnHoverAction([&]() { menu.options->SetSize(Vector2f(330, 110));  });
	menu.options->BindOnUnhoverAction([&]() { menu.options->SetSize(Vector2f(300, 100));  });
	menu.options->BindOnClickAction([&]() { hud->AddToViewport(option.canvas); });
	menu.canvas->AddChild(menu.options);

	// Quit Button
	menu.quit = hud->SpawnWidget<ButtonWidget>(RectangleShapeData(_buttonSize, "Menu/Button/ButtonExit"), "ButtonExit");
	menu.quit->SetZOrder(3);
	menu.quit->BindOnHoverAction([&]() { menu.quit->SetSize(Vector2f(330, 110));  });
	menu.quit->BindOnUnhoverAction([&]() { menu.quit->SetSize(Vector2f(300, 100));  });
	menu.quit->BindOnClickAction([&]() { window.close();  });
	menu.canvas->AddChild(menu.quit);

	/////////
	// Set //
	/////////

	// Logo
	menu.logo->SetSize({ 1000,350 });
	menu.logo->SetPosition(Vector2f(GetWindowSize().x / 2.0f, GetWindowSize().y / 7.0f));
	menu.logo->SetOriginAtMiddle();

	// selectMenu
	menu.selectMenu->SetSize({ 500,630 });
	menu.selectMenu->SetPosition(Vector2f(GetWindowSize().x / 2.0f, GetWindowSize().y / 1.7f));
	menu.selectMenu->SetOriginAtMiddle();

	// solo Button
	menu.solo->SetPosition(Vector2f(GetWindowSize().x / 2, GetWindowSize().y / 2.35));
	menu.solo->SetOriginAtMiddle();
	if (CanvasSlot* _slot = Cast<CanvasSlot>(menu.solo->GetSlot()))
	{
		_slot->SetFillToContent(true);
	}

	// duo Button
	menu.duo->SetPosition(Vector2f(GetWindowSize().x / 2, GetWindowSize().y / 1.86));
	menu.duo->SetOriginAtMiddle();
	if (CanvasSlot* _slot = Cast<CanvasSlot>(menu.duo->GetSlot()))
	{
		_slot->SetFillToContent(true);
	}

	// Options Button
	menu.options->SetPosition(Vector2f(GetWindowSize().x / 2, GetWindowSize().y / 1.54));
	menu.options->SetOriginAtMiddle();
	if (CanvasSlot* _slot = Cast<CanvasSlot>(menu.options->GetSlot()))
	{
		_slot->SetFillToContent(true);
	}

	// Quit Button
	menu.quit->SetPosition(Vector2f(GetWindowSize().x / 2, GetWindowSize().y / 1.32));
	menu.quit->SetOriginAtMiddle();
	if (CanvasSlot* _slot = Cast<CanvasSlot>(menu.quit->GetSlot()))
	{
		_slot->SetFillToContent(true);
	}

}

void MainMenuLevel::SetupOptionsMenu()
{
	//////////
	// INIT //
	//////////

	// Canvas
	option.canvas = hud->SpawnWidget<CanvasWidget>();
	option.canvas->SetDebugMode(true);
	option.canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	// Background
	option.background = hud->SpawnWidget<ImageWidget>(RectangleShapeData(GetWindowSize(), "Menu/BackGround/MenuBackground"), "Setting_Background");
	option.canvas->AddChild(option.background);

	// Title
	option.title = hud->SpawnWidget<LabelWidget>("Options", "Options_Title");
	option.title->SetZOrder(3);
	option.canvas->AddChild(option.title);

	// Back Button
	option.back = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 150.0f, 35.0f }, "Back"), "Options_Quit");
	option.back->SetZOrder(3);
	option.back->BindOnHoverAction([&]() { option.back->SetFillColor(Color(128, 192, 255));  });
	option.back->BindOnUnhoverAction([&]() { option.back->SetFillColor(Color(255, 255, 255));  });
	option.back->BindOnClickAction([&]() { hud->AddToViewport(menu.canvas);  });
	option.canvas->AddChild(option.back);

	// Volume Slider
	option.volumeSlider = hud->SpawnWidget<SliderWidget>("Options_Volume_Slider");
	option.volumeSlider->SetZOrder(3);
	option.canvas->AddChild(option.volumeSlider);

	// Volume Label
	option.volumeLabel = hud->SpawnWidget<LabelWidget>("Volume :", "Options_Volume_Label");
	option.volumeLabel->SetZOrder(3);
	option.canvas->AddChild(option.volumeLabel);

	/////////
	// Set //
	/////////

	// Title
	option.title->SetFont("Super_Milk", TTF);
	option.title->SetCharacterSize(72);
	option.title->SetPosition(Vector2f(GetWindowSize().x / 4, GetWindowSize().y / 3));

	// Back Button
	option.back->SetPosition(Vector2f(GetWindowSize().x / 4.4, GetWindowSize().y / 1.25));
	if (CanvasSlot* _slot = Cast<CanvasSlot>(option.back->GetSlot()))
	{
		_slot->SetFillToContent(true);
	}

	// Volume Slider
	option.volumeSlider->SetMaxValue(100);
	option.volumeSlider->SetPosition(Vector2f(GetWindowSize().x / 1.8, GetWindowSize().y / 3.25));
	option.volumeSlider->GetSliderBar()->SetFillColor(Color(156, 156, 156));
	option.volumeSlider->GetButton()->SetFillColor(Color(192, 192, 192));
	option.volumeSlider->GetButton()->BindOnClickAction([&]() { option.volumeSlider->GetButton()->SetFillColor(Color(128, 192, 255)); });
	option.volumeSlider->GetButton()->BindOnReleaseAction([&]() { option.volumeSlider->GetButton()->SetFillColor(Color(192, 192, 192)); });

	// Volume Label
	option.volumeLabel->SetFont("Super_Milk", TTF);
	option.volumeLabel->SetCharacterSize(36);
	option.volumeLabel->SetFillColor(Color(156, 156, 156));
	option.volumeLabel->SetPosition(Vector2f(GetWindowSize().x / 1.8, GetWindowSize().y / 4));
}

void MainMenuLevel::InitLevel()
{
	Super::InitLevel();

	hud = GetGameMode()->GetHUD();

	SetupMenu();
	SetupOptionsMenu();

	option.volumeLabel->GetSlot()->SetDebugMode(false);
	hud->AddToViewport(menu.canvas);
}

void MainMenuLevel::Load()
{
	Super::Load();
	//music->Play();
}

void MainMenuLevel::Unload()
{
	Super::Unload();
	//music->Stop();
}
