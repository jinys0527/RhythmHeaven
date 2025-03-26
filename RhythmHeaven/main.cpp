#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Fmod.h"
#include "FmodEffect.h"

// 애니메이션 상태를 관리하는 기본 값
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
    // 예시 - 키 입력에 따라 애니메이션 시작
   
    if (GetAsyncKeyState('5') & 0x8000)
    {
        // 모든 캐릭터에 shame 애니메이션 적용
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
        ProcessInput(); // 입력 처리 활성화
        Update();
        nowTick = GetTickCount64();

        anim::UpdateAnimation(); //애니메이션 업데이트

        //화면 렌더링 (33ms 마다 - 약 30fps)
        if (nowTick - prevTick >= 33)
        {
            Render();
            prevTick = nowTick;
        }
    }

    //EndGame();
    return 0;
}