#ifndef ORDERED_LIST_H_
#define ORDERED_LIST_H_
#include "list.h"

//Code written by Kuhail
/* The ordered list maintains a list of objects ordered by their less-than operator*/
template<typename Item_Type>
class Ordered_List {

private:
	/**A list to contain the ordered list*/
	list<Item_Type> a_list;

public:
	//Typedef
	typedef typename list<Item_Type>::iterator iter;

	//Functions

	/** searches for a date in a list
	@param indate - the date to find
	*/
	iter find(Date indate) {
		// Search through the list looking for the input date
		typename list<Item_Type>::iterator itr = a_list.begin();

		for (itr = a_list.begin(); itr != a_list.end(); ++itr) {

			// Compare the current assigned date to the input date
			if ((*itr).getAssignDate() == indate) {
				return itr; // If the date is found, return that iterator
			}
		}

		return end(); // Return the end of the list if not found
	}

	/** inserts a new item into the ordered list, maintaining order.
	@param an_item The item to be inserted
	*/
	void insert(Item_Type& an_item) {
		typename list<Item_Type>::iterator itr = a_list.begin();

		//Sorts in ascending order by assigned date
		while (itr != a_list.end() && ((*itr).getAssignDate() < an_item.getAssignDate() == 1))
			++itr; //itr points to the first item >= an_item
				   //or the end
		a_list.insert(itr, an_item);

	}

	/** Remove an item from the ordered list.
	@param item The value to be removed
	*/
	void remove(const Item_Type& item) {
		a_list.remove(item);
	}

	/** Return an iterator to the begining */
	iter begin() {
		return a_list.begin();
	}

	/** Return an iterator to the end */
	iter end() {
		return a_list.end();
	}

};

#endif