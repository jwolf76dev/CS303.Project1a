#ifndef ASSIGNMENT_LIST_H
#define ASSIGNMENT_LIST_H

#include "Assignment.h"
#include "Ordered_List.h"
#include "Date.h"
#include <iostream>
#include <fstream>

class Assignment_List {
private:
	Ordered_List<Assignment> assignedList;
	Ordered_List<Assignment> completedList;
	Ordered_List<Assignment>::iter listIter = assignedList.begin();
public:
	Assignment_List() { load_data(); }  // Load Data Here
	~Assignment_List() {}

	// Used for list population
	string trim(const string& the_string);
	void load_data();

	// List modifiers
    void addToList(Date due, string desc, Date assign, assignStatus status);
	bool addAssignment();
	bool findAssignment(Date inDate);
	bool editDueDate();
	bool editDescription();
	bool completeAssignment();

	// List accessors
	void displayAssignments();
	void listLateAssignments();

	// Program functions
	void saveLists();
	void exitProgram();


};


#endif
