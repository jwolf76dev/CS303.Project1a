#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Assignment.h"
#include "Ordered_List.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
using namespace std;

string trim(const string& the_string) {
	//Function cuts the string into chunks based on a delimiter
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");

	return the_string.substr(p, q - p + 1);
}

//Load assignment lists from file
void loadData(Ordered_List<Assignment>& assignedList, Ordered_List<Assignment>& completedList, Menu& menu) {
	
	//Variables to hold the line date from the text file
	string line, dueDate, desc, assignDate, status;
	ifstream in("assignments.txt");
	
	if (in) //Stream exists
	{
		while (getline(in, line)) //Read a line from the file
		{
			if (line == "")
				continue;
			//Parse the tokens in the line (separated by a comma)
			String_Tokenizer st(line, ","); 	
			dueDate = trim(st.next_token());
			desc = trim(st.next_token());
			assignDate = trim(st.next_token()); 
			status = trim(st.next_token());

			//Convert tokenized string to date and assignment status
			Date newDue(dueDate), newAssign(assignDate);
			assignStatus newStatus;

			//Set the enumerated status
			if (status == "assigned") {
				newStatus = assigned;
			}
			else if (status == "completed") {
				newStatus = completed;
			}
			else { newStatus = late;}

			//Add the item to the list
			menu.addToList(newDue, desc, newAssign, newStatus);
		}
	}
	//Close the input stream
	in.close();
}


void main_menu(Ordered_List<Assignment>& assignedList, Ordered_List<Assignment>& completedList, Menu& menu) {
	//main_menu is the user interface

	int task;
	cout << endl << "------------------------ Main Menu ---------------------------" << endl << endl;
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
		case 1: menu.displayAssignments();		break;
		case 2: menu.addAssignment();			break;
		case 3: menu.editDueDate();				break;
		case 4: menu.editDescription();			break;
		case 5: menu.completeAssignment();		break;
		case 6: menu.listLateAssignments();		break;
		case 7: menu.saveLists();				break;
		case 8: menu.exitProgram();				break;
		default: cout << "Incorrect option, try again!" << endl << endl;	break;
	}
}

#endif