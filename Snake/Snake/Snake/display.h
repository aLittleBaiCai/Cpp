#pragma once
#include<iostream>
#include"realSnake.h"
#include<string>
#include"player.h"
#include"config.h"
using namespace std;


class Display {
protected:
	//地图最大宽高，实际移动范围会比最大值小2，用于判定是否出界
	int max_width = 0;
	int max_height = 0;
	//地图打印宽高
	int width = 0;
	int height = 0;
	string** map = NULL;//动态创建一个地图数组
	Snake* snake = new Snake();
	int rand_birth_point_range = 0;//随机出生点范围
	Player * player = new Player("白菜菜");
	Coordinate*food = NULL;
public:
	Display(int max_w, int max_h);
	~Display();
	bool run();
protected:
	void disMap();
	void insertSnake();//插入蛇
	Snake* getSnake();
	void randBirthPoint();//随机出生点
	void changeSnakeMoveToward(int toward);
	void snakeController();
	void disGameOver();
	int isDeath();
	void initMap();
	bool isTouchWall();
	bool isTouchSelf();
	void foodBuilder();
	bool isCoorOverlapping(Coordinate* coor);
	void insertFood();
	void getFood();
	void startGameDis();
	bool startGame();
	void endGame();
};