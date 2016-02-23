#include "Menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//Classes should be all the same case, so it should be CamelCase. 
//All of the curly braces need to be the same. 
//Indentation needs to look same
//Language, style, and grammar of prompts need to look consistent. 
//Most comments should be the line above, and need to be similar. 

string statusTypes[] = { "assigned","completed","late" }; //Converts enum

void Menu::addToList(Date due, string desc, Date assign, assignStatus status) {
	Assignment tempAssign(due, desc, assign, status);

	if (status == assigned)
		assignedList.insert(tempAssign);
	else
		completedList.insert(tempAssign);
}

void Menu::displayAssignments() {
	string bar = "--------------------------------------------------------------"; 
	string tableHeader = " Assigned  Description                     Due Date   Status"; 

	cout << endl << "------------------------ Assigned List -----------------------" << endl
		<< tableHeader << endl << bar << endl; 

	iter = assignedList.begin();
	while (iter != assignedList.end()) {
		cout << iter->getAssignDate() << "|"; 
		cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|"; 
		cout << iter->getDueDate() << "|"; 
		cout << statusTypes[iter->getStatus()] << endl; 
		++iter; 
	}
		
	iter = completedList.begin();
	cout << endl << "------------------ Completed and Late List -------------------" << endl
		<< tableHeader << endl << bar << endl; 
	while (iter != assignedList.end()) {
		cout << iter->getAssignDate() << "|";
		cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|";
		cout << iter->getDueDate() << "|";
		cout << statusTypes[iter->getStatus()] << endl;
		++iter;
	}
	cout << endl;
}

bool Menu::addAssignment() {
	//Variables
	Date assignedDate, dueDate;
	string desc;
	int statChoice;
	assignStatus status;

	cout << endl << "** Add Assignment **" << endl;
	//Prompt user for assigned date
	do {
		cout << endl << "When was it assigned? (MM/DD/YYYY): ";
		cin >> assignedDate;

		//Verify unique assigned date
		if (findAssignment(assignedDate) == true) {
			cout << "Error: This assignment already exists." <<endl
				 << "Please check the date and try again." << endl;
		}

		//Verify valid assigned date
		if (assignedDate.getYear() < 2000) {
			cout << "Error: The date entered is invalid." << endl
				 << "Please make sure that the year is after 2000." << endl;
		}
	//Re-prompt if either condition fails
	} while (findAssignment(assignedDate) == true || assignedDate.getYear() < 2000);

	//Prompt user for due date
	do {
		cout << endl << "When is/was it due? (MM/DD/YYYY): ";
		cin >> dueDate;

		//Verify valid due date
		if (dueDate < assignedDate) {
			cout << "Error: The due date cannot be before the assigned date." << endl
				 << "Please check the date and try again." << endl;
		}
	//Re-prompt if condition fails
	} while (dueDate < assignedDate); 
	
	//Prompt user for assignment description
	cin.ignore(1);
	cout << endl << "Enter a brief description of the assignment: ";
	getline(cin, desc);

	//Prompt user for assignment status
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
	//Re-prompt if condition fails
	} while (statChoice > 3 || statChoice < 1);
		
	//Add the object
	addToList(dueDate, desc, assignedDate, status);
	cout << endl << "** Assignment added **" << endl;
	return true;
}

