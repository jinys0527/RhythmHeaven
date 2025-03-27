#pragma once

namespace input
{
	const int ESCAPE_KEY_INDEX = 0;
	const int USER_CMD_UP = 1;
	const int USER_CMD_DOWN = 2;
	const int USER_CMD_SPACE = 3;
	const int USER_CMD_ENTER = 4;

	const int MAX_KEY = 5;

	const int MAX_BUFFER = 2;

	void InitBuffer();
	void AddToBuffer(int key);
	bool HasPendingInput();
	int GetNextInput();
	void HandleBufferedInput(int currentInput, int nextInput);

	void Set(const int keyIndex, bool bOn);

	bool IsEscapeCmdOn();
	bool IsUpCmdOn();
	bool IsDownCmdOn();
	bool IsSpaceCmdOn();
	bool IsEnterCmdOn();

	void UpdateInput();

	void keyControl(bool& mButton);
}