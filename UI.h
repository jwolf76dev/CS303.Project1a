#ifndef UI_H
#define UI_H

#include "Assignment_List.h"
#include <iostream>
#include <fstream>
using namespace std;

// User Interface class for menu functions
class UI {
private:
	Assignment_List menu;
public:
	UI() {};

	void main_menu();
		
};
#endif