#include "AssignmentList.h"
#include <iostream>
using namespace std;

//Constructor
AssignmentList::AssignmentList()
{

}
//Destructor
AssignmentList::~AssignmentList()
{

}

void AssignmentList::displayAssignments()
{
	// Use while loop with iterator to go through lists
	// Create one list for assigned list
	// Create one list for completed list
	// Print out file exactly like the file name

}

void AssignmentList::addAssignment()
{

	Date assignedDate, dueDate;
	string desc; 
	int statChoice;
	assignStatus status;

	// Parameters are all the necessary parameters for assigned date (user will use menus). 
	// Prompt user for the assignedDate in MM/DD/YYYY format. 
	cout << "When was it assigned?" << endl; 
	cin >> assignedDate; 

	// Prompt the user for the dueDate in MM/DD/YYYY format. 
	cout << "When's the due date?" << endl; 
	cin >> dueDate; 

	// Prompt the user for the description. 
	cout << "Describe the assignment" << endl; 
	cin >> desc;

	// Prompt the user for the assignedStatus. Maybe put this in the menu()
	cout << "What's the status?" << endl;
	cout << "1 - Assigned" << endl
		<< "2 - Completed" << endl
		<< "3 - Late" << endl << endl;
	cin >> statChoice;
	
	switch (statChoice) {
		case 1: {status = assigned; break; }
		case 2: {status = completed; break; }
		case 3: {status = late; break; }
	}
	// Use a switch menu to get the status

	// Check if both dates are valid with the checkformat function and trying the Date class
	// Check if assigned Date is < due Date
	// Reprompt if the dates are incorrect - otherwise, break out of this function. 

}

void AssignmentList::editDueDate(Date assignDate, Date newDueDate)
{
	// Find assignment first
	// Prompt the user for a date
	// Call the checkformat function to make sure that it's a workable format. 
	// Search both lists for the assignment
	// Find date in lists, throw error if it doesn't exist
	// Display assignment details
	// Prompt for new due date 
	// Call the checkformat function to make sure that it's a workable format
	// Update the assignment
	cout << "Update complete." << endl;
}

void AssignmentList::editDescription(Date assignDate, string newDesc)
{
	// Find assignment first
	// Prompt the user for a date
	// Call the checkformat function to make sure that it's a workable format. 
	// Search both lists for the assignment
	// Find date in lists, throw error if it doesn't exist
	// Display assignment details
	// Prompt for new description
	// Update the assignment
	cout << "Update complete." << endl;
}

void AssignmentList::completeAssignment(Date assignDate)
{
	// Prompt for assigned date
	// Call the checkformat function to make sure that it's a workable date
	// Search the list in the assignedList to find it
	// Throw error if not found. 
	// If found, prompt for completed date
	// Check format
	// Then check if the completed date is greater than the assigned date, and if not, then it's invalid
	// If it's valid, if the completed date is before or equal to the due date, then mark it as completed
	// If it's past the due date, mark it as late. 

}

void AssignmentList::listLateAssignments()
{
	// Search the completed list and count the number of late assignments. 
	// Display the assignments as we find them. 
	// Increment the count. 
}

void AssignmentList::saveLists()
{
	// Overload the output operator
	// Reading out to old file
	// Let user know that this program is replacing the old file. 
}

void AssignmentList::exit()
{
	// Tell the user that any unsaved work will be lost. 
	cout << "Any unsaved data will be lost, are you sure(Y/N)?:";
	char quit;
	cin >> quit;
	if (quit == 'Y' || quit == 'y') {
		system("pause");
		exit();
	}
}

bool AssignmentList::checkformat(Date checkDate)
{
	// Compare the string and check if the date is right
	// Use the delimiters to check for proper format
	// Check for uniqueness in both lists. 
	return 0;
}