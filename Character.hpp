#pragma once

#include"DxLib.h"

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
		
		int getX() {
			return Character::x;
		}

		int getY() {
			return Character::y;
		}

		int getGraph() {
			return Character::graph;
		}

		int getHitW()
		{
			return Character::hitW;
		}

		int getHitH()
		{
			return Character::hitH;
		}

		HitBox getHitBox()
		{
			int GraphW, GraphH;
			GetGraphSize(Character::getGraph(), &GraphW, &GraphH);
			int W = Character::getHitW();
			int H = Character::getHitH();
			int Left = Character::getX() + GraphW / 2 - W / 2;
			int Up = Character::getY() + GraphH / 2 - H / 2;
			return HitBox(Left, Up, W, H);
		}

		void setX(int x) {
			this->x = x;
		}

		void setY(int y) {
			this->y = y;
		}
};