#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Fmod.h"
#include "FmodEffect.h"

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
    input::UpdateInput();
    // ���� - Ű �Է¿� ���� �ִϸ��̼� ����
   
    if (GetAsyncKeyState('5') & 0x8000)
    {
        // ��� ĳ���Ϳ� shame �ִϸ��̼� ����
        for (int i = 0; i < 2; i++)
        {
            anim::StartAnimation(anim::GetCharacter(i), anim::SHAME);
        }
    }
}

void Update()
{
    effectsound::Update();
}

int main()
{
    anim::StartGame();

    ULONGLONG nowTick = GetTickCount64();
    ULONGLONG prevTick = nowTick;

    sound::SoundSetUp();
    effectsound::EffectSoundSetUp();
    sound::Playsound(0);
    effectsound::EffectPlaySound(1, effectsound::GetChannel(3));
    note::InitNote();

    Render();

    while (1) //IsGameRun())
    {
        ProcessInput(); // �Է� ó�� Ȱ��ȭ
        Update();
        nowTick = GetTickCount64();

        anim::UpdateAnimation(); //�ִϸ��̼� ������Ʈ

        //ȭ�� ������ (33ms ���� - �� 30fps)
        if (nowTick - prevTick >= 33)
        {
            Render();
            prevTick = nowTick;
        }
    }

    //EndGame();
    return 0;
}