#pragma once
#include "Level.h"
#include "CanvasWidget.h"

struct GameplayHUDData
{
	CanvasWidget* canvas;
};

class DebugLevel : public Level
{
	HUD* hud;
	GameplayHUDData gameHUD;

public:
	DebugLevel(const string& _name);

protected:
	virtual void InitLevel() override;
};

