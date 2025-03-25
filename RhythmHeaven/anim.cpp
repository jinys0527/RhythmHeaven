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

	Character* chorus1 = nullptr;
	Character* chorus2 = nullptr;
	Character* player = nullptr;

	bool isShoutAnimating = false;

	// 애니메이션 프레임 배열
	const char* chantFrames[] = {
		"Character/Chorus_boys_silence.txt",
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
		"Character/Chorus_boys_silence.txt"
	};

	const char* fastChantFrames[] =	{
		"Character/Chorus_boys_silence.txt",
		"Character/Chorus_boys_sp2.txt",
		"Character/Chorus_boys_default.txt"
	};

	const char* fastMuteChantFrames[] = {
		"Character/Chorus_boys_default.txt",
		"Character/Chorus_boys_sp2.txt",
		"Character/Chorus_boys_silence.txt"
	};

	const char* shoutFrames[] = {
		"Character/Chorus_boys_silence.txt",
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
		"Character/Chorus_boys_silence.txt"
	};

	const char* fastShoutFrames[] = {
		"Character/Chorus_boys_silence.txt",
		"Character/Chorus_boys_enter2.txt",
		"Character/Chorus_boys_enter0.txt"
	};

	const char* fastMuteShoutFrames[] = {
		"Character/Chorus_boys_enter0.txt",
		"Character/Chorus_boys_enter2.txt",
		"Character/Chorus_boys_silence.txt"
	};

	const char* shameFrames[] = {
		"Character/Chorus_boys_shame.txt"
	};

	// 각 애니메이션 시퀀스의 프레임 개수
	const int chantFrameCount = sizeof(chantFrames) / sizeof(chantFrames[0]);
	const int muteChantFrameCount = sizeof(muteChantFrames) / sizeof(muteChantFrames[0]);
	const int fastChantFrameCount = sizeof(fastChantFrames) / sizeof(fastChantFrames[0]);
	const int fastMuteChantFrameCount = sizeof(fastMuteChantFrames) / sizeof(fastMuteChantFrames[0]);
	const int shoutFrameCount = sizeof(shoutFrames) / sizeof(shoutFrames[0]);
	const int muteShoutFrameCount = sizeof(muteShoutFrames) / sizeof(muteShoutFrames[0]);
	const int fastShoutFrameCount = sizeof(fastShoutFrames) / sizeof(fastShoutFrames[0]);
	const int fastMuteShoutFrameCount = sizeof(fastMuteShoutFrames) / sizeof(fastMuteShoutFrames[0]);
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
		InitCharacter(&characters[0], 70, 1, "Character/Chorus_boys_silence.txt", NONE, 0, false);
		//코러스 2
		InitCharacter(&characters[1], 120, 6, "Character/Chorus_boys_silence.txt", NONE, 0, false);
		//플레이어
		InitCharacter(&characters[2], 170, 11, "Character/Chorus_boys_default.txt", NONE, 0, false);
		//지휘자
		InitCharacter(&characters[3], 10, 40, "Character/Conductor.txt", NONE, 0, false);
		chorus1 = &characters[0];
		chorus2 = &characters[1];
		player = &characters[2];
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
		UpdateAnimation(GetCharacter(0));
		UpdateAnimation(GetCharacter(1));
		UpdateAnimation(GetCharacter(2));

		UpdateAIAnimation(GetCharacter(0), note::GetNotes(1), 22);
		UpdateAIAnimation(GetCharacter(1), note::GetNotes(2), 22);
	}

	void UpdateAnimation(Character*& character)
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
				isShoutAnimating = true;
				//effectsound::EffectPlaySound(2, effectsound::GetChannel(5));
				character->currentFrame = shoutFrames[character->frameIndex];
			}
			else
			{
				isShoutAnimating = false;
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
		case NONE:
			character->isAnimating = false;
			character->frameIndex--;
			break;
		}

	}

	void ResetState(Character*& character, bool isAnimating, AnimState currentState)
	{
		character->isAnimating = isAnimating;
		character->currentState = currentState;
	}

	void StartAnimation(Character*& character, AnimState state)
	{
		character->currentState = state;
		character->frameIndex = 0;
		character->isAnimating = true;

		// 애니메이션 시작 시 첫 프레임 설정
		switch (state)
		{
		case CHANT:
			character->currentFrame = chantFrames[0];
			break;
		case MUTE_CHANT:
			character->currentFrame = muteChantFrames[0];
			break;
		case FAST_CHANT:
			character->currentFrame = fastChantFrames[0];
			break;
		case FAST_MUTE_CHANT:
			character->currentFrame = fastMuteChantFrames[0];
			break;
		case SHOUT:
			character->currentFrame = shoutFrames[0];
			break;
		case SHAME:
			character->currentFrame = shameFrames[0];
			break;
		}
	}

	bool IsShoutAnimating()
	{
		return isShoutAnimating;
	}

	void AssignState(Character*& character, note::Note*& note, int index)
	{
		if (index >= 0 && index < 22) {
			switch (note[index].curNoteType)
			{
			case note::noteType::Chorus:
				character->currentState = CHANT;
				break;
			case note::noteType::Shout:
				character->currentState = SHOUT;
				break;
			}
		}
	}

	Character*& GetCharacter(int num)
	{
		switch (num)
		{
		case 0:
			return chorus1;
		case 1:
			return chorus2;
		case 2:
			return player;
		}
	}

	void UpdateAIAnimation(Character*& character, note::Note*& note, int noteSize)
	{
		unsigned int playPos = sound::GetPlayPosition();
		const int tolerance = 30; //30ms 오차 범위

		if (character->isAnimating)
			return;

		for (int i = 0; i < noteSize; i++)
		{
			if (i >= 0 && i < 22)
			{
				if ((note[i].startTime - tolerance) <= playPos && playPos <= (note[i].startTime + tolerance))
				{
					AssignState(character, note, i);
					if (note[i].duration < 200)
					{
						if (character->currentState == CHANT)
						{
							character->currentState = FAST_CHANT;
						}
						else if (character->currentState == SHOUT)
						{
							character->currentState = FAST_SHOUT;
						}
						bool animEnd = AIAnimEnd(character, note[i].startTime, note[i].duration);
						while (!animEnd)
						{
							animEnd = AIAnimEnd(character, note[i].startTime, note[i].duration);
						}
					}
					else if (note[i].duration >= 200)
					{
						bool animEnd = AIAnimEnd(character, note[i].startTime, note[i].duration);
						while (!animEnd)
						{
							animEnd = AIAnimEnd(character, note[i].startTime, note[i].duration);
						}
					}
				}
			}
			
			else
			{
				return;
			}
		}
	}

	bool AIAnimEnd(Character*& character, ULONGLONG startTime, ULONGLONG duration)
	{
		ULONGLONG currentTime = GetTickCount64();
		
		int animTime = 0;
		switch (character->currentState)
		{
		case CHANT:
			StartAnimation(character, CHANT);
			animTime = 33 * muteChantFrameCount;
			break;
		case FAST_CHANT:
			StartAnimation(character, FAST_CHANT);
			animTime = 33 * fastMuteChantFrameCount;
			break;
		case SHOUT:
			StartAnimation(character, SHOUT);
			animTime = 33 * shoutFrameCount;
			break;
		case FAST_SHOUT:
			StartAnimation(character, FAST_SHOUT);
			animTime = 33 * fastShoutFrameCount;
			break;
		case TOGGLE_CHANT:
			animTime = 0;
			DrawCharacter(character->x, character->y, "Character / Chorus_boys_default.txt");
			break;
		}

		ULONGLONG lastAnimStartTime = duration - animTime;

		if (currentTime - startTime >= lastAnimStartTime)
		{
			switch (character->currentState)
			{
			case CHANT:
				StartAnimation(character, MUTE_CHANT);
				break;
			case FAST_CHANT:
				StartAnimation(character, FAST_MUTE_CHANT);
				break;
			case SHOUT:
				StartAnimation(character, MUTE_SHOUT);
				break;
			case FAST_SHOUT:
				StartAnimation(character, FAST_MUTE_SHOUT);
				break;
			case TOGGLE_CHANT:
				DrawCharacter(character->x, character->y, "Character / Chorus_boys_silence.txt");
				break;
			}
			return true;
		}

		return false;
	}
}