#include <iostream>
#include "RenderSystem.h"
#include "GameManager.h"
#include "Fmod.h"

using namespace std;

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
		//ȭ�� ���� 2�� ���� / �б� | ����, ����X, ���� �⺻, ���� ���� NULL 
		hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0; //Ŀ�� ǥ�� ����(0 : Invisible, 1 : Visible)
		cursorInfo.dwSize = 1; //Ŀ�� ũ��(1 ~ 100)
		//ǥ�� ��� �ڵ� ���� ����
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
			FillConsoleOutputCharacter(GetScreenHandle(), ' ', consoleScreenX, Coor, &dw);
			//' '���� updateScreenX��ŭ, ���� ��ǥ : Coor, dw�� ä�� ���� ���� ����
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
		//���� Ŀ�� ��ġ�� ���� ���, 1���� ���
	}

	void ScreenDraw(int x, int y, const wchar_t* str)
	{
		DWORD dw;
		COORD Cur = { x, y };

		SetConsoleCursorPosition(GetScreenHandle(), Cur);

		WriteConsoleW(GetScreenHandle(), str, wcslen(str) * sizeof(wchar_t), &dw, NULL);
		//���� Ŀ�� ��ġ�� ���� ���, 1���� ���
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

	void DrawWord(int x, int y, const char* filename)
	{
		FILE* fp;
		fopen_s(&fp, filename, "rb");
		if (fp == NULL)
		{
			return;
		}
		char* Word = new char[maxsize_gTitle];
		static int xPos = x;
		while (fgets(Word, maxsize_gTitle, fp) != NULL)
		{   
			xPos = x;
			for (int i = 0; i < strlen(Word); i++)
			{
				char tem = Word[i];


				if (tem == '1')
				{
					setColor_DB(lightgray, black);
					ScreenDraw(x, y, L"��");
				}
				if (tem == '2')
				{
					setColor_DB(darkgray, black);
					ScreenDraw(x, y, L"��");
				}
				if (tem == '8')
				{
					setColor_DB(blue, black);
					ScreenDraw(x, y, L"��");
				}
				if (tem == '3')
				{
					setColor_DB(red, black);
					ScreenDraw(x, y, L"��");
				}
				if (tem == '4')
				{
					setColor_DB(darkgray, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '6')
				{
					setColor_DB(lightgreen, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == 'O')
				{
					setColor_DB(white, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == 'Q')
				{
					setColor_DB(darkgray, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '%')
				{
					setColor_DB(darkgray, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '0')
				{
					setColor_DB(white, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '@')
				{
					setColor_DB(yellow, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '-')
				{
					setColor_DB(lightblue, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '+')
				{
					setColor_DB(lightred, black);
					ScreenDraw(xPos++, y, L"��");
				}
				if (tem == '\n')
				{
					xPos = x; // X ��ġ �ʱ�ȭ
				}
				if (tem == ' ')
				{
					ScreenDraw(xPos, y, L" "); // ������ ��ġ �̵� ���� ���
					xPos++; // ��Ȯ�� ����
				}

				setColor_DB(white, black);
			}
			y++;
		}
		fclose(fp);
		delete[] Word;
	}

	bool GetIndex()
	{
		return bScreenIndex;
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

	void setColor(int forground, int background) // �۾� �� ��� ���� ����
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		int code = forground + background * 16;
		SetConsoleTextAttribute(consoleHandle, code);
	}

	void setColor_DB(int forground, int background) // �۾� �� ��� ���� ����
	{
		HANDLE consoleHandle = GetScreenHandle();
		int code = forground + background * 16;
		SetConsoleTextAttribute(consoleHandle, code);
	}

	void menuButton(bool mButton)
	{
		if (mButton == 0)
		{
			Draw("textFile/button1.txt", 55, 45);
		}
		if (mButton == 1)
		{
			Draw("textFile/button2.txt", 73, 45);
		}
	}

	void Draw(const char* GameTitle, int x, int y) // ���� �ҷ��ͼ� ���� ���� ���
	{
		FILE* fp;
		char* gTitle = new char[maxsize_gTitle];
		fopen_s(&fp, GameTitle, "rb");


		if (fp == NULL)
		{
			return;
		}


		while (1)
		{
			GotoXY(x, y++); // ���پ� �а� ���, y++�ؼ� ���� �ٵ� �ٽ� �а� ���
			fgets(gTitle, maxsize_gTitle, fp);
			for (int i = 0; i < strlen(gTitle); i++)
			{

				char tem = gTitle[i];


				if (tem == '1')
				{
					setColor(lightgray, black);
					cout << "��";
				}
				if (tem == '2')
				{
					setColor(darkgray, black);
					cout << "��";
				}
				if (tem == '8')
				{
					setColor(blue, black);
					cout << "��";
				}
				if (tem == '3')
				{
					setColor(red, black);
					cout << "��";
				}
				if (tem == '4')
				{
					setColor(darkgray, black);
					cout << "��";
				}
				if (tem == '6')
				{
					setColor(lightgreen, black);
					cout << "��";
				}
				if (tem == 'O')
				{
					setColor(white, black);
					cout << "��";
				}
				if (tem == 'Q')
				{
					setColor(darkgray, black);
					cout << "��";
				}
				if (tem == '%')
				{
					setColor(darkgray, black);
					cout << "��";
				}
				if (tem == '0')
				{
					setColor(white, black);
					cout << "��";
				}
				if (tem == '@')
				{
					setColor(yellow, black);
					cout << "��";
				}
				if (tem == '-')
				{
					setColor(lightblue, black);
					cout << "��";
				}
				if (tem == '+')
				{
					setColor(lightred, black);
					cout << "��";
				}
				if (tem == '\n')
				{
					cout << "\n";
				}
				if (tem == ' ')
				{
					cout << " ";
				}

				setColor(white, black);
			}

			if (feof(fp)) break;
		}
		fclose(fp);
	}

	void initScreen_Normal()
	{
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = 0; //Ŀ�� ǥ�� ����(0 : Invisible, 1 : Visible)
		cursorInfo.dwSize = 1; //Ŀ�� ũ��(1 ~ 100)
		//ǥ�� ��� �ڵ� ���� ����
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

		system("mode con cols=210 lines=75 | title ��ġ��ġ");
	}

	//ending credit
	void showEnding(int end_result, int x, int y)
	{
		int i = 10;
		if (end_result >= 0 && end_result < 8)
		{
			sound::Playsound(3, sound::GetChannel(3));
			Draw("textFile/Bad_Ending.txt", x, y); //��忣��
			game::delay(10); // ��� HOLD
			Draw("textFile/bad_ment.txt", 5, 1);
			game::delay(5);
		}
		if (end_result >= 8 && end_result < 16)
		{
			sound::Playsound(4, sound::GetChannel(4));
			Draw("textFile/Normal_Ending.txt", x, y); //�븻����
			game::delay(10); // ��� HOLD
			Draw("textFile/normal_ment.txt", 5, 1);
			game::delay(5);
		}
		if (end_result >= 16 && end_result <= 18)
		{
			sound::Playsound(5, sound::GetChannel(5));
			Draw("textFile/True_Ending.txt", x, y); //������
			game::delay(10); // ��� HOLD
			Draw("textFile/true_ment.txt", 5, 1);
			game::delay(5);
		}
	}

	int ending_credit(int x)//0�� ���, 1�� �븻, 2�� ������
	{

		int end_result;
		end_result = x;

		showEnding(end_result, 5, 1);



		return 0;
	}

	void ReturnToStandardConsole() {
		// ���� ���۸� ���� ���ҽ� ����
		render::ScreenRelease();  // ���� �̷� �Լ��� �ִٸ� ȣ��

		// ǥ�� ��� �ڵ� ���
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// �ܼ� ��� �缳��
		DWORD mode = ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT;
		SetConsoleMode(hStdOut, mode);

		// ȭ�� �����
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		FillConsoleOutputCharacter(hStdOut, ' ', dwConSize, coordScreen, &cCharsWritten);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(hStdOut, coordScreen);

		// Ŀ�� ǥ�� (�ʿ��)
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;  // Ŀ�� ũ�� (1~100)
		cursorInfo.bVisible = TRUE;  // Ŀ�� ǥ��
		SetConsoleCursorInfo(hStdOut, &cursorInfo);
	}
}