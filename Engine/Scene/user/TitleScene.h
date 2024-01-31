#pragma once

#include "../IScene.h"

class TitleScene : public IScene
{
private:



public:

	void Initialize() override;
	void Reset() override;
	
	void Update() override;

	void DrawModel() override;
	void DrawSprite() override;

private:


};