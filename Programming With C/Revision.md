# tool chain

            PreProcessor         Compiler                  linker
    file.c  file.i               file.o                    file.exe
            replace #define      compoile each file        links all files

# defines

    notice that the #define are in capital letters
    helps in avoiding magic numbers
    for example
        #define MAX 50
        #define p(A,B) A>B?A:B              //this is a macro

# Data types

    interger types
    size modifiers
        short
        long
    sign modifiers
        signed
        unsigned
    int     4 bytes    25  00000000    00000000    00000000     00011001   Stored in 2’s complement for negatives
    short   2 bytes    25  00000000  00011001 Smaller range
    long    8 bytes 25000... 00011001  (64 bits)Larger range
    float   4 bytes    12.5    IEEE 754 format  1 bit sign + 8 bits exponent + 23 bits mantissa
    double  8 bytes   12.5   IEEE 754 double precision  1 bit sign + 11 bits exponent + 52 bits mantissa
