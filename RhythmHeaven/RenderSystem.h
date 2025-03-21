#pragma once
#include <Windows.h>

namespace render
{
	void InitScreen();
	void ScreenRelease();

	void ScreenFlipping();
	void ScreenClear();

	void ScreenDraw(int x, int y, const char c);
	void ScreenDraw(int x, int y, const char* pStr);

	HANDLE GetScreenHandle();
	void GotoXY(int x, int y);
}