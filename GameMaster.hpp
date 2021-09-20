#pragma once

namespace master {
	enum class GameState { Title, Game, Config };
	void drawTitleScene();
	void drawTitles();
	void UpdateTitleSelect();
	void TitleUpdate();
	
	void drawConfigs();
	void ConfigUpdate();
	void UpdateConfigSelect();
	void ChangeConfig();
	void EditConfig();
	void ChangeConfigSelectNum(int& ChangeNum, int Limit);

	GameState GetGameState();
	void SetGameState(master::GameState state);
	
	void CheckGameStart();
	void ExitGame();
}