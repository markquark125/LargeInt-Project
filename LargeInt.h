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

class LargeInt : protected doublyLinkedList<int>
{
private:
    doublyLinkedList numberAsList; // to store number as a doubly-linked list.
    bool negFlag;                  // Flag if number is negative

    void fillTheList(int num);           // Function to fill the list with int data type
    void fillTheList(const string &num); // Fill with string data type
    void operator=(const string &num);   // Overload = for strings
    void operator=(const int &num);      // Overload = for ints

    // Arithmetic functions for LargeInt objects. Called by overloaded operators.
    doublyLinkedList<int> add(LargeInt &thisLarge, LargeInt &otherLarge);
    doublyLinkedList<int> sub(LargeInt &thisLarge, LargeInt &otherLarge);
    // doublyLinkedList<int> mult(LargeInt<int> &thisLarge, LargeInt<int> &otherLarge);

protected:
    /*********************** Helper functions. **********************/
    // Function to check if the absolute values of two ints are equal
    bool equalNums(LargeInt &otherLarge);
    // Checks if absolute value of this LargeInt is larger
    bool isLarger(LargeInt &otherLarge);

public:
    LargeInt(int num = 0); // Constructor

    /********** Overloaded operators, will call other functions******/
    LargeInt operator+(LargeInt &);
    LargeInt operator-(LargeInt &);
    // LargeInt<int> operator*(LargeInt &); // IN PROGRESS.
    bool operator==(LargeInt &);
    bool operator>(LargeInt &);
    bool operator<(LargeInt &);
    bool operator>=(LargeInt &);
    bool operator<=(LargeInt &);
    const LargeInt &operator=(const LargeInt &);

    /***************** Function to print LargeInt list.  ****************/
    // Overload output operator to output data of this object.
    friend ostream &operator<<(ostream &out, LargeInt &largeInt);
    // Overload output operator to get input integer, store in LargeInt object
    friend istream &operator>>(istream &in, LargeInt &LargeInt);
};

#endif