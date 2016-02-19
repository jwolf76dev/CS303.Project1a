#ifndef ORDERED_LIST_H_
#define ORDERED_LIST_H_
#include "list.h"
#include "Assignment.h"

/* The ordered list maintains a list of objects ordered by their less-than operator*/
template<typename Assignment>
class Ordered_List {

private:
	/**A list to contain the ordered list*/
	list<Assignment> a_list;

public:
	//Typedef
	typedef typename list<Assignment>::iterator iter;

	//Functions
	/** inserts a new item into the ordered list, maintaining order.
	@param an_item The item to be inserted
	*/
	void insert(Assignment& an_item){
		typename list<Assignment>::iterator itr = a_list.begin();
		//Sorts in ascending order by assigned date
		while (itr != a_list.end() && ((*itr).getAssignDate() < an_item.getAssignDate()==1))
			++itr; //itr points to the first item >= an_item
			//or the end
		a_list.insert(itr, an_item);
		
	}

	/** Remove an item from the ordered list.
	@param item The value to be removed
	*/
	void remove(const Assignment& item){
		a_list.remove(item);
	}

	/** Return an iterator to the begining */
	iter begin() {
		return a_list.begin();
	}

	iter find(Date indate) {
		//TODO: Comment
		typename list<Assignment>::iterator itr = a_list.begin();

		for (itr = a_list.begin(); itr != a_list.end(); ++itr) {
			if ((*itr).getAssignDate() == indate) {
				return itr;
			}
		}

		return end();
	}

	/** Return an iterator to the end */
	iter end()  {
		return a_list.end();
	}

};

#endif