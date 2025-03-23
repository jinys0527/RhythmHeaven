#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"

void Render()
{
	render::ScreenClear();
	if (render::GetIndex())
	{
		anim::DrawScreen("Character/Chorus_boys_shame.txt",
			"Character/Chorus_boys_shame.txt",
			"Character/Chorus_boys_default.txt",
			"Character/Conductor.txt");
	}
	else
	{
		anim::DrawScreen("Character/Chorus_boys_default.txt",
			"Character/Chorus_boys_default.txt",
			"Character/Chorus_boys_default.txt",
			"Character/Conductor.txt");
	}
	
	render::ScreenFlipping();
	//Print
}

int main()
{
	anim::StartGame();

	ULONGLONG nowTick = GetTickCount64();
	ULONGLONG prevTick = nowTick;

	Render();
	while (1)//IsGameRun())
	{
		//ProcessInput();
		//Update();
		nowTick = GetTickCount64();

		ULONGLONG elapsedTick = nowTick - prevTick;
		if (elapsedTick >= 1000)
		{
			Render();

			prevTick = nowTick;
		}
	}
	//EndGame();*/

	return 0;
}