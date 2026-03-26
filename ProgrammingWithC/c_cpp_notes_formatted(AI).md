# C/C++ Revision Notes

## Toolchain

```
PreProcessor → Compiler → Linker
file.c → file.i → file.o → file.exe
```

| Stage | Input | Output | Action |
|-------|-------|--------|--------|
| **PreProcessor** | `file.c` | `file.i` | Replace `#define` directives |
| **Compiler** | `file.i` | `file.o` | Compile each file to object code |
| **Linker** | `file.o` | `file.exe` | Link all object files together |

### CMake

**CMake** is an open-source, cross-platform build system generator. It manages the build process by generating native build files (like Makefiles on Linux or Visual Studio projects on Windows) from simple configuration files called `CMakeLists.txt`.

---

## Defines

**Convention:** `#define` directives are written in CAPITAL LETTERS.

### Benefits:
- Helps avoid magic numbers
- Makes code more maintainable

```c
#define MAX 50
#define p(A,B) A>B?A:B  // Macro - notice you can't check data types
```

⚠️ **Warning:** Macros don't have type checking!

---

## Data Types

**📝 Note:** Data types have different sizes on different machines.

### What Data Types Specify:
- Size of variable
- Range of values
- Available operations

### Categories:

#### Primitive Types:
`int`, `char`, `float`, `double`, `void`

#### Derived Types:
`Array`, `Pointer`, `Function`

#### User-Defined Types:
`enum`, `struct`, `union`

### Modifiers:

**Size Modifiers:**
- `short` (for integer)
- `long` (for integer, double)

**Sign Modifiers:**
- `signed` (for char, integer)
- `unsigned` (for char, integer)

### Size and Storage Details:

| Type | Size | Example | Binary Representation | Notes |
|------|------|---------|----------------------|-------|
| `int` | 4 bytes | 25 | `00000000 00000000 00000000 00011001` | Stored in 2's complement for negatives |
| `short` | 2 bytes | 25 | `00000000 00011001` | Smaller range |
| `long` | 8 bytes | 25000... | `00011001` (64 bits) | Larger range |
| `float` | 4 bytes | 12.5 | IEEE 754 format | 1 bit sign + 8 bits exponent + 23 bits mantissa |
| `double` | 8 bytes | 12.5 | IEEE 754 double precision | 1 bit sign + 11 bits exponent + 52 bits mantissa |
| `bool` | 1 byte | true/false | - | C++ only |

### Type Inference:

```cpp
auto x = 10;  // Type inferred as int
auto y = 3.14; // Type inferred as double
```

---

## Overflow

**Overflow** occurs when an arithmetic operation produces a result that exceeds the maximum (or minimum) value that can be stored in a given data type.

### Example:

```c
unsigned char x = 255;
x++;  // Returns to 0 (wraps around)
```

### Type Promotion Rules:

When comparing different data types, automatic promotion occurs:

**Integer Ranks:** `char < short < int < long < long long`

**Floating-Point Precision:** `float < double < long double`

### Signed vs Unsigned:

When comparing signed and unsigned, **signed is converted to unsigned**.

### Conversions in C++:

- **Widening:** Happens safely (implicit)
- **Narrowing:** Happens unsafely and may result in overflow (requires explicit cast)

```cpp
int x = 5;
double y = x;  // ✅ Widening - safe

double a = 4.3;
int b = (int)a; // ⚠️ Narrowing - requires cast
```

---

## Storage Class Specifiers

### extern

Declares a variable or function whose definition is present in some other file.

```c
extern int global_var;  // Declaration only
```

### static

**Outside function:** File-scoped global variable (internal linkage)

```c
static int file_var = 10;  // Only visible in this file
```

**Inside function:** Function-scoped variable that doesn't die when function ends; retains its value

```c
void counter() {
    static int count = 0;  // Initialized only once
    count++;
    printf("%d\n", count);
}
```

---

## Format Specifiers

| Specifier | Type |
|-----------|------|
| `%d`, `%i` | int |
| `%f` | float |
| `%lf` | double |
| `%c` | char |
| `%s` | string |
| `%u` | unsigned int |
| `%p` | pointer address |
| `%x`, `%X` | hex number |

---

## Taking Input

### C-style (scanf):

```c
int age;
scanf("%d", &age);  // Takes address
```

