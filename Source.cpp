/**************************************************************
CS 303 - Program 1a - Spring 2016
Collaborative effort of Kati Williams, Binh Mai, and Jay Wolf
with support code from Prof. M. Kuhail (kuhailm@umkc.edu)
**************************************************************/

#include "UI.h"
using namespace std;

void main() {
	// Create the User Interface
	UI user_interface;

	// Load the UI menu and run indefinitely
	for (;;) {
		user_interface.main_menu();
	}
	return;
}