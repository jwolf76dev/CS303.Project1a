#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

string StatusTypes[] = { "assigned","completed","late" }; //Converts enum

void Menu::addToList(Date due, string desc, Date assign, assignStatus status) {

	Assignment tempAssign(due, desc, assign, status);

	if (status == assigned)
		assignedList.insert(tempAssign);
	else
		completedList.insert(tempAssign);
}

void Menu::displayAssignments()
{	//TODO: Make it more elegant
	Ordered_List<Assignment>::iter iter = assignedList.begin();	
	string StatusTypes[] = { "assigned","completed","late" }; // Convert enum to text
	//TODO: Finish formatting

	cout << "------------- Assigned List ------------" << endl
		 << "Assigned  Description  Due Date  Status" << endl
	 	 << "----------------------------------------" << endl;
	while (iter != assignedList.end()) {
		cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl;
		++iter;
	}
	cout << endl;

	iter = completedList.begin();
	cout << "------- Completed and Late List --------" << endl
		 << "Assigned  Description  Due Date  Status" << endl
		 << "----------------------------------------" << endl;
	while (iter != completedList.end()) {
		cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl;
		++iter;
	}

}

bool Menu::addAssignment()
{
	//TODO: Check for uniquness of assignment date

	// Input variables from user
	Date assignedDate, dueDate;
	string desc;
	int statChoice;
	assignStatus status;

	// Continue to prompt user until they enter a vaild date
	cout << "When was it assigned? (MM/DD/YYYY)" << endl;
	cin >> assignedDate;
	do {
		// look for entry in list
		if (findAssignment(assignedDate) == true){
			cout << "Error: This assignment already exists. Please check the date and try again." << endl;
			cin >> assignedDate;
		}
	} while (findAssignment(assignedDate) == true); 

	cout << "When's the due date? (MM/DD/YYYY)" << endl;
	cin >> dueDate; //TODO: dueDate !<= assigndate

	if (dueDate < assignedDate) {
		cout << "Due date cannot be before assigned date!" << endl << endl;
	}

	while (dueDate < assignedDate);


	// Dates are vaild, get description and status
	cin.ignore(1);
	cout << "Describe the assignment: " << endl;
	getline(cin, desc);

	// Use a switch menu to get the status
	do {
		cout << "What's the status?" << endl;
		cout << "1 - Assigned" << endl
			<< "2 - Completed" << endl
			<< "3 - Late" << endl << endl;
		cin >> statChoice;
		switch (statChoice) {
		case 1: {status = assigned; break; }
		case 2: {status = completed; break; }
		case 3: {status = late; break; }
		default: {status = assigned;  cout << "Incorrect option!" << endl;}
		}
	} while (statChoice > 3); 
	

	// Add the object
	addToList(dueDate, desc, assignedDate, status);

	return true;
}

bool Menu::editDueDate()
{
	// Prompt the user for a date
	cout << "Enter the assigned date of the assignment to edit. (MM/DD/YYYY)" << endl; //TODO: WORDING OMG
	Date inDate;
	cin >> inDate;

	// Look for the date in the lists
	if (findAssignment(inDate) == false) {
		cout << "Assignment not found" << endl; 
		return false;
		}

	// Output found assignment to user
	cout << "Here is the assignment you chose:" << endl << endl;
	cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl << endl;

	// Prompt to confirm editing
	cout << "\nEdit this assignment? Y/n: ";
	cin.ignore(1);
	string ch;
	cin >> ch;
	if (ch == "n" || ch == "N") {
		return false; // Exit function if they enter no
	}

	// Prompt for a new due date until a vaild date is found
	do {
		cout << "Enter a new due date (MM/DD/YYYY): ";
		cin >> inDate;
	} while (checkformat(inDate, iter) == 0, cout << "Error");

	iter->setDueDate(inDate); // Update the assignment

	// Inform user of update
	cout << "\nUpdate complete." << endl << endl;
	return true;
}