### C++ style (cin):

```cpp
// Using cin (stops at space)
string name;
cin >> name;

// Using getline() (reads full line)
string fullName;
getline(cin, fullName);
```

⚠️ **Important:** Often you need `cin.ignore()` before `getline()` if mixed with other inputs.

### cin Fail Bit:

`cin` generates a fail bit if the input mismatches. You must manually clear the fail bit:

```cpp
int x;
if(cin >> x) {
    // Success
} else {
    cin.clear();  // Clear fail bit
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
}
```

---

## Control Flow

### if Statement

**📝 Remember:** In C and C++, values other than zero are considered **true**.

```c
if(x = 5)  // ⚠️ Assignment, always true!
    cout << "Always executed";

if(x == 5) // ✅ Comparison
    cout << "Executed if x equals 5";
```

### Dangling else Problem:

```c
if(true)
    cout << "hi";
    cout << "bi";  // Always executes (not part of if)
else               // ❌ Compiler error - else without if
    cout << "ti";
```

### switch Statement

**Can take:** integers, char, enums
**Cannot take:** float or strings

```c
switch(x) {
    case 1:
        // code
        break;  // ⚠️ Without break, continues to next case
    case 2:
        // code
        break;
    default:    // Optional
        // code
}
```

**📝 Note:** In C++, switch can take constant variables; in C it doesn't allow it.

### Headers:

```cpp
#include <iostream>  // C++ Library (IO operations)
#include <stdio.h>   // C Library (IO operations)
```

---

## Naming Rules

### Variable Naming Rules in C/C++:

✅ **Allowed:**
- Can contain letters, digits, and underscores
- Must NOT start with a digit

```c
int value1;  // ✅ Valid
int 1value;  // ❌ Invalid
```

❌ **Not Allowed:**
- No special characters except underscore
- Not allowed: `@`, `#`, `-`, `*`, etc.
- Cannot use C/C++ keywords

### Special Case - Function Name Collision:

C++ allows you to name variables as built-in function names:

```cpp
int printf;  // ✅ Compiles

printf("hello");  // ❌ Compiler error - printf is now a variable

std::printf("hello");  // ✅ Use scope operator to access library function
```

**Solution:** Use the scope operator `::` of the library

```cpp
int cout = 5;
std::cout << "Using library cout";  // ✅ Works
```

---

## Looping

### Three types:

```c
// for loop
for(int i = 0; i < 10; i++) {
    // code
}

// while loop
while(condition) {
    // code
}

// do-while loop
do {
    // code
} while(condition);
```

---

## Arrays

### Declaration and Initialization:

```c
int arr[5];                     // Uninitialized array of 5 ints
int arr[5] = {0};               // Zero-initialized
int arr[] = {1, 2, 3};          // Size deduced from initializer (size = 3)
int arr[5] = {1, 2};            // Partially initialized (rest = 0)
```

### Dynamic Allocation (C-style):

#### Using malloc:

```c
int arraySize = 10;
int* arr = (int*)malloc(arraySize * sizeof(int));
if (!arr) { /* handle error */ }

// ⚠️ Memory is uninitialized - contains garbage
// Use only for POD types (e.g., int, char, simple structs)

free(arr);  // Don't forget to free
```

#### Using calloc:

```c
int* arr = (int*)calloc(arraySize, sizeof(int));
if (!arr) { /* handle error */ }

// All bytes set to 0 → for int, this means 0 (safe for POD)

free(arr);
```

#### Using realloc:

```c
int* arr = (int*)malloc(5 * sizeof(int));
arr = (int*)realloc(arr, 10 * sizeof(int));
if (!arr) { /* handle error */ }

free(arr);
```

**📝 Note:** malloc and calloc return `void*` pointer.

### Dynamic Allocation (C++ style):

```cpp
int n = 10;
int* arr = new int[n];      // Uninitialized
int* arr = new int[n]();    // Value-initialized (zeroed for int)

delete[] arr;  // Don't forget to delete
```

### Array Pointer Arithmetic:

- **Array name** is a constant pointer to the first element
- `sizeof(arr)` = type × number of elements
- `arr + 1` jumps by the type size (e.g., int jumps 4 bytes)
- `&arr + 1` jumps by the entire array size (type × size)

