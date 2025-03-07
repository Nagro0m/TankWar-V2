#include "MainMenuLevel.h"
#include "LevelManager.h"

MainMenuLevel::MainMenuLevel(const string& _name) : Level(_name)
{
	hud = nullptr;
	menu = MenuData();
	option = OptionsMenuData();
	//music = SpawnSample<MusicSample>("BackgroundMusic", MP3);
	//music->SetLoop(true);
	//music->Stop();
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

	// InputLayer
	option.inputLayer = hud->SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(GetWindowSize().x / 1.5f, GetWindowSize().y / 1.7f), "Menu/Input/InputLayer"), "Setting_InputLayer");
	option.inputLayer->SetZOrder(3);
	option.canvas->AddChild(option.inputLayer);

	// Volume SliderVfx
	option.volumeSliderVfx = hud->SpawnWidget<SliderWidget>( "SliderVfx", "Menu/Slider", "Menu/ButtonSlider");
	option.volumeSliderVfx->SetZOrder(3);
	option.canvas->AddChild(option.volumeSliderVfx);

	// Volume SliderMusic
	option.volumeSliderMusic = hud->SpawnWidget<SliderWidget>("SliderMusic", "Menu/Slider", "Menu/ButtonSlider");
	option.volumeSliderMusic->SetZOrder(3);
	option.canvas->AddChild(option.volumeSliderMusic);

	// Mute Button
	/*option.mute = hud->SpawnWidget<ButtonWidget>(RectangleShapeData({ 40, 40 }, "Menu/Sound"), "Options_mute");
	option.mute->SetZOrder(3);
	option.mute->BindOnClickAction([&]() { option.volumeSlider->ToogleActivate();  });
	option.canvas->AddChild(option.mute);*/

	// volume Label
	option.volumeLabel = hud->SpawnWidget<LabelWidget>("Volume :");
	option.volumeLabel->SetZOrder(2);
	option.canvas->AddChild(option.volumeLabel);

	// vfx Label
	option.vfxLabel = hud->SpawnWidget<LabelWidget>("vFX");
	option.vfxLabel->SetZOrder(2);
	option.canvas->AddChild(option.vfxLabel);

	// music Label
	option.musicLabel = hud->SpawnWidget<LabelWidget>("MUSIC");
	option.musicLabel->SetZOrder(2);
	option.canvas->AddChild(option.musicLabel);

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

	// InputLayer
	option.inputLayer->SetOriginAtMiddle();
	option.inputLayer->SetPosition(Vector2f(GetWindowSize().x / 2, GetWindowSize().y - GetWindowSize().y / 2.5));


	// volume SliderVfx
	option.volumeSliderVfx->SetMaxValue(100);
	option.volumeSliderVfx->SetOriginAtMiddle();
	option.volumeSliderVfx->SetPosition(Vector2f(GetWindowSize().x / 1.5, GetWindowSize().y / 6));
	//option.volumeSlider->GetButton()->SetFillColor(Color(192, 192, 192));
	//option.volumeSlider->GetButton()->BindOnClickAction([&]() { option.volumeSlider->GetButton()->SetFillColor(Color(128, 192, 255)); });
	//option.volumeSlider->GetButton()->BindOnReleaseAction([&]() { option.volumeSlider->GetButton()->SetFillColor(Color(192, 192, 192)); });

	// Volume SliderMusic
	option.volumeSliderMusic->SetMaxValue(100);
	option.volumeSliderMusic->SetOriginAtMiddle();
	option.volumeSliderMusic->SetPosition(Vector2f(GetWindowSize().x / 2.70, GetWindowSize().y / 6));

	//volume Label
	option.volumeLabel->SetFont("zDirty War", OTF);
	option.volumeLabel->SetCharacterSize(70);
	option.volumeLabel->SetFillColor(Color(46, 94, 16));
	//option.volumeLabel->SetFillColor(Color(100, 168, 50));
	option.volumeLabel->SetOriginAtMiddle();
	option.volumeLabel->SetPosition(Vector2f(GetWindowSize().x / 1.91, GetWindowSize().y / 30));

	//vfx Label
	option.vfxLabel->SetFont("zDirty War", OTF);
	option.vfxLabel->SetCharacterSize(50);
	option.vfxLabel->SetFillColor(Color(46, 94, 16));
	//option.volumeLabel->SetFillColor(Color(100, 168, 50));
	option.vfxLabel->SetOriginAtMiddle();
	option.vfxLabel->SetPosition(Vector2f(GetWindowSize().x / 1.5, GetWindowSize().y / 9));

	//music Label
	option.musicLabel->SetFont("zDirty War", OTF);
	option.musicLabel->SetCharacterSize(50);
	option.musicLabel->SetFillColor(Color(46, 94, 16));
	//option.musicLabel->SetFillColor(Color(100, 168, 50));
	option.musicLabel->SetOriginAtMiddle();
	option.musicLabel->SetPosition(Vector2f(GetWindowSize().x / 2.7, GetWindowSize().y / 9));
}

void MainMenuLevel::InitLevel()
{
	Super::InitLevel();

	hud = GetGameMode()->GetHUD();

	SetupMenu();
	SetupOptionsMenu();

	//option.volumeLabel->GetSlot()->SetDebugMode(false);
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
