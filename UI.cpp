#include "UI.h"

void UI::main_menu()
{
	int task;
	cout << endl << "------------------------ Main Menu ---------------------------" << endl << endl
		<< "Choose an option:" << endl
		<< "1 - Display assignments" << endl
		<< "2 - Add an assignment" << endl
		<< "3 - Edit due date of an assignment" << endl
		<< "4 - Edit description of an assignment" << endl
		<< "5 - Complete an assignment" << endl
		<< "6 - Display late assignments" << endl
		<< "7 - Save" << endl
		<< "8 - Exit" << endl << endl
		<< "Your choice: ";
	cin >> task;

	switch (task) {
	case 1: { menu.displayAssignments(); break;	}
	case 2: { menu.addAssignment(); break; }
	case 3: { menu.editDueDate(); break; }
	case 4: { menu.editDescription(); break; }
	case 5: { menu.completeAssignment(); break; }
	case 6: { menu.listLateAssignments(); break; }
	case 7: { menu.saveLists(); break; }
	case 8: { menu.exitProgram(); break; }
	default: { cout << "Invalid option. Please select from 1 to 8." << endl << endl; break; }
	}
}

