#pragma once

namespace anim
{
	/*struct Animation
	{
		const char* _Address[] = { NULL, };
	};*/

	constexpr int MAX_CHARACTER_SIZE = 50;

	void StartGame();

	void DrawCharacter(int x, int y, const char* filename);
}