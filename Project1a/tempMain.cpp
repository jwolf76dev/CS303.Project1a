#include "assignment.h"
#include <iostream>

using namespace std;
//This is just random stuff.  I was playing around to make sure my class worked.  
void main() {
	string date = "5-1-2014";
	Date tempDueDate("4-1-2014");
	Date tempAssignDate(date);
	assignment::assignStatus temp = assignment::assigned;

	int a = 2015, b = 03, c = 23;
	Date whoCares(a, b, c); //sets date to 03/23/2015

	
	assignment temp1(tempDueDate, tempAssignDate, "things", temp);
	
	Date rando(2015, 2, 28);
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