#pragma once

namespace master {
	enum class GameState { Title, Game, Config, GameOver };

	void Update();

	void drawTitleScene();
	void drawTitles();
	void UpdateTitleSelect();
	void TitleUpdate();

	void MoveToConfig();

	GameState GetGameState();
	void SetGameState(master::GameState state);
	
	void CheckGameStart();
	void ExitGame();

	unsigned getWhite();
	unsigned getOrange();
}