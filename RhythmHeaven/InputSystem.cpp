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
		
		if (anim::IsShoutAnimating())
		{
			return;
		}

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

		if (isSpacePressed && !wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, true);
			anim::StartAnimation(2, anim::MUTE_CHANT); // 세 번째 캐릭터 조용해지는 애니메이션
 			effectsound::PauseChannel(effectsound::GetChannel(3));
			effectsound::EffectPlaySound(3, effectsound::GetChannel(4));
		}
		else if(!isSpacePressed && wasSpacePressed)
		{
			input::Set(USER_CMD_SPACE, false); 
			anim::StartAnimation(2, anim::CHANT); // 세 번째 캐릭터 말하기 애니메이션
			effectsound::UnpauseChannel(effectsound::GetChannel(3));
		}

		if (isSpacePressed && GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			input::Set(USER_CMD_ENTER, true);
			anim::StartAnimation(2, anim::SHOUT); // 세 번째 캐릭터 샤우트 애니메이션
		}
		else
		{
			input::Set(USER_CMD_ENTER, false);
		}
		wasSpacePressed = isSpacePressed;
	}
}