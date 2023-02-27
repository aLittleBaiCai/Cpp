#pragma once
#include<iostream>
#include <conio.h>
#include"config.h"

using namespace std;



class Player {
public:
	static int user_number;
	int id = 0;
	string name = "";
public:
	Player(string name_in);
	~Player();
	int getControllerMove();
};

int Player::user_number = 0;

Player::Player(string name_in) {
	this->user_number++;
	this->name = name_in;
	this->id = user_number;
}

Player::~Player() {

}

int Player::getControllerMove() {
	if (_kbhit() != NULL) {
		int key_value = _getch();
		switch (key_value) {
		case 87:
		case 119:
			return UP;
		case 83:
		case 115:
			return DOWN;
		case 65:
		case 97:
			return LEFT;
		case 68:
		case 100:
			return RIGHT;
		case 81:
		case 113:
			return EXIT;
		case 67:
		case 99:
			return CONTINUE;
		default:
			break;
		}
	}
	return NO_CIN;
}

