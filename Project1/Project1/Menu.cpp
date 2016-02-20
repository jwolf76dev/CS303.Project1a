#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

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

	cout << "----------------------- Assigned List ----------------------" << endl
		 << " Assigned  Description                Due Date  Status"	   << endl
	 	 << "------------------------------------------------------------" << endl;
	while (iter != assignedList.end()) {
		cout << setw(11) << iter->getAssignDate() << " ";
		cout << setw(26) << left << iter->getDescription() << " ";
		cout << setw(11) << iter->getDueDate() << " ";
		cout << StatusTypes[iter->getStatus()] << endl;
		++iter;
	}
	cout << endl;

	iter = completedList.begin();
	cout << "------------------ Completed and Late List -----------------" << endl;
	cout << "Assigned     Description              Due Date      Status" << endl
		 << "------------------------------------------------------------" << endl;
	while (iter != completedList.end()) {
		cout << iter->getAssignDate() << ", " << iter->getDescription() << ", " << iter->getDueDate() << ", " << StatusTypes[iter->getStatus()] << endl;
		++iter;
	}

}

void Menu::addAssignment()
{
	Date assignedDate, dueDate;
	string desc;
	int statChoice;
	assignStatus status;

	// Parameters are all the necessary parameters for assigned date (user will use menus). 
	// Prompt user for the assignedDate in MM/DD/YYYY format. 
	cout << "When was it assigned? (MM/DD/YYYY)" << endl;
	cin >> assignedDate; //TODO: Date error checking

	// Prompt the user for the dueDate in MM/DD/YYYY format. 
	cout << "When's the due date? (MM/DD/YYYY)" << endl;
	cin >> dueDate; //TODO: dueDate !<= assigndate


	cin.ignore(1);
	// Prompt the user for the description. 
	cout << "Describe the assignment: " << endl;
	getline(cin, desc);

	// Prompt the user for the assignedStatus. Maybe put this in the menu()
	cout << "What's the status?" << endl;
	cout << "1 - Assigned" << endl
		 << "2 - Completed" << endl
		 << "3 - Late" << endl << endl;
	cin >> statChoice;

	// Use a switch menu to get the status
	switch (statChoice) {
		case 1: {status = assigned; break; }
		case 2: {status = completed; break; }
		case 3: {status = late; break; }
		default: {status = assigned;  cout << "Incorrect option!" << endl; break; } //TODO: fix me! This is dumb.
	}

	addToList(dueDate, desc, assignedDate, status);

	// Check if assigned Date is < due Date
	// Reprompt if the dates are incorrect - otherwise, break out of this function. 

}



bool Menu::editDueDate()
{
	// Prompt the user for a date
	cout << "Enter the assigned date of the assignment to edit. (MM/DD/YYYY)" << endl; //TODO: WORDING OMG
	Date inDate;
	cin >> inDate;

	Ordered_List<Assignment>::iter iter= assignedList.begin();
	
	iter = assignedList.find(inDate);
	if (iter == assignedList.end()) {
		//Not found in Assigned list
		iter = completedList.find(inDate);
		if (iter == completedList.end()) {
			//Not Found in completed List
			cout << "Assignment Not Found." << endl << endl;
			return false;
		}
	}

	//TODO: Edit due date stuff








	// Find date in lists, throw error if it doesn't exist
	// Display assignment details
	// prompt to confirm correct assignment to edit - return to main menu if incorrect assignment
	// if correct assignment, prompt for new due date 
	// verify new due date > assigned date
	// Update the assignment
	cout << "Update complete." << endl << endl;
	return true;
}

bool Menu::editDescription()
{
	cout << "Enter the assigned date of the assignment to edit. (MM/DD/YYYY)" << endl; //TODO: WORDING OMG
	Date inDate;
	cin >> inDate;

	Ordered_List<Assignment>::iter iter = assignedList.begin();

	iter = assignedList.find(inDate);
	if (iter == assignedList.end()) {
		//Not found in Assigned list
		iter = completedList.find(inDate);
		if (iter == completedList.end()) {
			//Not Found in completed List
			cout << "Assignment Not Found." << endl << endl;
			return false;
		}
	}


	//TODO: Edit description stuff



	// Prompt the user for a date
	// Find date in lists, throw error if it doesn't exist
	// Display assignment details
	// prompt to confirm correct assignment to edit - return to main menu if incorrect assignment
	// if correct assignment, prompt for new description 
	// Update the assignment
	cout << "Update complete." << endl;
	return true;
}

void Menu::completeAssignment()
{

	//TODO: Bool-lize
	//TODO: iter.find(indate);

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
	// Search the completed list and count the number of late assignments. 
	// Display the assignments as we find them. 
	// Increment the count. 
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

bool Menu::checkformat(Date checkDate)
{
	// Compare the string and check if the date is right
	// Use the delimiters to check for proper format
	// Check for uniqueness in both lists. 
	/*


	//Rando Error Checking - for later, bullshit for now
	/*if (inDate < temp1.getAssignDate()) //If an input date is before assign date
	{
	cout << "Error" << endl;
	}

	if (tempDueDate <= tempAssignDate) //If DueDate <= AssignDate
	{
	cout << "Error" << endl;
	}

	if (tempAssignDate == temp1.getAssignDate()) //If new assignment date already exists
	{
	cout << "Error" << endl;
	}

	*/
	return 0;
}