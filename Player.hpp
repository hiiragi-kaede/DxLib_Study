#pragma once
#include<vector>
#include"Character.hpp"

class Shot :public Character {
private:
	int flag;

public:
	Shot(int x, int y, int graph, int hitW, int hitH, int flag);
	Shot(int x, int y, int graph, int hitSize, int flag);
	Shot();
	Shot(Shot* s);
	
	void Update();
	void UpdateShotView();

	int getFlag() {
		return Shot::flag;
	}

	void setFlag(int flag)
	{
		this->flag = flag;
	}
};

class Player :public Character {
private:
	int MaxHP;
	int HP;

	void UpdatePlayer();
	void UpdateShotState(Shot* shot);
	void UpdateHPView();
	void CheckGameOver();

public:
	Player(int x, int y, int graph, int hitSize, int MaxHP);
	Player(int x, int y, int graph, int hitW, int hitH, int MaxHP);
	void Update();

	int getHP()
	{
		return Player::HP;
	}

	void DecreaseHP(int damage)
	{
		this->HP -= damage;
		if (this->HP < 0) this->HP = 0;
	}

	void IncreaseHP(int heal)
	{
		this->HP += heal;
		if (this->HP > this->MaxHP) this->HP = this->MaxHP;
	}

	
};

namespace pl {
	void Instantiate();
	void Update();
	Player* getPlayer();
	std::vector<Shot*> getShots();
}