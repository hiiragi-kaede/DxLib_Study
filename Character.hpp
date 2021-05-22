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
		int getFlag();
		void setFlag(int flag);
};

class Enemy :public Character{
	private:
		int dir;
		int damageFlag;
		int damageCounter;
		int damageGraph;
		Shot shot;
		int shotCounter;

	public:
		Enemy(int x, int y, int graph, int dir, int dFlag, int dCounter, int dGraph, Shot es,int esCounter);
		int getDir();
		void setDir(int dir);
		int getDamageFlag();
		void setDamageFlag(int damageFlag);
		int getDamageCounter();
		void setDamageCounter(int damageCounter);
		int getDamageGraph();
		Shot getShot();
		void setShot(Shot shot);
};