bool Menu::editDueDate() {
	//Variables
	Date inDate;
	char response;
	bool isInvalid = false;
	string tableHeader = " Assigned  Description                     Due Date   Status";
	string bar = "--------------------------------------------------------------";
	
	cout << endl << "** Edit Assignment Due Date **" << endl;

	//Prompt user for assigned date
	cout << endl << "When was it assigned? (MM/DD/YYYY): ";
	cin >> inDate;

	//Search for the date in the lists
	if (findAssignment(inDate) == false) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	//Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl;
	cout << tableHeader << endl << bar << endl; 
	cout << iter->getAssignDate() << "|";
	cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|";
	cout << iter->getDueDate() << "|";
	cout << statusTypes[iter->getStatus()] << endl;
	cout << bar << endl;

	//Prompt to confirm editing
	do {
		cout << endl << "Edit this assignment? Y/N: ";
		cin >> response;
		//Check for valid response
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
			//Prompt user for new due date
			cout << endl << "Enter the new due date (MM/DD/YYYY): ";
			cin >> inDate;

			//Verify valid due date
			if (inDate < iter->getAssignDate()) {
				cout << "Error: The due date cannot be before the assigned date." << endl
					<< "Please check the date and try again." << endl;
			}
		//Re-prompt if condition fails
		} while (inDate < iter->getAssignDate());
	}

	//Update the assignment
	iter->setDueDate(inDate);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Menu::editDescription() {
	//Variables
	Date inDate;
	string newDesc;
	char response;
	bool isInvalid = false;
	string tableHeader = " Assigned  Description                     Due Date   Status";
	string bar = "--------------------------------------------------------------";

	cout << endl << "** Edit Assignment Description **" << endl;

	//Prompt user for assigned date
	cout << endl << "When was it assigned? (MM/DD/YYYY): ";
	cin >> inDate;

	//Search for the date in the lists
	if (findAssignment(inDate) == false) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	//Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl;
	cout << tableHeader << endl << bar << endl;
	cout << iter->getAssignDate() << "|";
	cout << setw(30) << left << iter->getDescription().substr(0, 30) << "|";
	cout << iter->getDueDate() << "|";
	cout << statusTypes[iter->getStatus()] << endl;
	cout << bar << endl;

	//Prompt to confirm editing
	do {
		cout << endl << "Edit this assignment? Y/N: ";
		cin >> response;
		//Check for valid response
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
		//Prompt user for new description
		cin.ignore(1);
		cout << endl << "Enter the new description: ";
		getline(cin, newDesc);
	}

	//Update the assignment
	iter->setDescription(newDesc);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Menu::completeAssignment() {
	//Get the assignment date from the user
	cout << "Enter the assigned date of the assignment to complete. (MM/DD/YYYY)" << endl;
	Date inDate;
	cin >> inDate;

	//Search for the assignment in the assigned list only
	iter = assignedList.begin();
	iter = assignedList.find(inDate);

	iter = assignedList.find(inDate); //Search the list for the specified date, .find() will return the end() if not found. 
	if (iter == assignedList.end()) { //If date was not found in Assigned list
		cout << "Assignment Not Found. Please check assignments by using Display Assignments. " << endl; 
		return false; //Return assignment not found
	}

	cout << "Please enter the date you completed the assignment" << endl; 
	Date completedDate; 
	do {
		cin >> completedDate;
		//Then check if the completed date is greater than the assigned date, and if not, then it's invalid
		if (completedDate < inDate) {
			cout << "This completed date is before the assignment date. Please try again. " << endl; 
		}
	} while (completedDate < inDate); 

	//If it's valid, if the completed date is before or equal to the due date, then mark it as completed
	if (completedDate < iter->getDueDate()) {
		iter->setStatus(completed);
	}
	//If it's past the due date, mark it as late.
	else
		iter->setStatus(late); 

	completedList.insert(*iter);
	assignedList.remove(*iter);  
}

void Menu::listLateAssignments() {
	string bar = "--------------------------------------------------------------";
	string tableHeader = " Assigned  Description                     Due Date   Status";
	cout << endl << "--------------------- Late assignments -----------------------" << endl
		<< tableHeader << endl << bar << endl;
	//Peruse through the completed list only
	iter = completedList.begin(); 

	//Counter for number of late assignments
	int counter = 0; 

	//Search the list looking for late assignments only
	while (iter != completedList.end()) {
		if (iter->getStatus() == late) {
			//Display the assignment and increment counter
			cout << iter->getAssignDate() << "|";
			cout << setw(30) << left << iter->getDescription() << "|";
			cout << iter->getDueDate() << "|";
			cout << statusTypes[iter->getStatus()] << endl;
			++counter;
		}
		++iter;
	}

	//Output the total number of late assignments
	cout << endl << "Total late assignments: " << counter << endl;
	cout << bar << endl;

}

void Menu::saveLists() {
	//Overload the filestream 
	fstream fout;
	fout.open("assignments.txt"); 

	//Let user know that this program is replacing the old file. 
	cout << "This is replacing the old assignments.txt file" << endl; 

	//Reading out to old file
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


	return; 

}

void Menu::exitProgram() {
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

//Search both lists for a specified date
bool Menu::findAssignment(Date inDate) {

	//Start in the assigned list
	iter = assignedList.begin(); 

	//Search the list for the specified date
	iter = assignedList.find(inDate); 

	//If date was not found in Assigned list
	if (iter == assignedList.end()) { 
		//Check  the completed list
		iter = completedList.find(inDate); 
		//If date was not Found in completed List
		if (iter == completedList.end()) { 
			//Return assignment not found
			return false; 
		}
	}
	return true; //Return assignment found
}