```c
int arr[5] = {1, 2, 3, 4, 5};
printf("%p\n", arr);      // Address of first element
printf("%p\n", arr + 1);  // Address + sizeof(int)
printf("%p\n", &arr + 1); // Address + sizeof(entire array)
```

---

## static_cast vs C-style Cast

### C-style Cast - "Swiss Army Knife" (Too Powerful)

A C-style cast tries multiple kinds of casts until one works:

1. `const_cast` (remove const/volatile)
2. `static_cast`
3. `static_cast + const_cast`
4. `reinterpret_cast` (dangerous raw reinterpretation)
5. `reinterpret_cast + const_cast`

### Example - The Danger:

```cpp
const int x = 10;
int* p = (int*)&x;  // ⚠️ C-style cast: silently removes const!
*p = 20;            // ❌ Undefined behavior! (modifying const)
```

### static_cast - Safer Alternative:

```cpp
const int x = 10;
int* p = static_cast<int*>(&x); // ❌ COMPILE ERROR! (Good!)
```

✅ **Recommendation:** Always use C++ casts (`static_cast`, `const_cast`, `reinterpret_cast`, `dynamic_cast`) over C-style casts for type safety.

---

## Character Arrays (C-Strings)

### Without Null Terminator:

```c
char arr[10] = {'h', 'e'};
printf("%s", arr);  // ⚠️ Unexpected behavior - no null terminator
```

### With Null Terminator:

```c
char arr[10] = "he";
printf("%s", arr);  // ✅ Has automatic null terminator

char arr[2] = "he"; // ❌ Compiler error - size must be string length + 1
```

### String Literal Pointer:

```c
char* ptr = "hello";  // Points to read-only memory

ptr[0] = 'H';  // ❌ Runtime error - trying to modify read-only memory
ptr = "hi";    // ✅ Works fine - changing pointer, not content
```

---

## Pointers

### Types of Problem Pointers:

#### 1. Null Pointer:

```cpp
int* p = nullptr;  // Pointer points at address 0x0
```

#### 2. Dangling Pointer:

```c
// Example 1: Returning address of local variable
int* dangling() {
    int x = 10;
    return &x;  // ❌ x is destroyed when function returns!
}

int main() {
    int* p = dangling();
    printf("%d", *p);  // ❌ Dangling pointer → undefined behavior
}

// Example 2: After free
int* p = malloc(sizeof(int));
*p = 42;
free(p);
printf("%d", *p);  // ❌ p is now dangling!
```

#### 3. Wild Pointer:

```c
int* p;      // ❌ Wild pointer! (uninitialized)
*p = 42;     // ❌ Write to random memory → crash or corruption
```

### Void Pointer:

A generic pointer that you must cast each time you want to access it.

```c
#include <stdio.h>

int main() {
    int i = 10;
    double d = 3.14;
    char c = 'A';
    
    void* ptr;
    
    ptr = &i;
    printf("int: %d\n", *(int*)ptr);
    
    ptr = &d;
    printf("double: %f\n", *(double*)ptr);
    
    ptr = &c;
    printf("char: %c\n", *(char*)ptr);
    
    return 0;
}
```

### Const Pointers:

**📝 Note:** `const int` is the same as `int const`

```cpp
int x = 10, y = 20;

// Normal pointer
int* ptr = &x;
ptr = &y;   // ✅ Can change
*ptr = 5;   // ✅ Can modify

// Pointer to constant
int const* ptr = &x;  // or: const int* ptr = &x;
ptr = &y;   // ✅ Can change pointer
*ptr = 5;   // ❌ Cannot modify value

// Constant pointer
int* const ptr = &x;
ptr = &y;   // ❌ Cannot change pointer
*ptr = 4;   // ✅ Can modify value

// Constant pointer to constant
int const* const ptr = &x;
ptr = &y;   // ❌ Cannot change pointer
*ptr = 5;   // ❌ Cannot modify value
```

---

## Default Arguments

### Rules:

1. **Default arguments must be at the end**
2. If you define one on the left, all the right ones must have default arguments

```cpp
void fun(int x = 10, int y);    // ❌ Wrong
void fun(int x, int y = 10);    // ✅ Correct
```

### Works Only in Declaration:

```cpp
fun(x = 10, y);  // ❌ Wrong - can't specify defaults in calls
```

