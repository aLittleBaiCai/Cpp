#pragma once
#include"display.h"
#include<Windows.h>


Display::Display(int max_w, int max_h) {
	this->max_height = max_h;
	this->max_width = max_w;
	this->width = max_w - 2;
	this->height = max_h - 2;
	this->rand_birth_point_range = width / 4;
	this->randBirthPoint();
	this->foodBuilder();
	//��ʼ����ͼ����
	this->map = new string *[this->max_height];
	for (int i = 0; i < this->max_height; i++) {
		this->map[i] = new string[this->max_width];
	}
}

Display::~Display() {
	delete this->map;
	delete this->snake;
	delete this->player;
}

void Display::disMap() {
	this->initMap();//���õ�ͼ
	this->insertSnake();//������
	this->insertFood();
	for (int i = 0; i < this->max_height; i++) {
		for (int j = 0; j < this->max_width; j++) {
			cout << this->map[i][j];
		}
		cout << endl;
	}
}

void Display::initMap() {
	for (int i = 1; i <= this->height; i++) {
		for (int j = 1; j <= this->width; j++) {
			this->map[i][j] = GRASS;
		}
	}
	for (int i = 0; i < this->max_height; i++) {
		this->map[i][0] = "||";
	}
	for (int i = 0; i < this->max_height; i++) {
		this->map[i][this->width+1] = "||";
	}
	for (int j = 0; j < this->max_width; j++) {
		this->map[0][j] = "==";
	}
	for (int j = 0; j < this->max_width; j++) {
		this->map[this->height+1][j] = "==";
	}

}

void Display::insertSnake() {
	Coordinate* coor = NULL;
	cout << "������" << this->snake->getSnakeLength() - 1 << endl;
	Node* current_node = this->snake->getFirstNode();
	Node* next_node = current_node->getEnd();
	while (current_node) {
		//cout << current_node->getCoordinate()->getX()<<" " <<current_node->getCoordinate()->getY() << endl;
		coor = current_node->getCoordinate();
		this->map[coor->getY()][coor->getX()] = SNAKE;
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
}

void Display::insertFood() {
	map[this->food->getY()][this->food->getX() ] = FOOD;
}

Snake* Display::getSnake() {
	return this->snake;
}

void Display::randBirthPoint() {
	int xx = rand() % this->rand_birth_point_range;
	int yy = rand() % this->rand_birth_point_range;
	this->snake->setBirthPoint((width - rand_birth_point_range * 2) / 2 + xx,
		(height - rand_birth_point_range * 2) / 2 + yy);
}

void Display::changeSnakeMoveToward(int toward) {
	this->snake->changeMoveToward(toward);
}

void Display::snakeController() {
	int new_move_toward = this->player->getControllerMove();
	this->snake->changeMoveToward(new_move_toward);
}

int Display::isDeath() {
	if (this->isTouchSelf())
		return TOUCH_ITS_SELF;
	else if (this->isTouchWall())
		return TOUCH_THE_WALL;
	return 0;
}

bool Display::isTouchWall() {
	Coordinate* coor = this->snake->getFirstNode()->getCoordinate();
	return coor->getX() == 0 | coor->getY() == 0
		|coor->getX()==this->width+1 | coor->getY()==this->height+1;
}

bool Display::isTouchSelf() {
	Node* current_node = this->snake->getFirstNode()->getEnd();//��ǰ�ڵ��ʼΪͷ���
	Node* next_node = NULL;//������һ���ڵ�
	current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	while (current_node) {
		if (current_node->getCoordinate()->getX() == this->snake->getFirstNode()->getCoordinate()->getX()
			and current_node->getCoordinate()->getY() == this->snake->getFirstNode()->getCoordinate()->getY()) 
			return TRUE;
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
	return FALSE;
}

void Display::disGameOver() {
	cout << "��Ϸ����" << endl;
}

bool Display::run() {
	this->startGameDis();
	while (1) {
		if (this->player->getControllerMove() == CONTINUE) {
			while (this->startGame());
			return 1;
		}
		else if (this->player->getControllerMove() == EXIT) {
			this->endGame();
			return 0;
		}
	}
}

void Display::endGame() {
	cout << "******��Ϸ���˳�******" << endl;
}

bool Display::startGame() {
	this->getSnake()->autoMove();
	this->snakeController();
	this->getFood();
	this->disMap();
	switch (this->isDeath()) {
	case TOUCH_THE_WALL:
		cout << "��·ǧ��������ȫ��һ�����г����淶������������" << endl;
		return 0;
	case TOUCH_ITS_SELF:
		cout << "����ʱ����������doge��" << endl;
		return 0;
	default:
		break;
	}
	Sleep(SNAKE_MOVE_SPEED);
	system("cls");
	return 1;
}

void Display::startGameDis() {
	cout << "******��C��ʼ��Ϸ******" << endl;
	cout << "******��Q�˳���Ϸ******" << endl;
}

void Display::foodBuilder() {
	this->food = new Coordinate((rand() % this->width) + 1, (rand() % this->height) + 1);
	while (this->isCoorOverlapping(this->food)) {
		this->food = new Coordinate((rand() % this->width) + 1, (rand() % this->height) + 1);
	}
}

bool Display::isCoorOverlapping(Coordinate* coor) {
	Node* current_node = this->snake->getFirstNode();//��ǰ�ڵ��ʼΪͷ���
	Node* next_node = current_node->getEnd();//������һ���ڵ�
	while (current_node) {
		if (current_node->getCoordinate()->getX() == coor->getX()
			and current_node->getCoordinate()->getY() == coor->getY()) {
			return TRUE;
		}
		current_node = next_node;
		current_node == NULL ? next_node = NULL : next_node = current_node->getEnd();
	}
	return FALSE;
}
void Display::getFood() {
	if (this->snake->getFirstNode()->getCoordinate()->getX() == this->food->getX()
		&& this->snake->getFirstNode()->getCoordinate()->getY() == this->food->getY()) {
		this->snake->addSnakeNode();
		this->foodBuilder();
	}
}