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

	void DrawScreen(const char* filename1, const char* filename2, const char* filename3, const char* filename4)
	{
		DrawCharacter(70, 1, filename1);
		DrawCharacter(120, 6, filename2);
		DrawCharacter(170, 11, filename3);
		DrawCharacter(10, 40, filename4);
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
