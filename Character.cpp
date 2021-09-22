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

int Character::getX() {
	return Character::x;
}

int Character::getY() {
	return Character::y;
}

int Character::getGraph() {
	return Character::graph;
}

int Character::getHitW()
{
	return Character::hitW;
}

int Character::getHitH()
{
	return Character::hitH;
}

HitBox Character::getHitBox()
{
	int GraphW, GraphH;
	GetGraphSize(Character::getGraph(), &GraphW, &GraphH);
	int W = Character::getHitW();
	int H = Character::getHitH();
	int Left = Character::getX() + GraphW / 2 - W / 2;
	int Up = Character::getY() + GraphH / 2 - H / 2;
	return HitBox(Left, Up, W, H);
}

void Character::setX(int x) {
	this->x = x;
}

void Character::setY(int y) {
	this->y = y;
}

Player::Player(int x, int y, int graph, int hitSize, int MaxHP) : Character(x, y, graph, hitSize), MaxHP(MaxHP), HP(MaxHP) {}

Player::Player(int x, int y, int graph, int hitW, int hitH, int MaxHP) : Character(x, y, graph, hitW, hitH), MaxHP(MaxHP), HP(MaxHP) {}

int Player::getHP()
{
	return Player::HP;
}

void Player::DecreaseHP(int damage)
{
	this->HP -= damage;
	if (this->HP < 0) this->HP = 0;
}

void Player::IncreaseHP(int heal)
{
	this->HP += heal;
	if (this->HP > this->MaxHP) this->HP = this->MaxHP;
}

Enemy::Enemy(int x, int y, int graph, int hitW, int hitH, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter) :
	Character(x, y, graph, hitW, hitH), MaxHP(MaxHP), HP(MaxHP), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph), shot(es), shotCounter(sCounter) {}

Enemy::Enemy(int x, int y, int graph, int hitSize, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter) :
	Character(x, y, graph, hitSize), MaxHP(MaxHP), HP(MaxHP), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph), shot(es), shotCounter(sCounter) {}

int Enemy::getHP()
{
	return Enemy::HP;
}

void Enemy::DecreaseHP(int damage)
{
	this->HP -= damage;
	if (this->HP < 0) this->HP = 0;
}

void Enemy::IncreaseHP(int heal)
{
	this->HP += heal;
	if (this->HP > this->MaxHP) this->HP = this->MaxHP;
}

int Enemy::getDir() {
	return Enemy::dir;
}

void Enemy::setDir(int dir)
{
	this->dir = dir;
}

int Enemy::getDamageFlag()
{
	return this->damageFlag;
}

void Enemy::setDamageFlag(int damageFlag)
{
	this->damageFlag = damageFlag;
}

int Enemy::getDamageCounter()
{
	return this->damageCounter;
}

void Enemy::setDamageCounter(int damageCounter)
{
	this->damageCounter = damageCounter;
}

int Enemy::getDamageGraph()
{
	return this->damageGraph;
}

EnemyShot* Enemy::getShot()
{
	return &(this->shot);
}

void Enemy::setShot(EnemyShot shot)
{
	this->shot = shot;
}

int Enemy::getShotCounter()
{
	return this->shotCounter;
}

void Enemy::setShotCounter(int count)
{
	this->shotCounter = count;
}

Shot::Shot(int x, int y, int graph, int hitW, int hitH, int flag) : Character(x, y, graph, hitW, hitH), flag(flag) {}

Shot::Shot(int x, int y, int graph, int hitSize, int flag) : Character(x, y, graph, hitSize), flag(flag) {}

Shot::Shot() : Character(0, 0, 0, 10), flag(0) {}

Shot::Shot(Shot* s) : Character(s->getX(), s->getY(), s->getGraph(), s->getHitW(), s->getHitH()), flag(s->getFlag()) {}

int Shot::getFlag() {
	return Shot::flag;
}

void Shot::setFlag(int flag)
{
	this->flag = flag;
}

EnemyShot::EnemyShot(int x, int y, int graph, int hitW, int hitH, int flag) :
	Shot(x, y, graph, hitW, hitH, flag), dx(0), dy(0) {}

EnemyShot::EnemyShot(int x, int y, int graph, int hitSize, int flag) :
	Shot(x, y, graph, hitSize, flag), dx(0), dy(0) {}

EnemyShot::EnemyShot(EnemyShot* es) : Shot(es->getX(), es->getY(), es->getGraph(), es->getHitW(), es->getHitH(), es->getFlag()), dx(0), dy(0) {}

double EnemyShot::getDx()
{
	return this->dx;
}

void EnemyShot::setDx(double dx)
{
	this->dx = dx;
}

double EnemyShot::getDy()
{
	return this->dy;
}

void EnemyShot::setDy(double dy)
{
	this->dy = dy;
}