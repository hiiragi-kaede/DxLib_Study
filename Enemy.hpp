#pragma once

#include"Character.hpp"
#include"Player.hpp"
#include<vector>

namespace ene {
	void Instantiate();
	void Update();
}

class Enemy;

class EnemyShot :public Shot {
private:
	double dx;
	double dy;

	void EnemyShotCtrl(Enemy* enemy, Player* player);
	void UpdateEnemyShotView();
	void AttackPlayer(Player* player);

public:
	EnemyShot(int x, int y, int graph, int hitW, int hitH, int flag);
	EnemyShot(int x, int y, int graph, int hitSize, int flag);
	EnemyShot(EnemyShot* es);
	void Update(Enemy* enemy, Player* player);

	double getDx()
	{
		return this->dx;
	}

	void setDx(double dx)
	{
		this->dx = dx;
	}

	double getDy()
	{
		return this->dy;
	}

	void setDy(double dy)
	{
		this->dy = dy;
	}
};

class Enemy :public Character {
private:
	int dir;
	int damageFlag;
	int damageCounter;
	int damageGraph;
	EnemyShot shot;
	int shotCounter;
	int MaxHP;
	int HP;

	void UpdateEnemy(Player* player);
	void UpdateHPView();
	void HitCheck(std::vector<Shot*> shots);
	
public:
	Enemy(int x, int y, int graph, int hitW, int hitH, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter);
	Enemy(int x, int y, int graph, int hitSize, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter);
	void Update(Player* player, std::vector<Shot*> shots);

	int getHP()
	{
		return Enemy::HP;
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

	int getDir() {
		return Enemy::dir;
	}

	void setDir(int dir)
	{
		this->dir = dir;
	}

	int getDamageFlag()
	{
		return this->damageFlag;
	}

	void setDamageFlag(int damageFlag)
	{
		this->damageFlag = damageFlag;
	}

	int getDamageCounter()
	{
		return this->damageCounter;
	}

	void setDamageCounter(int damageCounter)
	{
		this->damageCounter = damageCounter;
	}

	int getDamageGraph()
	{
		return this->damageGraph;
	}

	EnemyShot* getShot()
	{
		return &(this->shot);
	}

	void setShot(EnemyShot shot)
	{
		this->shot = shot;
	}

	int getShotCounter()
	{
		return this->shotCounter;
	}

	void setShotCounter(int count)
	{
		this->shotCounter = count;
	}
};