#include "Engine.h"
#include "LevelManager.h"
#include "CUSTOMLevel.h"
#include "MainMenuLevel.h"
#include "TankCreation.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
	system("cls");
}

int main()
{
	InitConfig();

	MainMenuLevel* _level = new MainMenuLevel("MainMenu");
	M_LEVEL.SetLevel(_level);

	Engine _engine;
	_engine.Start();

	return EXIT_SUCCESS;
}