bool Menu::editDescription()
{
	// Prompt user for a date
	cout << "Enter the assigned date of the assignment to edit. (MM/DD/YYYY)" << endl;
	Date inDate;
	cin >> inDate;

	// If the date is invaild, exit function
	if (findAssignment(inDate) == false) {
		cout << "Assignment not found" << endl; 
		return false;
		}

	// Display found assignment
	cout << "Here is the assignment you chose:" << endl;
	cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl << endl;


	// Confirm with user to edit assignment
	cout << "\nEdit this assignment? Y/n: ";
	cin.ignore(1);
	string ch;
	cin >> ch;
	if (ch == "n" || ch == "N") {
		return false; // Exit if user does not want to edit
	}

	// Prompt user for new description
	cin.ignore(1);
	string newDesc;
	cout << "Enter a description: ";
	getline(cin,newDesc);

	iter->setDescription(newDesc); // Set new description

	// Inform user of the update
	cout << "\nUpdate complete." << endl << endl;
	return true;
}

bool Menu::completeAssignment()
{
	// Get the assignment date from the user
	cout << "Enter the assigned date of the assignment to complete. (MM/DD/YYYY)" << endl;
	Date inDate;
	cin >> inDate;

	// Search for the assignment in the assigned list only
	iter = assignedList.begin();

	iter = assignedList.find(inDate);
	if (iter == assignedList.end()) {
		// Not found in Assigned list
		cout << "Assignment Not Found." << endl << endl;
		return false; // Exit function
	}
	/*
	completedList.insert(*iter);
	assignedList.remove(*iter);

	// Prompt the user for the assignedStatus. Maybe put this in the menu()
	cout << "What's the status?" << endl;
	cout << "1 - Assigned" << endl
		<< "2 - Completed" << endl
		<< "3 - Late" << endl << endl;
	int statChoice;
	cin >> statChoice;

	// Use a switch menu to get the status
	assignStatus status;
	switch (statChoice) {
	case 1: {status = assigned; break; }
	case 2: {status = completed; break; }
	case 3: {status = late; break; }
	default: {status = assigned;  cout << "Incorrect option!" << endl; break; } //TODO: fix me! This is dumb.
	} */

	// Prompt for assigned date
	// Search the list in the assignedList to find it
	// Throw error if not found. 
	// If found, prompt for completed date
	// Check format
	// Then check if the completed date is greater than the assigned date, and if not, then it's invalid
	// If it's valid, if the completed date is before or equal to the due date, then mark it as completed
	// If it's past the due date, mark it as late. 
}


void Menu::listLateAssignments()
{
	cout << "--------------Late assignments--------------------" << endl;
	iter = completedList.begin(); // Peruse through the completed list only
	int counter = 0; // Counter for number of late assignments

	// Search the list looking for late assignments only
	while (iter != completedList.end()) {
		if (iter->getStatus() == late) {
			// Display the assignment and increment counter
			cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl << endl;
			++counter;
		}
		++iter;
	}

	// Output the total number of late assignments
	cout << endl << "Total late assignments: " << counter << endl;
	cout << "----------------------------------------------------" << endl;

}

void Menu::saveLists()
{
	// Overload the output operator
	// Reading out to old file
	// Let user know that this program is replacing the old file. 
}

void Menu::exitProgram()
{
	// Tell the user that any unsaved work will be lost. 
	cout << "Any unsaved data will be lost, are you sure(Y/N)?:";
	char quit;
	cin >> quit;
	if (quit == 'Y' || quit == 'y' || quit == '1') {
		exit(1);
	}
	else
		cout << endl << "Invalid entry." << endl << endl;
}

// Search both lists for a specified date
bool Menu::findAssignment(Date inDate) {

	iter = assignedList.begin(); // Start in the assigned list
	iter = assignedList.find(inDate); // Search the list for the specified date
	if (iter == assignedList.end()) { // If date was not found in Assigned list
		iter = completedList.find(inDate); // Check  the completed list
		if (iter == completedList.end()) { // If date was not Found in completed List
			return false; // Return assignment not found
		}
	}
	return true; // Return assignment found
	}

bool Menu::checkformat(Date inDate, Ordered_List<Assignment>::iter& iter)
	{
	// TODO: Check for uniqueness in both lists. 
	// TODO: Do we need the passed in iterator?
	
	if (inDate <= iter->getAssignDate()) {
		cout << "Error! Due date cannot be before the assigned date." << endl;
		return 0;
	}

	if (inDate == iter->getAssignDate()) //If new assignment date already exists
	{
	cout << "Error! Due date cannot be on the assigned date" << endl;
	return 0;
	}

	return 1; // Date is vaild
}