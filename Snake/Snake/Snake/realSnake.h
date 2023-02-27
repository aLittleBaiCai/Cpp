#pragma once
#include"snake.h"


Coordinate::Coordinate(int xx_in, int yy_in) {
	this->xx = xx_in;
	this->yy = yy_in;
}

Coordinate::~Coordinate() {

}

int Coordinate::getX() {
	return this->xx;
}

int Coordinate::getY() {
	return this->yy;
}

void Coordinate::setCoor(int xx_in, int yy_in) {
	this->xx = xx_in;
	this->yy = yy_in;
}


Node::Node() {
	this->head = NULL;
	this->end = NULL;
	this->coordinate->setCoor(0, 0);
}

Node::Node(Node* head_in, Node* end_in, Coordinate* coor_in) {
	this->head = head_in;
	this->end = end_in;
	this->coordinate->setCoor(coor_in->getX(), coor_in->getY());
}

Node::~Node() {
	delete this->coordinate;
}

Node* Node::getHead() {
	return this->head;
}

Node* Node::getEnd() {
	return this->end;
}

void Node::setHead(Node* node) {
	this->head = node;
}

void Node::setEnd(Node* node) {
	this->end = node;
}

Coordinate* Node::getCoordinate() {
	return this->coordinate;
}

void Node::setCoordinate(Coordinate* coor) {
	this->coordinate = coor;
}

Snake::Snake() {
	this->first_node = this->last_node = new Node();
	//this->randMoveToward();//创建阶段即为蛇头随机移动朝向
	this->move_towards = NULL;
}

Snake::Snake(Node* first, Node* last) {
	this->first_node = first;
	this->last_node = last;
	//this->randMoveToward();//创建阶段即为蛇头随机移动朝向
	this->move_towards = NULL;
	
}

Snake::~Snake() {
	Node* current_node = this->first_node;
	Node* next_node = current_node->getEnd();
	Node* node_temp = NULL;
	while (current_node) {
		delete current_node;
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
}

Node* Snake::getFirstNode() {
	return this->first_node;
}

Node* Snake::getLastNode() {
	return this->last_node;
}

void Snake::setFirstNode(Node* node) {
	this->first_node = node;
}

void Snake::setLastNode(Node* node) {
	this->last_node = node;
}

int Snake::getSnakeLength() {
	int length = 0;
	Node* current_node = this->first_node;
	Node* next_node = current_node->getEnd();
	while (current_node) {
		//cout << current_node << endl;
		length++;
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
	return length;
}

void Snake::addSnakeNode() {
	Node* node = new Node();
	this->last_node->setEnd(node);
	node->setHead(this->last_node);
	this->last_node = node;
}

void Snake::randMoveToward() {
	srand((unsigned)time(NULL));
	this->move_towards = (rand() % 4) + 1;//随机默认朝向
}

void Snake::setBirthPoint(int xx_in, int yy_in) {
	Coordinate* coor = new Coordinate(xx_in, yy_in);
	this->first_node->setCoordinate(coor);
}


void Snake::autoMove() {
	Coordinate* current_coor = this->first_node->getCoordinate();
	int current_xx = current_coor->getX();
	int current_yy = current_coor->getY();
	switch (this->move_towards) {
	case UP:
		this->first_node->setCoordinate(new Coordinate(current_xx, current_yy - 1));
		break;
	case DOWN:
		this->first_node->setCoordinate(new Coordinate(current_xx, current_yy + 1));
		break;
	case LEFT:
		this->first_node->setCoordinate(new Coordinate(current_xx - 1, current_yy));
		break;
	case RIGHT:
		this->first_node->setCoordinate(new Coordinate(current_xx + 1, current_yy));
		break;
	}
	this->nodeFollowMove(current_coor);
}

void Snake::nodeFollowMove(Coordinate* coor) {
	Node* current_node = this->first_node->getEnd();
	Node* next_node = NULL;
	Coordinate* coor_temp = NULL;
	current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	while (current_node) {
		coor_temp = coor;
		coor = current_node->getCoordinate();
		current_node->setCoordinate(new Coordinate(coor_temp->getX(), coor_temp->getY()));
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
}

void Snake::changeMoveToward(int toward) {
	switch (toward) {
	case UP:
	case DOWN:
	case LEFT:
	case RIGHT:
		if(this->move_towards!=-toward)
			this->move_towards = toward;
		break;
	default:
		break;
	}
}