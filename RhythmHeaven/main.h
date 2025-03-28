#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>  // C ��Ÿ�� ���� ����� (fopen, fgets, fclose)
#include <cstring>

#define maxsize_gTitle 256

using namespace std;

void delay(int x)// x�� 0.5�� ��� ������
{
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    while (1)
    {
        QueryPerformanceCounter(&end);
        double elapsedTime = (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart; // ���� ��������
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
    cursorInfo.bVisible = 0; //Ŀ�� ǥ�� ����(0 : Invisible, 1 : Visible)
    cursorInfo.dwSize = 1; //Ŀ�� ũ��(1 ~ 100)
    //ǥ�� ��� �ڵ� ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    system("mode con cols=210 lines=75 | title ��ġ��ġ");
}

void gotoXY(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

void setColor(int forground, int background) // �۾� �� ��� ���� ����
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}

void Draw(const char* GameTitle, int x, int y) // ���� �ҷ��ͼ� ���� ���� ���
{
    FILE* fp;
    char* gTitle = new char[maxsize_gTitle];
    fopen_s(&fp, GameTitle, "rb");


    if (fp == NULL)
    {
        cout << "open ����\n";
        return;
    }


    while (1)
    {
        gotoXY(x, y++); // ���پ� �а� ���, y++�ؼ� ���� �ٵ� �ٽ� �а� ���
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
    INPUT inputs[6] = {}; // Ű �Է� 6�� (Ctrl ����/��, Shift ����/��, Esc ����/��)

    // Ctrl ����
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LCONTROL;

    // Shift ����
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_LSHIFT;

    // 'W' ����
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'W';

    // 'W' ��
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = 'W';
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    // Shift ��
    inputs[4].type = INPUT_KEYBOARD;
    inputs[4].ki.wVk = VK_LSHIFT;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

    // Ctrl ��
    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = VK_LCONTROL;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

    // ��� Ű �Է� ó��
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
            Draw("textFile/Bad_Ending.txt", x--, y); //��忣��
            Draw("textFile/Bad_Ending.txt", x++, y);
        }
        delay(1); // ��� HOLD
        Draw("textFile/bad_ment.txt", 5, 1);
    }
    if (end_result == 1)
    {
        while (i--)
        {
            Draw("textFile/Normal_Ending.txt", x--, y); //�븻����
            Draw("textFile/Normal_Ending.txt", x++, y);
        }
        delay(1); // ��� HOLD
        Draw("textFile/normal_ment.txt", 5, 1);
    }
    if (end_result == 2)
    {
        while (i--)
        {
            Draw("textFile/True_Ending.txt", x--, y); //������
            Draw("textFile/True_Ending.txt", x++, y);
        }
        delay(1); // ��� HOLD
        Draw("textFile/true_ment.txt", 5, 1);
    }

}

int ending_credit(int x)//0�� ���, 1�� �븻, 2�� ������
{

    int end_result;
    end_result = x;

    showEnding(end_result, 5, 1);



    return 0;
}