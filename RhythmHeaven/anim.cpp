#include <iostream>
#include "RenderSystem.h"
#include "Anim.h"
using namespace std;

namespace anim
{
    // 캐릭터 데이터
    Character characters[4];

    // 애니메이션 프레임 배열
    const char* chantFrames[] = {
        "Character/Chorus_boys_slience.txt",
        "Character/Chorus_boys_sp3.txt",
        "Character/Chorus_boys_sp2.txt",
        "Character/Chorus_boys_sp1.txt",
        "Character/Chorus_boys_sp0.txt",
        "Character/Chorus_boys_default.txt"
    };

    const char* muteChantFrames[] = {
        "Character/Chorus_boys_default.txt",
        "Character/Chorus_boys_sp0.txt",
        "Character/Chorus_boys_sp1.txt",
        "Character/Chorus_boys_sp2.txt",
        "Character/Chorus_boys_sp3.txt",
        "Character/Chorus_boys_slience.txt"
    };

    const char* shoutFrames[] = {
        "Character/Chorus_boys_slience.txt",
        "Character/Chorus_boys_enter3.txt",
        "Character/Chorus_boys_enter2.txt",
        "Character/Chorus_boys_enter1.txt",
        "Character/Chorus_boys_enter0.txt"
    };

    const char* muteShoutFrames[] = {
        "Character/Chorus_boys_enter0.txt",
        "Character/Chorus_boys_enter1.txt",
        "Character/Chorus_boys_enter2.txt",
        "Character/Chorus_boys_enter3.txt",
        "Character/Chorus_boys_slience.txt"
    };

    const char* shameFrames[] = {
        "Character/Chorus_boys_shame.txt"
        //,"Character/Chorus_boys_slience.txt"
    };

    // 각 애니메이션 시퀀스의 프레임 개수
    const int chantFrameCount = sizeof(chantFrames) / sizeof(chantFrames[0]);
    const int muteChantFrameCount = sizeof(muteChantFrames) / sizeof(muteChantFrames[0]);
    const int shoutFrameCount = sizeof(shoutFrames) / sizeof(shoutFrames[0]);
    const int muteShoutFrameCount = sizeof(muteShoutFrames) / sizeof(muteShoutFrames[0]);
    const int shameFrameCount = sizeof(shameFrames) / sizeof(shameFrames[0]);

    void StartGame()
    {
        render::InitScreen();

        // 캐릭터 초기화
        characters[0].x = 70;
        characters[0].y = 1;
        characters[0].currentFrame = "Character/Chorus_boys_default.txt";
        characters[0].currentState = NONE;
        characters[0].frameIndex = 0;
        characters[0].isAnimating = false;

        characters[1].x = 120;
        characters[1].y = 6;
        characters[1].currentFrame = "Character/Chorus_boys_default.txt";
        characters[1].currentState = NONE;
        characters[1].frameIndex = 0;
        characters[1].isAnimating = false;

        characters[2].x = 170;
        characters[2].y = 11;
        characters[2].currentFrame = "Character/Chorus_boys_default.txt";
        characters[2].currentState = NONE;
        characters[2].frameIndex = 0;
        characters[2].isAnimating = false;

        characters[3].x = 10;
        characters[3].y = 40;
        characters[3].currentFrame = "Character/Conductor.txt";
        characters[3].currentState = NONE;
        characters[3].frameIndex = 0;
        characters[3].isAnimating = false;

        // 최초 화면 출력
        DrawScreen();
    }

    void DrawScreen()
    {
        // 현재 캐릭터 프레임을 그린다
        for (int i = 0; i < 4; i++)
        {
            DrawCharacter(characters[i].x, characters[i].y, characters[i].currentFrame);
        }
    }

    void DrawCharacter(int x, int y, const char* filename)
    {
        FILE* fp;
        fopen_s(&fp, filename, "rb");
        if (fp == NULL)
        {
            return;
        }
        char* Word = new char[MAX_CHARACTER_SIZE];
        while (fgets(Word, MAX_CHARACTER_SIZE, fp) != NULL)
        {
            render::ScreenDraw(x, y++, Word);
        }
        fclose(fp);
        delete[] Word; // 메모리 누수 방지를 위해 delete[]로 수정
    }

    void UpdateAnimation()
    {
        bool anyAnimating = false;

        // 모든 캐릭터의 애니메이션 상태 업데이트
        for (int i = 0; i < 4; i++)
        {
            if (!characters[i].isAnimating)
                continue;

            anyAnimating = true;
            characters[i].frameIndex++;

            // 애니메이션 상태에 따라 프레임 업데이트
            switch (characters[i].currentState)
            {
            case CHANT:
                if (characters[i].frameIndex < chantFrameCount)
                    characters[i].currentFrame = chantFrames[characters[i].frameIndex];
                else
                {
                    characters[i].isAnimating = false;
                    characters[i].currentState = NONE;
                }
                break;

            case MUTE_CHANT:
                if (characters[i].frameIndex < muteChantFrameCount)
                    characters[i].currentFrame = muteChantFrames[characters[i].frameIndex];
                else
                {
                    characters[i].isAnimating = false;
                    characters[i].currentState = NONE;
                }
                break;

            case SHOUT:
                if (characters[i].frameIndex < shoutFrameCount)
                    characters[i].currentFrame = shoutFrames[characters[i].frameIndex];
                else
                {
                    characters[i].isAnimating = false;
                    characters[i].currentState = NONE;
                }
                break;

            case MUTE_SHOUT:
                if (characters[i].frameIndex < muteShoutFrameCount)
                    characters[i].currentFrame = muteShoutFrames[characters[i].frameIndex];
                else
                {
                    characters[i].isAnimating = false;
                    characters[i].currentState = NONE;
                }
                break;

            case SHAME:
                if (characters[i].frameIndex < shameFrameCount)
                    characters[i].currentFrame = shameFrames[characters[i].frameIndex];
                else
                {
                    characters[i].isAnimating = false;
                    characters[i].currentState = NONE;
                }
                break;
            }
        }
    }

    void StartAnimation(int characterIndex, AnimState state)
    {
        if (characterIndex < 0 || characterIndex >= 4)
            return;

        characters[characterIndex].currentState = state;
        characters[characterIndex].frameIndex = 0;
        characters[characterIndex].isAnimating = true;

        // 애니메이션 시작 시 첫 프레임 설정
        switch (state)
        {
        case CHANT:
            characters[characterIndex].currentFrame = chantFrames[0];
            break;
        case MUTE_CHANT:
            characters[characterIndex].currentFrame = muteChantFrames[0];
            break;
        case SHOUT:
            characters[characterIndex].currentFrame = shoutFrames[0];
            break;
        case MUTE_SHOUT:
            characters[characterIndex].currentFrame = muteShoutFrames[0];
            break;
        case SHAME:
            characters[characterIndex].currentFrame = shameFrames[0];
            break;
        }
    }

    bool IsAnimating()
    {
        for (int i = 0; i < 4; i++)
        {
            if (characters[i].isAnimating)
                return true;
        }
        return false;
    }
}