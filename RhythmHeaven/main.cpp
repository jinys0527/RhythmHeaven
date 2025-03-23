#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"

// �ִϸ��̼� ���¸� �����ϴ� �⺻ ��
int currentAnimationState = 0;

void Render()
{
    render::ScreenClear();
    anim::DrawScreen();
    render::ScreenFlipping();
}

void ProcessInput()
{
    // ���� - Ű �Է¿� ���� �ִϸ��̼� ����
    if (GetAsyncKeyState('1') & 0x8000)
    {
        anim::StartAnimation(2, anim::CHANT); // �� ��° ĳ���� ���ϱ� �ִϸ��̼�
    }
    if (GetAsyncKeyState('2') & 0x8000)
    {
        anim::StartAnimation(2, anim::MUTE_CHANT); // �� ��° ĳ���� ���������� �ִϸ��̼�
    }
    if (GetAsyncKeyState('3') & 0x8000)
    {
        anim::StartAnimation(2, anim::SHOUT); // �� ��° ĳ���� ���� �ִϸ��̼�
    }

    if (GetAsyncKeyState('4') & 0x8000)
    {
        anim::StartAnimation(2, anim::MUTE_SHOUT); // �� ��° ĳ���� ���� �ִϸ��̼�
    }
    if (GetAsyncKeyState('5') & 0x8000)
    {
        // ��� ĳ���Ϳ� shame �ִϸ��̼� ����
        for (int i = 0; i < 2; i++)
        {
            anim::StartAnimation(i, anim::SHAME);
        }
    }
}

int main()
{
    anim::StartGame();

    ULONGLONG nowTick = GetTickCount64();
    ULONGLONG prevTick = nowTick;
    ULONGLONG animTick = nowTick;

    Render();

    while (1) //IsGameRun())
    {
        ProcessInput(); // �Է� ó�� Ȱ��ȭ

        nowTick = GetTickCount64();

        // �ִϸ��̼� ������Ʈ (200ms ����)
        if (nowTick - animTick >= 200)
        {
            anim::UpdateAnimation();
            animTick = nowTick;
        }

        // ȭ�� ������ (33ms ���� - �� 30fps)
        if (nowTick - prevTick >= 33)
        {
            Render();
            prevTick = nowTick;
        }
    }

    //EndGame();
    return 0;
}