#pragma once
#include <Windows.h>

namespace game
{
	enum State {
		Title = 0,
		Tutorial,
		Game,
		Ending,
		Ranking
	};
	
	void SetState(State nextState);
	State& GetState();

	void delay(int x);

	void Render();
	void ProcessInput();
	void Update();
	bool IsGameRun();
	void SetUp();

	void ShowTitle();
	void StartTutorial(LARGE_INTEGER start, LARGE_INTEGER end);
	void StartGame(LARGE_INTEGER start, LARGE_INTEGER end);
	void ShowEnding();
	void ShowRanking();
	void EndGame();
}