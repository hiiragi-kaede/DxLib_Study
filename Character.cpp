#include"Character.hpp";

Character::Character(int x, int y, int graph) : x(x), y(y), graph(graph) {}

int Character::getX() {
	return Character::x;
}

int Character::getY() {
	return Character::y;
}

int Character::getGraph() {
	return Character::graph;
}

void Character::setX(int x) {
	this->x = x;
}

void Character::setY(int y) {
	this->y = y;
}

//���������̏ꏊ
//Shot��Shot�^�������Ɏ��R���X�g���N�^�͍���ĂȂ��ł����A����ȑO�Ɂushot�̓N���Xenemy�̐ÓI�łȂ��f�[�^ �����o�[�܂��͊��N���X�ł͂���܂���v
//�Ƃ����G���[���o�Ă܂�
Enemy::Enemy(int x, int y, int graph, int dir, int dFlag, int dCounter, int dGraph, Shot es, int sCounter) :
	Character(x, y, graph), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph), shot(es), shotCounter(sCounter) {}

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

Shot* Enemy::getShot()
{
	return &(this->shot);
}

void Enemy::setShot(Shot shot)
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

Shot::Shot(int x, int y, int graph, int flag) : Character(x, y, graph), flag(flag) {}

Shot::Shot() : Character(0, 0, 0), flag(0) {}

Shot::Shot(Shot* s) : Character(s->getX(), s->getY(), s->getGraph()), flag(s->getFlag()) {}

int Shot::getFlag() {
	return Shot::flag;
}

void Shot::setFlag(int flag)
{
	this->flag = flag;
}