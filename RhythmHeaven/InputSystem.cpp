#include "InputSystem.h"
#include <cassert>
#include <windows.h>
#include "FmodEffect.h"
#include "Anim.h"
#include "inc/fmod_errors.h"
#include "ScoreSystem.h"
#include "Note.h"
#include "GameManager.h"
#include "RenderSystem.h"

namespace input
{
	bool inputKeyTable[MAX_KEY];

	bool wasSpacePressed = false;

	int inputBuffer[MAX_BUFFER];
	int bufferStart = 0;
	int bufferEnd = 0;

	void InitBuffer()
	{
		for (int i = 0; i < MAX_BUFFER; i++)
		{
			inputBuffer[i] = -1;
		}
		bufferStart = 0;
		bufferEnd = 0;
	}

	void AddToBuffer(int key)
	{
		if ((bufferEnd + 1) % MAX_BUFFER != bufferStart) // 버퍼가 가득 차지 않았는지 확인
		{
			inputBuffer[bufferEnd] = key;
			bufferEnd = (bufferEnd + 1) % MAX_BUFFER; // 원형 버퍼처럼 작동
		}
	}

	bool HasPendingInput()
	{
		return bufferStart != bufferEnd;
	}

	int GetNextInput()
	{
		if (!HasPendingInput())
		{
			return -1;
		}
		int cmd = inputBuffer[bufferStart];
		inputBuffer[bufferStart] = -1; // 사용한 버퍼 슬롯 초기화
		bufferStart = (bufferStart + 1) % MAX_BUFFER;
		return cmd;
	}

	void HandleBufferedInput(int currentInput, int nextInput)
	{
		if (currentInput == USER_CMD_SPACE && nextInput == USER_CMD_ENTER)
		{
			anim::StartAnimation(anim::GetCharacter(2), anim::PLAYER_SHOUT); // 세 번째 캐릭터 샤우트 애니메이션
		}
	}

	void Set(const int keyIndex, bool bOn)
	{
		assert(keyIndex >= 0 && keyIndex < MAX_KEY);

		inputKeyTable[keyIndex] = bOn;
	}

	bool IsEscapeCmdOn()
	{
		return inputKeyTable[ESCAPE_KEY_INDEX];
	}

	bool IsUpCmdOn()
	{
		return inputKeyTable[USER_CMD_UP];
	}

	bool IsDownCmdOn()
	{
		return inputKeyTable[USER_CMD_DOWN];
	}

	bool IsSpaceCmdOn()
	{
		return inputKeyTable[USER_CMD_SPACE];
	}

	bool IsEnterCmdOn()
	{
		return inputKeyTable[USER_CMD_ENTER];
	}

	void UpdateInput()
	{
		bool isSpacePressed = (GetKeyState(VK_SPACE) & 0x8000) != 0;

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			if (game::GetState() == game::State::Tutorial)
			{
				bool isPlay;
				sound::GetChannel(1)->isPlaying(&isPlay);
				if (isPlay)
				{
					sound::GetChannel(1)->stop();
				}
				game::SetState(game::State::Game);
			}
			input::Set(ESCAPE_KEY_INDEX, true);
		}
		else
		{
			input::Set(ESCAPE_KEY_INDEX, false);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			input::Set(USER_CMD_UP, true);
		}
		else
		{
			input::Set(USER_CMD_UP, false);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			input::Set(USER_CMD_DOWN, true);
		}
		else
		{
			input::Set(USER_CMD_DOWN, false);
		}

		if (isSpacePressed && !wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, true);
			if (bufferStart != 1)
			{
				AddToBuffer(USER_CMD_SPACE);
			}
			anim::StartAnimation(anim::GetCharacter(2), anim::MUTE_CHANT); // 세 번째 캐릭터 조용해지는 애니메이션
 			effectsound::PauseChannel(effectsound::GetChannel(0));
			if (game::GetState() == game::State::Game)
			{
				score::JudgeEndTime(anim::GetCharacter(2), note::GetNotes(anim::GetCharacter(2)));
			}
			else if (game::GetState() == game::State::Tutorial)
			{
				score::JudgeEndTime(anim::GetCharacter(2), note::GetTutorialNotes(anim::GetCharacter(2)));
			}

		}
		else if(!isSpacePressed && wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, false); 
			anim::StartAnimation(anim::GetCharacter(2), anim::CHANT); // 세 번째 캐릭터 말하기 애니메이션
			effectsound::UnpauseChannel(effectsound::GetChannel(0));
			if (game::GetState() == game::State::Game)
			{
				score::JudgeStartTime(anim::GetCharacter(2), note::GetNotes(anim::GetCharacter(2)));
			}
			else if (game::GetState() == game::State::Tutorial)
			{
				score::JudgeStartTime(anim::GetCharacter(2), note::GetTutorialNotes(anim::GetCharacter(2)));
			}
		}

		if (isSpacePressed && GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			input::Set(USER_CMD_ENTER, true);
			if (bufferStart == 1)
			{
				AddToBuffer(USER_CMD_ENTER);
			}
			
			anim::StartAnimation(anim::GetCharacter(2), anim::PLAYER_SHOUT); // 세 번째 캐릭터 샤우트 애니메이션
			score::JudgeStartTime(anim::GetCharacter(2), note::GetNotes(anim::GetCharacter(2)));
		}
		else
		{
			input::Set(USER_CMD_ENTER, false);
		}
		wasSpacePressed = isSpacePressed;
	}

	void keyControl(bool& mButton)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (mButton == 1)
			{
				effectsound::EffectPlaySound(2, effectsound::GetChannel(2));
				render::Draw("textFile/erase_menuButton.txt", 55, 45);
				render::menuButton(!mButton);
				mButton = 0;
			}

		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (mButton == 0)
			{
				effectsound::EffectPlaySound(2, effectsound::GetChannel(2));
				render::Draw("textFile/erase_menuButton.txt", 55, 45);
				render::menuButton(!mButton);
				mButton = 1;
			}

		}

		if (mButton == 0)
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				effectsound::EffectPlaySound(3, effectsound::GetChannel(3));
				system("cls");
				game::SetState(game::State::Tutorial);
			}
		}
		if (mButton == 1)
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				effectsound::EffectPlaySound(3, effectsound::GetChannel(3));
				game::EndGame();
				exit(0);
			}
		}
	}
}