
#include <>
using namespace std;


// Function trim() code from M. Kuhail
// email: kuhailm@umkc.edu

// Break the string into individual elements
string trim(const string& the_string) {
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");
	return the_string.substr(p, q - p + 1);
}
void Assignment_List::load_data() {

	// Load assignment lists from file
	void loadData(Ordered_List<Assignment>& assignedList, Ordered_List<Assignment>& completedList, Menu& menu) {

		// Variables from file input
		string line, dueDate, desc, assignDate, status;
		ifstream in("assignments.txt");

		// Stream exists
		if (in)
		{
			// Read a line from the file
			while (getline(in, line))
			{
				if (line == "")
					continue;

				// Function st() from M. Kuhail
				// Parse the elements in the line using a comma delimiter
				String_Tokenizer st(line, ",");
				dueDate = trim(st.next_token());
				desc = trim(st.next_token());
				assignDate = trim(st.next_token());
				status = trim(st.next_token());

				// Convert tokenized string to date and assignment status
				Date newDue(dueDate), newAssign(assignDate);
				assignStatus newStatus;

				// Set the enumerated status
				if (status == "assigned") {
					newStatus = assigned;
				}
				else if (status == "completed") {
					newStatus = completed;
				}
				else { newStatus = late; }

				// Add the item to the list
				menu.addToList(newDue, desc, newAssign, newStatus);
			}
		}
		// Close the input stream
		in.close();
	}
}
