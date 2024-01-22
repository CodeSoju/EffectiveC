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

When you use the unary * operator in expressions w/in the function, the unary * operator dereferneces the pointer to the object

pa = pb; // This replaces the value of the pointer pa with the value of the pointer of pointer pb. 

Now consider the actual assignment in the swap fuction:
    *pa = *pb; 

This dereferences the pointer pb, reads the referenced value, dereferences the pointer pa, and then overwrites the value
at the location referenced by pa with the value referenced by pb

The unary & is the address-of operator, which generates a pointer  to its operand. This change is necessary because the swap function now accepts
pointers to objects of type int as params instead of simply values of type int. 


W/in the swap function, the params pa and pb now both declared to havwe the type pointer to int and contains copies of the args
passed to swap from the calling function (in this case, main). These address copies still refer to the exact same objects, 
so when the values of the objects they reference are swapped in the swap function, the contents of the orignal objects declared in main are accessed and also swapped. 
This approach simulates CALL-BY-REFERENCE (AKA pass by reference) by generating object addresses, passing those by value, and then 
dereferencing the copied addresses to access the original objects.

STORAGE DURATION:
-----------------
Object have a storage duration that determines their lifetime. Altogether, four storage durations are available:
Automatic,
Static, 
Thread,
Allocated

Objects of automatic storage duration are declared w/in a block or as a function parameters. The lifetime of these objects begins when the block
in which they're declared begins execution, and ends when execution of the block ends. If the block is entered recursively, a new object is created each time, 
each with its own storage. 

Scope applies to identifiers, whereas Lifetime applies to objects. The scope of an identifier is the code region where the object
denoted by the identifier can be accessed by its name. The lifetime of an object is the time period for which the object exists. 

Objects declared in file scope have STATIC storage suration. The lifetime of these objects is the entire execution of the program, and the stored values is initialized prior to program startup.  
These objects persists after the function has exited. 

Static objects must be initalized with a constant value and not a variable:

int *func(int i) {
    const int j = i; // ok
    static int k = j; // error
    return &k;
}

