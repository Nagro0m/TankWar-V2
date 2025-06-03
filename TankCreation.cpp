#include "TankCreation.h"
#include "LevelManager.h"

TankCreation::TankCreation(const string& _name) : Level(_name)
{
	hud = nullptr;
}

void TankCreation::InitLevel()
{
	Super::InitLevel();
	hud = GetGameMode()->GetHUD();


}

void TankCreation::Load()
{
	Super::Load();
}

void TankCreation::Unload()
{
	Super::Unload();
}
