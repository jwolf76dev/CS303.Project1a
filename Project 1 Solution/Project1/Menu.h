#ifndef MENU_H
#define MENU_H

#include "Assignment.h"
#include "Date.h"
#include "Ordered_List.h"

class Menu
{
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

	void addToList(Date due, string desc, Date assign, assignStatus status); //working
	void displayAssignments(); //working

	// Modifiers
	bool addAssignment(); // Pretty much completed, check for it again
	bool findAssignment(Date inDate); // working
	bool editDueDate(); // working
	bool editDescription(); // working
	bool completeAssignment(); //Pretty much completed, check for it again. 


	void listLateAssignments(); // working
	void saveLists(); //Pretty much completed, check for it again.
	void exitProgram(); //Pretty much completed, check for it again. 

	// Error handling
	bool checkformat(Date checkDate, Ordered_List<Assignment>::iter& iter); //TODO: Do we need the iterator passed in????????? IDK MAN
};

#endif