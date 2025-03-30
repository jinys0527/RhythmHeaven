#include "GameManager.h"
#include "Fmod.h"
#include "FmodEffect.h"
#include "ScoreSystem.h"
#include "Anim.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Note.h"
#include <iostream>
using namespace std;

namespace game
{
	State currentState = Title;

	void SetState(State nextState)
	{
		currentState = nextState;
	}

	State& GetState()
	{
		return currentState;
	}

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

    void SetUp()
    {
        anim::PrepareCharacter();
        isRun = true;
        sound::SoundSetUp();
        effectsound::EffectSoundSetUp();
    }

    void ShowTitle()
    {
        game::SetState(game::State::Title);
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
        cout << "  클릭은 엔터양! \"";

        while (game::GetState() == game::State::Title)
        {
            input::keyControl(menuButton);
        }
        sound::Stopsound(sound::GetChannel(0));
    }

    void StartTutorial(LARGE_INTEGER start, LARGE_INTEGER end)
    {
        note::InitTutorialNote(); //튜토리얼

        anim::Shame();

        sound::Playsound(1, sound::GetChannel(1));
        effectsound::EffectPlaySound(0, effectsound::GetChannel(0));

        QueryPerformanceCounter(&start);
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
                Render();
                start.QuadPart = end.QuadPart;
            }

            sound::GetChannel(1)->isPlaying(&isPlaying);
        }
        effectsound::GetChannel(0)->stop();
        game::SetState(game::State::Game);
    }

    void StartGame(LARGE_INTEGER start, LARGE_INTEGER end)
    {
        sound::Playsound(2, sound::GetChannel(2));

        QueryPerformanceCounter(&start);

        effectsound::EffectPlaySound(0, effectsound::GetChannel(0));
        note::InitNote();
        anim::Shame();
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

    void ShowEnding()
    {
        render::ScreenClear();
        render::ScreenFlipping();
        render::ReturnToStandardConsole();

        //ending 조건 맞춘 개수 0-7 bad, 8-15 normal, 16-18 true 0/18
        int presentScore = score::GetScore();
        render::showEnding(presentScore, 0, 0);

        system("cls");
    }

    void ShowRanking()
    {
        //랭킹씬 출력
        score::callShowScore();
    }

    void EndGame()
    {
        sound::Releasesound();
        effectsound::ReleaseEffectSound();
    }
}