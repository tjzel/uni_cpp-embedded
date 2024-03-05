#include <iostream>
#include <algorithm>
#include "String.h"

using namespace std;

int main(){
    String a("hi");   // Constructor from C string
    String b;             // Default constructor
    const String c = a;   // no copy (c points to string in a)
    String d = a+b;       // no copy (d points to string in a)
    a.set(0,'l');           // Copy constructor
    a.set(1,'l');           // no copy
    d = c+a;              // Constructing new string
    cout << c << " "<< d << endl; // hi hill  (no copy)
    cout << c.get(0) << endl;         // h        (no copy)
    return 0;
}
/* Expected output

Constructor from C string
Default constructor
Copy constructor
Constructor from C string
hi hill
h
*/