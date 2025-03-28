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

// �ִϸ��̼� ���¸� �����ϴ� �⺻ ��
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
        render::Draw("textFile/GameTitle.txt", 25, 4); //��ġ?
        cout << endl;
        game::delay(1);
        render::Draw("textFile/GameTitle11.txt", 35, 23); //��ġ!
        game::delay(1);

        render::menuButton(menuButton); // �޴� render

        render::Draw("textFile/conductor.txt", 3, 40);
        render::Draw("textFile/title_chorusboy.txt", 160, 40);

        render::setColor(render::lightgray, render::black);
        render::GotoXY(43, 35);
        cout << "\" �޴� �̵��� ����Ű �� ��" << endl;
        render::GotoXY(43, 37);
        cout << "  Ŭ���� �����̽��پ�! \"";

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
        note::InitTutorialNote(); //Ʃ�丮��
        anim::Shame();
        Render();

        bool isPlaying = false;
        sound::GetChannel(1)->isPlaying(&isPlaying);

        while (game::GetState() == game::State::Tutorial && isPlaying)
        {
            ProcessInput(); // �Է� ó�� Ȱ��ȭ

            if (!anim::IsShoutAnimating() && input::HasPendingInput())
            {
                int currentInput = input::GetNextInput();
                int nextInput = input::GetNextInput();
                // ���ۿ� ����� �Է¿� ���� �׼� ����
                input::HandleBufferedInput(currentInput, nextInput);
            }

            Update();
            QueryPerformanceCounter(&end);

            anim::UpdateAnimation(); //�ִϸ��̼� ������Ʈ

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
            ProcessInput(); // �Է� ó�� Ȱ��ȭ

            if (!anim::IsShoutAnimating() && input::HasPendingInput())
            {
                int currentInput = input::GetNextInput();
                int nextInput = input::GetNextInput();
                // ���ۿ� ����� �Է¿� ���� �׼� ����
                input::HandleBufferedInput(currentInput, nextInput);
            }

            Update();
            QueryPerformanceCounter(&end);

            anim::UpdateAnimation(); //�ִϸ��̼� ������Ʈ

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
   
    //��ŷ�� ���
    score::callShowScore();
    //ending -> end -> ranking sound������
    //ending ���� ���� ���� 0-7 bad, 8-15 normal, 16-18 true 0/18
    //raking -> title goto -> title
    sound::Releasesound();
    effectsound::ReleaseEffectSound();
    game::SetState(game::State::Title);
    goto loop;

    return 0;
}