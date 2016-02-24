#include "Menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Convert enum to text
string statusTypes[] = { "assigned", "completed", "late" };

// Load and populate assignment lists from assignments.txt
void Menu::addToList(Date due, string desc, Date assign, assignStatus status) {

	Assignment tempAssign(due, desc, assign, status);

	if (status == assigned)
		assignedList.insert(tempAssign);
	else
		completedList.insert(tempAssign);
	return;
}

// Display both lists of assignments
void Menu::displayAssignments() {
	// Variables
	string bar = "--------------------------------------------------------------";
	string tableHeader = " Assigned  Description                     Due Date   Status";

	// Output formatted Assigned list
	cout << endl << "------------------------ Assigned List -----------------------" << endl
		 << tableHeader << endl
		 << bar << endl;

	iter = assignedList.begin();
	while (iter != assignedList.end()) {
		cout << iter->getAssignDate() << "|"
			<< setw(30) << left << iter->getDescription().substr(0, 30) << "|"
			<< iter->getDueDate() << "|"
			<< statusTypes[iter->getStatus()] << endl;
		++iter;
	}
	cout << endl;

	// Output formatted Completed and Late list
	cout << endl << "------------------ Completed and Late List -------------------" << endl
		 << tableHeader << endl
		 << bar << endl;

	iter = completedList.begin();
	while (iter != completedList.end()) {
		cout << iter->getAssignDate() << "|"
			 << setw(30) << left << iter->getDescription().substr(0, 30) << "|"
			 << iter->getDueDate() << "|"
			 << statusTypes[iter->getStatus()] << endl;
		++iter;
	}
	cout << endl;
	return;
}

// Add a new assignment to a list
bool Menu::addAssignment() {
	// Variables
	Date assignedDate, dueDate;
	string desc;
	int statChoice;
	assignStatus status;

	cout << endl << "** Add Assignment **" << endl;
	// Prompt user for assigned date
	do {
		cout << endl << "When was it assigned? (MM/DD/YYYY): ";
		cin >> assignedDate;

		// Verify unique assigned date
		if (findAssignment(assignedDate) == true) {
			cout << "Error: An assignment with this date already exists." <<endl
				 << "Please check the date and try again." << endl;
		}

		// Verify valid assigned date
		if (assignedDate.getYear() < 2000) {
			cout << "Error: The date entered is invalid." << endl
				 << "Please make sure that the year is after 2000." << endl;
		}
	// Re-prompt if either condition fails
	} while (findAssignment(assignedDate) == true || assignedDate.getYear() < 2000);

	// Prompt user for due date
	do {
		cout << endl << "When is/was it due? (MM/DD/YYYY): ";
		cin >> dueDate;

		// Verify valid due date
		if (dueDate < assignedDate) {
			cout << "Error: The due date cannot be before the assigned date." << endl
				 << "Please check the date and try again." << endl;
		}
	// Re-prompt if condition fails
	} while (dueDate < assignedDate);
	
	// Prompt user for assignment description
	cin.ignore(1);
	cout << endl << "Enter a brief description of the assignment: ";
	getline(cin, desc);

	// Prompt user for assignment status
	do {
		cout << endl << "What is the assignment's status?" << endl;
		cout << "1 - Assigned" << endl
			 << "2 - Completed" << endl
			 << "3 - Late" << endl
			 << "Status: ";
		cin >> statChoice;

		switch (statChoice) {
		case 1: { status = assigned; break; }
		case 2: { status = completed; break; }
		case 3: { status = late; break; }
		default: { cout << "Invalid option. Please select 1, 2, or 3." << endl; break; }
		}
	// Re-prompt if condition fails
	} while (statChoice > 3 || statChoice < 1);

	// Add the object to the appropriate list
	addToList(dueDate, desc, assignedDate, status);
	cout << endl << "** Assignment added **" << endl;
	return true;
}

