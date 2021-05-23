#pragma once
class Character {
	private:
		int x, y;
		int graph;

	public:
		Character(int x, int y, int graph);
		int getX();
		int getY();
		int getGraph();
		void setX(int x);
		void setY(int y);
};

class Player :public Character{
public:
	//継承コンストラクタ
	using Character::Character;
};

class Shot :public Character {
	private:
		int flag;

	public:
		Shot(int x, int y, int graph, int flag);
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
		EnemyShot(int x, int y, int graph, int flag);
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
		Enemy(int x, int y, int graph, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter);
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

