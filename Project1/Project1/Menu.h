#ifndef MENU_H
#define MENU_H

#include "Assignment.h"
#include "Date.h"
#include "Ordered_List.h"

class Menu : public Assignment
{
private: 
	Ordered_List<Assignment> assignedList;
	Ordered_List<Assignment> completedList;

public: 
	Menu() {} //Constructor
	Menu(Ordered_List<Assignment>& aList, Ordered_List<Assignment>& cList) : assignedList(aList), completedList(cList) {}
	~Menu() {} //Destructor

	void addToList(Date due, string desc, Date assign, assignStatus status);
	void displayAssignments();
	void addAssignment();
	bool editDueDate();
	bool editDescription();
	void completeAssignment();
	void listLateAssignments();
	void saveLists();
	void exit();

	// Error handling
	bool checkformat(Date checkDate); 
};

#endif