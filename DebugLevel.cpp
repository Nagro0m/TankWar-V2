#include "DebugLevel.h"
#include "Tank.h"

DebugLevel::DebugLevel(const string& _name) : Level(_name)
{
	hud = nullptr;
}

void DebugLevel::InitLevel()
{
	Super::InitLevel();
	hud = GetGameMode()->GetHUD();

	SpawnActor<Tank>();
	//hud->AddToViewport(gameHUD.canvas);
}
