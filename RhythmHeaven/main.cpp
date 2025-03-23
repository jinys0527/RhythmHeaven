#include <iostream>
#include <Windows.h>
#include "Anim.h"
#include "RenderSystem.h"

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
    // 예시 - 키 입력에 따라 애니메이션 시작
    if (GetAsyncKeyState('1') & 0x8000)
    {
        anim::StartAnimation(2, anim::CHANT); // 세 번째 캐릭터 말하기 애니메이션
    }
    if (GetAsyncKeyState('2') & 0x8000)
    {
        anim::StartAnimation(2, anim::MUTE_CHANT); // 세 번째 캐릭터 조용해지는 애니메이션
    }
    if (GetAsyncKeyState('3') & 0x8000)
    {
        anim::StartAnimation(2, anim::SHOUT); // 세 번째 캐릭터 입장 애니메이션
    }

    if (GetAsyncKeyState('4') & 0x8000)
    {
        anim::StartAnimation(2, anim::MUTE_SHOUT); // 세 번째 캐릭터 입장 애니메이션
    }
    if (GetAsyncKeyState('5') & 0x8000)
    {
        // 모든 캐릭터에 shame 애니메이션 적용
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
        ProcessInput(); // 입력 처리 활성화

        nowTick = GetTickCount64();

        // 애니메이션 업데이트 (200ms 마다)
        if (nowTick - animTick >= 200)
        {
            anim::UpdateAnimation();
            animTick = nowTick;
        }

        // 화면 렌더링 (33ms 마다 - 약 30fps)
        if (nowTick - prevTick >= 33)
        {
            Render();
            prevTick = nowTick;
        }
    }

    //EndGame();
    return 0;
}