### Header vs Implementation:

When a function is declared multiple times (header + source), default args must appear **only once**.

```cpp
// header.h
void fun(int x, int y = 10);  // ✅ Default in header

// source.cpp
void fun(int x, int y) {      // ✅ No default in implementation
    // code
}
```

### Compile-time vs Run-time:

- **Compile-time:** Which default argument applies is decided
- **Run-time:** The actual expression (if any) is evaluated

### Not Part of Function Signature:

Default arguments are **not** part of the function signature.

### Virtual Functions and Default Arguments:

```cpp
class Base {
public:
    virtual void show(int x = 10) { 
        cout << "Base: " << x << endl; 
    }
};

class Derived : public Base {
public:
    void show(int x = 20) override { 
        cout << "Derived: " << x << endl; 
    }
};

int main() {
    Derived d;
    Base* pb = &d;
    
    d.show();       // Static type: Derived → default is 20
                    // Prints: "Derived: 20"
    
    pb->show();     // Static type: Base* → default is 10
                    // Dynamic dispatch to Derived::show
                    // Prints: "Derived: 10"
    
    Base* ptr = new Derived();
    ptr->show();    // Prints: "Derived: 10"
    ptr->show(20);  // Prints: "Derived: 20"
}
```

⚠️ **Important:** Default argument is chosen based on **static type**, not dynamic type!

---

## Reference vs Pointers

### Pointers:

| Feature | Description |
|---------|-------------|
| **Store** | Memory address of a variable |
| **Null** | Can be null (may not point to any object) |
| **Reassignment** | Can be reassigned to different objects |
| **Declaration** | Use `*` operator to declare |
| **Get Address** | Use `&` operator to get address of variable |

```cpp
int a = 10;
int* ptr = &a;  // Pointer to a
*ptr = 20;      // Modify through pointer
ptr = nullptr;  // Can be null
```

### References:

| Feature | Description |
|---------|-------------|
| **Alias** | Another name for an existing object |
| **Binding** | Once initialized, cannot be reseated |
| **Initialization** | Must be initialized |
| **Null** | Cannot be null |
| **Reassignment** | Cannot be reassigned |
| **Implementation** | Typically implemented as pointers under the hood |

```cpp
int a = 10;
int& r = a;     // r is a reference to a
r = 20;         // Modifies 'a'
cout << a;      // Output: 20
```

### Constant Values and References:

**Cannot bind constant values to references unless the reference itself is constant:**

```cpp
int& ref = 4;       // ❌ Error

const int& ref = 4; // ✅ OK

int&& ref = 4;      // ✅ OK (rvalue reference - used in move semantics)
```

---

## Boolean Logic as Arithmetic

### Convention:
- **False = 0**
- **True = 1**
- Variables: x, y ∈ {0, 1}

### Basic Operators:

| Operation | Formula |
|-----------|---------|
| **NOT** | `¬x = 1 - x` |
| **AND** | `x ∧ y = x · y` |
| **OR** | `x ∨ y = x + y - x·y` |
| **XOR** | `x ⊕ y = x + y - 2x·y` |

### Derived Operators:

| Operation | Formula |
|-----------|---------|
| **NAND** | `x ↑ y = 1 - x·y` |
| **NOR** | `x ↓ y = 1 - (x + y - x·y)` |
| **XNOR** | `x ↔ y = 1 - (x + y - 2x·y)` |

### Implication:

| Operation | Formula |
|-----------|---------|
| **x → y** | `1 - x + x·y` |
| **y → x** | `1 - y + x·y` |

### Constants:

- **TRUE:** 1
- **FALSE:** 0

### Key Notes:

- All Boolean operations can be expressed using addition, subtraction, and multiplication
- These formulas are valid when variables are restricted to {0, 1}
- Any Boolean function can be written as a polynomial (Boolean/Zhegalkin polynomial)

### Minimal Building Blocks:

Using only: `1`, `x`, `+`, `·`, `-` you can construct every logical operator.

---

## C-String Operations

### String Length:

```c
int str_length(char arr[]) {
    int target_size = 0;
    while(*(arr)) {
        arr++;
        target_size++;
    }
    return target_size;
}
```

### String Comparison:

