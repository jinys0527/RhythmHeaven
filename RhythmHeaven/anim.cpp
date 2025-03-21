#include <iostream>
#include "RenderSystem.h"
using namespace std;

int main()
{
	render::InitScreen();
	FILE* fp;
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;

	fopen_s(&fp, "Character/Conductor.txt", "rb");
	fopen_s(&fp1, "Character/Chorus_boys_shame.txt", "rb");
	fopen_s(&fp2, "Character/Chorus_boys_shame.txt", "rb");
	fopen_s(&fp3, "Character/Chorus_boys_default.txt", "rb");

	char* Word = new char[88];

	if (fp == NULL)
	{
		return 0;
	}

	if (fp1 == NULL)
	{
		return 0;
	}

	if (fp2 == NULL)
	{
		return 0;
	}
	
	if (fp3 == NULL)
	{
		return 0;
	}
	render::GotoXY(60, 0);
	cout << 'a';
	int index = 40;
	
	render::GotoXY(0, index);
	while (fgets(Word, 88, fp) != nullptr)
	{
		//render::ScreenDraw(0, index++, Word);
		cout << Word;
	}
	
	int index1 = 0;
		
	while (fgets(Word, 88, fp1) != nullptr)
	{
		//render::ScreenDraw(75, index1++, Word);
		render::GotoXY(60, index1++);
		cout << Word;
	}
	int index2 = 5;
	
	while (fgets(Word, 88, fp2) != nullptr)
	{
		//render::ScreenDraw(150, index2++, Word);
		render::GotoXY(110, index2++);
		cout << Word;
	}
	
	int index3 = 10;
	
	while (fgets(Word, 88, fp3) != nullptr)
	{
		//render::ScreenDraw(225, index3++, Word);
		render::GotoXY(160, index3++);
		cout << Word;
	}
	

	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	delete Word;
	getchar();
	//return 0;
}