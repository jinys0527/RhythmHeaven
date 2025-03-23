#include "InputSystem.h"
#include <cassert>
#include <windows.h>
#include "FmodEffect.h"

namespace input
{
	bool inputKeyTable[MAX_KEY];

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
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
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

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			input::Set(USER_CMD_SPACE, true);
			effectsound::EffectPlaySound(0);
		}
		else
		{
			input::Set(USER_CMD_SPACE, false);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			input::Set(USER_CMD_ENTER, true);
		}
		else
		{
			input::Set(USER_CMD_ENTER, false);
		}
	}
}