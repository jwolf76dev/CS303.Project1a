/**************************************************************
 CS 303 - Program 1a - Spring 2016
 Collaborative effort of Kati Williams, Binh Mai, and Jay Wolf
 with support code from Prof. M. Kuhail (kuhailm@umkc.edu)
**************************************************************/

#include "Functions.h"

void main() {
	// Create assignment lists
	Ordered_List<Assignment> assignedList;
	Ordered_List<Assignment> completedList;

	// Create Menu object for interaction with lists
	Menu menu(assignedList, completedList);

	// Load and populate lists from file
	// Uses addToList function from Menu
	loadData(assignedList, completedList, menu);

	// User interface menu
	// Run the main menu until program exit
	for (;;) {
		main_menu(assignedList, completedList, menu);
	}
	return;
}