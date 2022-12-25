/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: October 5, 2022                                       */
/* Purpose: A node template structure with two links.		   */
/* Input: N/a												   */
/* Output:	N/a												   */
/***************************************************************/

#ifndef NODETYPE_H
#define NODETYPE_H

template <class T>
struct nodeType
{
	T info;			   // Hold info/data
	nodeType<T> *next; // Link to next node
	nodeType<T> *back; // Link to back node
};

#endif