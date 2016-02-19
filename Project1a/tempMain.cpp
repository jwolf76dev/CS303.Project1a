#include "assignment.h"
#include "Ordered_List.h"
#include <iostream>
#include <fstream>


using namespace std;
//This is just random stuff.  I was playing around to make sure my class worked.
void load_data( Ordered_List<assignment>&, Ordered_List<assignment>&);
string trim(const string& the_string);
void main() {
	Ordered_List<assignment> completed;
	Ordered_List<assignment> assigned;

	load_data(completed, assigned);


	//Iterators for the lists
	Ordered_List<assignment>::iter iterA = assigned.begin();
	Ordered_List<assignment>::iter iterC = completed.begin();

	//Read out the lists

	cout << "Assigned List" << endl;
	while (iterA != assigned.end()) {
		cout << iterA->getDueDate()<< ", " << iterA->getDescription() << ", "<< iterA->getAssignDate() << ", " << iterA->getStatus()<< endl;
		++iterA;
	}

	cout << "completed/late List" << endl;
	while (iterC != completed.end()) {
		cout << iterC->getDueDate() << ", " << iterC->getDescription() << ", " << iterC->getAssignDate() << ", " << iterC->getStatus() << endl;
		++iterC;
	}
	system("pause");
	
	/*
	/*string date = "5-1-2014";
	Date tempDueDate("4-1-2014");
	Date tempAssignDate(date);
	assignStatus temp = assigned;

	int a = 2015, b = 03, c = 23;
	Date whoCares(a, b, c); //sets date to 03/23/2015

	while (whoCares.check_valid() != 1) {

	}
	
	assignment temp1(tempDueDate, tempAssignDate, "things", temp);
	*/

	//Date rando(2015, 2, 28);
	//cin >> date;
	//Date inDate(date);
	
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

	cout << "--------------------Main Menu-------------------------------" << endl;
	cout<< "1 - Load Assignments" << endl
		<< "2 - Display Assignments" << endl
		<< "3 - Edit Assignment" << endl
		<< "4 - Count Late assignments" << endl
		<< "5 - Add assignment" << endl
		<< "6 - Mark assignment as complete" << endl
		<< "7 - Save assignments" << endl
		<< "8 - Exit"<< endl;*/

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
		while (getline(in, line)) { //read the next line
			String_Tokenizer st(line, ","); //parse the tokens in the line (separated by a comma)	
			dueDate = trim(st.next_token());
			desc = trim(st.next_token());
			assignDate = trim(st.next_token());
			status = trim(st.next_token());
			Date newDue(dueDate);
			Date newAssign(assignDate);
			assignStatus newStatus;

			if (status == "assigned") {
				newStatus = assigned;
			}
			else if (status == "complete") {
				newStatus = completed;
			}
			else {
				newStatus = late;
			}

			assignment newAssignment(newDue, desc, newAssign, newStatus);

			if (newStatus != assigned)
				assignedList.insert(newAssignment);
			else
				completedList.insert(newAssignment);
		}
	}
	in.close();


}


