# tool chain

            PreProcessor         Compiler                  linker
    file.c  file.i               file.o                    file.exe
            replace #define      compoile each file        links all files
    CMake is an open-source, cross-platform build system generator.
    It is used to manage the build process of software projects by generating native build files
    (like Makefiles on Linux, or Visual Studio projects on Windows) from simple configuration files called CMakeLists.txt.

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
    Bool  1 byte

    auto    //type infernce

# overflow

    Overflow occurs when an arithmetic operation produces a result that exceeds the maximum (or minimum) value that can be stored in a given data type.
    exmple
    unsigned char x= 255
    x++             //returns to 0
    when comparing differnet data types it is automatically prompoted
    Ranks (for integers: char < short < int < long < long long)
    Precision (for floats: float < double < long double)
    when comparring signed and unsigned signed is converted to unsigned
    c++ does implict conversions
    widening happens safely
    narowwing happens unsafely an may result in overflow

# class storage

    extern:
            the extern keyword is used to declare a variable or a function whose definition is present in some other file.
    static:
        outside function: file scoped global variable
        inside function:  function scoped variable that doesnt die when function ends
                          instead it retains its value

# Specifiers %

    Specifier Meaning
    %d, %i int
    %f float
    %lf double
    %c char
    %s string
    %u unsigned int
    %p pointer address
    %x, %X hex number

# taking input

    scanf("%d", &age);  //takes address
                 //Using cin (stops at space)
    string name;
    cin >> name;
                 //Using getline() (reads full line)
    string name;
    getline(cin, name);
    //Often you need cin.ignore() before getline if mixed with other inputs.
    a gentle reminder that cin generates a fail bit if the input mismatches
    you have to manually clear the fail bit if you want to use it in conditions again
    if(cin>>x)
        cin.clear()

# control flow

    if / switch
    remember that in c and c++ values other than zero are considered true
    so if(x=5) will always be true
                                                    //compiler error , else without if
       if(true)
        cout<<"hi";
        cout<<"bi";
    else
        cout<<"ti";
    switch takes integers ,char , enums.      //no float or strings
    in c++ switch can take constants var in c it doesnt allow it
    switch(x){
        case 1:
            break;                          //breaks from the switch if you dont it
                                            continues
        default:                            //default is optional
    }
    #include <iostream> // Needed to perform IO operations (C++ Library)
    #include <stdio.h> // Needed to Perform IO Operation (C Library)

# naming rules

    Variable Naming Rules in C/C++
    Can contain letters, digits, and underscores
    Must NOT start with a digit
    int 1value;//invalid
    int value1;//valid
    No special characters except underscore Not allowed: @, #, -, *, etc.
    Cannot use C/C++ keywords
    C++ allows you to name variables as built in function names like

        int printf;

    but once you try to use the printf function it will give a complier error

        printf("haai");
    you can solve this using the scope operator of the libary
        Example:
            int cout=5;
            std::cout;

# looping

    for
    while
    do while

# Array

    int arr[5];                     // Uninitialized array of 5 ints
    int arr[5] = {0};               // Zero-initialized
    int arr[] = {1, 2, 3};          // Size deduced from initializer (size = 3)
    int arr[5] = {1, 2};            // Partially initialized (rest = 0)

    using malloc and calloc     //they return void pointer
        int arraySize = 10;
        int* arr = static_cast<int*>(std::malloc(arraySize * sizeof(int)));
        if (!arr) { /* handle error */ }

        // ❗ Memory is uninitialized — contains garbage
        // Use only for POD types (e.g., int, char, simple structs)

        // Don't forget to free:
        std::free(arr);

        int* arr = static_cast<int*>(std::calloc(arraySize, sizeof(int)));
        if (!arr) { /* handle error */ }

        // All bytes set to 0 → for int, this means 0 (safe for POD)

        std::free(arr);

        int* arr = static_cast<int*>(std::malloc(5 * sizeof(int)));
        arr = static_cast<int*>(std::realloc(arr, 10 * sizeof(int)));
        if (!arr) { /* handle error */ }

        std::free(arr);


    using new c++
        int n = 10;
        int* arr = new int[n];          // Uninitialized
        int* arr = new int[n]();        // Value-initialized (zeroed for int)

    array name is a constant pointer to the first element of the array
    sizeof(arr)= type * number of elements
    arr+1 jumps by the type byte for example int will jump 4 bytes
    &arr+1 jumps by the type*size

# static cast vs normal cast

    C-style cast is a “Swiss Army knife” — too powerful

    A C-style cast tries multiple kinds of casts, in this order, until one works:

        const_cast (remove const/volatile)
        static_cast
        static_cast + const_cast
        reinterpret_cast (dangerous raw reinterpretation)
        reinterpret_cast + const_cast

        const int x = 10;
        int* p = (int*)&x;  // C-style cast: silently removes const!
        *p = 20;            // ❌ Undefined behavior! (modifying const)

        const int x = 10;
        int* p = static_cast<int*>(&x); // ❌ COMPILE ERROR!

# char Array

    char arr[10]={'h','e'};
    printf("%s",arr);               //un expected behavior because i havent specefied the
                                     terminator
    char arr[10]="he";
    printf("%s",arr)                //has an automatic termiantor
    BUT
    char arr[2]="he"                //compiler error , size of array must be size of string+1

    char* ptr="hello";
                                    // this is pointing at a read only memory
    ptr[0]                          //runtime error you are trying to modify read only
    ptr="hi"                        //works fine

# pointers

# refrence

