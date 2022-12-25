/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: December 19 2022                                      */
/* Purpose: A LargeInt class that will store large integers    */
/* in a doubly linked list, each node containg a single digit. */
/* Overload operators to perform basic arithmetic using LargeInt*/
/* objects. 													*/
/* Input: n/a (Hardcoded)							           */
/* Output: Prints LargeInts computation               		    */
/***************************************************************/

#include "LargeInt.cpp"

int main()
{
	LargeInt<int> LargeValue; // hold sum, difference of two LargeInts

	// TEST: ADDING TWO POSITVE NUMBERS
	LargeInt<int> LargeInt1(999);
	LargeInt<int> LargeInt2(1);

	LargeInt1.printLargeInt();
	cout << " + ";
	LargeInt2.printLargeInt();
	cout << " = ";
	LargeValue = (LargeInt1 + LargeInt2);
	LargeValue.printLargeInt();

	cout << "\n\n";

	// BUG: last digit only shown. Subtraction bug.
	LargeInt1.printLargeInt();
	cout << " - ";
	LargeInt2.printLargeInt();
	cout << " = ";
	LargeValue = (LargeInt1 - LargeInt2);
	LargeValue.printLargeInt();

	cout << "\n\n";

	LargeInt1.printLargeInt();
	cout << " > ";
	LargeInt2.printLargeInt();
	cout << " = ";
	LargeValue = (LargeInt1 > LargeInt2);
	LargeValue.printLargeInt();

	cout << "\n\n";

	LargeInt1.printLargeInt();
	cout << " < ";
	LargeInt2.printLargeInt();
	cout << " = ";
	LargeValue = (LargeInt1 < LargeInt2);
	LargeValue.printLargeInt();

	cout << "\n\n";

	LargeInt1.printLargeInt();
	cout << " == ";
	LargeInt2.printLargeInt();
	cout << " is " << (LargeInt1 == LargeInt2);

	cout << "\n\n";

	LargeInt1.printLargeInt();
	cout << " <= ";
	LargeInt2.printLargeInt();
	cout << " is " << (LargeInt1 == LargeInt2);

	cout << "\n\nEND\n\n";
	return 0;
}
