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

Examples offunction type declarations:
   int f(void);
   int *fip(); 
   void g(int i, int j);
   void h(int, int); 

Specifying parameters with identifiers (as done her with g) can be problematic if an identifier is a macro. However, providing parameter
names is good practice for self-documenting code, so omitting the identifiers (as done in h) is not typically recommended. 

In a function declaration, specfying params is optional. However, failing to do so is occasionally problematic. If you were to write the function declaration for fip in C++
it would declare a function accepting no argument and returning an int*. In C, fip declares a function accpeting any number of args of any type and returning an int*.

                    You should never declare funcs w/ an empty parameter list in C!!!!!!!
So explicitly list params types and use void when there are no params. 

A function type with a parameter type list is known as a function prototype. 
A functino prototype informs the compiler about the number and types of params a function accepts. Compiler use this information to 
verify that the correct number and type of params are used in the functino definition and any calls to the function. 

The function definition provides the actual implementation of the function. 

    int max(int a, int b) {
        return a > b ? a : b;
    }


DERIVED TYPES:
---------------
These are types that are constructed from other types. These include pointers, arrays, type defintions, structures, and 
unions. 

Pointer Types:
---------------
A pointer type is derived from the function or object type that it points to, called the referenced type. A pointer provides a reference to an entity of the referenced type. 
    int *ip;  // pointer to int
    char *cp; // pointer to char
    void *vp; // pointer to void

& op (address-of) and indirection (*) op. You use the & op to take the address of an object or function.
    int i = 17; 
    int *ip = &i; 
 We declare the var ip as a pointer to int and assign it the address of i. You can also use the & operator on the result
 of the * op:
    ip = &*ip; 

Dereferencing ip by using the indirection operator resolves to the actual object i. Taking the address of *ip by using the & op 
retrieves the pointer, so these two ops cancel each other out. 

Arrays:
------
An array is a contiguously allocated sequence of objects that all have the same element type. 
    int ia[11]; 
    float *afp[17];

Creates the string "0123456789" to demonstrate how to assign values to the elements of an array:
char str[11]; 
for(unsigned int i = 0; i < 10; ++i) {
    str[i] = '0' + i;
} 
str[10] = '\0';  //null character


    void func(int arr[5]); 
    int main(void) {
        unsigned int i = 0; 
        unsigned int j = 0; 
        int arr[3][5]; 
        func(arr[i]); 
        int x = arr[i][j]; 
        return 0; 
    }

Type Definitions:
-----------------
You use typedef to declare an alias for an existing type; it creates a new type. For example, each of the 
following declarations creates a new type alias:

typedef unsigned int uint_type; 
typedef signed char schar_type, *schar_p, (*fp)(void); 


STRUCTURES:
------------
A structure type (struct) contains sequentially allocated member objects. Each object has its own name and may have a distinct type -
unlike arrays, which must all be of the same type. 

    struct sigrecord { 
        int signum; 
        char signame[20]; 
        char sigdesc[100]; 
    } sigline, *sigline_p;

The structure has 3 members objects: signum is an object of type int, signmae is an array of typ.....
Strcutures are sueful for declaring collections of related objects and may be used to represent things such as a 
date, customer, or personel record. They are especially useful for grouping objects that are frequently passed together as args to a function, 
so you don't need to repeatedly pass individual objects separately. 

You reference members of an object of the structure type by using the structure member (.) operator. If you have a pointer to a structure, you can reference
its members with the structure pointer(->) operator

    sigline.signum = 5; 
    strcpy(sigline.signame, "SIGINT"); 
    strcpy(sigline.sigdesc, "Interrup from keyboard"); 

     sigline_p = &sigline;
     sigline_p->signum = 5; 
     strcpy(sigline_p->signame, "Sigint"); 
     strcpy(signline->sigdesc, "Interrupt from keyboard"); 


UNIONS:
-------
Union types are similar to structures, except that the memory used by the member objects overlaps. Unions can contain
an object of one type at one time, and an object of a different type at a different time, but never both objects at the same time, 
and are primarily used to save memory. 

union {
    struct {
        int type; 
    }n;
    struct {
        int type; 
        int intnode; 
    }ni; 
    struct {
        int type;
        double doublenode; 
    }nf;
}u;
u.nf.type = 1;
u.nf.doublenode = 3.14; 

TAGS:
----
Tags are special naming mechanism for structs, unions and enumerations. For example, the identifier s appearing in the following structure is a tag:
struct s {
 -//--- snip=----
};

By itself, a tag is not a type name and cannot be used to declare a variable . Instead, you must declare variables of this type as follows:
    struct s v;    //instance of struct s
    struct s *p;  // pointer to struct s

The names of unions and enumerations are also tags and not types, meaning that they cannot be used alone to declare a variable. 

    enum day {sun, mon, tue, wed, thu, fri, sat}; 
    day today; // error
    enum day tomorrow; // OK

The tags of structures, unions, and enumeration are defined in a separate namesapce from ordinary identifiers
    enum status {ok, fail}; // enumeration
    enum status status(void); //function

You can even decalre an object s of type struct s:
    struct s s;  //Not good practice, but valid in C

