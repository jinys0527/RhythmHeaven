#include <iostream>
#include "RenderSystem.h"
#include "Anim.h"
using namespace std;

namespace anim
{
	void StartGame()
	{
		render::InitScreen();
		DrawCharacter(70, 1, "Character/Chorus_boys_shame.txt");
		DrawCharacter(120, 6, "Character/Chorus_boys_shame.txt");
		DrawCharacter(170, 11, "Character/Chorus_boys_default.txt");
		DrawCharacter(10, 40, "Character/Conductor.txt");
	}

	void DrawCharacter(int x, int y, const char* filename)
	{
		FILE* fp;
		fopen_s(&fp, filename, "rb");

		if (fp == NULL)
		{
			return;
		}

		char* Word = new char[MAX_CHARACTER_SIZE];

		while (fgets(Word, MAX_CHARACTER_SIZE, fp) != NULL)
		{
			render::ScreenDraw(x, y++, Word);
		}

		fclose(fp);
		delete Word;
	}
}
