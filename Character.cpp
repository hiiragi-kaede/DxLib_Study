#include"Character.hpp";
#include"DxLib.h"

HitBox::HitBox(int Left, int Up, int W, int H) : Left(Left), Up(Up), W(W), H(H) {}

bool HitBoxCheck(HitBox a, HitBox b) {
	return ((a.Left > b.Left && a.Left < b.Left + b.W) ||
		(b.Left > a.Left && b.Left < a.Left + a.W)) &&
		((a.Up > b.Up && a.Up < b.Up + b.H) ||
			(b.Up > a.Up && b.Up < a.Up + a.H));
}

Character::Character(int x, int y, int graph, int hitSize) : x(x), y(y), graph(graph), hitH(hitSize), hitW(hitSize) {}

Character::Character(int x, int y, int graph, int hitW, int hitH) : x(x), y(y), graph(graph), hitW(hitW), hitH(hitH) {}