# Boolean Logic as Arithmetic

    Convention
    False = 0, True = 1
    Variables: x, y \in \{0,1\}

    ⸻

    Basic Operators

    NOT
    \text{NOT } x = 1 - x

    AND
    x \land y = x \cdot y

    OR
    x \lor y = x + y - x\cdot y

    XOR
    x \oplus y = x + y - 2x\cdot y

    ⸻

    Derived Operators

    NAND
    x \uparrow y = 1 - x\cdot y

    NOR
    x \downarrow y = 1 - (x + y - x\cdot y)

    XNOR (Equivalence)
    x \leftrightarrow y = 1 - (x + y - 2x\cdot y)

    ⸻

    Implication

    Implication (x → y)
    x \to y = 1 - x + x\cdot y

    Reverse Implication (y → x)
    y \to x = 1 - y + x\cdot y

    ⸻

    Constants

    TRUE
    1

    FALSE
    0

    ⸻

    Key Notes
    • All Boolean operations can be expressed using addition, subtraction, and multiplication.
    • These formulas are valid when variables are restricted to \{0,1\}.
    • Any Boolean function can be written as a polynomial (Boolean/Zhegalkin polynomial).

    ⸻

    Minimal Building Blocks

    Using only:
    1, x, +, \cdot, -

    you can construct every logical operator.

# CString operations

    //size
    int str_length(char arr[]){
        int target_size=DEFAULT_VAL;
        while(*(arr)){
            arr++;
            target_size++;

        }
        return target_size;
    }
    //comparison
    int str_compare(char str1[],char str2[]){
        int sumStr1=DEFAULT_VAL,sumStr2=DEFAULT_VAL;
        int size1=str_length(str1),size2=str_length(str2);
        if(size1<size2)
            return 1;
        else if (size1>size2)
            return -1;
        while(*(str1)||*(str2)){
            if(*(str1)){
                str1++;
                sumStr1+=*str1;
            }
            if(*(str2)){
                str2++;
                sumStr2+=*str2;
            }
        }
        if(sumStr1>sumStr2){
                return -1;

        }else if(sumStr1<sumStr2){
            return 1;
        }else{
            return 0;
        }


    }
    //to lower
    bool toLower(char str[]){
        int diff='a'-'A';
        while(*(str)){
            if(*str>='A'&&*str<='Z'){
                *str+=diff;
            }
            str++;
        }
        return 1;
    }
    //concat
    bool str_concatinate(char str1[],char str2[],int size_str1){
    int str1Length=str_length(str1),str2Length=str_length(str2);
    if(str1Length+str2Length>size_str1)return 0;

    str1+=str1Length;

    while(*(str2)){

        *(str1)=*(str2);

        str1++;
        str2++;
    }
    *(str1)='/0'
    return 1;

    }
    //copy
    bool str_copy(char str1[],char str2[],int size_str2){
    int str1Length=str_length(str1);
    if(str1Length>size_str2)return 0;
    while(*(str1)){
        *(str2)=*(str1);
        str1++;
        str2++;

    }
    *(str1)='/0';
    return 1;

    }

# String operations

    just remember to check for the null when dealing with pointers

# Type C & C++ Description

    Array  Fixed-size collection of elements
    Pointer  Holds memory address
    Reference C++ only Alias to another variable
    Struct  Group of variables
    Union  Same memory for multiple types
    Enum  Named integral constants
    Class C++ only Encapsulates data + functions

# structs

    Structs
    Cleaner and shorter syntax.
    Without typedef:
    struct Student {
    char name[50];
    int age;
    };

    With typedef:
    struct Student s1;
    typedef struct {
    char name[50];
    int age;
    } Student;
    Student s1;
    // No need to write 'struct' keyword

# funciton

    Arrays are passed by address
    functions cant return more than one value
        Examples:
            // ❌ INVALID — won’t compile
            int[5] get_array() {
                int arr[5] = {1, 2, 3, 4, 5};
                return arr;  // Error: function cannot return array
            }
            int* get_array() {
            int arr[5] = {1, 2, 3, 4, 5};
            return arr;  // ❌ DANGEROUS! Returns pointer to local stack memory
            }
            // The array is destroyed when function exits → undefined behavior!

            //Correct way
               -> you can use static inside function
                int* get_array() {
                    static int arr[5] = {1, 2, 3, 4, 5};  // static = lives forever
                    return arr;
                }
               ->use malloc /calloc/new
               int* create_array(size_t size) {
                    int* arr = malloc(size * sizeof(int));
                    if (arr) {
                        for (size_t i = 0; i < size; i++) {
                            arr[i] = i;
                        }
                    }
                    return arr;  // valid — heap memory persists
                }

# pointers

    Null pointer
         int* p = nullptr;
    Dangling pointer
    int* dangling() {
        int x = 10;
        return &x;  // ❌ x is destroyed when function returns!
    }

    int main() {
            int* p = dangling();
            printf("%d", *p);  // ❌ Dangling pointer → undefined behavior
    }
    OR
    int* p = malloc(sizeof(int));
    *p = 42;
    free(p);
    printf("%d", *p);  // ❌ p is now dangling!

# Side Notes

    you can use typedef to define pointers or functions
    example:
        typedef int* IntPtr;
        int a = 10;
        IntPtr p = &a; // same as: int* p = &a;
        printf("%d", *p)

        typedef int (*Operation)(int, int);
        int add(int a, int b) { return a + b; }
        int main() {
        Operation op = add;
        printf("%d", op(5, 3)); // Output: 8
        return 0;
        }

    same number of [][][] same number of ***

    pointer have the same size but the differnce is in the size of the jump

# notes problems

    in 3-notes unsigned char
    for (unsigned char i = 5; i >= 0; i--) {
    // This loop never ends!
    // When i = 0, i-- wraps to 255
    // Condition i >= 255 is always true
    }
