#ifndef BIGNUMBERLIBRARY_H
#define BIGNUMBERLIBRARY_H

#include <iostream>

using namespace std;

class BigNumber {
    public:
        BigNumber();
        BigNumber(int n);
        ~BigNumber();
        BigNumber& add(const BigNumber& n);
        BigNumber& subtract(const BigNumber & n);
        BigNumber& multiply(const BigNumber & n);
        BigNumber& divide(const BigNumber & n);
        void push_back(int n);
        void push_front(int n);
        int size() const;
        BigNumber(const BigNumber & n);
        BigNumber & operator=(const BigNumber & n);
        BigNumber& operator+=(const BigNumber & n);
        BigNumber& operator+(const BigNumber & n);
        BigNumber& operator-=(const BigNumber & n);
        BigNumber& operator-(const BigNumber & n);
        BigNumber & operator-();
        BigNumber& operator*=(const BigNumber & n);
        BigNumber& operator*(const BigNumber & n);
        BigNumber& operator/=(const BigNumber & n);
        BigNumber& operator/(const BigNumber & n);
        BigNumber& pow(int n, bool showProgress=false);
        BigNumber& fact(int n, bool showProgress=false);
        bool operator<(const BigNumber & n);
        bool operator<=(const BigNumber & n);
        bool operator>=(const BigNumber & n);
        bool operator>(const BigNumber & n);
        bool operator==(const BigNumber & n);
    private:
        static const int INITIAL_CAPACITY = 10;
        struct Digit {
            signed val:14;
        };
        Digit *number;
        int count;
        int capacity;
        bool neg;
        void init(int n);
        void convertInteger(int n);
        string toString() const;
        void resize(int d);
        void multiplyByDigit(int digit);
        void printProgress(int i, int t);
        void expandCapacity();
        void deepCopy(const BigNumber & n);
        void normalize();
        friend ostream& operator <<(ostream & os, const BigNumber & n);

};

ostream& operator <<(ostream & os, const BigNumber & n);

#endif // BIGNUMBERLIBRARY_H
