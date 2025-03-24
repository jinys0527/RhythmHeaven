#include "Note.h"
#include <iostream>
#include "RenderSystem.h"
#include "Anim.h"
#include "FmodEffect.h"
#include "Fmod.h"
using namespace std;

namespace anim
{
	// 캐릭터 데이터
	Character characters[4];
	
	bool isShoutAnimating = false;

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
		"Character/Chorus_boys_enter0.txt",
		"Character/Chorus_boys_enter1.txt",
		"Character/Chorus_boys_enter2.txt",
		"Character/Chorus_boys_enter3.txt",
		"Character/Chorus_boys_slience.txt"

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

	void InitCharacter(Character* character, int x, int y, const char* currentFrame, AnimState currentState, int frameIndex, bool isAnimating)
	{
		character->x = x;
		character->y = y;
		character->currentFrame = currentFrame;
		character->currentState = currentState;
		character->frameIndex = frameIndex;
		character->isAnimating = isAnimating;
	}

	void StartGame()
	{
		render::InitScreen();

		//코러스 1
		InitCharacter(&characters[0], 70, 1, "Character/Chorus_boys_default.txt", NONE, 0, false);
		//코러스 2
		InitCharacter(&characters[1], 120, 6, "Character/Chorus_boys_default.txt", NONE, 0, false);
		//플레이어
		InitCharacter(&characters[2], 170, 11, "Character/Chorus_boys_default.txt", NONE, 0, false);
		//지휘자
		InitCharacter(&characters[3], 10, 40, "Character/Conductor.txt", NONE, 0, false);

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
		UpdateAnimation(&characters[0]);
		UpdateAnimation(&characters[1]);
		UpdateAnimation(&characters[2]);
	}

	void UpdateAnimation(Character* character)
	{
		ULONGLONG nowTick = GetTickCount64();

		if (nowTick - character->lastAnimTick < 33)
		{
			return;
		}

		character->isAnimating = true;
		character->lastAnimTick = nowTick;
		character->frameIndex++;

		// 애니메이션 상태에 따라 프레임 업데이트
		switch (character->currentState)
		{
		case CHANT:
			if (character->frameIndex < chantFrameCount)
			{
				character->currentFrame = chantFrames[character->frameIndex];
			}
			else
			{
				ResetState(character, false, NONE);
			}
			break;

		case MUTE_CHANT:
			if (character->frameIndex < muteChantFrameCount)
			{
				character->currentFrame = muteChantFrames[character->frameIndex];
			}
			else
			{
				ResetState(character, false, NONE);
			}
			break;

		case SHOUT:
			if (character->frameIndex < shoutFrameCount)
			{
				if(character->frameIndex == 1)
				{
					isShoutAnimating = true;
					effectsound::EffectPlaySound(2, effectsound::GetChannel(5));
				}
				character->currentFrame = shoutFrames[character->frameIndex];
			}
			else
			{
				isShoutAnimating = false;
				ResetState(character, false, NONE);
			}
			break;

		case MUTE_SHOUT:
			if (character->frameIndex < muteShoutFrameCount)
			{
				character->currentFrame = muteShoutFrames[character->frameIndex];
			}
			else
			{
				ResetState(character, false, NONE);
			}
			break;

		case SHAME:
			if (character->frameIndex < shameFrameCount)
			{
				character->currentFrame = shameFrames[character->frameIndex];
			}
			else
			{
				ResetState(character, false, NONE);
			}
			break;
		}

	}

	void ResetState(Character* character, bool isAnimating, AnimState currentState)
	{
		character->isAnimating = isAnimating;
		character->currentState = currentState;
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

	bool IsShoutAnimating()
	{
		return isShoutAnimating;
	}

	void UpdateAIAnimation(note::Note*& note, int noteSize, unsigned long long currentTime)
	{
		/*unsigned int playPos = sound::GetPlayPosition();
		for (int i = 0; i < noteSize; i++)
		{
			if (note[i].startTime < playPos)
			{
				return;
			}
			if (note[i].startTime == playPos)
			{

			}
		}*/
	}
}