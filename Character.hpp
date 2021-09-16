#pragma once

class HitBox {
	public:
		int Left, Up;
		int W, H;
		HitBox(int Left, int Up, int W, int H);
};

bool HitBoxCheck(HitBox a, HitBox b);

class Character {
	private:
		int x, y;
		int graph;
		int hitW, hitH;

	public:
		Character(int x, int y, int graph,int hitSize);
		Character(int x, int y, int graph, int hitW, int hitH);
		int getX();
		int getY();
		int getGraph();
		int getHitW();
		int getHitH();
		HitBox getHitBox();
		void setX(int x);
		void setY(int y);
};

class Player :public Character{
	private:
		int MaxHP;
		int HP;
	public:
		Player(int x, int y, int graph, int hitSize, int MaxHP);
		Player(int x, int y, int graph, int hitW, int hitH, int MaxHP);
		int getHP();
		void DecreaseHP(int damage);
		void IncreaseHP(int heal);
};

class Shot :public Character {
	private:
		int flag;

	public:
		Shot(int x, int y, int graph, int hitW, int hitH, int flag);
		Shot(int x, int y, int graph, int hitSize, int flag);
		Shot();
		Shot(Shot* s);
		int getFlag();
		void setFlag(int flag);
};

class EnemyShot :public Shot {
	private:
		double dx;
		double dy;
	public:
		EnemyShot(int x, int y, int graph, int hitW, int hitH, int flag);
		EnemyShot(int x, int y, int graph, int hitSize, int flag);
		EnemyShot(EnemyShot* es);
		double getDx();
		void setDx(double dx);
		double getDy();
		void setDy(double dy);
};

class Enemy :public Character{
	private:
		int dir;
		int damageFlag;
		int damageCounter;
		int damageGraph;
		EnemyShot shot;
		int shotCounter;

	public:
		Enemy(int x, int y, int graph, int hitW, int hitH, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter);
		Enemy(int x, int y, int graph, int hitSize, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter);
		int getDir();
		void setDir(int dir);
		int getDamageFlag();
		void setDamageFlag(int damageFlag);
		int getDamageCounter();
		void setDamageCounter(int damageCounter);
		int getDamageGraph();
		EnemyShot* getShot();
		void setShot(EnemyShot shot);
		int getShotCounter();
		void setShotCounter(int count);
};

