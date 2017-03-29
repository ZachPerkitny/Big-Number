/*
 * Implementation
 * -----------------------
 * Yay!
 */

#include <cmath>
#include "bignumberlibrary.h"

/*
 * Implementation Notes: BigNumber constructor
 * -------------------------------------------
 * The constructor makes a call to the private method 'init'.
 * This method allocates the array storage and initalizes the fields.
 */

BigNumber::BigNumber(){
    init(0);
}

BigNumber::BigNumber(int n){
    init(n);
}

/*
 * Implementation Notes: BigNumber destructor
 * -------------------------------------------
 * The destructor frees any heap storage allocated by the implementation.
 */

BigNumber::~BigNumber(){
    delete[] number;
}

/*
 * Implementation Notes: add
 * -------------------------------------------
 * Adds n to the reciever.
 * The implementation uses long addition.
 * Runs in O(N).
 */

BigNumber& BigNumber::add(const BigNumber &n){
    if(n.size() > size()) resize(n.size() - size(), "left");
    for(int i = 0; i < n.size(); i++){
        number[i] += n.number[i];
        if(number[i] >= 10){
            number[i] %= 10;
            if(i == size() - 1) push_back(1);
            else number[i+1]++;
        }
    }
    for(int j = n.size(); j < size(); j++){
        if(number[j] >= 10){
            number[j] %= 10;
            if(j == size() - 1) push_back(1);
            else number[j+1]++;
        }
    }
    normalize();
    return *this;
}

/*
 * Implementation Notes: subtract
 * -------------------------------------------
 * Subtracts n from the reciever.
 * The implementation uses long subtraction.
 * Runs in O(N).
 */

BigNumber& BigNumber::subtract(const BigNumber & n){
    if(*this < n){
        BigNumber temp = n;
        temp.subtract(*this);
        return *this = -temp;
    } else {
        for(int i = 0; i < n.size(); i++){
            number[i] -= n.number[i];
            if(number[i] < 0){
                number[i] += 10;
                number[i+1]--;
            }
        }
    }
    normalize();
    return *this;
}

/*
 * Implementation Notes: multiply
 * -------------------------------------------
 * Multiples n by the reciever.
 * The implementation uses a combination of long multiplication and the Karatsuba algorithm.
 * Scroll down to see the details.
 */

BigNumber& BigNumber::multiply(const BigNumber & n){
    *this = karatsuba(*this, n);
    return *this;
}

/*
 * Implementation Notes: divide
 * -------------------------------------------
 * Divides the reciever by n.
 * This is incredibly inefficient. Will fix.
 */

BigNumber& BigNumber::divide(const BigNumber & n){
    BigNumber t = 0;
    while(*this > 0){
        this->subtract(n);
        t+=1;
    }
    *this = (t - 1);
    normalize();
    return *this;
}

/*
 * Implementation Notes: raiseToPower
 * -------------------------------------------
 * Raises n to the power of p.
 * If showprogress is passed as true, it will show the current progress in the current calculation.
 */
BigNumber& BigNumber::raiseToPower(int p, bool showProgress) {
    BigNumber n = *this;
    for(int i = 0; i < p - 1; i++){
        *this *= n;
        if(showProgress) printProgress(i, p);
    }
    if(showProgress) cout << endl;
    return *this;
}

/*
 * Implementation Notes: raiseToPower
 * -------------------------------------------
 * Returns n!
 * If showprogress is passed as true, it will show the current progress in the current calculation.
 */
BigNumber& BigNumber::fact(int n, bool showProgress){
    *this = 1;
    for(int i = 2; i <= n; i++){
        *this *= i;
        if(showProgress) printProgress(i, n);
    }
    if(showProgress) cout << endl;
    return *this;
}

/*
 * Implementation Notes: raiseToPower
 * -------------------------------------------
 * Returns count (number of digits)
 */
int BigNumber::size() const {
    return count;
}

/*
 * Implementation Notes: copyConstructor
 * -------------------------------------------
 * Calls the deepCopy method.
 */
BigNumber::BigNumber(const BigNumber & n){
    deepCopy(n);
}

/*
 * Implementation Notes: assignment operator
 * -------------------------------------------
 * If the bigNumber provided is not the same instance,
 * then it call deepCopy.
 */
