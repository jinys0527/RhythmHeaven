#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>  // C 스타일 파일 입출력 (fopen, fgets, fclose)
#include <cstring>

#define maxsize_gTitle 256

using namespace std;

void delay(int x)// x는 0.5초 몇번 곱할지
{
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    while (1)
    {
        QueryPerformanceCounter(&end);
        double elapsedTime = (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart; // 몇초 지났는지
        if (elapsedTime >= x * 500)
        {
            break;
        }
    }
}

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

void initScreen()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0; //커서 표시 여부(0 : Invisible, 1 : Visible)
    cursorInfo.dwSize = 1; //커서 크기(1 ~ 100)
    //표준 출력 핸들 설정 변경
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    system("mode con cols=210 lines=75 | title 눈치박치");
}

void gotoXY(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

void setColor(int forground, int background) // 글씨 및 배경 색깔 설정
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}

void Draw(const char* GameTitle, int x, int y) // 파일 불러와서 색깔 입혀 출력
{
    FILE* fp;
    char* gTitle = new char[maxsize_gTitle];
    fopen_s(&fp, GameTitle, "rb");


    if (fp == NULL)
    {
        cout << "open 실패\n";
        return;
    }


    while (1)
    {
        gotoXY(x, y++); // 한줄씩 읽고 출력, y++해서 다음 줄도 다시 읽고 출력
        fgets(gTitle, maxsize_gTitle, fp);
        for (int i = 0; i < strlen(gTitle); i++)
        {

            char tem = gTitle[i];


            if (tem == '1')
            {
                setColor(lightgray, black);
                cout << "■";
            }
            if (tem == '2')
            {
                setColor(darkgray, black);
                cout << "∥";
            }
            if (tem == '8')
            {
                setColor(blue, black);
                cout << "■";
            }
            if (tem == '3')
            {
                setColor(red, black);
                cout << "■";
            }

            if (tem == 'O')
            {
                setColor(white, black);
                cout << "■";
            }
            if (tem == 'Q')
            {
                setColor(darkgray, black);
                cout << "◆";
            }
            if (tem == '%')
            {
                setColor(darkgray, black);
                cout << "■";
            }
            if (tem == '0')
            {
                setColor(white, black);
                cout << "■";
            }
            if (tem == '@')
            {
                setColor(yellow, black);
                cout << "■";
            }
            if (tem == '-')
            {
                setColor(lightblue, black);
                cout << "■";
            }
            if (tem == '+')
            {
                setColor(lightred, black);
                cout << "■";
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

void sendCtrlShiftW() {
    INPUT inputs[6] = {}; // 키 입력 6개 (Ctrl 누름/뗌, Shift 누름/뗌, Esc 누름/뗌)

    // Ctrl 누름
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LCONTROL;

    // Shift 누름
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_LSHIFT;

    // 'W' 누름
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'W';

    // 'W' 뗌
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = 'W';
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    // Shift 뗌
    inputs[4].type = INPUT_KEYBOARD;
    inputs[4].ki.wVk = VK_LSHIFT;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

    // Ctrl 뗌
    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = VK_LCONTROL;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

    // 모든 키 입력 처리
    SendInput(6, inputs, sizeof(INPUT));
}


//ending credit
void showEnding(int end_result, int x, int y)
{
    int i = 10;
    if (end_result == 0)
    {
        while (i--)
        {
            Draw("textFile/Bad_Ending.txt", x--, y); //배드엔딩
            Draw("textFile/Bad_Ending.txt", x++, y);
        }
        delay(1); // 잠시 HOLD
        Draw("textFile/bad_ment.txt", 5, 1);
    }
    if (end_result == 1)
    {
        while (i--)
        {
            Draw("textFile/Normal_Ending.txt", x--, y); //노말엔딩
            Draw("textFile/Normal_Ending.txt", x++, y);
        }
        delay(1); // 잠시 HOLD
        Draw("textFile/normal_ment.txt", 5, 1);
    }
    if (end_result == 2)
    {
        while (i--)
        {
            Draw("textFile/True_Ending.txt", x--, y); //진엔딩
            Draw("textFile/True_Ending.txt", x++, y);
        }
        delay(1); // 잠시 HOLD
        Draw("textFile/true_ment.txt", 5, 1);
    }

}

int ending_credit(int x)//0은 배드, 1은 노말, 2는 진엔딩
{

    int end_result;
    end_result = x;

    showEnding(end_result, 5, 1);



    return 0;
}