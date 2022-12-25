/***************************************************************/
/* Programmer: Marcos Ortega                                   */
/* Date: December 19, 2022                                     */
/* Purpose: The definition file of the LargeInt class.         */
/* Input: N/A										           */
/* Output: N/A		                                           */
/***************************************************************/

#include "LargeInt.h"

// ******************** Fill the list functions************************** //

LargeInt::LargeInt(int num)
{
    // Call function to fill LargeInt's list
    negFlag = false;
    fillTheList(num);
}

void LargeInt::fillTheList(int num)
{
    // Case 0: Just a single digit 0;
    if (num == 0)
    {
        numberAsList.insertFront(num);
        negFlag = false;
        return; // END FUNCTION HERE.
    }
    // Case 1: Negative num. Store absolute value, set negFlag
    else if (num < 0)
    {
        negFlag = true;
        num = num * -1;
    }
    // Case 2: Is a positive number.
    else
        negFlag = false;

    // Use modulo to store integer backwards: 100 as 001.
    while (num)
    {
        numberAsList.insertBack(num % 10);
        num = num / 10;
    }
}

void LargeInt::fillTheList(const string &num)
{
    // Make sure list is empty before use.
    if (!(numberAsList.isEmptyList()))
        numberAsList.destroy();

    long size = num.length(); // Hold string length
    int i = 0;                // To iterate

    // Fill linked list with string integer, digit by digit.
    if (0 < size)
    {
        // Check if negative and increment i
        if (num[0] == '-')
        {
            this->negFlag = true;
            i = 1;
        }

        while (i < size)
        {
            assert(isdigit(num[i]));

            numberAsList.insertBack(num[i]);
            i++;
        }
    }
}

// Fill list using a string
void LargeInt::operator=(const string &num)
{
    fillTheList(num);
}

// Fill list using a integer
void LargeInt::operator=(const int &num)
{
    fillTheList(num);
}

/**************** Overloaded operators ***********************************/
const LargeInt &LargeInt::operator=(const LargeInt &otherLarge)
{
    this->negFlag = otherLarge.negFlag;
    this->numberAsList = otherLarge.numberAsList;
    return *this;
}

bool LargeInt::operator==(LargeInt &otherLarge)
{
    return this->equalNums(otherLarge);
}

bool LargeInt::operator>(LargeInt &otherLarge)
{
    // In the case that both numbers are equal absolute values
    if (this->equalNums(otherLarge))
    {
        // Case 1: Equal nums and equal flags
        // (10 > 10), (-10 > -10), (0 > 0)
        if (this->negFlag == otherLarge.negFlag)
            return false;
        // Case 2: Equal nums and !equal flags
        // 1.(-10 > 10), 2.(10 > -10)
        else
        {
            if (this->negFlag) // 1. Neg !> Pos
                return false;
            else // 2  Pos > Neg
                return true;
        }
    }
    // Now we consider cases where they are NOT equal absolute values.
    // Let's check for larger absolute values. Then compare flags.

    // Case 3: *this is larger absolute value. Check flags.
    else if (this->isLarger(otherLarge))
    {
        // Compare flags; both positive or both negative.
        if (this->negFlag == otherLarge.negFlag)
        {
            // Case 3a. Larger absolute value and positive.
            if (!(this->negFlag)) // i.e. 10 > 0, 10 > 1
                return true;
            // Case 3b. Larger absolute value and negative.
            else // i.e. -10 > -1
                return false;
        }
        // Different signs.
        else
        {
            if (this->negFlag) // i.e. -10 > 0, -1 > 1
                return false;
            else // i.e. +10 > 0, +3 > +2
                return true;
        }
    }
    // Case 4. *this is NOT larger absolute value.
    else
    {
        // Case 4a. Right side is larger abs value and negative.
        if (otherLarge.negFlag) // i.e. (-2 > -3, +2 > -5)
            return true;
        // Case 4b. Right side is larger abs value and positive.
        else // i.e. (-2 > +3, +2 > +6)
            return false;
    }
}

