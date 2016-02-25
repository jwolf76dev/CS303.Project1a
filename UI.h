#ifndef UI_H
#define UI_H

//#include "Menu.h"
//#include "Functions.h"
#include "Assignment_List.h"
#include <iostream>
#include <fstream>
using namespace std;

class UI {
private:
	Assignment_List menu;
public:
	UI() {};

	void main_menu();
		
};
#endif