#include "Assignment.h"

Assignment::Assignment() {	
}

Assignment::~Assignment() {
}

void Assignment::setDueDate(Date newDate) {
	dueDate = newDate;
}

void Assignment::setAssignDate(Date newDate) {
	assignDate = newDate;
}

void Assignment::setDescription(string newDescription) {
	description = newDescription;
}

void Assignment::setStatus(assignStatus newStatus) {
	status = newStatus;
}

Date Assignment::getDueDate() const {
	return dueDate;
}

Date Assignment::getAssignDate() const {
	return assignDate;
}

string Assignment::getDescription() const {
	return description;
}

assignStatus Assignment::getStatus() const {
	return status;
}

bool Assignment::operator==(const Assignment rhs) const {
	return getAssignDate() == rhs.getAssignDate(); 
}