bool LargeInt::operator<(LargeInt &otherLarge)
{
    // Call isLarger function. Will return negation of < function,
    // i.e. (10 < 1) == !(10 > 1),  (-10 < 1) == !(-10 > 1)
    // We only need to consider the case where two values are equal and same sign.

    bool temp = this->isLarger(otherLarge);

    // If both LargeInts are equal and equal sign, we don't need to check
    // stored temp value and just return false.
    if (this->numberAsList.isIterNull() && this->negFlag == otherLarge.negFlag)
        return false;
    // For cases where values differ with +,- sign or equal values with differ
    // signs. For example, (-10 < 10) == !(-10 > 10), (10 < -1) == !(10 > -1)
    // Thus, < and > are negations of each in this sense.
    else
        return !temp;
}

bool LargeInt::operator>=(LargeInt &otherLarge)
{
    // Similar to > sign but just need to check for equal abs value and signs

    bool temp = this->isLarger(otherLarge);

    // If both LargeInts are equal and equal sign, we don't need to check
    // stored temp value and just return false.
    if (this->numberAsList.isIterNull() && this->negFlag == otherLarge.negFlag)
        return true;
    // For cases where values differ with +,- sign or equal values with differ
    // signs. For example, (-10 < 10) == !(-10 > 10), (10 < -1) == !(10 > -1)
    // Thus, < and > are negations of each in this sense.
    else
        return temp;
}

bool LargeInt::operator<=(LargeInt &otherLarge)
{
    // Similar to < sign but just need to check for equal abs value and signs

    bool temp = this->isLarger(otherLarge);

    // If both LargeInts are equal and equal sign, we don't need to check
    // stored temp value and just return true.
    if (this->numberAsList.isIterNull() && this->negFlag == otherLarge.negFlag)
        return true;
    // For cases where values differ with +,- sign or equal values with differ
    // signs. For example, (-10 < 10) == !(-10 > 10), (10 < -1) == !(10 > -1)
    // Thus, < and > are negations of each in this sense.
    else
        return !temp;
}

LargeInt LargeInt::operator+(LargeInt &otherLarge)
{
    LargeInt temp;

    // Case 1: Check if both numbers are negative. Sum is negative.
    if (this->negFlag == true && otherLarge.negFlag == true)
    {
        temp.numberAsList = add((*this), otherLarge);
        temp.negFlag = true;
    }
    // Case 2: Check if both numbers are positive. Sum is positive.
    else if (this->negFlag == false && otherLarge.negFlag == false)
    {
        temp.numberAsList = add((*this), otherLarge);
        temp.negFlag = false;
    }
    // Case 3: Numbers are different signs but equal absolute values,
    // i.e. |10| == |-10|
    else if (equalNums(otherLarge))
    {
        temp.negFlag = false;
        temp.numberAsList.insertBack(0);
        // sub((*this), otherLarge) may replace to keep logic/order
    }
    // Case 4: Numbers are different signs and values.
    else
    {
        // Case 4+: Depending on larger LargeInt, subtract larger abs value
        // from smaller abs value and then assign negFlag as needed.
        // For example: (-10 + 9) can be rewritten as -(10 - 9)

        if (this->isLarger(otherLarge))
        {
            temp.numberAsList = sub((*this), otherLarge);

            // REVISE: MIGHT BE REDUNDENT since in both code blocks
            if (this->negFlag)
                temp.negFlag = true;
            else
                temp.negFlag = false;
        }
        else
        {
            // REPEATED.
            temp.numberAsList = sub(otherLarge, (*this));

            if (otherLarge.negFlag)
                temp.negFlag = true;
            else
                temp.negFlag = false;
        }
    }

    return temp;
}

