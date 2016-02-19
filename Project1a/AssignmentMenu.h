#ifndef ASSIGNMENT_MENU_H
#define ASSIGNMENT_MENU_H

#include "assignment.h"
#include "Date.h"

#include "Ordered_List.h" //Maybe jay's and binh's 201


class assignmentMenu : public assignment
{
private: 
	assignmentMenu(); //Constructor
	~assignmentMenu(); //Destructor

public: 
	static void addToList(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList, Date due, string desc, Date assign, assignStatus status);
	static void displayAssignments(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void addAssignment(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void editDueDate(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void editDescription(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void completeAssignment(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void listLateAssignments(Ordered_List<assignment>& completedList);
	static void saveLists(Ordered_List<assignment>& assignedList, Ordered_List<assignment>& completedList);
	static void exit(); 

	// Error handling
	bool checkformat(Date checkDate); 
};

#endif