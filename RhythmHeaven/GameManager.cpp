#include "GameManager.h"
#include <Windows.h>
#include "Fmod.h"
#include "FmodEffect.h"

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

    void EndGame()
    {
        sound::Releasesound();
        effectsound::ReleaseEffectSound();
    }
}