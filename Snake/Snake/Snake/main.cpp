#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"realSnake.h"
#include"realDisplay.h"
#include<Windows.h>

using namespace std;



int main() {
	Display* my_display = new Display(25,25);//创建一个地图
	while (1) {
		if (my_display->run()) {
			delete my_display;
			my_display = new Display(25, 25);
		}
		else {
			delete my_display;
			break;
		}
	}
	system("pause");
	return 0;
}
