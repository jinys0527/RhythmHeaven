#pragma once

namespace anim
{
	/*struct Animation
	{
		const char* _Address[] = { NULL, };
	};*/

	constexpr int MAX_CHARACTER_SIZE = 50;

	void StartGame();

	void DrawScreen(const char* filename1, const char* filename2, const char* filename3, const char* filename4);

	void DrawCharacter(int x, int y, const char* filename);
}