#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include"config.h"
using namespace std;


//������
class Coordinate {
protected:
	int xx = 0;
	int yy = 0;

public:
	Coordinate(int xx_in, int yy_in);//���캯��
	~Coordinate();//��������
	void setCoor(int xx_in, int yy_in);//��������
	int getX();
	int getY();
};

//�ڵ���
class Node {
protected:
	Node* head = NULL;
	Node* end = NULL;
	Coordinate* coordinate = new Coordinate(0, 0);
public:
	Node();
	Node(Node* head_in, Node* end_in, Coordinate* coor_in);
	~Node();
	Node* getHead();
	Node* getEnd();
	Coordinate* getCoordinate();
	void setHead(Node* node);
	void setEnd(Node* noed);
	void setCoordinate(Coordinate* coor);
};

//����
class Snake {
protected:
	Node* first_node = NULL;
	Node* last_node = NULL;
	int move_towards = UP;//��ͷ�ƶ�����
public:
	Snake();
	Snake(Node* first, Node* last);
	~Snake();
	Node* getFirstNode();
	Node* getLastNode();
	void setFirstNode(Node* node);
	void setLastNode(Node* node);
	int getSnakeLength();
	void addSnakeNode();
	void randMoveToward();//����ƶ�����
	void setBirthPoint(int xx_in, int yy_in);
	void autoMove();
	void nodeFollowMove(Coordinate* coor);
	void changeMoveToward(int toward);
};