BigNumber & BigNumber::operator=(const BigNumber & n){
    if(this != &n){
        delete[] number;
        deepCopy(n);
    }
    return *this;
}

/*
 * Implementation Notes: arithmetic operators
 * -------------------------------------------
 * Makes a call to the associated method for each
 * operation. The unary operator - sets the boolean
 * instance variable neg to not neg.
 */

BigNumber& BigNumber::operator+=(const BigNumber & n){
    return add(n);
}

BigNumber& BigNumber::operator+(const BigNumber & n){
    return add(n);
}

BigNumber& BigNumber::operator-=(const BigNumber & n){
    return subtract(n);
}

BigNumber& BigNumber::operator-(const BigNumber & n){
    return subtract(n);
}

BigNumber & BigNumber::operator-(){
    this->neg = !this->neg;
    return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber & n){
    return multiply(n);
}

BigNumber& BigNumber::operator*(const BigNumber & n){
    return multiply(n);
}

BigNumber& BigNumber::operator/=(const BigNumber & n){
    return divide(n);
}

BigNumber& BigNumber::operator/(const BigNumber & n){
    return divide(n);
}

/*
 * Implementation Notes: comparison operators
 * -------------------------------------------
 * The implementation checks if both values
 * are negative or positive, compares the
 * number of digits, and then compares
 * each individual digit.
 */

bool BigNumber::operator<(const BigNumber & n){
    if(neg != n.neg)
        return neg;
    if(size() != n.size())
        return size() < n.size();
    for(int i = count - 1; i >= 0; i--){
        if(number[i] != n.number[i])
            return number[i] < n.number[i];
    }
    return false;
}

bool BigNumber::operator<=(const BigNumber & n){
    if(neg != n.neg)
        return neg;
    if(size() != n.size())
        return size() <= n.size();
    for(int i = count - 1; i >= 0; i--){
        if(number[i] != n.number[i])
            return number[i] < n.number[i];
    }
    return true;
}

bool BigNumber::operator>=(const BigNumber & n){
    return !operator<=(n);
}

bool BigNumber::operator>(const BigNumber & n){
    return !operator<(n);
}

bool BigNumber::operator==(const BigNumber & n){

}

/*
 * Private Methods
 * --------------
*/

/*
 * Implementation Notes: init
 * -------------------------------------------
 * Called by the constructors (excluding the copy constructor).
 * This method allocates the array storage and initalizes the fields.
 */

void BigNumber::init(int n){
    capacity = INITIAL_CAPACITY;
    count = 0;
    number = new short[capacity];
    if(n){
        neg = (n < 0) ? true : false;
        convertInteger(n);
    } else neg = false;
}

/*
 * Implementation Notes: convertInteger
 * -------------------------------------------
 * Splits an integer into individual digits and adds them to the array.
 * Ex.
 * n = 1245
 * push_back(n % 10) = 5
 * n /= 10 = 124
 * push_back(n % 10) = 4
 * ...
 */

void BigNumber::convertInteger(int n){
    if(n == 0) push_back(n);
    else {
        while(n > 0){
            push_back(n % 10);
            n /= 10;
        }
    }
}

/*
 * Implementation Notes: push_back
 * -------------------------------------------
 * Adds a digit to the end of the array and increments the count variable.
 */

void BigNumber::push_back(int n){
    if(count >= capacity) expandCapacity();
    number[count++] = n;
}

/*
 * Implementation Notes: push_front
 * -------------------------------------------
 * Shifts all elements in the array by one space,
 * puts the digit N in the front of the array
 * and increments the count variable.
 */

void BigNumber::push_front(int n){
    if(count >= capacity) expandCapacity();
    for(int i = count - 1; i >= 0; i--){
        number[i+1] = number[i];
    }
    number[0] = n;
    ++count;
}

/*
 * Implementation Notes: resize
 * -------------------------------------------
 * Resizes the reciever array by adding zeros as padding to the front or to the back.
 */

void BigNumber::resize(int d, string dir){
    for(int i = 0; i < d; i++){
        if(dir == "left") push_back(0);
        else if(dir == "right") push_front(0);
    }
}

/*
 * Implementation Notes: karatsuba
 * -------------------------------------------
 * The karatsuba algorithm is faster when the multiplicands
 * are between 320-640 bits.
 * Otherwise, it calls the longMultiplication method.
 * (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)
 */

