#include "Engine/GameClass/MyGame.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	MyGame* mygame_ = new MyGame();

	mygame_->Initialize();

	while (true)
	{
		mygame_->Update();

		if (mygame_->IsEndRequest()) {
			break;
		}

		mygame_->Draw();
	}

	mygame_->Finalize();

	return 0;

}