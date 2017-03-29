/*
 * File: bignumberlibrary.h
 * -------------------------
 * This interface exports the big number class.
 */

#ifndef BIGNUMBERLIBRARY_H
#define BIGNUMBERLIBRARY_H

#include <iostream>

using namespace std;

/*
 * Class: BigNumber
 * -----------------------------------------------------
 * This class is an implementation for bignum arithmetic.
 */
class BigNumber {
    public:
        /*
         * Constructor: BigNumber
         * Usage: BigNumber n;
         * ------------------------------
         * Initializes an empty BigNumber.
         */
        BigNumber();
        /*
         * Constructor: BigNumber
         * Usage: BigNumber n(1234);
         * ----------------------------------------------------
         * Initalizes BigNumber with the provided integer value.
         */
        BigNumber(int n);
        /*
         * Destructor: ~BigNumber
         * Usage: (usually implicit)
         * -------------------------
         * Frees any heap storage.
         */
        ~BigNumber();
        /*
         * Method: add
         * Usage: n.add(n2);
         * --------------------------
         * reciever + bigNumberPassed
         */
        BigNumber& add(const BigNumber& n);
        /*
         * Method: subtract
         * Usage: n.subtracts(n2);
         * ---------------------------
         * reciever - bigNumberPassed
         */
        BigNumber& subtract(const BigNumber & n);
        /*
         * Method: multiply
         * Usage: n.multiply(n2);
         * ---------------------------
         * reciever * bigNumberPassed
         */
        BigNumber& multiply(const BigNumber & n);
        /*
         * Method: divide
         * Usage: n.divide(n2);
         * ---------------------------
         * reciever / bigNumberPassed
         */
        BigNumber& divide(const BigNumber & n);
        /*
         * Method: size
         * Usage: n.size();
         * -----------------------------
         * Returns the number of digits.
         */
        int size() const;
        /*
         * Method: raiseToPower
         * Usage: n.raiseToPower(64);
         * -------------------------------------------------------------------------------
         * Returns n raised to the power of p.
         * showProgress is an optional boolean that shows the progress of the calculation.
         */
        BigNumber& raiseToPower(int p, bool showProgress=false);
        /*
         * Method: fact
         * Usage: n.fact(100);
         * -------------------------------------------------------------------------------
         * Returns n!
         * showProgress is an optional boolean that shows the progress of the calculation.
         */
        BigNumber& fact(int n, bool showProgress=false);
        /*
         * Copy constructor and assignment operator
         * ----------------------------------------
         * These methods implement deep copying.
         */
        BigNumber(const BigNumber & n);
        BigNumber & operator=(const BigNumber & n);
        /*
         * Arithmetic Operators
         * ------------------------------------------------------------------------------
         * ( +, += ) : uses add method.
         * ( -, -=) : uses subtract method.
         * ( - ) : if no argument is supplied, it simply returns the value * -1.
         * ( *=, *) : uses multiply method.
         * ( /, /=) : uses divide method.
         */
        BigNumber& operator+=(const BigNumber & n);
        BigNumber& operator+(const BigNumber & n);
        BigNumber& operator-=(const BigNumber & n);
        BigNumber& operator-(const BigNumber & n);
        BigNumber & operator-();
        BigNumber& operator*=(const BigNumber & n);
        BigNumber& operator*(const BigNumber & n);
        BigNumber& operator/=(const BigNumber & n);
        BigNumber& operator/(const BigNumber & n);
        /*
         * Comparison Operators
         * ------------------------------
         * < : Less Than
         * <= : Less Than or Equal to
         * >= : Greater Than or Equal to
         * > : Greater Than
         * == : Equal to
         */
        bool operator<(const BigNumber & n);
        bool operator<=(const BigNumber & n);
        bool operator>=(const BigNumber & n);
        bool operator>(const BigNumber & n);
        bool operator==(const BigNumber & n);

    /* Private Section */

    /*
     * Implementation Notes
     * ---------------------
     * This implementation of bignum arithmetic stores individual digits
     * in a dynamic array. If space in the array runs out, the implementation
     * doubles the capacity of the array.
     */
    private:
        static const int INITIAL_CAPACITY = 10;
        /* Instance Variables */
        short *number;
        int count;
        int capacity;
        bool neg;
        /* Private Method Prototypes */
        void init(int n);
        void convertInteger(int n);
        void push_back(int n);
        void push_front(int n);
        string toString() const;
        void resize(int d, string dir);
        BigNumber karatsuba(BigNumber n1, BigNumber n2);
        BigNumber longMultiplication(BigNumber& n1, BigNumber& n2);
        BigNumber copyRange(int start, int end);
        void printProgress(int i, int t);
        void expandCapacity();
        void deepCopy(const BigNumber & n);
        void normalize();
        friend ostream& operator <<(ostream & os, const BigNumber & n);

};

ostream& operator <<(ostream & os, const BigNumber & n);

#endif // BIGNUMBERLIBRARY_H
