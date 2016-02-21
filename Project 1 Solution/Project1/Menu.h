#ifndef MENU_H
#define MENU_H

#include "Assignment.h"
#include "Date.h"
#include "Ordered_List.h"

class Menu {
private:
	Ordered_List<Assignment> assignedList;
	Ordered_List<Assignment> completedList;
	Ordered_List<Assignment>::iter iter = assignedList.begin();

public:
	//Constructors
	Menu() {}
	Menu(Ordered_List<Assignment>& aList, Ordered_List<Assignment>& cList) : assignedList(aList), completedList(cList) {}

	//Destructor
	~Menu() {}

	//Modifiers
	bool addAssignment();
	bool findAssignment(Date inDate);
	bool editDueDate();
	bool editDescription();
	bool completeAssignment();

	//Other menu options
	void displayAssignments();
	void listLateAssignments();
	void saveLists();
	void exitProgram();

	//Other
	void addToList(Date due, string desc, Date assign, assignStatus status);
}; 
#endif