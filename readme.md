### BigNumberLibrary C++
Example
~~~~
    BigNumber n(2);
    /* 2^222 * 2^222
     * Expected: 45427420268475430659332737993000283397102585042957378767593137448789955507087370207886940669610222847547657600391636120845912601788416
     * Output:   45427420268475430659332737993000283397102585042957378767593137448789955507087370207886940669610222847547657600391636120845912601788416  */
    n.pow(222);
    cout << "2^222 * 2^222 = " << n * n << endl;
~~~~

##### Overloaded Operators 
Multiplication 
`* *=`
Division 
`/ /=`
Addition 
`+ +=`
Subtraction 
`- -=`
Comparison Operators 
`< <= > >=`

#### Some Useful Methods
Raises the current value of the big number to the power of n. The show progress boolean is optional (default = false). It will simply print a precent to show the progress of the calculation (helpful if you're impatient).
`
BigNumber& pow(int n, bool showProgress=false);
`
Usage: 
~~~~
// 2^100 =
// 1267650600228229401496703205376
cout << "2^100 = " << n.pow(100) << endl;
~~~~
Returns n!
`
BigNumber& fact(int n, bool showProgress=false);
`
Usage:
~~~~
// 100! =
//93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000
cout << "100! = " << n.fact(100) << endl;
~~~~

#### Note
This is an incomplete project. Some methods are incredibly inefficient (the division especially), I just made it in one afternoon. I will push updates from time to time if requested.