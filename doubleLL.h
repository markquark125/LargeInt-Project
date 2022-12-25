/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: October 5, 2022                                       */
/* Purpose: Header file for the class of an unsorted 		   */
/*		doubly-linked list. Contains the declarations.	 	   */
/* Input: N/A										           */
/* Output: N/A		                                           */
/***************************************************************/

#ifndef DLL_H
#define DLL_H

#include "nodeType.h"
#include <assert.h>
#include <iostream>
using namespace std;

template <class T>
class doublyLinkedList
{
private:
	// Function to make a copy of otherList.
	// Postcondition: A copy of otherList is created and assigned to this list.
	void copyList(const doublyLinkedList<T> &otherList);

	// Was 'protected:' but didn't see the point to it since not going to be
	// inherited.
	int count;			  // keep count of num of nodes; length of list.
	nodeType<T> *first;	  // pointer to the first node
	nodeType<T> *last;	  // pointer to the last node.
	nodeType<T> *current; // iterator for search
public:
	void printList() const; // Function just to print list. To be used by LargeInt class
							// for testing .

	// public:
	//  Default constructor.
	//  Postcondition: first = NULL, last = NULL; count = 0;
	doublyLinkedList();

	// Copy constructor.
	doublyLinkedList(const doublyLinkedList<T> &otherList);

	// Destructor.
	// Postcondition: The list object is destroyed.
	~doublyLinkedList();

	void initializeList(); // Initialize the list to an empty state.

	bool isEmptyList() const;  // Determines whether list is empty.
	int length();			   // Return number of nodes in list
	T front() const;		   // Return first element in the not-empty list.
	T back() const;			   // Return last element in the not-empty list.
	bool search(T searchItem); // Determine if searchItem in list.

	void iterateForw();	 // Move iterator forward
	void iterateBack();	 // Move iterator backward
	void setIterFront(); // Set iterator to first node
	void setIterBack();	 // Set iterator to back node
	bool isIterNull();	 // Checks if iterator is NULL
	T iterInfo() const;	 // Return current node info

	void insertFront(const T &insertItem); // Insert at beginnig of the list
	void insertBack(const T &insertItem);  // Insert at end of the list
	void deleteNode(const T &deleteItem);  // Delete from list
	void destroy();						   // Delete whole list

	// Overload assignment operator
	const doublyLinkedList<T> &operator=(const doublyLinkedList<T> &);
};

#endif