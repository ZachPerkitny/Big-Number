#include <iostream>
#include <fstream>
#include "bignumberlibrary.h"

using namespace std;

int main()
{
    BigNumber n(2);
    n.raiseToPower(600);
    cout << "Digits: " << n.size() << endl;
    cout << n << endl;
    return 0;
}
