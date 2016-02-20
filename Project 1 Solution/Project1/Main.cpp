#include "Functions.h"

void main() {
	Ordered_List<Assignment> assignedList; // List of "assigned" assignments
	Ordered_List<Assignment> completedList; // List of "completed" and "late" assignments

	Menu menu(assignedList, completedList); // Menu object for manipulating lists and UI

	load_data(assignedList, completedList, menu); // Read-in and populate lists from file

	for (;;) { // Run the main menu forever
		main_menu(assignedList, completedList,menu); // User interface menu
	}
}