/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: October 5, 2022                                       */
/* Purpose: The definition file of the class of a unsorted     */
/* 		doubly-linked list. Contains defintions and iterator  */
/*		functions, using current pointer.					  */
/* Input: N/A    										      */
/* Out: N/A		                                               */
/***************************************************************/

#include "doubleLL.h"

// *********** OVERLOADED OPERATOR ************************
template <class T>
const doublyLinkedList<T> &doublyLinkedList<T>::operator=(const doublyLinkedList<T> &otherList)
{
	if (this != &otherList) // avoid self-copy
	{
		copyList(otherList);
	}

	return *this;
} // *********** END OF OVERLOADED OPERATOR ****************

// ********* COPYLIST *************************
template <class T>
void doublyLinkedList<T>::copyList(const doublyLinkedList<T> &otherList)
{
	// Corresponding to each node in the otherList, we...
	// 1. Create a node and call it newNode
	// 2. Copy info from otherList node into newNode.
	// 3. Insert newNode at the end of the list being created.

	nodeType<T> *newNode; // pointer to create node.
	nodeType<T> *current; // pointer to travel the list

	if (first != NULL) // if this list is nonempty, make it empty.
		destroy();

	if (otherList.first == NULL) // if otherList is empty
	{
		first = NULL;
		last = NULL;
		this->current = NULL;
		count = 0;
	}
	else
	{
		current = otherList.first; // current points to the list to be copied.
		count = otherList.count;

		// Copy the first node.
		first = new nodeType<T>;	 // Create first node
		first->info = current->info; // Copy the info
		first->back = NULL;			 // Set node's next to NULL
		first->next = NULL;			 // Set node's back to NULL

		// Set both first and last to only node so far
		last = first;			 // Make last point to first node.
		current = current->next; // Make current point to next node.

		// Copy remaining list
		while (current != NULL)
		{
			newNode = new nodeType<T>;	   // Create a node
			newNode->info = current->info; // Copy the info
			newNode->next = NULL;		   // set the next of newNode to NULL
			last->next = newNode;		   // attach newNode after last
			newNode->back = last;		   // attach last node (trailing here) to newNode
			last = newNode;				   // Make last point to actual last node (so far)
			current = current->next;	   // Move current ptr to next node.
		}								   // end while
	}									   // end else
} // ******* END OF COPYLIST **********************

// *************************** CONSTRUCTORS & DESTRUCTOR *********************************
// **********CONSTRUCTOR *************************
template <class T>
doublyLinkedList<T>::doublyLinkedList()
{
	first = NULL;
	last = NULL;
	current = NULL;
	count = 0;
}

// ******** COPY CONSTRUCTOR ********************
template <class T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T> &otherList)
{
	copyList(otherList);

	current = NULL;
}

// ******* DESTRUCTOR ************************
template <class T>
doublyLinkedList<T>::~doublyLinkedList()
{
	destroy();
}

// *********************** END OF CONSTRUCTORS & DESTRUCTOR *****************************

// ************ INITIALIZELIST **********************
template <class T>
void doublyLinkedList<T>::initializeList()
{
	destroy(); // destroy the list. Reset list.
}

// ************************** GETTTERS **********************************************

// ******* ISEMPTYLIST ************************
template <class T>
bool doublyLinkedList<T>::isEmptyList() const
{
	return (first == NULL); // Return true if empty, else false
}

// ******** LENGTH *************************
template <class T>
int doublyLinkedList<T>::length()
{
	return count; // Return length of list
}

// ****************** FUNCTIONS TO RETURN FIRST AND LAST NODES*******************
// ASSERT ENDS PROGRAM IF CONDITION IS FALSE,

template <class T>
T doublyLinkedList<T>::front() const
{
	assert(first != NULL);

	return first->info;
}

template <class T>
T doublyLinkedList<T>::back() const
{
	assert(last != NULL);

	return last->info;
}

// ************ END OF FUNCTIONS TO RETURN FIRST AND LAST NODES*******************

// ******* SEARCH ********************************
template <class T>
bool doublyLinkedList<T>::search(T searchItem)
{
	bool found = false; // Set found as false
	current = first;	// Assign *current to start at beginning of list

	while (current != NULL && !found)
	{
		if (current->info == searchItem)
			found = true; // Break if found or end of list

		current = current->next;
	}

	return found;
} // **** END OF SEARCH **************************

// ********************** END OF GETTERS *****************************************

// ********************** ITERATORS ********************************