```c
int str_compare(char str1[], char str2[]) {
    int sumStr1 = 0, sumStr2 = 0;
    int size1 = str_length(str1), size2 = str_length(str2);
    
    if(size1 < size2)
        return 1;
    else if(size1 > size2)
        return -1;
    
    while(*(str1) || *(str2)) {
        if(*(str1)) {
            str1++;
            sumStr1 += *str1;
        }
        if(*(str2)) {
            str2++;
            sumStr2 += *str2;
        }
    }
    
    if(sumStr1 > sumStr2)
        return -1;
    else if(sumStr1 < sumStr2)
        return 1;
    else
        return 0;
}
```

### To Lower:

```c
bool toLower(char str[]) {
    int diff = 'a' - 'A';
    while(*(str)) {
        if(*str >= 'A' && *str <= 'Z') {
            *str += diff;
        }
        str++;
    }
    return true;
}
```

### String Concatenation:

```c
bool str_concatenate(char str1[], char str2[], int size_str1) {
    int str1Length = str_length(str1), str2Length = str_length(str2);
    if(str1Length + str2Length > size_str1) 
        return false;
    
    str1 += str1Length;
    
    while(*(str2)) {
        *(str1) = *(str2);
        str1++;
        str2++;
    }
    *(str1) = '\0';  // Note: should be '\0', not '/0'
    return true;
}
```

### String Copy:

```c
bool str_copy(char str1[], char str2[], int size_str2) {
    int str1Length = str_length(str1);
    if(str1Length > size_str2) 
        return false;
    
    while(*(str1)) {
        *(str2) = *(str1);
        str1++;
        str2++;
    }
    *(str2) = '\0';  // Note: should be '\0', not '/0'
    return true;
}
```

---

## String Operations (C++)

**📝 Remember:** Always check for null when dealing with pointers.

```cpp
#include <string>

string str = "Hello";
str += " World";           // Concatenation
str.length();              // Get length
str.substr(0, 5);          // Substring
str.find("World");         // Find substring
str.replace(0, 5, "Hi");   // Replace
```

---

## Type Categories

| Type | C | C++ | Description |
|------|---|-----|-------------|
| **Array** | ✅ | ✅ | Fixed-size collection of elements |
| **Pointer** | ✅ | ✅ | Holds memory address |
| **Reference** | ❌ | ✅ | Alias to another variable |
| **Struct** | ✅ | ✅ | Group of variables |
| **Union** | ✅ | ✅ | Same memory for multiple types |
| **Enum** | ✅ | ✅ | Named integral constants |
| **Class** | ❌ | ✅ | Encapsulates data + functions |

---

## Structs

### Without typedef:

```c
struct Student {
    char name[50];
    int age;
};

struct Student s1;  // Must use 'struct' keyword
```

### With typedef:

```c
typedef struct {
    char name[50];
    int age;
} Student;

Student s1;  // No need to write 'struct' keyword
```

### Self-Referential Structs:

**❌ Cannot have:** An instance of struct inside struct
**✅ Can have:** A struct pointer inside struct

```c
typedef struct Student Student;

struct Student {
    char name[50];
    int age;
    Student *next;  // ✅ Pointer is allowed
    // Student s;   // ❌ Instance not allowed
};

Student s1;
```

---

## Union

A union stores different data types in the **same memory location**. At any time, only **one member** is active. All members share the same starting memory address.

### Example:

```c
#include <stdio.h>
#include <string.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data d;
    
    d.i = 10;
    printf("d.i = %d\n", d.i);        // ✅ OK
    
    d.f = 220.5f;
    printf("d.f = %f\n", d.f);        // ✅ OK
    printf("d.i = %d\n", d.i);        // ⚠️ Garbage! (i is corrupted)
    
    strcpy(d.str, "Hello");
    printf("d.str = %s\n", d.str);    // ✅ OK
    // d.f and d.i are now garbage
    
    return 0;
}
```

**Size of union:** Equal to the size of its largest member.

---

## Functions

### Arrays are Passed by Address:

```c
void modify(int arr[], int size) {
    arr[0] = 100;  // Modifies original array
}
```

### Functions Cannot Return More Than One Value:

#### ❌ Invalid - Won't Compile:

```c
int[5] get_array() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // ❌ Error: function cannot return array
}
```

