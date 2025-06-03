#pragma once
#include "Level.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "LabelWidget.h"
#include "SliderWidget.h"
#include "TimerManager.h"
#include "MusicSample.h"

class TankCreation : public Level
{
	HUD* hud;


public:
	TankCreation(const string& _name);

public:
	virtual void InitLevel() override;
	virtual void Load() override;
	virtual void Unload() override;
};