template <class T>
void doublyLinkedList<T>::iterateForw()
{
	current = current->next; // move iterator one node forward
}

template <class T>
void doublyLinkedList<T>::iterateBack()
{
	current = current->back; // move iterator one node back
}

template <class T>
void doublyLinkedList<T>::setIterFront()
{
	current = first; // Set iterator to first node list
}

template <class T>
void doublyLinkedList<T>::setIterBack()
{
	current = last; // Set iterator to last node in list
}

template <class T>
bool doublyLinkedList<T>::isIterNull()
{
	return current == NULL; // Checks if current is NULL
}

template <class T>
T doublyLinkedList<T>::iterInfo() const
{
	return current->info; // Returns current node info
}
// ********************** END OF ITERATORS *************************************

// ************************** SETTERS **************************************

// ********INSERTFRONT ***********************
template <class T>
void doublyLinkedList<T>::insertFront(const T &insertItem)
{
	nodeType<T> *newNode = new nodeType<T>; // Create new node
	newNode->info = insertItem;				// Store insertItem in the new node.
	newNode->back = NULL;
	newNode->next = NULL; // NULL <- [back| info | next] -> NULL

	if (first == NULL) // If list is empty, newNode is the only node
	{
		first = newNode;
		last = newNode;
	}
	else // ****List is NOT empty ****
	{
		newNode->next = first;
		first->back = newNode;
		first = newNode;
	}

	count++;

} // ********* END OF INSERTFRONT************************

// ********INSERTBACK ***********************
template <class T>
void doublyLinkedList<T>::insertBack(const T &insertItem)
{
	nodeType<T> *newNode = new nodeType<T>; // Create new node
	newNode->info = insertItem;				// Store insertItem in the new node.
	newNode->back = NULL;
	newNode->next = NULL; // NULL <- [back| info | next] -> NULL

	if (first == NULL) // If list is empty, newNode is the only node
	{
		first = newNode;
		last = newNode;
	}
	else // ****List is NOT empty ****
	{
		newNode->back = last;
		last->next = newNode;
		last = newNode;
	}

	count++;
} // ********* END OF INSERTBACK************************

// ********** DELETE *****************************
template <class T>
void doublyLinkedList<T>::deleteNode(const T &deleteItem)
{
	nodeType<T> *current;	   // Pointer to traverse the list
	nodeType<T> *trailCurrent; // Pointer just before current

	if (first == NULL) // CASE 1: List is empty
		cout << "Cannot delete from an empty list." << endl;

	else if (first->info == deleteItem) // CASE 2: Node to be deleted is the first node
	{
		current = first;
		first = first->next;

		if (first != NULL)		// If there is more than one node in list, next node's
			first->back = NULL; // back is assigned NULL.
		else					// There was only one node in the list.
			last = NULL;

		count--;

		delete current; // Deallocate former-first node
	}
	else // Now considering the other two cases: somewhere in the list or not in it.
	{
		bool found = false; // Flag if deleteItem found
		current = first;

		while (current != NULL && !found)	 // Search the list.
			if (current->info == deleteItem) // Check if deleteItem is found
				found = true;				 // Flag up!
			else
				current = current->next; // else keep checking.

		// We reached the end of list and deleteItem not found
		if (current == NULL)
			cout << "The item is to be deleted is not in the list." << endl;

		else if (current->info == deleteItem) //  deleteItem found and check for equality.
		{
			trailCurrent = current->back;
			trailCurrent->next = current->next;

			if (current->next != NULL)
				current->next->back = trailCurrent;

			if (current == last)
				last = trailCurrent;

			count--;
			delete current;
		}
	} // End outer else
} // ******** END OF DELETE ***************************

// ********* DESTROY ***************************
template <class T>
void doublyLinkedList<T>::destroy()
{
	nodeType<T> *temp; // pointer to delete node

	while (first != NULL)
	{
		temp = first;		 //    first--> [node1] --> [node2]
							 //  temp--^
		first = first->next; //  temp	--> [node1] 	[node2]
							 //           			first--^
		delete temp;		 // 	X		  first --> [node2], then while()....
	}

	// *first should be null, thus we need to reset the rest.
	first = NULL; // just in case
	last = NULL;
	current = NULL;
	count = 0;
}

// ***************************** END OF SETTERS *******************************

/********************** Print function. Protected. **************************/
template <class T>
void doublyLinkedList<T>::printList() const
{
	nodeType<T> *p = last;
	while (p != NULL)
	{
		cout << p->info;
		p = p->back;
	}
}