#### ❌ Dangerous - Returns Pointer to Local Memory:

```c
int* get_array() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // ❌ Array is destroyed when function exits
}
```

### ✅ Correct Ways to Return Arrays:

#### Method 1: Use Static (Shared State):

```c
int* get_array() {
    static int arr[5] = {1, 2, 3, 4, 5};  // Lives forever
    return arr;
}
```

⚠️ **Warning:** Dangerous in multithreaded code.

#### Method 2: Pass Pointer to Caller's Buffer (Most Common):

```c
void fill_array(int* arr, size_t size) {
    for(size_t i = 0; i < size; i++) {
        arr[i] = i;
    }
}
```

#### Method 3: Allocate on Heap (Caller Must Free):

```c
int* create_array(size_t size) {
    int* arr = malloc(size * sizeof(int));
    if(arr) {
        for(size_t i = 0; i < size; i++) {
            arr[i] = i;
        }
    }
    return arr;  // ✅ Valid - heap memory persists
}
```

#### Method 4: Wrap Array in Struct:

```c
struct Array {
    int data[5];
};

struct Array get_array() {
    struct Array a = {{1, 2, 3, 4, 5}};
    return a;  // ✅ Returns by value
}
```

### TLDR - Methods to Return Multiple Values:

1. **Global array** (not recommended)
2. **Pass pointer to caller's buffer** (most common, safe)
3. **Return pointer to static array** (shared state - dangerous in multithreaded)
4. **Wrap array in struct** (safe, fixed size)
5. **Allocate on heap with malloc** (caller must free)

---

## Polymorphism

### Static Polymorphism (OVERLOADING):

Resolved at **compile-time**.

```cpp
void add(int x = 10, int y = 10) {
    cout << "Int: " << x + y << endl;
}

void add(float x = 10.0f, float y = 10.0f) {
    cout << "Float: " << x + y << endl;
}

int main() {
    add(10, 20);         // Output: Int: 30
    add(10.5, 20.4);     // ❌ Error: ambiguous (use 10.5f for float)
    add(10.5f, 20.4f);   // Output: Float: 30.9
}
```

### Dynamic Polymorphism (OVERRIDING):

Resolved at **runtime**. The method that gets executed is determined at runtime.

#### Java Example:

```java
class Animal {
    void speak() {
        System.out.println("Animal makes a sound");
    }
}

class Dog extends Animal {
    @Override
    void speak() {
        System.out.println("Dog barks");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal a = new Dog();  // Base reference, child object
        a.speak();             // Calls Dog's speak()
    }
}
```

#### C++ Example:

**⚠️ Important:** C++ uses **static binding by default**. Without `virtual`, the method call is decided at compile time based on the pointer type, not the object type.

```cpp
class Animal {
public:
    virtual void speak() {  // ⚠️ Must use 'virtual'
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog barks" << endl;
    }
};

int main() {
    Animal* a = new Dog();
    a->speak();  // ✅ Calls Dog's speak() (with virtual)
                 // ❌ Would call Animal's speak() (without virtual)
}
```

### @Override (Java) vs override (C++):

Used to tell the compiler that a method is meant to override a superclass method. Highly recommended!

**Benefits:**
- Compiler error if you try to override a function that shouldn't be overridden
- Makes code more readable and maintainable

### final Keyword:

#### Prevent Function Override:

```cpp
class Animal {
public:
    virtual void speak() final {
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal {
    void speak() override {  // ❌ Compiler error
        cout << "Dog barks" << endl;
    }
};
```

#### Prevent Class Inheritance:

```cpp
class Animal final {
    // ...
};

class Dog : public Animal {  // ❌ Compiler error
    // ...
};
```

---

## Abstract Class

An **abstract class** is a class that cannot be instantiated and is used as a base class for other classes.

```cpp
class Animal {
public:
    virtual void speak() = 0;  // Pure virtual function
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog barks" << endl;
    }
};

int main() {
    // Animal a;  // ❌ Error: cannot instantiate abstract class
    Dog d;        // ✅ OK
    d.speak();
}
```

**Pure Virtual Function:** `virtual fun() = 0`
- Must be implemented in derived classes
- Makes the class abstract

---

## Multiple Inheritance and the Diamond Problem

### The Diamond Problem:

