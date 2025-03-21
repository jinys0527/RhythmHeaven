#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"

void Render()
{
	render::ScreenClear();
	anim::DrawScreen("Character/Chorus_boys_shame.txt", 
		"Character/Chorus_boys_shame.txt", 
		"Character/Chorus_boys_default.txt", 
		"Character/Conductor.txt");
	render::ScreenFlipping();
	//Print
}

int main()
{
	anim::StartGame();
	system("cls");
	while (1)//IsGameRun())
	{
		//ProcessInput();
		//Update();
		Render();
	}
	//EndGame();*/

	return 0;
}