#include "Engine/GameClass/MyGame.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Framework* mygame_ = new MyGame();
	
	mygame_->Run();

	delete mygame_;

	return 0;

}