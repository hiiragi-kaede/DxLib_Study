#pragma once
class Character {
	protected:
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

class Enemy :public Character{
	private:
		int dir;

	public:
		Enemy(int x,int y,int graph,int dir);
		int getDir();
		void setDir(int dir);
};

class Shot :public Character{
	private:
		int flag;

	public:
		Shot(int x, int y, int graph, int flag);
		int getFlag();
		void setFlag(int flag);
};