// NEEDS REVISION
LargeInt LargeInt::operator-(LargeInt &otherLarge)
{
    LargeInt temp;

    // 16 Dec 2022: Consider easiest cases first. First, check for equal valued
    // LargeInts. Then check other cases

    // Case 0: Check for equal values firstly.
    if (this->equalNums(otherLarge))
    {
        // Check for equivalent signs, return if true.
        if (this->negFlag == otherLarge.negFlag)
        {
            temp.negFlag = false;
            temp.numberAsList.insertBack(0);
        }
        else
        {
            temp.numberAsList = add((*this), otherLarge);
            temp.negFlag = this->negFlag;
        }
    }
    // !!! From this point, LargeInt values are not equal and can differ in signs.
    // Lets check for equal signs first
    else if (this->negFlag == otherLarge.negFlag)
    {
        // Both LargeInts are positive.
        if (this->negFlag == false)
        {
            // Consider 10 - 9 = 1
            if (this->isLarger(otherLarge))
            {
                temp.numberAsList = sub((*this), otherLarge);
                temp.negFlag = false;
            }
            // Consider 9 - 10 = -1
            else
            {
                temp.numberAsList = sub(otherLarge, (*this));
                temp.negFlag = true;
            }
        }
        // Both LargeInts are negative.
        else
        {
            if (this->isLarger(otherLarge))
            {
                temp.numberAsList = sub((*this), otherLarge);
                temp.negFlag = false;
            }
            // Consider 9 - 10 = -1
            else
            {
                temp.numberAsList = sub(otherLarge, (*this));
                temp.negFlag = true;
            }
        }
    }
    // Values have opposite signs and values at this point.
    else
    {
        // Notice a pattern. The left operand denotes the computed negFlag.
        // -10 -  11 = -21
        //  10 - -11 =  21
        // -11 -  10 = -21
        //  11 - -10 =  21

        temp.numberAsList = add((*this), otherLarge);
        temp.negFlag = this->negFlag;
    }

    return temp;
}
/*
template <class T>
LargeInt<T> LargeInt<T>::operator*(LargeInt<T> &otherLarge)
{
    // Multiplication is associative; i.e. 10 * 20 == 20 * 10;
    // For simplicity we will use terms: product = multiplicand * multiplier.
    // We will check which list is larger and assign it as multiplicand.
    // Multiplication is just multiple additions, thus we will treat it as such.
    // Use the multipliers most significant digit; consider base10 as (10^n * digit).
    //  103         1    0    3            103 * 10 * 2 = 2060
    //   22   (10^1 * 2) + (10^0 * 2)      103 *  1 * 2    206
    //  ---   ------------------------    -----------------------
    //                                                     2266
    // Using powers of 10, we can append zeros and use a for-loop

    LargeInt<T> temp;

    // Check for equal signs. -x * -y == x * y == xy. Else, -xy.
    bool equalSigns = (this->negFlag == otherLarge.negFlag);

    // Check if an operand is zero.
    if ((this->numberAsList.length() == 1) || (otherLarge.numberAsList.length() == 1))
    {
        if ((this->numberAsList.front() == 0) ||
            (otherLarge.numberAsList.front() == 0))
        {
            temp.numberAsList.insertBack(0);
            temp.negFlag = false;
            // any int x, x * 0 = 0.
        }
    }
    // Check for non-zero multiplicaiton
    else
    {
        // Choose larger absolute value, if it exists, as multiplicand.
        if (this->numberAsList.length() > otherLarge.numberAsList.length())
            temp.numberAsList = mult((*this), otherLarge);
        else
            temp.numberAsList = mult(otherLarge, (*this));
    }

    return temp;
}
*/

/**********************END Overloaded operators*******************************/

