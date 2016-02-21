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
	//Constructors
	Assignment();
	Assignment(Date newDue, string newDisc, Date newAssign, assignStatus newStatus) :dueDate(newDue), assignDate(newAssign), description(newDisc), status(newStatus) {}
	Assignment(const Assignment& a) :dueDate(a.dueDate), assignDate(a.assignDate), description(a.description), status(a.status) {} //Copy Constructor

	//Destructor
	~Assignment();

	//Setters
	void setDueDate(Date newDate);
	void setAssignDate(Date newDate);
	void setDescription(string newDescription);
	void setStatus(assignStatus newStatus);

	//Getters
	Date getDueDate() const;
	Date getAssignDate() const;
	string getDescription() const;
	assignStatus getStatus() const;

	//Other
	bool operator==(const Assignment rhs) const; 
};

#endif