BigNumber BigNumber::karatsuba(BigNumber n1, BigNumber n2){
    if(n1.size() <= 160 || n2.size() <= 160){
        return longMultiplication(n1, n2);
    }
    if(n1.size() > n2.size()) n2.resize(n1.size() - n2.size(), "left");
    if(n2.size() > n1.size()) n1.resize(n2.size() - n1.size(), "left");
    int m = n1.size();
    int m2 = m/2;
    BigNumber high1 = n1.copyRange(m2, m);
    BigNumber low1 = n1.copyRange(0, m2);
    BigNumber high2 = n2.copyRange(m2, m);
    BigNumber low2 = n2.copyRange(0, m2);
    /* 3 recursive calls */
    BigNumber z0 = karatsuba(low1, low2);
    BigNumber z2 = karatsuba(high1, high2);
    BigNumber z1 = karatsuba(high1 + low1, high2 + low2);
    BigNumber z3 = z1 - z2 - z0;
    z2.resize(2*m2, "right");
    z3.resize(m2, "right");
    return (z2) + (z3) + (z0);
}

/*
 * Implementation Notes: longMultiplication
 * -------------------------------------------
 * It's long multiplication!
 */

BigNumber BigNumber::longMultiplication(BigNumber& n1, BigNumber& n2){
    BigNumber top;
    BigNumber bottom;
    if(n1.size() >= n2.size()){
        top = n1;
        bottom = n2;
    } else {
        top = n2;
        bottom = n1;
    }
    BigNumber final;
    for(int i = 0; i < bottom.size(); i++){
        int carry = 0;
        BigNumber temp;
        if(i > 0) temp.resize(i, "left");
        for(int j = 0; j < top.size(); j++){
            int prod = bottom.number[i] * top.number[j] + carry;
            carry = prod / 10;
            prod %= 10;
            temp.push_back(prod);
        }
        if(carry != 0){
            temp.push_back(carry);
        }
        final += temp;
    }
    return final;
}

/*
 * Implementation Notes: copyRange
 * -------------------------------------------
 * Copies the reciever's array from [start, end).
 */

BigNumber BigNumber::copyRange(int start, int end){
    BigNumber cpy;
    int j = 0;
    for(int i = start; i < end; i++){
        cpy.push_back(number[i]);
    }
    return cpy;
}

/*
 * Implementation Notes: printProgress
 * -------------------------------------------
 * Prints the progress of a calculation on the same line.
 */
void BigNumber::printProgress(int i, int t){
    double progress = 100 * (double(i)/t);
    cout << "\rProgress: " << progress << "% complete";
}

/*
 * Implementation Notes: expandCapacity
 * -------------------------------------------
 * Doubles the capacity and copies
 * all the old elements into a new array.
 */
void BigNumber::expandCapacity(){
    short *oldNumber = number;
    capacity *= 2;
    number = new short[capacity];
    for(int i = 0; i < count; i++){
        number[i] = oldNumber[i];
    }
    delete oldNumber;
}

/*
 * Implementation Notes: deepCopy
 * -------------------------------------------
 * Copies all elements from n.
 */

void BigNumber::deepCopy(const BigNumber & n){
    capacity = n.count + INITIAL_CAPACITY;
    this->number = new short[capacity];
    for(int i = 0; i < n.count; i++){
        number[i] = n.number[i];
    }
    count = n.count;
    neg = n.neg;
}

/*
 * Implementation Notes: normalize
 * -------------------------------------------
 * Removes leading zeros.
 */

void BigNumber::normalize(){
    int i = size() - 1;
    while(number[i] == 0 && size() > 1){
        i -= 1;
        count -= 1;
    }
}

/*
 * Implementation Notes: toString
 * -------------------------------------------
 * Copies all the content from the array to a string.
 */

string BigNumber::toString() const{
    string str = "";
    str += (neg) ? "-" : "+";
    for(int i = count - 1; i >= 0; i--){
        str += (number[i] + '0');
    }
    return str;
}

/*
 * Implementation Notes: insertion operator
 * -------------------------------------------
 * Utilizes the toString method to insert the value into the output stream.
 */

ostream & operator<<(ostream & os, const BigNumber & n){
    return os << n.toString();
}