// Edit the due date of an existing assignment
bool Menu::editDueDate() {
	// Variables
	Date inDate;
	char response;
	bool isInvalid = false;
	string tableHeader = " Assigned  Description                     Due Date   Status";
	string bar = "--------------------------------------------------------------";
	
	cout << endl << "** Edit Assignment Due Date **" << endl;

	// Prompt user for assigned date
	cout << endl << "When was it assigned? (MM/DD/YYYY): ";
	cin >> inDate;

	// Search for the date in the lists
	if (findAssignment(inDate) == false) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	// Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl
		 << tableHeader << endl
		 << bar << endl
		 << iter->getAssignDate() << "|"
		 << setw(30) << left << iter->getDescription().substr(0, 30) << "|"
		 << iter->getDueDate() << "|"
		 << statusTypes[iter->getStatus()] << endl
		 << endl;

	// Prompt to confirm editing
	do {
		cout << endl << "Edit this assignment? Y/N: ";
		cin >> response;
		// Check for valid response
		isInvalid = !(response == 'n' || response == 'N' || response == 'y' || response == 'Y');
		if (isInvalid)
			cout << "Invalid option. Please enter Y or N." << endl;

	// Re-prompt if invalid response
	} while (isInvalid);

	if (response == 'n' || response == 'N') {
		cout << endl << "** Edit cancelled **" << endl;
		return false;
	}
	else {
		do {
			// Prompt user for new due date
			cout << endl << "Enter the new due date (MM/DD/YYYY): ";
			cin >> inDate;

			// Verify valid due date
			if (inDate < iter->getAssignDate()) {
				cout << "Error: The due date cannot be before the assigned date." << endl
					<< "Please check the date and try again." << endl;
			}
		// Re-prompt if condition fails
		} while (inDate < iter->getAssignDate());
	}

	// Update the assignment
	iter->setDueDate(inDate);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Menu::editDescription() {
	// Variables
	Date inDate;
	string newDesc;
	char response;
	bool isInvalid = false;
	string tableHeader = " Assigned  Description                     Due Date   Status";
	string bar = "--------------------------------------------------------------";

	cout << endl << "** Edit Assignment Description **" << endl;

	// Prompt user for assigned date
	cout << endl << "When was it assigned? (MM/DD/YYYY): ";
	cin >> inDate;

	// Search for the date in the lists
	if (findAssignment(inDate) == false) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	// Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl;
	cout << tableHeader << endl << bar << endl;
	cout << iter->getAssignDate() << "|";
	cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|";
	cout << iter->getDueDate() << "|";
	cout << statusTypes[iter->getStatus()] << endl;
	cout << endl;

	// Prompt to confirm editing
	do {
		cout << endl << "Edit this assignment? Y/N: ";
		cin >> response;
		// Check for valid response
		isInvalid = !(response == 'n' || response == 'N' || response == 'y' || response == 'Y');
		if (isInvalid)
			cout << "Invalid option. Please enter Y or N." << endl;

	// Re-prompt if invalid response
	} while (isInvalid);

	if (response == 'n' || response == 'N') {
		cout << endl << "** Edit cancelled **" << endl;
		return false;
	}
	else {
		// Prompt user for new description
		cin.ignore(1);
		cout << endl << "Enter the new description: ";
		getline(cin, newDesc);
	}

	// Update the assignment
	iter->setDescription(newDesc);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Menu::completeAssignment() {
	// Variables
	Date inDate;
	char response;
	bool isInvalid = false;
	Date doneDate;
	string tableHeader = " Assigned  Description                     Due Date   Status";
	string bar = "--------------------------------------------------------------";

	cout << endl << "** Complete Assignment **" << endl;

	// Prompt user for assigned date
	cout << endl << "When was it assigned? (MM/DD/YYYY): ";
	cin >> inDate;

	// Search for the date in the assigned list only
	iter = assignedList.find(inDate);

	if (iter == assignedList.end()) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	// Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl;
	cout << tableHeader << endl << bar << endl;
	cout << iter->getAssignDate() << "|";
	cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|";
	cout << iter->getDueDate() << "|";
	cout << statusTypes[iter->getStatus()] << endl;
	cout << endl;

	// Prompt to confirm editing
	do {
		cout << endl << "Complete this assignment? Y/N: ";
		cin >> response;

		// Check for valid response
		isInvalid = !(response == 'n' || response == 'N' || response == 'y' || response == 'Y');
		if (isInvalid)
			cout << "Invalid option. Please enter Y or N." << endl;

		// Re-prompt if invalid response
	} while (isInvalid);

	if (response == 'n' || response == 'N') {
		cout << endl << "** Edit cancelled **" << endl;
		return false;
	}
	else {
		do {
			cout << endl << "Please enter the date you completed the assignment: ";
			cin >> doneDate;

			// Verify completed date >= assigned date
			if (doneDate < inDate) {
				cout << "Error: The completed date is before the assigned date." << endl
					<< "Please check the date and try again. " << endl;
			}
			// Re-prompt if invalid response
		} while (doneDate < inDate);

		// Update the assignment
		if (doneDate <= iter->getDueDate()) {
			iter->setStatus(completed);
		}
		else
			iter->setStatus(late);

		// Move completed assignment to completed list
		completedList.insert(*iter);
		assignedList.remove(*iter);

		cout << endl << "** Assignment updated **" << endl;
		return true;
	}
}

void Menu::listLateAssignments() {
	string bar = "--------------------------------------------------------------";
	string tableHeader = " Assigned  Description                     Due Date   Status";
	int counter = 0;

	cout << endl << "--------------------- Late assignments -----------------------" << endl
		 << tableHeader << endl << bar << endl;
	
	// Search in the completed list only
	iter = completedList.begin(); 

	// Search the list for late assignments only
	while (iter != completedList.end()) {
		if (iter->getStatus() == late) {
			// Display the assignment and increment counter
			cout << iter->getAssignDate() << "|";
			cout << setw(30) << left << iter->getDescription() << "|";
			cout << iter->getDueDate() << "|";
			cout << statusTypes[iter->getStatus()] << endl;
			++counter;
		}
		++iter;
	}

	// Output the total number of late assignments
	cout << endl << "Total late assignments: " << counter << endl;
	cout << endl;
	return;
}

void Menu::saveLists() {
	char response;
	bool isInvalid = false;

	// Open the filestream 
	fstream fout;
	fout.open("assignments.txt"); 

	// Prompt user to confirm overwriting the previous assignments.txt file
	cout << endl << "Saving will overwrite and update the assignments list." << endl;

	// Prompt to confirm editing
	do {
		cout << endl << "Save changes? Y/N: ";
		cin >> response;
		// Check for valid response
		isInvalid = !(response == 'n' || response == 'N' || response == 'y' || response == 'Y');
		if (isInvalid)
			cout << "Invalid option. Please enter Y or N." << endl;

	// Re-prompt if invalid response
	} while (isInvalid);

	if (response == 'n' || response == 'N') {
		cout << endl << "** Save cancelled **" << endl;
		return;
	}
	else {
		// Write assignment lists to assignments.txt
		iter = assignedList.begin();
		while (iter != assignedList.end()) {
			fout << iter->getDueDate() << ", " << iter->getDescription() << ", " << iter->getAssignDate() << ", " << statusTypes[iter->getStatus()] << endl;
			++iter;
		}

		iter = completedList.begin();
		while (iter != completedList.end()) {
			fout << endl << iter->getDueDate() << ", " << iter->getDescription() << ", " << iter->getAssignDate() << ", " << statusTypes[iter->getStatus()];
			++iter;
		}
	}

	cout << endl << "** Assignments saved **" << endl;
	return; 
}

void Menu::exitProgram() {
	char response;
	bool isInvalid = false;
	
	cout << endl << "Warning: Any unsaved data will be lost." << endl;
	// Prompt to confirm editing
	do {
		cout << endl << "Exit program? Y/N: ";
		cin >> response;
		// Check for valid response
		isInvalid = !(response == 'n' || response == 'N' || response == 'y' || response == 'Y');
		if (isInvalid)
			cout << "Invalid option. Please enter Y or N." << endl;

		// Re-prompt if invalid response
	} while (isInvalid);

	if (response == 'n' || response == 'N') {
		cout << endl << "** Exit cancelled **" << endl;
		return;
	}
	else
		exit(1);
}

// Search both lists for a specified date
bool Menu::findAssignment(Date inDate) {

	// Start in the assigned list
	iter = assignedList.begin(); 

	// Search the list for the specified date
	iter = assignedList.find(inDate); 

	// If date was not found in Assigned list
	if (iter == assignedList.end()) { 
		// Check  the completed list
		iter = completedList.find(inDate); 
		// If date was not Found in completed List
		if (iter == completedList.end()) { 
			// Return assignment not found
			return false; 
		}
	}
	// Return assignment found
	return true;
}
