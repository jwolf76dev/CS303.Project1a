
#include "Assignment_List.h"
using namespace std;
string statusTypes[] = { "assigned", "completed", "late" };

// Function trim() code from M. Kuhail
// email: kuhailm@umkc.edu

// Break the string into individual elements
string Assignment_List::trim(const string& the_string) {
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");
	return the_string.substr(p, q - p + 1);
}


void Assignment_List::load_data() {
	// Load assignment lists from file

	// Variables from file input
	string line, dueDate, desc, assignDate, status;
	ifstream in("assignments.txt");

	// Stream exists
	if (in)
	{
		// Read a line from the file
		while (getline(in, line))
		{
			if (line == "")
				continue;

			// Function st() from M. Kuhail
			// Parse the elements in the line using a comma delimlistIter
			String_Tokenizer st(line, ",");
			dueDate = trim(st.next_token());
			desc = trim(st.next_token());
			assignDate = trim(st.next_token());
			status = trim(st.next_token());

			// Convert tokenized string to date and assignment status
			Date newDue(dueDate), newAssign(assignDate);
			assignStatus newStatus;

			// Set the enumerated status
			if (status == "assigned") {
				newStatus = assigned;
			}
			else if (status == "completed") {
				newStatus = completed;
			}
			else { newStatus = late; }

			// Add the item to the list
			addToList(newDue, desc, newAssign, newStatus);
		}
	}
	// Close the input stream
	in.close();

}

void Assignment_List::addToList(Date due, string desc, Date assign, assignStatus status) {

	Assignment tempAssign(due, desc, assign, status);

	if (status == assigned)
		assignedList.insert(tempAssign);
	else
		completedList.insert(tempAssign);
	return;
}

// Display both lists of assignments
void Assignment_List::displayAssignments() {
	// Variables
	string bar = "--------------------------------------------------------------";
	string tableHeader = " Assigned  Description                     Due Date   Status";

	// Output formatted Assigned list
	cout << endl << "------------------------ Assigned List -----------------------" << endl
		<< tableHeader << endl
		<< bar << endl;

	listIter = assignedList.begin();
	while (listIter != assignedList.end()) {
		cout << listIter->getAssignDate() << "|"
			<< setw(30) << left << listIter->getDescription().substr(0, 30) << "|"
			<< listIter->getDueDate() << "|"
			<< statusTypes[listIter->getStatus()] << endl;
		++listIter;
	}
	cout << endl;

	// Output formatted Completed and Late list
	cout << endl << "------------------ Completed and Late List -------------------" << endl
		<< tableHeader << endl
		<< bar << endl;

	listIter = completedList.begin();
	while (listIter != completedList.end()) {
		cout << listIter->getAssignDate() << "|"
			<< setw(30) << left << listIter->getDescription().substr(0, 30) << "|"
			<< listIter->getDueDate() << "|"
			<< statusTypes[listIter->getStatus()] << endl;
		++listIter;
	}
	cout << endl;
	return;
}
// Add a new assignment to a list
bool Assignment_List::addAssignment() {
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
			cout << "Error: An assignment with this date already exists." << endl
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
bool Assignment_List::editDueDate() {
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
		<< listIter->getAssignDate() << "|"
		<< setw(30) << left << listIter->getDescription().substr(0, 30) << "|"
		<< listIter->getDueDate() << "|"
		<< statusTypes[listIter->getStatus()] << endl
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
			if (inDate < listIter->getAssignDate()) {
				cout << "Error: The due date cannot be before the assigned date." << endl
					<< "Please check the date and try again." << endl;
			}
			// Re-prompt if condition fails
		} while (inDate < listIter->getAssignDate());
	}

	// Update the assignment
	listIter->setDueDate(inDate);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Assignment_List::editDescription() {
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
	cout << listIter->getAssignDate() << "|";
	cout << setw(30) << left << listIter->getDescription().substr(0, 30) << "|";
	cout << listIter->getDueDate() << "|";
	cout << statusTypes[listIter->getStatus()] << endl;
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
	listIter->setDescription(newDesc);
	cout << endl << "** Assignment updated **" << endl;
	return true;
}

bool Assignment_List::completeAssignment() {
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
	listIter = assignedList.find(inDate);

	if (listIter == assignedList.end()) {
		cout << "Error: Assignment not found." << endl;
		return false;
	}

	// Output assignment to user
	cout << endl << "--------------------- Assignment Details ---------------------" << endl;
	cout << tableHeader << endl << bar << endl;
	cout << listIter->getAssignDate() << "|";
	cout << setw(30) << left << listIter->getDescription().substr(0, 30) << "|";
	cout << listIter->getDueDate() << "|";
	cout << statusTypes[listIter->getStatus()] << endl;
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
		if (doneDate <= listIter->getDueDate()) {
			listIter->setStatus(completed);
		}
		else
			listIter->setStatus(late);

		// Move completed assignment to completed list
		completedList.insert(*listIter);
		assignedList.remove(*listIter);

		cout << endl << "** Assignment updated **" << endl;
		return true;
	}
}

void Assignment_List::listLateAssignments() {
	string bar = "--------------------------------------------------------------";
	string tableHeader = " Assigned  Description                     Due Date   Status";
	int counter = 0;

	cout << endl << "--------------------- Late assignments -----------------------" << endl
		<< tableHeader << endl << bar << endl;

	// Search in the completed list only
	listIter = completedList.begin();

	// Search the list for late assignments only
	while (listIter != completedList.end()) {
		if (listIter->getStatus() == late) {
			// Display the assignment and increment counter
			cout << listIter->getAssignDate() << "|";
			cout << setw(30) << left << listIter->getDescription() << "|";
			cout << listIter->getDueDate() << "|";
			cout << statusTypes[listIter->getStatus()] << endl;
			++counter;
		}
		++listIter;
	}

	// Output the total number of late assignments
	cout << endl << "Total late assignments: " << counter << endl;
	cout << endl;
	return;
}

void Assignment_List::saveLists() {
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
		listIter = assignedList.begin();
		while (listIter != assignedList.end()) {
			fout << listIter->getDueDate() << ", " << listIter->getDescription() << ", " << listIter->getAssignDate() << ", " << statusTypes[listIter->getStatus()] << endl;
			++listIter;
		}

		listIter = completedList.begin();
		while (listIter != completedList.end()) {
			fout << endl << listIter->getDueDate() << ", " << listIter->getDescription() << ", " << listIter->getAssignDate() << ", " << statusTypes[listIter->getStatus()];
			++listIter;
		}
	}

	cout << endl << "** Assignments saved **" << endl;
	return;
}

void Assignment_List::exitProgram() {
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
bool Assignment_List::findAssignment(Date inDate) {

	// Start in the assigned list
	listIter = assignedList.begin();

	// Search the list for the specified date
	listIter = assignedList.find(inDate);

	// If date was not found in Assigned list
	if (listIter == assignedList.end()) {
		// Check  the completed list
		listIter = completedList.find(inDate);
		// If date was not Found in completed List
		if (listIter == completedList.end()) {
			// Return assignment not found
			return false;
		}
	}
	// Return assignment found
	return true;
}