/********************** Operator functions ***********************/
doublyLinkedList<int> LargeInt::add(LargeInt &thisLarge, LargeInt &otherLarge)
{
    /* ISSUE: (6 Dec 2022) Need to revise to avoid verbosity.                   */
    /* Not sure; will just have to call functions to iterate and return info;   */
    /* consider using const to avoid changing of either LargeInt. */
    doublyLinkedList<int> temp;
    bool carry = false;

    // Set both iterator-of-list to first node for each LargeInt's list
    thisLarge.numberAsList.setIterFront();
    otherLarge.numberAsList.setIterFront();

    // Iterate until largest number exhausted. One LargeInt could have more
    // digits than other LargeInt.
    while (!(otherLarge.numberAsList.isIterNull()) ||
           !(thisLarge.numberAsList.isIterNull()))
    {
        int total = 0; // Will hold sum for pair of digits

        if (carry) // Check for carry-over int
            total += 1;

        // We have two operands to add.
        if (!(otherLarge.numberAsList.isIterNull()) &&
            !(thisLarge.numberAsList.isIterNull()))
        {
            total += (thisLarge.numberAsList.iterInfo() + otherLarge.numberAsList.iterInfo());
            thisLarge.numberAsList.iterateForw();
            otherLarge.numberAsList.iterateForw();
        }
        // We have one operand to add.
        else if (!(thisLarge.numberAsList.isIterNull()))
        {
            total += thisLarge.numberAsList.iterInfo();
            thisLarge.numberAsList.iterateForw();
        }
        else
        {
            total += otherLarge.numberAsList.iterInfo();
            otherLarge.numberAsList.iterateForw(); // was iterateBack(). Mistake?
        }

        // Check for double-digit total. Use modulo.
        if (total > 9)
        {
            carry = true;
            temp.insertBack(total % 10);
        }
        else
        {
            carry = false;
            temp.insertBack(total);
        }
    }

    // Check for a last carry-over.
    if (carry)
        temp.insertBack(1);

    return temp;
}

doublyLinkedList<int> LargeInt::sub(LargeInt &minuLarge, LargeInt &subtraLarge)
{
    /******************************************************************************/
    // About subtraction, because order matters: Difference = Minuend - Subtrahend;
    // So this function reads as: minuLarge - subtraLarge. This functions assumes
    // parameters will be: (larger abs value, smaller abs value). Note that it is
    // assumed the minued will have greater-then or equal number of digits to
    // subtrahend. NOTE: parameters are absolute values.
    /*****************************************************************************/

    doublyLinkedList temp; // List containing computed diffenence
    bool borrow = false;   // To store if number was borrowed.
    int difference;        // To store the difference

    // Set both iterator-of-list to first node for each LargeInt object's list
    minuLarge.numberAsList.setIterFront();
    subtraLarge.numberAsList.setIterFront();

    // Iterate through until minuend LargeInt is exhausted.
    while (!(minuLarge.numberAsList.isIterNull()))
    {
        difference = 0; // Reset value.

        difference += minuLarge.numberAsList.iterInfo(); // Store minuend digit

        // Case 0: A number was borrowed from successive digit; a power of 10.
        if (borrow)          // Subtract 1 if borrowed from. For example,
        {                    //  1 0 0    1 (0-1)(10+0)  (1-1)(-1+10) 10
            difference -= 1; // -  9 9      -    9   9            9    9
            borrow = false;  //  ------     ----------     --------------
        }                    //                      1      0     0    1

        // Case 1: Subtract if we have two operands.
        if (/*!(minuLarge.numberAsList.isIterNull()) &&*/ !(subtraLarge.numberAsList.isIterNull()))
        {
            // Case 1.1: Minuend digit is smaller than subtrahend digit, i.e. 0 < 9)
            if (minuLarge.numberAsList.iterInfo() < subtraLarge.numberAsList.iterInfo())
            {
                borrow = true;                                     // borrowed from successive digit
                difference += 10;                                  // add 10 to difference
                difference -= subtraLarge.numberAsList.iterInfo(); // subtract
                temp.insertBack(difference);
            }
            // Case 1.2: Minuend digit is larger than or equal to subtrahend digit.
            else
            {
                difference -= subtraLarge.numberAsList.iterInfo();
                temp.insertBack(difference);
                borrow = false;
            }

            subtraLarge.numberAsList.iterateForw();
        }
        else
        {
            // Case 2: Minuend LargeInt has more digits than subtrahend LargeInt,
            difference += minuLarge.numberAsList.iterInfo();
            minuLarge.numberAsList.insertBack(difference);
            minuLarge.numberAsList.iterateForw();
        }

        minuLarge.numberAsList.iterateForw();

    } // END while

    return temp;
}
/*
template <class T>
doublyLinkedList<T> LargeInt<T>::mult(LargeInt<T> &multiplicand, LargeInt<T> &multiplier)
{
    doublyLinkedList<T> runningTotal
        /******************************************************************************/
// About mult: this function assumes multiplicand will have more or equal num
// of digits. Useful to use with powers of ten.
/*****************************************************************************/

