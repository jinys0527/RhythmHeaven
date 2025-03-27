#include "InputSystem.h"
#include <cassert>
#include <windows.h>
#include "FmodEffect.h"
#include "Anim.h"
#include "inc/fmod_errors.h"

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
		if ((bufferEnd + 1) % MAX_BUFFER != bufferStart) // ���۰� ���� ���� �ʾҴ��� Ȯ��
		{
			inputBuffer[bufferEnd] = key;
			bufferEnd = (bufferEnd + 1) % MAX_BUFFER; // ���� ����ó�� �۵�
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
		inputBuffer[bufferStart] = -1; // ����� ���� ���� �ʱ�ȭ
		bufferStart = (bufferStart + 1) % MAX_BUFFER;
		return cmd;
	}

	void HandleBufferedInput(int currentInput, int nextInput)
	{
		if (currentInput == USER_CMD_SPACE && nextInput == USER_CMD_ENTER)
		{
			anim::StartAnimation(anim::GetCharacter(2), anim::PLAYER_SHOUT); // �� ��° ĳ���� ����Ʈ �ִϸ��̼�
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
			input::Set(ESCAPE_KEY_INDEX, true);
			AddToBuffer(ESCAPE_KEY_INDEX);
		}
		else
		{
			input::Set(ESCAPE_KEY_INDEX, false);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			input::Set(USER_CMD_UP, true);
			AddToBuffer(USER_CMD_UP);
		}
		else
		{
			input::Set(USER_CMD_UP, false);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			input::Set(USER_CMD_DOWN, true);
			AddToBuffer(USER_CMD_DOWN);
		}
		else
		{
			input::Set(USER_CMD_DOWN, false);
		}

		if (isSpacePressed && !wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, true);
			AddToBuffer(USER_CMD_SPACE);
			anim::StartAnimation(anim::GetCharacter(2), anim::MUTE_CHANT); // �� ��° ĳ���� ���������� �ִϸ��̼�
 			effectsound::PauseChannel(effectsound::GetChannel(0));
		}
		else if(!isSpacePressed && wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, false); 
			anim::StartAnimation(anim::GetCharacter(2), anim::CHANT); // �� ��° ĳ���� ���ϱ� �ִϸ��̼�
			effectsound::UnpauseChannel(effectsound::GetChannel(0));
		}

		if (isSpacePressed && GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			input::Set(USER_CMD_ENTER, true);
			AddToBuffer(USER_CMD_ENTER);
			anim::StartAnimation(anim::GetCharacter(2), anim::PLAYER_SHOUT); // �� ��° ĳ���� ����Ʈ �ִϸ��̼�
		}
		else
		{
			input::Set(USER_CMD_ENTER, false);
		}
		wasSpacePressed = isSpacePressed;
	}
}