You can think of struct tags as type names and define an alias fro the tag by using typedef. Here's an example:
    typedef struct s{ int x; } t;

    typedef struct tnode {
        int count; 
        struct tnode *left; 
        struct tnode *right; 
    }tnode; 

Type Qualifers:
-------------
All the types examined so far have been unqualified types. Types can be qualified by using one or more of the following
qualifiers: const, volatile, and restrict. Each of the qualifiers changes behaviors when accessing objects of the qualified type.

    const
        Objects declared with the 'const' qualifier (const-qualified types) are not modifiable. In particular, they're not assignable but 
        can have constant intializers. This means objects with const-qualified types can be placed in read-only memory by the compiler, and any attempt to write to them 
        willl result in a runtime error:
            const int i = 1;  //const-qualified int
            i = 2;  //error: i is const-qualified
        It's possible to accidently convince your compiler to change a const-qualified object for you. In the following eaxmple, we take the 
        address of a const-qualified object i and tell the cimpiler that this is actually a pointer to an int:
            const int i =1; //object of const-qualified type
            int *ip = (int *)&i; 
            *ip = 2; //undefined behavior 
C does not allow you to cast away the const if the original was declared as a const-qualified object. This code might appear to work, 
but it's defctive and may fail later. For example, the compiler might place the const-qualified object in read-only memory, causing a memory fault when trying to store a value in 
the object at runtime. 

C allows you to modify an object that is pointed to by a const-qualified pointer by casting the const away, provided that the original object was not declared
const:
    int i = 12;
    const int j = 12; 
    const int *ip = &i; 
    const int *jp = &j;
    *(int *)ip = 42;  // ok 
    *(int *)jp = 42;  //undefined behavior

volatile
---------
objects of volatile-qualified types serve a special purpose. Static volatile-quialified objects are used to model memory-mapped I/O  ports, and static 
constant volatile-qualified objects model memory-mapped input ports such as a real-time clock. 

   The values stored in these objects may change w/o the knowledge of the compiler. For example, every time the value from the real-time clock is read, 
it may change, even if the value has not been written to by the C program. 
Using a volatile-qualified type lets the compiler know that the value may change, and ensures that every access to the real-time clock occurs (otherwise, an access to the real-time clock
may be optimized away or replaced by a previously read and cached value). In the following code, for example, the compiler must generate instructions to read the value from port
and then writes this value back to the port. 

    volatile int port; 
    port = port;

Without the volatile qualification, the compiler would see this as a no-op ( a programming statement that does nothing) and potentially eliminate both the read and the write. 
Also , volatile qualified types are used for communication with signal handlers and with setjmp/longjmp. 

restrict:
---------
A restrict-qualified pointer is used to promote optimization. Objects indirectly accessed through a pointer frequently cannot be fully optimzied because of potential aliasing, which occurs when more than one pointer refers to the same object. 
Aliasing can inhibit optimizations, bc the compiler can't tell if portions of an object can change values when another apparently  unrelated object is modified. 
The following function copies n bytes from the storage referenced by q to the storage referrenced by p. The function parameters p and q are both restrict-qualified pointers:
    void f(unsigned int n, int * restrict p, int * restrict q) {
        while(n-- > 0) {
            *p++ = *q++; 
        }
    } 

Because both p and q are restrict-qualified pointers, the compiler  can assume that an object accessed through one of the pointer parameters is not also accessed through the other. 
The compiler can make this assessment based solely on the parameter declarations w/o analyzing  the function body. 
Although using restrict-qualified pointers can result in more efficient code, you must ensure that the pointers do not refer to overlapping memory to prevent undefined behavior. 


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

unsigned int retrieve(int counter) {
    printf("inside the retrieve function\n");
    return counter; 
}
// Demonstrating the storage class specifier static keyword
void increment(void) {
    static unsigned int counter = 0; 
    counter++;
    printf("%d", retrieve(counter)); 
    //printf("%d", counter); 
}
int add(int a, int b) {
    return a + b; 
}

int subtract( int a, int b) {
    return a - b; 
}

int multiply(int a, int b) {
    return a * b;
}

int (*funct_ptr[3])() = {add, subtract, multiply};

int main(void) { 
    int a = 21;     // a: 21
    int b = 17;        //b: 17
    int result; 
    int option;  

    /*swap(a, b); 
    printf(" Swap:\n\tmain: a = %d, b = %d\n", a, b);
    swap_ptrs(&a, &b); 
    printf(" Swap With Pointers:\n\tmain: a = %d, b = %d\n", a, b);
    */

   printf("\nEnter fuction number you want");
   printf("\nYou should not enter other than 0, 1, 2\n"); 
   scanf("%d", &option);

   if((option >= 0) && (option <= 2)) {
    result = (*funct_ptr[option])(a, b);
    printf("Result: %d\n", result);
   }

   /*for(int i = 0; i < 5; i++) {
    increment(); 
    printf("\n");
   } */
    return 0;
}

/* 
Exercises:
    1. Add a retrieve function to the counting example from Listing 2-6 to retrieve the current value of counter

    2. DEclare an array of three pointers to functions and invoke the appropriate 
    function based on an index value passed in as an argument. 

*/