#pragma once
#include <Windows.h>
#define maxsize_gTitle 256

namespace render
{
    enum
    {
        black,
        blue,
        green,
        cyan,
        red,
        purple,
        brown,
        lightgray,
        darkgray,
        lightblue,
        lightgreen,
        lightcyan,
        lightred,
        lightpurple,
        yellow,
        white
    };

	void InitScreen();
	void ScreenRelease();

	void ScreenFlipping();
	void ScreenClear();

	void ScreenDraw(int x, int y, const char c);
	void ScreenDraw(int x, int y, const char* pStr);
	
	bool GetIndex();

	HANDLE GetScreenHandle();
	void GotoXY(int x, int y);

	void setColor(int forground, int background);
    void menuButton(bool mButton);
	void Draw(const char* GameTitle, int x, int y);
    void showEnding(int end_result, int x, int y);
    int ending_credit(int x);
}