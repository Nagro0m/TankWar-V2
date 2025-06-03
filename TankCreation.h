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

struct CreationMenuData
{
	CanvasWidget* canvas;
	ImageWidget* background;
	ImageWidget* workbench;
	ButtonWidget* previous;
	ButtonWidget* next;
	ButtonWidget* select;
	ButtonWidget* quit;
	ImageWidget* tankPartText;

	ImageWidget* hull;
	ImageWidget* turret;
	ImageWidget* track;

	int currentHullIndex = 0;
	int currentTrackIndex = 0;
	int currentTurretIndex = 0;
	int currentCategoryIndex = 0;
	
};



class TankCreation : public Level
{
	int playerCount;
	HUD* hud;
	CreationMenuData menuFirst;
	CreationMenuData menuSecond;
	vector<CreationMenuData*> menu;


public:
	TankCreation(const string& _name, const int _playerCount = 1);

private:
	void SetupMenu();
	void SetupMenuData(const int _playerCount);
	void UpdateTankVisual( const int _playerIndex);
	string GetCategoryName(int _index);

public:
	virtual void InitLevel() override;
	virtual void Load() override;
	virtual void Unload() override;
};

