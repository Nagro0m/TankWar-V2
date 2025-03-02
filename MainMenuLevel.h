#pragma once
#include "Level.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "LabelWidget.h"
#include "SliderWidget.h"
#include "TimerManager.h"
#include "MusicSample.h"

using namespace UI;

struct MenuData
{
	CanvasWidget* canvas;
	ImageWidget* background;
	ImageWidget* logo;
	ImageWidget* selectMenu;
	ButtonWidget* solo;
	ButtonWidget* duo;
	ButtonWidget* options;
	ButtonWidget* quit;
};

struct OptionsMenuData
{
	CanvasWidget* canvas;
	ImageWidget* background;
	LabelWidget* title;
	ButtonWidget* back;

	LabelWidget* volumeLabel;
	SliderWidget* volumeSlider;
};

class MainMenuLevel : public Level
{
	HUD* hud;
	MenuData menu;
	OptionsMenuData option;
	MusicSample* music;

public:
	MainMenuLevel(const string& _name);

private:
	void SetupMenu();
	void SetupOptionsMenu();

public:
	virtual void InitLevel() override;
	virtual void Load() override;
	virtual void Unload() override;
};

