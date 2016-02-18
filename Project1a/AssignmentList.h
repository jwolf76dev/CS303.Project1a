#ifndef _ASSIGNMENT_LIST_H_
#define _ASSIGNMENT_LIST_H_

#include "assignment.h"
#include "Date.h"

#include "Ordered_List.h" //Maybe jay's and binh's 201


class AssignmentList// : public Ordered_List
{
private: 
	AssignmentList(); //Constructor
	~AssignmentList(); //Destructor

public: 
	void displayAssignments(); 
	void addAssignment();
	void editDueDate(Date assignDate, Date newDueDate); 
	void editDescription(Date assignDate, string newDesc); 
	void completeAssignment(Date assignDate); 
	void listLateAssignments(); 
	void saveLists(); 
	void exit(); 

	// Error handling
	bool checkformat(Date checkDate); 
};

#endif