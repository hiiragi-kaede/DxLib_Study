#pragma once

namespace master {

	void Update();

	void drawTitleScene();
	void drawTitles();
	void UpdateTitleSelect();
	void TitleUpdate();

	void MoveToConfig();
	void ResetSelectNum();

	void SetToTitle();
	void SetToGame();
	void SetToConfig();
	void SetToGameOver();
	
	void CheckGameStart();
	void ExitGame();
}