/*
// One to add, one to be added to.
doublyLinkedList<T> runningTotal = multiplicand.numberAsList;
doublyLinkedList<T> sum;

LargeInt<T> multParameter;
LargeInt<T> xParameter;

int powerTen = multiplier.numberAsList.length() - 1;

for (int i = 0; i < powerTen; i++)
{
    runningTotal.insertFront(0);
}

multParameter.numberAsList = runningTotal;

multiplier.numberAsList.setIterBack(); // Set to leading digit of multipliers

while (!multiplier.numberAsList.isIterNull())
{

    T digit = multiplier.numberAsList.iterInfo();

    for (int i = 0; i < digit; i++)
    {
        sum = this->add(multParameter, xParameter);

    }

    multiplier.numberAsList.iterateBack;
}
*/
/*
        return runningTotal;
}
*/
/*************************** END Operators Functions *************************/
ostream &operator<<(ostream &out, LargeInt &largeInt)
{
    largeInt.numberAsList.setIterBack(); // Set to back of list

    // Check for negFlag
    if (largeInt.negFlag)
    {
        out << '-';
    }

    while (!largeInt.numberAsList.isIterNull())
    {
        out << largeInt.numberAsList.iterInfo();
        largeInt.numberAsList.iterateBack();
    }
    return out;
}

istream &operator>>(istream &in, LargeInt &largeInt)
{
    // String to hold the integer
    string num;

    // Input stream object reads and stores in num.
    in >> num;

    largeInt = num;

    return in;
}

/****************************** HELPER FUNCTIONS ********************************/
/****************** functions used by overloaded operators *********************/
// Date: 12/16/22

bool LargeInt::equalNums(LargeInt &otherLarge)
{
    // Case 0: Are both LargeInts equal length?
    if (this->numberAsList.length() != otherLarge.numberAsList.length())
    {
        return false;
    }
    // If both LargeInts are equal list, we compare each digit of both lists
    else
    {
        this->numberAsList.setIterFront();
        otherLarge.numberAsList.setIterFront();
        bool areEqual = true; // Flag for equality. We start by assuming both
                              // LargeInts are equal.

        // Case 1: Check each digit/place of LargeInt for equality. Will iterate
        // while not-null or till digits differs.
        while (!(this->numberAsList.isIterNull()) && areEqual)
        {
            // Check for equality throughout the both lists
            if (this->numberAsList.iterInfo() != otherLarge.numberAsList.iterInfo())
            {
                areEqual = false;
            }

            this->numberAsList.iterateForw();
            otherLarge.numberAsList.iterateForw();
        }

        return areEqual;
    }
}

bool LargeInt::isLarger(LargeInt &otherLarge)
{
    /**********************************************************************/
    // This function compares the *absolute values* of two LargeInts.
    /*********************************************************************/
    bool iAmLarger; // Bool to return if this->list is larger

    // Case 1: list length is larger than other list
    if (this->numberAsList.length() > otherLarge.numberAsList.length())
        iAmLarger = true;
    // Case 2: other list is larger than this->list
    else if (this->numberAsList.length() < otherLarge.numberAsList.length())
        iAmLarger = false;
    // Case 3: Both LargeInts' length are equal so check most significant digit
    // and iterate until unequal digits or lists are exhausted
    else
    {
        // Set both LargeInts' iterators to back of list, its most signficant digit
        this->numberAsList.setIterBack();
        otherLarge.numberAsList.setIterBack();

        // Iterate and compare both lists till exhausted or equal comparison fails.
        while (!(this->numberAsList.isIterNull()))
        {
            if ((this->numberAsList.iterInfo() == otherLarge.numberAsList.iterInfo()))
            {
                this->numberAsList.iterateBack();
                otherLarge.numberAsList.iterateBack();
            }
            else
                break;
        }

        // Check if lists are exhausted, either LargeInt . Else check digits.
        if (this->numberAsList.isIterNull())
            iAmLarger = false;
        else if (this->numberAsList.iterInfo() > otherLarge.numberAsList.iterInfo())
            iAmLarger = true;
        else
            iAmLarger = false;
    }

    return iAmLarger;
}