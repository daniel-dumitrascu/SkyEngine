#include "../../engine/sources/system/System.h"
#include "../../game/sources/Game.h"

int main()
{
	System* sys = System::GetSystem();
	sys->SetApplication(&Game::GetInstance(), "The Great Escape Game");
	
	sys->Init();
	sys->Run();
	sys->Close();

	return 0;
}