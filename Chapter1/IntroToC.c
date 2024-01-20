/*

HOW TO COMPILE C CODE:
----------------------
On Linux and other Unix-like OSs, you can invole the system compiler with the cc command. 
To compile your program, enter 'cc' command:
    cc name_of_file.c

If you entered the program correctly, the compile command will crete a new file called 'a.out'
in the same directory as your source code.

The a.out file is an executable program, which you can run on the terminal:
    ./a.out


The cc command has numerous flags and compiler options. The -o file flag, for example, let's you give the executable
file a memorable ame instead of 'a.out'. The following compiler invocation names the executable 'hello':
    cc -o hello hello.c
    ./hello


Preprocessor Directives:
0--------------------------
#include preprocessor directive, which behaves as if you replaced it with the contents of the 
specfied file at the exact same location. We include the <stdio.h> and <stdlib.h> headers to access 
the functions declared in those headers, which we can then call from the program. The 'puts' function
is declared in <stdio.h>, and the EXIT_SUCCESS maro is defined in <stdlib.h>. As the filenames suggest, 
<stdio.h> contains the declarations for C Standard I/O functions, and <stdlib.h> contains the declarations for general
utility functions. You need to include the declaration for any library functions that you use in your program. 

The main function defines the main entry point for the program that's executed in a hosted environment when the 
command line or from another program. C defines two possible execution enviroments: freestanding and hosted. 

A FREESTANDING environment may not provide an OS and is typically used in embedded programming. 
These implementations provide a minimal set of library functions, and the name and type of the function
called at program startup are implementation defined. 

We define main to return a value of type int and place void inside the ()s to indicate that the function does not 
accept args. The int type is a signed integer type that can be used to represent both positive and negative 
integer values as well as zero. Similar to other procedural languages, C programs consist of procedures 
(referred to as functions) that can accept args and return values. 
Each function is a reusable unit of work that you can invoke as frequency as necessary in your program. 
In this case, ,the value returned by the main function indicates whether the program terminated successfully. The
actual work performed by this particular function is to print out the line

The puts function is a C Standard Lib function that write a string arg to stdout, which typically represents 
the console or terminal window, and appends a newline character to the output.
"Hello, world!" is a string literal that behaves like a read-only string. This function invocation outputs
Hello, world! to the terminal. 

EXIT_SUCCESS is an object-like macro that commonly expands to 0 and is typically defined as follows:
#define EXIT_SUCCESS 0

Each occurrence of EXIT_SUCCESS is replaced by a 0, which is then returned to the host environment from 
the call to main. The script that invokes the program can then check its status to determine whether the invocation 
was successful. A return from the initial call to the main function is equivalent to calling the C Standard Lib exit function
with the value returned by the main function as its arg. 

CHECKING FUNCTION RETURN VALUES:
---------------------------------
Functions will often return a value that's the result of a computation or that signifies whether the function successfully
completed its task. For example, the puts function we used in our "Hello, world!"  program takes a string to print
and returns a value of type int. The puts function returns the value of the macro EOF (a negative int) if a write eroor occurs; 
otherwise, it returns a nonnegative integer value. 

This revised version of the "Hello, world!" program checks whether the puts call returns the value EOF, 
indicating a write error. If the function return EOF, the program returns the value of the EXIT_FAILURE macro
(which evaluates to a nonzero value). Otherwise, the function succeeds, and the program returns EXIT_SUCCESS (which is required to be 0). 
The script that invokes the program can then check its status to determine whether it wa successful. 

PRINT FORMATTING:
--------------
The printf function takes a format string that defines how the ouptut is formatted, follwed by the variable number
of args that are the actua values you want to print. 
    printf("%s\n", "Hello, world!");

The %s is a conversion specfication that instructs the printf function to read the second arg (a string literal) and 
print it to stdout.

The simplest way to output a string is to use the puts function, as previously shown. If you do use 
printf instead of puts in the revised version of the "Hello, world!" program, you'll find it no longer works, because the printf 
functions returns status differently than the puts functions. The printf function returns the number of chars printed if it's successful, 
or a negative value if an output or encoding error occurred. 


COMPILERS:
------------
Many compilers are available, so I won't discuss them all here. Different compilers implement different versions
oof the C Standard. Many compiler for embedded systems support only C89/C90.

GNU Compiler Collection:
-----------------------
The GNU Compiler Collection (GCC) includes frontends for C, C++, and Objective-C, as well as other languages


IMPLEMENTATION-DEFINED BEHAVIOR:
-----------------------------------
is program behavior that's not specified by the C Standard and that may offer different results among implementations, but 
has consistent, documented behavior within an implementation. An ex of implementation-defined behavior is the number of bits in a byte.

Implementation-defined behavior are mostly harmless but can cause defects when porting to different implementations.
Whenever possible, aviod writing code that depends on implementation-defined behaviors that vary among the C implementations you might
use to compile your code


UNSPECIFIED BEHAVIOR:
--------------------
is program behavior for which the standard provides two or more options. The standard imposes no requirements on which
option is chosen in any instance. Each execution of a given expression may have different results or produce a different value than a previous 
execution of the same expression. An ex of unspecified behavior is function parameter storage layout, which can vary 
among function invocations within the same program. Avoid writing code that depends on the unspecified behaviors

UNDEFINED BEHAVIOR:
--------------------
is behavior that isn't defined by the C Standard, or less circularly, "behavior ,upon use of a nonportable or erroneous program construct or
of erroneous data, for which the standard imposes no requirements". Examples of undefined behavior include signed int overflow 
and dereferencing an invalid point value. Code that has undefined behavior is often erroneous, but iss more nuanced than that. 
Undefined behaviors are identified in the standard as follows:

- When a "shall" or "shall not" requirement is violated, and that requirement appears outside a constraint, the behavior is undefined

- When behavior is explicitly specified by the words "undefined behavior"

- By the omission of any explicit definition of behavior

The first two kinds of undefined behavior are frequently referre to as EXPLICIT UNDEFINED BEHAVIORS, while the 3rd kind 
is referred to as IMPLICIT UNDEFINED BEHAVIOR

Behaviors are classified as undefined by the C Standard comittee to do the following:
- Give the implementer license not to catch program errors that are difficult to diagnose

- Avoid defining obscure corner cases that would favor one implementation strategy over another

- Identify areas of possible conforming language extension in which the implementer may augment the language by providing a definition of the officially 
undefined behavior

Compiler (implemetations) have the latitude to do the following:
- Ignore undefined behavior completely, giving unpredictable results
- Behave in a documented manner characteristic of the environment (with or w/o issuing a diagnostic)
- Terminate a translation or execution (with issuing a diagnostic)

LOCALE-SPECIFIC BEHAVIOR AND COMMON EXTENSIONS:
--------------------------------------------------
depends on local conventions of nationality, culture, and language that each implementation documents. Common
extensions are widelt used in many systems but are not portable to all implementations. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    if(puts("Hello, world!") == EOF) {
        return EXIT_FAILURE;
    } 
    return EXIT_SUCCESS; 
}