#include "assignment.h"
#include "Ordered_List.h"
#include "assignmentMenu.h"
#include <iostream>
#include <fstream>
using namespace std;

// funciton declarations
void load_data(Ordered_List<assignment>&, Ordered_List<assignment>&);
void main_menu(Ordered_List<assignment>&, Ordered_List<assignment>&);
string trim(const string& the_string);

void main() {

	// create lists
	Ordered_List<assignment> assignedList; // List of "assigned" assignments
	Ordered_List<assignment> completedList; // List of "completed" and "late" assignments

	// load assignments from file
	// populate each list as appropriate
	load_data(assignedList, completedList);

	// call menu to perform list actions
	for (;;) {
		main_menu(assignedList, completedList);
	}

	system("pause");
}

string trim(const string& the_string)
{
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");

	return the_string.substr(p, q - p + 1);
}

void load_data(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList) {
	string line, dueDate, desc, assignDate, status;
	ifstream in("assignments.txt");
	if (in) { // Stream exists.
		while (getline(in, line)) { 
			//Read in the line from the file
			String_Tokenizer st(line, ","); //parse the tokens in the line (separated by a comma)	
			dueDate = trim(st.next_token());
			desc = trim(st.next_token());
			assignDate = trim(st.next_token());
			status = trim(st.next_token());

			//Convert tokenized string to date and assignment status
			Date newDue(dueDate);
			Date newAssign(assignDate);
			assignStatus newStatus;
								
			//Set the enumerated status
			if (status == "assigned") {
				newStatus = assigned;
			}
			else if (status == "completed") {
				newStatus = completed;
			}
			else {
				newStatus = late;
			}

			assignmentMenu::addToList(assignedList, completedList, newDue, desc, newAssign, newStatus);
		}
	}

	in.close(); // do we want to close this in the "load" function?
}

void main_menu(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList) {
	int task;
	cout << "-----------------Main Menu-------------------" << endl << endl;
	cout << "Choose an option:" << endl;
	cout << "1 - Display assignments" << endl
		 << "2 - Add an assignment" << endl
		 << "3 - Edit due date of an assignment" << endl
		 << "4 - Edit description of an assignment" << endl
		 << "5 - Complete an assignment" << endl
		 << "6 - Display late assignments" << endl
		 << "7 - Save" << endl
		 << "8 - Exit" << endl << endl;
	cout << "Your choice: ";
	cin >> task;

	
	switch (task) {
		case 1: {
			assignmentMenu::displayAssignments(assignedList,completedList);
			break;
			}
		case 2: {
			assignmentMenu::addAssignment(assignedList, completedList);
			break;
		}
		case 3: {
			assignmentMenu::editDueDate(assignedList, completedList);
			break;
		}
		case 4: {
			assignmentMenu::editDescription(assignedList, completedList);
			break;
		}
		case 5: {
			assignmentMenu::completeAssignment(assignedList, completedList);
			break;
		}
		case 6: {
			assignmentMenu::listLateAssignments(completedList);
			break;
		}
		case 7: {
			assignmentMenu::saveLists(assignedList, completedList);
			break;
		}
		case 8: {
			assignmentMenu::exit();
			break;
		}
	
	}
}

