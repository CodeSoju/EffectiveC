/*
Every type in C is either an object type or a function type.

OBJECTS, FUNCTIONS, TYPES , AND POINTERS:
-------------------------------------------
An object is storage in which you can represent values. An object is defined by the C Standard (ISO) as a "region
of data storage in the execution environment. the contents of which can represent values," with the added note, "when referenced, an object can be
interpreted as having a particular type." A variable is an example of an object. 

Vars have a declared type that tells you the kind of object its value represents. For example, an object with type int 
contains an integer value. 
The number 1 is represented in IEEE 754 (the IEEE Standard for Floating-Point Arithmetic) by the bit patters 
0x3f800000 (IEEE 754-2008). But if you were to interpret this same bit pattern as an integer, you'd get the value
1,065,353,216 instead of 1.

Functions are not objects but do have types. A function type is characterized by both its return type as well 
as the number and types of its parameters.

The C language also has pointers, which can be thought of as an address -- an location in memory where an 
object or function is stored. A pointer type is derived from a functionn or object type called the 
referenced type. A pointer type derived from the referenced type T is called a pointer to T.

Because objects and functions are different things, object pointers and function pointers are also different things, 
and should not be used interchangably. In the following section, you'll write a simple program that attempts to swap 
the values of two variables to help you better understand objects, functions, pointers, and types. 

Declaring Multiple Vars:
-------------------------
char *src, c; 
int x, y[5]
int m[12], n[15][3], o[21];

Swapping Values (First Attempt):
--------------------------------
Each object has a storage duration that determines its lifetime, which is the time during program
execution for which the object exists, has storage , has a constant address, and retains its last-stored value. 
Objects must not be referenced outside their lifetime. 

Local vars such as a and b from the code below have AUTOMATIC STORAGE DURATION , meaning that they exist 
until execution leaves the block in which they're defined. We are going to attempt to swap the values stored in these 
two vars. 


C is call-by-value (also called PASS BY VALUE) language, which means that when you provide an argument to a function, 
the value of that arg is copied into a distinct variable for use within the function. 
The swap function assigns the values of the objects you pass as args to the respective parameters. When the values 
of the params in the function are changed, the values in the caller are unaffected because they are distinct objects. 
Consequently, the vars a and b retian their original values in main during the second call to printf. The goal 
of the program was to swap the values of these two objects. 

Swapping Values (2nd Attempt)
----------------------------
To fix this bug, you can use pointers to rewrite the swap function. 
*/
#include <stdio.h>

void swap(int a, int b) {
    int t = a; 
    a = b; 
    b = t; 
    printf("swap: a = %d, b = %d\n", a, b);
}

void swap_ptrs(int *pa, int *pb) {
    int t = *pa; 
    *pa = *pb; 
    *pb = t;
    return; 
}

int main(void) { 
    int a = 21; 
    int b = 17; 

    swap(a, b); 
    printf(" Swap:\n\tmain: a = %d, b = %d\n", a, b);
    swap_ptrs(a, b); 
    printf(" Swap With Pointers:\n\tmain: a = %d, b = %d\n", a, b);
    return 0;
}
