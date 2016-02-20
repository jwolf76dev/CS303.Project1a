#include "Assignment.h"

Assignment::Assignment()
{	
}

Assignment::~Assignment()
{
}

void Assignment::setDueDate(Date newDate)
{
	dueDate = newDate;
}

void Assignment::setAssignDate(Date newDate)
{
	assignDate = newDate;
}

void Assignment::setDescription(string newDescription)
{
	description = newDescription;
}

void Assignment::setStatus(assignStatus newStatus)
{
	status = newStatus;
}

Date Assignment::getDueDate()
{
	return dueDate;
}

Date Assignment::getAssignDate()
{
	return assignDate;
}

string Assignment::getDescription()
{
	return description;
}

assignStatus Assignment::getStatus()
{
	return status;
}