```cpp
class A {
public:
    int x;
};

class B : public A {};
class C : public A {};

class D : public B, public C {};  // Diamond problem!

int main() {
    D obj;
    // obj.x = 10;  // ❌ Error: x is ambiguous (from B::A or C::A?)
}
```

**Problem:** `D` contains two copies of `A`, so `x` is ambiguous.

### Solution - Virtual Inheritance:

```cpp
class A {
public:
    int x;
};

class B : virtual public A {};  // ✅ Virtual inheritance
class C : virtual public A {};  // ✅ Virtual inheritance

class D : public B, public C {};

int main() {
    D obj;
    obj.x = 10;  // ✅ OK: only one copy of A
}
```

**Virtual inheritance** ensures only one copy of the base class is inherited.

---

## Side Notes

### typedef for Pointers:

```c
typedef int* IntPtr;

int main() {
    int a = 10;
    IntPtr p = &a;  // Same as: int* p = &a;
    printf("%d", *p);
    return 0;
}
```

### typedef for Function Pointers:

```c
typedef int (*Operation)(int, int);

int add(int a, int b) { 
    return a + b; 
}

int main() {
    Operation op = add;
    printf("%d", op(5, 3));  // Output: 8
    return 0;
}
```

### typedef vs #define for Pointers:

```c
typedef int* ptr;
#define ptr2 int*

int main() {
    ptr p, p1;      // p, p1 → both pointers to int
    ptr2 p2, p3;    // p2 → pointer, p3 → integer ⚠️
}
```

**Rule:** Same number of `[]` = same number of `*`

### Pointer Sizes:

All pointers have the same size (typically 4 or 8 bytes depending on architecture). The difference is in the **size of the jump** when doing pointer arithmetic.

### Fraction Literals:

Fraction literals are by default `double`.

```c
float x = 3.14;   // ⚠️ Actually a double, then converted to float
float y = 3.14f;  // ✅ Float literal
```

---

## Common Problems

### Unsigned Char Loop Problem:

```c
// ⚠️ This loop never ends!
for (unsigned char i = 5; i >= 0; i--) {
    // When i = 0, i-- wraps to 255
    // Condition i >= 0 is always true for unsigned
}
```

**Solution:** Use signed type or different loop condition.

### typedef for Cross-Platform Compatibility:

`typedef` is used to create generic fixed data sizes to solve the change in data types across machines.

```c
typedef long int u16;  // Define fixed-size type

// Better: use stdint.h
#include <stdint.h>
uint16_t value;  // Guaranteed 16-bit unsigned integer
int32_t number;  // Guaranteed 32-bit signed integer
```

---

## Summary Table

### Key Differences:

| Feature | C | C++ |
|---------|---|-----|
| **Type Safety** | Weaker | Stronger |
| **Casts** | C-style `(type)` | `static_cast<type>()`, etc. |
| **Strings** | `char[]` | `string` class |
| **Memory** | `malloc/free` | `new/delete` |
| **I/O** | `printf/scanf` | `cin/cout` |
| **OOP** | Structs only | Classes + inheritance |
| **References** | ❌ | ✅ |
| **Function Overloading** | ❌ | ✅ |
| **Default Arguments** | ❌ | ✅ |
| **Namespaces** | ❌ | ✅ |

---

## Best Practices

✅ **Do:**
- Always initialize pointers
- Use `nullptr` instead of `NULL` in C++
- Use C++ casts (`static_cast`, etc.) over C-style casts
- Free/delete dynamically allocated memory
- Use `const` when possible
- Check return values of `malloc/new`
- Use references when you don't need null or rebinding

❌ **Don't:**
- Return pointers to local variables
- Mix `malloc/free` with `new/delete`
- Ignore compiler warnings
- Use magic numbers (use `#define` or `const`)
- Forget null terminators in C-strings
- Use uninitialized variables

---

## Memory Management Checklist

| Allocation | Deallocation | Notes |
|------------|--------------|-------|
| `malloc()` | `free()` | C-style, uninitialized |
| `calloc()` | `free()` | C-style, zero-initialized |
| `realloc()` | `free()` | Resize allocation |
| `new` | `delete` | C++, single object |
| `new[]` | `delete[]` | C++, array |

**Golden Rule:** Every allocation must have exactly one corresponding deallocation!