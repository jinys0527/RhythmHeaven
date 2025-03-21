#include <iostream>
#include "RenderSystem.h"

namespace render
{
	bool bScreenIndex;
	HANDLE hScreen[2];

	SMALL_RECT consoleScreenSize;
	INT consoleScreenX;
	INT consoleScreenY;

	SMALL_RECT updateScreenSize;
	INT updateScreenX;
	INT updateScreenY;

	
	void InitScreen()
	{
		//화면 버퍼 2개 생성 / 읽기 | 쓰기, 공유X, 보안 기본, 버퍼 내부 NULL 
		hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0; //커서 표시 여부(0 : Invisible, 1 : Visible)
		cursorInfo.dwSize = 1; //커서 크기(1 ~ 100)
		//표준 출력 핸들 설정 변경
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		consoleScreenSize.Left = csbi.srWindow.Left;
		consoleScreenSize.Right = csbi.srWindow.Right;
		consoleScreenSize.Top = csbi.srWindow.Top;
		consoleScreenSize.Bottom = csbi.srWindow.Bottom;

		consoleScreenX = csbi.dwSize.X;
		consoleScreenY = csbi.dwSize.Y;

		system("mode con cols=210 lines=75");
	}

	void ScreenRelease()
	{
		CloseHandle(hScreen[0]);
		CloseHandle(hScreen[1]);
	}

	void ScreenFlipping()
	{
		SetConsoleActiveScreenBuffer(GetScreenHandle());
		bScreenIndex = !bScreenIndex;
	}

	void ScreenClear()
	{
		COORD Coor = { consoleScreenSize.Left, consoleScreenSize.Top };
		DWORD dw;

		for (int y = 0; y < consoleScreenY; y++)
		{
			Coor.Y = consoleScreenSize.Top + y;
			//FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', consoleScreenX, Coor, &dw);
			FillConsoleOutputCharacter(GetScreenHandle(), ' ', consoleScreenX, Coor, &dw);
			//' '으로 updateScreenX만큼, 시작 좌표 : Coor, dw에 채운 문자 개수 저장
		}
	}

	void ScreenDraw(int x, int y, const char c)
	{
		DWORD dw;
		COORD Cur = { x, y };
		char buffer[10];
		sprintf_s(buffer, "%c", c);

		SetConsoleCursorPosition(GetScreenHandle(), Cur);

		WriteFile(GetScreenHandle(), buffer, 1, &dw, NULL);
		//현재 커서 위치에 문자 출력, 1개씩 출력
	}

	void ScreenDraw(int x, int y, const char* pStr)
	{
		DWORD dw;
		COORD Cur = { x, y };
		
		//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
		SetConsoleCursorPosition(GetScreenHandle(), Cur);


		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pStr, strlen(pStr), &dw, NULL);
		WriteFile(GetScreenHandle(), pStr, strlen(pStr), &dw, NULL);
	}

	HANDLE GetScreenHandle()
	{
		int index = (bScreenIndex ? 1 : 0);

		return hScreen[index];
	}

	void GotoXY(int x, int y)
	{
		COORD Cur = { x, y };

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	}

}