#include <iostream>
#include <windows.h>
#include "Anim.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Fmod.h"
#include "FmodEffect.h"
#include "Note.h"
#include "GameManager.h"
#include "ScoreSystem.h"
using namespace std;

// 애니메이션 상태를 관리하는 기본 값
int currentAnimationState = 0;
bool isRun = true;

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

bool IsGameRun()
{
    return isRun;
}

int main()
{   
    LARGE_INTEGER start, end; // QPC

    loop:

    anim::StartGame();

    sound::SoundSetUp();
    effectsound::EffectSoundSetUp();

    ////title
    {
        bool menuButton = 0;
        sound::Playsound(0, sound::GetChannel(0));
        render::Draw("textFile/GameTitle.txt", 25, 4); //눈치?
        cout << endl;
        game::delay(1);
        render::Draw("textFile/GameTitle11.txt", 35, 23); //코치!
        game::delay(1);

        render::menuButton(menuButton); // 메뉴 render

        render::Draw("textFile/conductor.txt", 3, 40);
        render::Draw("textFile/title_chorusboy.txt", 160, 40);

        render::setColor(render::lightgray, render::black);
        render::GotoXY(43, 35);
        cout << "\" 메뉴 이동은 방향키 ↑ ↓" << endl;
        render::GotoXY(43, 37);
        cout << "  클릭은 스페이스바양! \"";

        while (game::GetState() == game::State::Title)
        {
            input::keyControl(menuButton);
        }
        sound::Stopsound(sound::GetChannel(0));
    }
    
    //Tutorial
    {
        sound::Playsound(1, sound::GetChannel(1));

        QueryPerformanceCounter(&start);

        effectsound::EffectPlaySound(0, effectsound::GetChannel(0));
        note::InitTutorialNote(); //튜토리얼
        anim::Shame();
        Render();

        bool isPlaying = false;
        sound::GetChannel(1)->isPlaying(&isPlaying);

        while (game::GetState() == game::State::Tutorial && isPlaying)
        {
            ProcessInput(); // 입력 처리 활성화

            if (!anim::IsShoutAnimating() && input::HasPendingInput())
            {
                int currentInput = input::GetNextInput();
                int nextInput = input::GetNextInput();
                // 버퍼에 저장된 입력에 따라 액션 실행
                input::HandleBufferedInput(currentInput, nextInput);
            }

            Update();
            QueryPerformanceCounter(&end);

            anim::UpdateAnimation(); //애니메이션 업데이트

            if (end.QuadPart - start.QuadPart >= 40)
            {
                render::DrawWord(3, 1, "textFile/practice.txt");
                render::DrawWord(170, 67, "textFile/skip.txt");
                Render();
                start.QuadPart = end.QuadPart;
            }

            sound::GetChannel(1)->isPlaying(&isPlaying);
        }
        effectsound::GetChannel(0)->stop();
    }
    //tutorial -> esc -> game
    //tutorial -> end -> game sound::GetChannel(1)->isPlaying(&bool value)

    //Game
    {
        sound::Playsound(2, sound::GetChannel(2));

        QueryPerformanceCounter(&start);

        effectsound::EffectPlaySound(0, effectsound::GetChannel(0));
        note::InitNote();
        anim::Shame();
        Render();
        bool isPlaying;

        while (IsGameRun()) //IsGameRun())
        {
            ProcessInput(); // 입력 처리 활성화

            if (!anim::IsShoutAnimating() && input::HasPendingInput())
            {
                int currentInput = input::GetNextInput();
                int nextInput = input::GetNextInput();
                // 버퍼에 저장된 입력에 따라 액션 실행
                input::HandleBufferedInput(currentInput, nextInput);
            }

            Update();
            QueryPerformanceCounter(&end);

            anim::UpdateAnimation(); //애니메이션 업데이트

            if (end.QuadPart - start.QuadPart >= 40)
            {
                Render();
                start.QuadPart = end.QuadPart;
            }

            sound::GetChannel(2)->isPlaying(&isPlaying);
            if (!isPlaying)
            {
                isRun = false;
            }
        }
        effectsound::GetChannel(0)->stop();
    }

    render::ScreenClear();
    render::ScreenFlipping();
    render::ReturnToStandardConsole();

    int presentScore = score::GetScore();
    render::showEnding(presentScore, 0, 0);

    system("cls");
   
    //랭킹씬 출력
    score::callShowScore();
    //ending -> end -> ranking sound끝나면
    //ending 조건 맞춘 개수 0-7 bad, 8-15 normal, 16-18 true 0/18
    //raking -> title goto -> title
    sound::Releasesound();
    effectsound::ReleaseEffectSound();
    game::SetState(game::State::Title);
    goto loop;

    return 0;
}