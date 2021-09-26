#include"Character.hpp";
#include"DxLib.h"

HitBox::HitBox(int Left, int Up, int W, int H) : Left(Left), Up(Up), W(W), H(H) {}

/// <summary>
/// 2��HitBox���󂯎��A����炪������Ă��邩�ǂ����𔻒肷��
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>2��HitBox��������Ă���Ȃ�True�A�����łȂ����False��Ԃ��B</returns>
bool HitBoxCheck(HitBox a, HitBox b) {
	return ((a.Left > b.Left && a.Left < b.Left + b.W) ||
		(b.Left > a.Left && b.Left < a.Left + a.W)) &&
		((a.Up > b.Up && a.Up < b.Up + b.H) ||
			(b.Up > a.Up && b.Up < a.Up + a.H));
}

Character::Character(int x, int y, int graph, int hitSize) : x(x), y(y), graph(graph), hitH(hitSize), hitW(hitSize) {}

Character::Character(int x, int y, int graph, int hitW, int hitH) : x(x), y(y), graph(graph), hitW(hitW), hitH(hitH) {}