A constant value refers to literal constans (for example, '1, 'a', or 0xFF), enum members, and the results of operators 
such as alignof or sizeof; not const-qualified objects.

Thread storage duration is used in concurrent porgrammming. 

Allocated storage duration deals with dynamically allocated memory. 

Alignment:
-----------
    Object types have alignment requirements that places restrictions on the addresses at which objects of that type 
    maybe allocated. An alignment represents the number of bytes successive addresses at which a given object can 
    be allocated. CPUs may have different behavior when accessing aligned data (for example, the data address is a multiple of the 
    data size) versus unaligned data.

    Some machine instructions can perform multibyte accesses on non-word boundaries, but there may be a performance penalty. A word is 
a natural, fixed-sized unit of data handled by the instruction set or the hardware of the processor. Some platforms can't access
unaligned memory. Alignment requirements may depend on the CPU word size (typically, 16, 32, 64 bits). 

Generally, C programmers need not concern themselves with alignment requirements, because the compiler chooses suitable alignments 
for its various types. Dynamically allocated memory from malloc is required to be sufficiently aligned  for all standard types, including arrays and structures. 
However, on rare occassions, you might need to override the compiler's default choices; for example, to align data on the boundaries of the 
memory cache lines that must start at power-of-two address boundaries, or to meet other system-specific requirements. Tradtionally, these requirements were met
by linker commands, or by overallocating memory with malloc following by rounding the user address upward, or similar ops invloving other 
nonstandard facilities. 

C11 introduced a simple, foward-compatible mechanism for specifying alignments. Alignments are represented as values of the type size_t. Every valid alignment 
value is a nonnegative integral power of two. An object type imposes a default alignment requirment on every object of that type:
a stricter alignment (a larger power of two) can be requested using the alignment specifier (_Alignas). You can include an alignment specifier in the declaration specifiers of a 
declaration. 

struct S {
    int i; double d; char c;
};

int main (void) {
    unsigned char bad_buff[sizeof(struct S)];
    _Alignas(struct S) unsigned char good_buff[sizeof(struct S)];

    struct S *bad_s_ptr = (struct S *)bad_buff; // wrong pointer alignment
    struct S *good_s_ptr = (struct S *)good_buff;  //correct pointer alignment
}

Alignments are ordered from weaker to stronger (aslo called stricter) alignments. Stricter alignments have larger
alignment values. An address that satifies an alignment requirement also satifies any valid, weaker, alignment requirement.

Boolean Types
---------------
Objects decalred as _Bool can store only the values 0 and 1

If you inclkude the header <stdbool.h>, you can also spell this type as bool and assign it the values true (which expands to the int constant 1)
 and false => constant 0

    #include <stdbool.h>
    _Bool flag1= 0; 
    bool flag2 = false;


Character Types:
---------------
The C language defines three character types: char, signed char, and unsigned char. Each compiler
implementation will define char to have the same alignment size, range, representation, and behavior as either signed char or
unsigned char. Regardless of the choice made, char is a separate type from the other two and is incompatible with both.

The char type is commonly used to represent character data in C language programs. In particular, objects of type char must able to represent 
the minimum set of characters required in the execution environment (known as the BASIC EXECUTION CHARACTER SET), including upper-and lowercase letters, the 10 decimal digit, 
the space character, and various punctuation and control characters. The char type is inappropriate for integer data; 
it is safer to use signed char to represent small signed integer values, and unsigned char to represent small unsigned values. 

You can represent the characters of a larger character set as WIDE CHARACTERS by using 'wchar_t 'type, which generally takes more space
space than a basic character. Typically, implementations choose 16 or 32 bits to represent a wide character.

Numerical Types:
-----------------
C provides several numerical types that can be used to represent integers, enumerators, and floating-point values. 

Integer Values:
--------------
Signed intetger types can be used to represent negative numbers, positive numers, and zero. The signed integer types include signed char, short int, int long, 
and long long int.The signed integer types include signed char, short int, int, long int, and long long int. 
Except for int itself, the keyword int may be omitted in the delarations for these types, so you might, for example, declare a type by using long long instead of
long long int. 

For each signed int type, there is a corresponding unsigned int type that uses the same amount of storage: unsigned char, unsigned short in, unsigned int, unsigned long int, and unsigned long long int. 
The unsigned type can be used to represent only positive numbers and zero. 

The signed and unsigned int types are used to represent ints of various sizes. Each platform (current or historical) determines the size for each of these types, 
given some constraints. Each type has a minimum representable rrange. The types are ordered by width, guaranteeing that wider types are at least as large as narrower types
so that an object of type long long int can represent all values that an object of type long int can represent and so forth. 
The actual size of the various int types can be inferred from the minimum and maximum representable values for the various int types specified in the <limits.h> header file. 

The int type usually has the natural size suggested by the architecture of the execution environment, so the size would be 16 bits wide on a 16-bit arcchitecture, and 32 bits wide on a 32-bit
architecture. You can specify actual-width integers by using type defs from the <stdint.h> or <inttypes.h> headers, like uint32_t. These headers also provide type defintions for the widest 
available int types: uintmax_t and intmax_t, 

enum Types:
------------
An enumeration, or enum, allows you to define a type that assigns names (enumerators) to integer values in cases with an enumerable set of constant values. 
    enum day { sun, mon, tue, wed, thu, fir, sat}; 
    enum cardinal_points {north = 0, east = 90, south = 180, west = 270}; 
    enum months {jan = 1, feb. march. apr, may, jun, jul };

If you don't specify a value to the first enumerator eith the = operator, the value of its enumeration contant is 0, and each subsequent constant. Consequently, the value of sun in the day enumeration is 0, mon is 1, and so forth. 
You can also assign specfic values to each enumerator, as shown by the cardinal_points enumeration. 

The actual value of the enumeration constand must be representable as an int, but its type is implementation defined. 

void Types:
-----------
The void tpe is a rather strange type. The keyword void (by itself) means "cannot hold any value". 
The derived type void * means that the pointer can reference any object.

FUnciton Types:
---------------
Function types are derived types. In this case, the type is derived from the return type and the number and types of its params. The reutnr type of a function 
can't be an array type

When you declare a function, you use the function declarator to specify the name of the function and the return type. 
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

// Demonstrating the storage class specifier static keyword
void increment(void) {
    static unsigned int counter = 0; 
    counter++;
    printf("%d", counter); 
}

int main(void) { 
    int a = 21;     // a: 21
    int b = 17;        //b: 17

    /*swap(a, b); 
    printf(" Swap:\n\tmain: a = %d, b = %d\n", a, b);
    swap_ptrs(&a, &b); 
    printf(" Swap With Pointers:\n\tmain: a = %d, b = %d\n", a, b);
    */

   for(int i = 0; i < 5; i++) {
    increment(); 
    printf("\n");
   }
    return 0;
}