#pragma once

namespace master {
	enum class GameState { Title, Game };
	void drawTitleScene();
	void Update();
	GameState GetGameState();
	void SetGameState(master::GameState state);
}