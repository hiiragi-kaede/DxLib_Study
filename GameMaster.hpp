#pragma once

namespace master {
	enum class GameState { Title, Game };
	void drawTitleScene();
	void drawTitleOptions();
	void Update();
	GameState GetGameState();
	void SetGameState(master::GameState state);
	void CheckGameStart();
	void UpdateTitleSelect();
	void ExitGame();
}