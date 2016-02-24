#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include "Date.h"

enum assignStatus { assigned, completed, late };

class Assignment {
private:
	Date dueDate;
	Date assignDate;
	string description;
	assignStatus status;
public:
	// Constructors
	Assignment() { ; }
	Assignment(Date newDue, string newDisc, Date newAssign, assignStatus newStatus) : dueDate(newDue), assignDate(newAssign), description(newDisc), status(newStatus) {}
	
	// Copy Constructor
	Assignment(const Assignment& a) : dueDate(a.dueDate), assignDate(a.assignDate), description(a.description), status(a.status) {}

	// Destructor
	~Assignment() { ; }

	// Setters
	void setDueDate(Date newDate) { dueDate = newDate; }
	void setAssignDate(Date newDate) { assignDate = newDate; }
	void setDescription(string newDescription) { description = newDescription; }
	void setStatus(assignStatus newStatus) { status = newStatus; }

	// Getters
	Date getDueDate() const { return dueDate;  }
	Date getAssignDate() const { return assignDate; }
	string getDescription() const { return description; }
	assignStatus getStatus() const { return status; }

	// Overloaded operators
	bool operator==(const Assignment rhs) const { return getAssignDate() == rhs.getAssignDate(); }
};

#endif