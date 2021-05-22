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

//ここが問題の場所
//ShotにShot型を引数に取るコンストラクタは作ってないですが、それ以前に「shotはクラスenemyの静的でないデータ メンバーまたは基底クラスではありません」
//というエラーが出てます
Enemy::Enemy(int x, int y, int graph, int dir, int dFlag, int dCounter, int dGraph, Shot es,int esCounter) :
	Character(x, y, graph), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph),Shot(es),shotCounter(esCounter){
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

Shot::Shot(int x, int y, int graph, int flag) : Character(x, y, graph), flag(flag) {}

int Shot::getFlag() {
	return Shot::flag;
}

void Shot::setFlag(int flag)
{
	this->flag = flag;
}