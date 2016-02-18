#include "assignment.h"

assignment::assignment()
{	
}

assignment::~assignment()
{
}

void assignment::setDueDate(Date newDate)
{
	dueDate = newDate;
}

void assignment::setAssignDate(Date newDate)
{
	assignDate = newDate;
}

void assignment::setDescription(string newDescription)
{
	description = newDescription;
}

void assignment::setStatus(assignStatus newStatus)
{
	status = newStatus;
}

Date assignment::getDueDate()
{
	return dueDate;
}

Date assignment::getAssignDate()
{
	return assignDate;
}

string assignment::getDescription()
{
	return description;
}

assignStatus assignment::getStatus()
{
	return status;
}
