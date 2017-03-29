#include <stack>
#include <queue>
#include "bignumberlibrary.h"

/* Public */
BigNumber::BigNumber(){
    init(0);
}

BigNumber::BigNumber(int n){
    init(n);
}

BigNumber::~BigNumber(){
    delete[] number;
}

void BigNumber::push_back(int n){
    if(count >= capacity) expandCapacity();
    number[count++].val = n;
}

void BigNumber::push_front(int n){
    if(count >= capacity) expandCapacity();
    for(int i = count - 1; i >= 0; i--){
        number[i+1].val = number[i].val;
    }
    number[0].val = n;
    ++count;
}

BigNumber& BigNumber::add(const BigNumber &n){
    if(n.size() > size()) resize(n.size() - size());
    for(int i = 0; i < n.size(); i++){
        number[i].val += n.number[i].val;
        if(number[i].val >= 10){
            number[i].val %= 10;
            if(i == size() - 1) push_back(1);
            else number[i+1].val++;
        }
    }
    for(int j = n.size(); j < size(); j++){
        if(number[j].val >= 10){
            number[j].val %= 10;
            if(j == size() - 1) push_back(1);
            else number[j+1].val++;
        }
    }
    normalize();
    return *this;
}

BigNumber& BigNumber::subtract(const BigNumber & n){
    if(*this < n){
        BigNumber temp = n;
        temp.subtract(*this);
        return *this = -temp;
    } else {
        for(int i = 0; i < n.size(); i++){
            number[i].val -= n.number[i].val;
            if(number[i].val < 0){
                number[i].val += 10;
                number[i+1].val--;
            }
        }
    }
    normalize();
    return *this;
}

BigNumber& BigNumber::multiply(const BigNumber & n){
    queue<BigNumber> q;
    for(int i = 0; i < n.size() ; i++){
        BigNumber copy = *this;
        copy.multiplyByDigit(n.number[i].val);
        for(int j = 0; j < i; j++){
            copy.push_front(0);
        }
        q.push(copy);
    }
    BigNumber sum(0);
    while(!q.empty()){
        sum.add(q.front());
        q.pop();
    }
    *this = sum;
    normalize();
    return *this;
}

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

BigNumber& BigNumber::pow(int p, bool showProgress) {
    BigNumber n = *this;
    for(int i = 0; i < p - 1; i++){
        *this *= n;
        if(showProgress) printProgress(i, p);
    }
    if(showProgress) cout << endl;
    return *this;
}

BigNumber& BigNumber::fact(int n, bool showProgress){
    *this = 1;
    for(int i = 2; i <= n; i++){
        *this *= i;
        if(showProgress) printProgress(i, n);
    }
    if(showProgress) cout << endl;
    return *this;
}

int BigNumber::size() const {
    return count;
}

BigNumber::BigNumber(const BigNumber & n){
    deepCopy(n);
}

BigNumber & BigNumber::operator=(const BigNumber & n){
    if(this != &n){
        delete[] number;
        deepCopy(n);
    }
    return *this;
}

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

bool BigNumber::operator<(const BigNumber & n){
    if(neg != n.neg)
        return neg;
    if(size() != n.size())
        return size() < n.size();
    for(int i = count - 1; i >= 0; i--){
        if(number[i].val != n.number[i].val)
            return number[i].val < n.number[i].val;
    }
    return false;
}

bool BigNumber::operator<=(const BigNumber & n){
    if(neg != n.neg)
        return neg;
    if(size() != n.size())
        return size() <= n.size();
    for(int i = count - 1; i >= 0; i--){
        if(number[i].val != n.number[i].val)
            return number[i].val < n.number[i].val;
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

/* Private */
void BigNumber::init(int n){
    capacity = INITIAL_CAPACITY;
    count = 0;
    number = new Digit[capacity];
    neg = (n < 0) ? true : false;
    convertInteger(n);
}

void BigNumber::convertInteger(int n){
    if(n == 0) push_back(n);
    else {
        while(n > 0){
            push_back(n % 10);
            n /= 10;
        }
    }
}

void BigNumber::resize(int d){
    for(int i = 0; i < d; i++){
        push_back(0);
    }
}

void BigNumber::multiplyByDigit(int digit){
    for(int i = 0; i < size(); i++){
        number[i].val *= digit;
    }
    for(int i = 0; i < size(); i++){
        if(number[i].val >= 10){
            int f = number[i].val/10;
            number[i].val %= 10;
            if(i == size() - 1) push_back(f);
            else number[i+1].val += f;
        }
    }
}

void BigNumber::printProgress(int i, int t){
    double progress = 100 * (double(i)/t);
    cout << "\rProgress: " << progress << "% complete";
}

void BigNumber::expandCapacity(){
    Digit *oldNumber = number;
    capacity *= 2;
    number = new Digit[capacity];
    for(int i = 0; i < count; i++){
        number[i].val = oldNumber[i].val;
    }
    delete oldNumber;
}

void BigNumber::deepCopy(const BigNumber & n){
    capacity = n.count + INITIAL_CAPACITY;
    this->number = new Digit[capacity];
    for(int i = 0; i < n.count; i++){
        number[i].val = n.number[i].val;
    }
    count = n.count;
    neg = n.neg;
}

void BigNumber::normalize(){
    int i = size() - 1;
    while(number[i].val == 0 && size() > 1){
        i -= 1;
        count -= 1;
    }
}

string BigNumber::toString() const{
    string str = "";
    str += (neg) ? "-" : "+";
    for(int i = count - 1; i >= 0; i--){
        str += (number[i].val + '0');
    }
    return str;
}

ostream & operator<<(ostream & os, const BigNumber & n){
    return os << n.toString();
}
