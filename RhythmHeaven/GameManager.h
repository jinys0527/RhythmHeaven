#pragma once

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

	void EndGame();
}