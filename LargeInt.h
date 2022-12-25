/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: December 19, 2022                                     */
/* Purpose: Header file for the LargeInt class. Large integers */
/*          are store as a doubly-linked list, with each node  */
/*          containing a single digit of the integer.          */
/* Input: N/A										           */
/* Output: N/A		                                           */
/***************************************************************/

#include "doubleLL.cpp"

#ifndef LARGEINT_H
#define LARGEINT_H

template <class T>
class LargeInt : protected doublyLinkedList<T>
{
private:
    doublyLinkedList<T> numberAsList; // to store number as a doubly-linked list.
    bool negFlag;                     // Flag if number is negative

    void fillTheList(T num); // Function to fill the list.

    // Function to add LargeInt objects. Called by other functions.
    doublyLinkedList<T> add(LargeInt<T> &thisLarge, LargeInt<T> &otherLarge);
    doublyLinkedList<T> sub(LargeInt<T> &thisLarge, LargeInt<T> &otherLarge);

    // doublyLinkedList<T> mult(LargeInt<T> &thisLarge, LargeInt<T> &otherLarge);

protected:
    /*********************** Helper functions. **********************/
    // Function to check if the absolute values of two ints are equal
    bool equalNums(LargeInt<T> &otherLarge);
    // Checks if absolute value of this LargeInt is larger
    bool isLarger(LargeInt<T> &otherLarge);

public:
    LargeInt(T num = 0); // Constructor

    /********** Overloaded operators, will call other functions******/
    LargeInt<T> operator+(LargeInt &);
    LargeInt<T> operator-(LargeInt &);
    // LargeInt<T> operator*(LargeInt &); // IN PROGRESS.
    bool operator==(LargeInt &);
    bool operator>(LargeInt &);
    bool operator<(LargeInt &);
    bool operator>=(LargeInt &);
    bool operator<=(LargeInt &);
    const LargeInt<T> &operator=(const LargeInt<T> &);

    // Function to print LargeInt list. For testing/debugging
    void printLargeInt() const; // Print function to check list.
};

#endif