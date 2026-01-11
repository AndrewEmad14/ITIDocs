# Personal Java Notes

## Main Boilerplate

```java
class MyClass {
    public static void main(String args[]) {
        // your code here
    }
}
```

---

## Naming Conventions

### Don't Use:
- Can't start with a number
- Single underscore only
- `-` (hyphen)
- `@` (at sign)
- `.` (period)
- `/` (forward slash)
- `#` (hash)

---

## Command Line Arguments (args[])

Arguments that the main function takes are separated by space delimiter.

```java
// Access arguments through args[i]
String firstArg = args[0];
```

**⚠️ Warning:** The `args` array may be empty, so always check the size using `.length`

---

## Weird Modifiers

| Modifier | Description |
|----------|-------------|
| `native` | Marks a method whose implementation is written in non-Java code (usually C/C++) via JNI. Cannot be both abstract and native. |
| `transient` | Prevents a field from being serialized. Used for security or derived data. |
| `volatile` | Ensures visibility of variable changes across threads. Reads always get the latest written value (visibility only). |
| `synchronized` | Provides mutual exclusion and thread safety (atomicity + visibility). |

---

## Taking Input

```java
import java.util.Scanner;

Scanner scan = new Scanner(System.in);
// ... use scanner
scan.close(); // ⚠️ Warning: closing System.in scanner denies any more input
              // since InputStream is static and shared across the application
```

---

## Data Types

- **Integers:** `byte`, `short`, `int`, `long` - for whole-valued signed numbers
- **Floating-point:** `float`, `double` - numbers with fractional precision
- **Characters:** `char` - represents symbols in a character set
- **Boolean:** `boolean` - represents true/false values

---

## Displaying Output

```java
System.out.println("Hello World");
```

---

## Widening and Narrowing

**📝 Note:** This only works on primitive types, not on wrappers.

### Widening (Implicit)
```java
int x = 5;
double y = x; // ✅ Automatic conversion
```

### Narrowing (Explicit Casting Required)
```java
double x = 4.3;
int y = (int) x; // ⚠️ Must cast explicitly
```

**⚠️ Important:** `char` and `boolean` aren't compatible with numeric types.

---

## instanceof Operator

The `instanceof` operator determines the type of class at **runtime**.

```java
String s = "Hello";
boolean result = s instanceof String; // true

Animal a = new Cat();
System.out.println(a instanceof Cat);    // runtime → true
System.out.println(a instanceof Animal); // runtime → true

Animal a2 = new Animal();
System.out.println(a2 instanceof Cat);   // false

Animal a3 = null;
System.out.println(a3 instanceof Animal); // false
```

---

## Java Constructor

Same as C++, Java provides a default constructor if none is defined.

---

## Variable Initialization in Class

Can be done in the same line as declaration, unlike C.

```java
class Example {
    private int count = 0; // ✅ Initialized at declaration
    private String name = "Default";
}
```

---

## Free Floating Blocks

```java
class FreeBlocksExample {
    
    static { // Static initialization block
        System.out.println("Static block - runs once when class loads");
    }
    
    { // Instance initialization block
        System.out.println("Instance block - runs before every constructor");
    }
    
    public FreeBlocksExample() {
        System.out.println("Constructor");
    }
}
```

---

## Interface

An interface specifies **what must be done**, not how to do it.

### Key Points:
- Syntactically similar to an abstract class
- One class can implement any number of interfaces
- Variables in interfaces are implicitly `public`, `static`, and `final`
- Methods are implicitly `public` and `abstract`

### Default Methods (JDK 8+)

```java
interface InterfaceA {
    void saySomething(); // Abstract method
    
    default void sayHi() { // Default implementation
        System.out.println("Hi");
    }
}
```

You can:
- Override the default method with your own implementation
- Make it abstract again by re-declaring it

### Static Methods in Interfaces

```java
interface MyInterface {
    static void staticMethod() {
        System.out.println("Static method in interface");
    }
}

// Call directly: MyInterface.staticMethod();
```

**Difference from default:** You don't need a class instance; use the interface directly.

### Private Methods (JDK 9+)

```java
interface MyInterface {
    default void publicMethod() {
        privateHelper(); // ✅ Can call private method
    }
    
    private void privateHelper() {
        System.out.println("Private helper method");
    }
}
```

**Restrictions:**
- Can only be called by default or other private methods in the same interface
- Not accessible by sub-interfaces or implementing classes

### @Override Annotation

```java
class Animal {
    void makeSound() {
        System.out.println("Some sound");
    }
}

class Dog extends Animal {
    @Override
    void makeSound() { // Compiler verifies this overrides a superclass method
        System.out.println("Bark");
    }
}
```

### ⚠️ Important Notes:
- **CANNOT** reduce visibility (e.g., implementing as `private`)
- **CANNOT** make it `static` (interface methods are instance methods by design)
- **CAN** make it `final` to prevent overriding

---

## Callbacks / Lambda

### 1. Define Callback Interface

```java
interface Callback {
    void onComplete(String result);
    void onError(String error);
}
```

### 2. Class Using Callback

```java
class DataFetcher {
    public void fetchData(Callback callback) {
        try {
            Thread.sleep(1000);
            String data = "Data from server";
            callback.onComplete(data); // Call back when done
        } catch (Exception e) {
            callback.onError(e.getMessage());
        }
    }
}
```

### 3. Using the Callback

```java
public class Main {
    public static void main(String[] args) {
        DataFetcher fetcher = new DataFetcher();
        
        // Anonymous class implementation
        fetcher.fetchData(new Callback() {
            @Override
            public void onComplete(String result) {
                System.out.println("Success: " + result);
            }
            
            @Override
            public void onError(String error) {
                System.out.println("Error: " + error);
            }
        });
    }
}
```

---

## Method Reference

Allows you to use a method as a value: `Reference::methodName`

### Example - All Three Are Equivalent:

```java
// 1. Anonymous class
File fObj = new File(".");
File[] directories = fObj.listFiles(new FileFilter() {
    public boolean accept(File file) {
        return file.isDirectory();
    }
});

// 2. Lambda
File[] directories = fObj.listFiles((file) -> file.isDirectory());

// 3. Method reference
File[] directories = new File(".").listFiles(File::isDirectory);
```

---

## Functional Interface

Also called **Single Abstract Method (SAM) Interfaces** - only one abstract method allowed.

```java
@FunctionalInterface // Annotation ensures only one abstract method
interface MyFunction {
    void execute();
}
```

---

## Inner Classes

### Why Use Inner Classes?
1. Logical grouping of classes that are only used in one place
2. Increases encapsulation
3. More readable and maintainable code

### 1. Non-static (Member) Inner Class

- Defined as a non-static member of the outer class
- Has access to all members (even private) of the outer class
- Outer class has access to all private members of the inner class
- Must be instantiated within the context of an outer class instance

```java
class Outer {
    private int x = 10;
    
    class Inner {
        void print() {
            System.out.println(x); // ✅ Can access outer's private members
        }
    }
}

// Usage:
Outer outer = new Outer();
Outer.Inner inner = outer.new Inner(); // Note: needs outer instance
```

### 2. Static Nested Class

- Declared with `static` keyword
- Does NOT have access to outer instance members (only static ones)
- Does NOT require an instance of the outer class

```java
class Outer {
    static int y = 20;
    
    static class Nested {
        void print() {
            System.out.println(y); // ✅ Only static members
        }
    }
}

// Usage:
Outer.Nested n = new Outer.Nested(); // No outer instance needed!
```

### 3. Local Inner Class

- Defined inside a method
- Can only be used within that method
- Can access final or effectively final local variables

```java
void method() {
    final int z = 30;
    
    class Local {
        void print() {
            System.out.println(z); // ✅ z is effectively final
        }
    }
    
    Local l = new Local();
}
```

### 4. Anonymous Inner Class

- Has no name; defined and instantiated in one line
- Often used for implementing interfaces or extending classes on the fly

```java
Runnable r = new Runnable() {
    public void run() {
        System.out.println("Running!");
    }
};

// Or with lambda (modern alternative for functional interfaces):
Runnable r2 = () -> System.out.println("Running!");
```

**📝 Note:** When you compile, two class files will be produced:
- `MyClass.class`
- `MyClass$MyInnerClass.class`

---

## Wrapper Classes

### Three Reasons to Use Wrapper Classes:

1. As an argument of a method that expects an object
2. To use constants defined by the class (e.g., `MIN_VALUE`, `MAX_VALUE`)
3. To use class methods for:
   - Converting values to and from other primitive types
   - Converting to and from strings
   - Converting between number systems (decimal, octal, hexadecimal, binary)

### Common Wrappers:

| Primitive | Wrapper Class |
|-----------|---------------|
| `int` | `Integer` |
| `double` | `Double` |
| `boolean` | `Boolean` |
| `char` | `Character` |

### Autoboxing and Unboxing

- **Autoboxing:** Automatic conversion from a primitive to its wrapper class
- **Unboxing:** Automatic conversion from a wrapper class to its primitive type

```java
Integer x = 5;        // Autoboxing: int → Integer
int y = x;            // Unboxing: Integer → int
```

**⚠️ Important:** Autoboxing happens on values, not on types.

**📝 Note:** Collections and Generics work only with wrappers, not primitives.

---

## String

Strings are **immutable** - their values cannot be changed after they are created.

### What happens when you do `x += "hi"`?

```java
x = new String(oldString + "hi"); // Creates a new String object
```

### String Pool

String literals are stored in a **String Pool** for memory optimization.

```java
String a = "hi";
String b = "hi";
// Both a and b point to the same location in memory (String Pool)
```

### intern() Method

Use `.intern()` to check if the string already exists in the String Pool.

```java
class Example {
    public static void main(String[] args) {
        // S1 refers to object in the Heap Area
        String s1 = new String("GFG");
        
        // S2 refers to object in the SCP Area
        String s2 = s1.intern();
        
        // Comparing memory locations
        System.out.println(s1 == s2);        // false
        
        // Comparing values
        System.out.println(s1.equals(s2));   // true
        
        // S3 refers to object in the SCP Area
        String s3 = "GFG";
        
        // Comparing s2 and s3 in SCP
        System.out.println(s2 == s3);        // true
    }
}
```

### ⚠️ VIP NOTE:
**Don't use `==` when comparing strings** as it compares addresses, not actual content. Use `.equals()` instead!

```java
String a = "hello";
String b = "hello";

a == b;         // ⚠️ Compares memory addresses
a.equals(b);    // ✅ Compares content
```

---

## StringBuilder

- **Mutable** sequence of characters
- **Faster** than String for concatenation
- **Not thread-safe**

```java
StringBuilder sb = new StringBuilder("Hello");
sb.append(" World");  // ✅ Modifies in place, no new object created
System.out.println(sb.toString());
```

### Key Points:
- Use `append()` to benefit from speed, not `+` (which converts to String)
- Remember to use `.toString()` when passing to ensure immutability
- Uses a fixed-size char array and increases capacity when exceeded

**⚠️ Warning:** Not thread-safe. For multi-threaded environments, use `StringBuffer`.

---

## StringBuffer

- **Thread-safe**, mutable sequence of characters
- **Slower** than StringBuilder due to synchronization
- Methods are synchronized for thread safety

```java
StringBuffer sb = new StringBuffer("Hello");
sb.append(" World");  // Thread-safe operation
```

### When to Use:
- Use `StringBuilder` for single-threaded operations (faster)
- Use `StringBuffer` for multi-threaded operations (thread-safe)

---

## Covariance vs Invariance

### Covariance

If `Rectangle` is a subtype of `Shape`, then `Container<Rectangle>` is considered a subtype of `Container<Shape>`.

**Example - Arrays are Covariant:**

```java
Rectangle[] rectangles = new Rectangle[5];
Shape[] shapes = rectangles; // ✅ This works! Arrays are covariant
shapes[0] = new Circle();    // 💥 RUNTIME ERROR: ArrayStoreException!
```

### Invariance

If `Rectangle` is a subtype of `Shape`, `Container<Rectangle>` is NOT considered a subtype of `Container<Shape>`.

**Example - Generics are Invariant:**

```java
ArrayList<Rectangle> rectangles = new ArrayList<>();
ArrayList<Shape> shapes = rectangles; // ❌ COMPILATION ERROR: Generics are invariant
```

---

## Generics

### Template vs Generic:

| C++ Templates | Java Generics |
|---------------|---------------|
| Code generation at compile-time | Type erasure with compile-time type checking |
| Generate separate code for each type | Single compiled class for all type parameters |
| True parametric polymorphism | Types checked at compile-time but erased to Object at runtime |
| - | Must use wrappers, no primitive types |

### Why Not Use Object and Skip Generics?

Generics allow the compiler to type check at **compile-time**. If we use Object, the crash happens at **runtime**.

### Wildcard Types:

#### a. Unbounded:
```java
public void printList(List<?> list) { ... }
```

#### b. Upper Bounded:
```java
public void processNumbers(List<? extends Number> list) { ... }
```

#### c. Lower Bounded:
```java
public void addIntegers(List<? super Integer> list) { ... }
```

### Generic Methods:

```java
public <T> T getFirst(List<T> list) {
    return list.get(0);
}

// Usage:
List<String> strings = Arrays.asList("a", "b");
String first = getFirst(strings); // T is String
```

### When to Use:

- **Use Generic Type Parameters (T):** Return the same specific type, preserve type information, work with specific subtype methods
- **Use Wildcards (?):** Only reading data, don't care about specific type

### Important Notes:

- You can't have a static instance with type `T` (generics are instance-specific)
- Use `T extends Comparable<T>` when you need to compare

---

## Wildcards vs Generics

### With T - You Can READ and WRITE:

```java
public <T> void addAndGet(List<T> list, T item) {
    list.add(item);           // ✅ Can write
    T retrieved = list.get(0); // ✅ Can read
}
```

### With ? - You Can Only READ (as Object):

```java
public void process(List<?> list) {
    list.add("something");    // ❌ Error! Don't know what type the list holds
    Object item = list.get(0); // ✅ Can only read as Object
}
```

---

## Stream API (Java 8+)

A Stream is **not a data structure** - it's a pipeline for processing data.

### Key Concepts:
- Get data from a source (collection, array, etc.)
- Apply operations (filter, map, sort, etc.)
- Produce a result (collect, count, find, etc.)
- Supports parallelism
- **Intermediate operations are lazy** - they aren't performed until a terminal operation is invoked

### Intermediate Operations (Return a Stream):

```java
filter(Predicate<T>)              // Filters elements based on condition
map(Function<T, R>)               // Transforms each element
flatMap(Function<T, Stream<R>>)   // Flattens nested streams
peek(Consumer<T>)                 // Performs action without modifying stream
sorted(Comparator<T>)             // Sorts elements
distinct()                        // Removes duplicates
limit(long)                       // Truncates stream
skip(long)                        // Skips elements
```

### Terminal Operations (Produce a Result):

```java
forEach(Consumer<T>)              // Performs action on each element
forEachOrdered(Consumer<T>)       // forEach but maintains order
reduce(BinaryOperator<T>)         // Combines elements into single result
collect(Collector<T, A, R>)       // Collects into collection/map
anyMatch(Predicate<T>)            // Checks if any element matches
allMatch(Predicate<T>)            // Checks if all elements match
noneMatch(Predicate<T>)           // Checks if no elements match
findFirst()                       // Finds first element
findAny()                         // Finds any element (non-deterministic in parallel)
min(Comparator<T>)                // Finds minimum
max(Comparator<T>)                // Finds maximum
count()                           // Counts elements
```

### Example - Lazy Evaluation:

```java
List<String> names = Arrays.asList("Alice", "Bob", "Charlie", "David");

// These intermediate operations DON'T execute yet
Stream<String> stream = names.stream()
    .filter(name -> {
        System.out.println("Filtering: " + name);
        return name.length() > 3;
    })
    .map(name -> {
        System.out.println("Mapping: " + name);
        return name.toUpperCase();
    });

System.out.println("Stream created, but nothing printed yet!");
System.out.println("Now calling terminal operation...");

// Terminal operation triggers execution
stream.forEach(System.out::println);
```

**Output:**
```
Stream created, but nothing printed yet!
Now calling terminal operation...
Filtering: Alice
Mapping: Alice
ALICE
Filtering: Bob
Filtering: Charlie
Mapping: Charlie
CHARLIE
Filtering: David
Mapping: David
DAVID
```

### Parallel Streams:

A parallel stream splits elements into multiple chunks, processing each chunk with a different thread.

```java
List<String> names = Arrays.asList("Alice", "Bob", "Charlie");
names.parallelStream()
     .filter(name -> name.length() > 3)
     .forEach(System.out::println);
```

**⚠️ Note:** `findAny()` is non-deterministic in parallel streams.

---

## Other Higher-Order Function Methods

### Collection Methods (Java 8+):

```java
forEach(Consumer<T>)              // Iterates over collection
removeIf(Predicate<T>)            // Removes elements matching predicate
replaceAll(UnaryOperator<T>)      // Replaces all elements (List)
```

### Map Methods (Java 8+):

```java
forEach(BiConsumer<K, V>)                    // Iterates over key-value pairs
compute(K, BiFunction<K, V, V>)              // Computes new value
computeIfAbsent(K, Function<K, V>)           // Computes if key absent
computeIfPresent(K, BiFunction<K, V, V>)     // Computes if key present
merge(K, V, BiFunction<V, V, V>)             // Merges values
replaceAll(BiFunction<K, V, V>)              // Replaces all values
```

### Optional Methods (Java 8+):

```java
map(Function<T, R>)                          // Transforms value if present
flatMap(Function<T, Optional<R>>)            // Flattens nested Optionals
filter(Predicate<T>)                         // Filters based on condition
ifPresent(Consumer<T>)                       // Executes if value present
ifPresentOrElse(Consumer<T>, Runnable)       // Executes with fallback
or(Supplier<Optional<T>>)                    // Provides alternative Optional
```

---

## Parallelism vs Concurrency

### Concurrency (Single Core):
```
Single core CPU switching between tasks:

Time →
Task A: ████░░░░████░░░░████
Task B: ░░░░████░░░░████░░░░

Tasks take turns, but don't run at the same time
```

### Parallelism (Multi-Core):
```
Multi-core CPU running tasks simultaneously:

Core 1: ████████████████████  Task A
Core 2: ████████████████████  Task B

Both tasks run at the exact same time
```

---

## Exceptions

### RuntimeException (Unchecked)

A runtime exception happens due to a programming error. These exceptions are not checked at compile-time but at run-time.

### Common Runtime Exceptions:

**Null and Reference Issues:**
- `NullPointerException` - Attempting to use a null reference
- `ClassCastException` - Invalid casting between types

**Array Issues:**
- `ArrayIndexOutOfBoundsException` - Accessing invalid array index
- `NegativeArraySizeException` - Creating array with negative size

**Arithmetic Issues:**
- `ArithmeticException` - Illegal arithmetic operation (e.g., division by zero)

**Illegal Arguments:**
- `IllegalArgumentException` - Method receives inappropriate argument
- `NumberFormatException` - Failed string-to-number conversion
- `IllegalStateException` - Method called at inappropriate time

**Unsupported Operations:**
- `UnsupportedOperationException` - Requested operation not supported

**Security:**
- `SecurityException` - Security manager denies access

**Concurrency:**
- `IllegalMonitorStateException` - Illegal monitor operation
- `ConcurrentModificationException` - Concurrent modification detected

### Creating Custom Exceptions

#### 1. Extend from Exception Class:

```java
class MyException extends Exception {
    MyException() {
        super("YO I AM A NEW EXCEPTION");
    }
    
    MyException(String message) {
        super(message);
    }
}
```

#### 2. Using Your Exception:

```java
public void checkTrue(Boolean test) throws MyException {
    if (test) {
        System.out.println("Successful");
    } else {
        throw new MyException("Failed");
    }
}
```

### Available Super Constructors:

```java
Exception()                              // No arguments
Exception(String message)                 // With a message
Exception(String message, Throwable cause) // With message and cause
Exception(Throwable cause)                // With just a cause
```

### Exception Handling Best Practices:

**General Rule:** Catch exceptions you know how to handle and propagate those you don't.

### Rethrowing and Chaining Exceptions:

```java
try {
    // call a method to access the database
} catch (SQLException e) {
    Throwable se = new ServletException("database error");
    se.initCause(e);
    throw se;
}
```

This wrapping technique allows you to throw high-level exceptions without losing details of the original failure.

### Finally Block:

`finally` executes code whether an error is thrown or not.

```java
try {
    // risky code
} catch (Exception e) {
    // handle exception
} finally {
    // always executes
}
```

**⚠️ CAUTION:** A finally clause can yield unexpected results when it contains return statements.

### Try-with-Resources:

```java
try (Resource res = new Resource()) {
    // work with res
} // res.close() is called automatically
```

### Exception Handling Notes:

1. If several methods throw different exceptions:
   - Write separate try-catch blocks for each method
   - Put them all in the same try block with multiple catch blocks
   - Catch the parent `Exception` class

2. When writing multiple catch blocks:
   - Must not handle a parent exception before a child exception
   - The compiler will give an error if you attempt to do so

3. When overriding methods that throw exceptions:
   - You may throw the same exception
   - You may throw a subclass of the exception
   - You may decide not to throw an exception at all
   - You **CANNOT** throw different exceptions other than those declared in the original method

---

## Try-with-Resources

### Key Points:

- Implements `AutoCloseable` interface
- Closing happens in **reverse order**
- The `close()` checked exception is suppressed
- Neither `catch` nor `finally` are required
- The close exception doesn't have to throw a checked exception

```java
try (FileReader fr = new FileReader("file.txt");
     BufferedReader br = new BufferedReader(fr)) {
    // Use resources
} // Automatically closes br, then fr
```

---

## Iterator

### iterator() - For Naturally Ordered Data Structures:

```java
Collection<String> c = ...;
Iterator<String> iter = c.iterator();

while (iter.hasNext()) {
    String element = iter.next();
    // do something with element
}
```

### listIterator() - For Linked Lists:

```java
ListIterator<String> iter = staff.listIterator();
```

### Concurrent Modification:

If an iterator finds that its collection has been modified by another iterator or by a method of the collection itself, it throws a `ConcurrentModificationException`.

**Rule to avoid concurrent modification exceptions:**
- You can attach as many iterators to a collection as you like, provided that all of them are **only readers**
- Alternatively, you can attach a single iterator that can both **read and write**

### Useful Map Methods:

```java
Map<String, Integer> scores = ...;

// Gets 0 if the id is not present
int score = scores.getOrDefault(id, 0);

// Put if absent
counts.putIfAbsent(word, 0);
counts.put(word, counts.get(word) + 1);

// Or use merge
counts.merge(word, 1, Integer::sum);
```

---

## Sorting

The `sort` method in the Collections class sorts a collection that implements the List interface.

```java
List<String> staff = new LinkedList<>();
// fill collection
Collections.sort(staff);
```

This method assumes that the list elements implement the `Comparable` interface.

### Custom Sorting:

```java
// Using List.sort() with a Comparator
staff.sort(Comparator.comparing(String::length));

// Or using Collections.sort()
Collections.sort(staff, (s1, s2) -> s1.length() - s2.length());
```

---

## Threads

### Two Ways to Work with Threads:

1. **Extending class Thread**
2. **Implementing Runnable Interface**

### Methods:

**Class Thread:**
- `start()`
- `run()`
- `sleep()`
- `suspend()` *
- `resume()` *
- `stop()` *

**Class Object:**
- `wait()`
- `notify()`
- `notifyAll()`

### Extending the Thread Class:

**Pros:**
- Easier to implement
- Each object is separated from other threads

**Cons:**
- Your class can no longer extend any other class

```java
class MyThread extends Thread {
    public void run() {
        System.out.println("Thread running");
    }
}

// Usage:
MyThread t = new MyThread();
t.start();
```

### Implementing Runnable:

**Pros:**
- Your class can still extend other classes
- An object from an implemented Runnable can be shared among many threads
- More flexible - can be passed to executor services

**Cons:**
- May take more work

```java
class MyRunnable implements Runnable {
    public void run() {
        System.out.println("Thread running");
    }
}

// Usage:
Thread t = new Thread(new MyRunnable());
t.start();
```

---

## Miscellaneous

### Data Access Object (DAO)

A design pattern for abstracting database access.

### Object Storage

All objects are stored by reference in the **heap**.

### Serializable

An object's state can be converted into a format (like a stream of bytes) so it can be:
- Saved to a file or database
- Sent over a network
- Passed between different programming environments

### Java History

- Created by **Sun Microsystems**
- Team led by **James Gosling**
- Java Applet: A special kind of Java program designed to be transmitted over the Internet and automatically executed inside a Java-compatible web browser

### Java Virtual Machine (JVM)

- Java programs run on the JVM (interpreter)
- The output of a Java compiler is **bytecode**, not executable code
- Java also supports **Remote Method Invocation (RMI)**

### Main Method

The keyword `static` allows `main()` to be called without having to instantiate a particular instance of the class. This is necessary since `main()` is called by the JVM before any objects are made.

```java
public static void main(String[] args) {
    // Entry point
}
```

### Data Type Sizes

- `char` in Java is **2 bytes** (supports Unicode)

### Operators

Unary operators return the same data type.

### Functional Interfaces

- `IntUnaryOperator` is a pre-built interface that takes an integer

### Generics Rules

- `super` and `extends` work with the original class
  - Example: `T extends Animal` or `T super Animal` works with Animal

### Iterator

- You must call `next()` before calling `remove()` in an iterator

### Threads

Every program in Java has at least two threads:
1. The **main thread** of the program
2. The **garbage collector thread**

### Switch Case

- Switch case can only work with **constant values**

```java
switch(variable) {
    case CONSTANT_VALUE:
        // code
        break;
}
```

### Comparable Interface

When you wish for your class to be comparable:

1. Implement `Comparable<YourClassName>`
2. Override `compareTo()` method

```java
class Student implements Comparable<Student> {
    private int grade;
    
    @Override
    public int compareTo(Student other) {
        return this.grade - other.grade;
    }
}
```

### Type Promotions

`short` and `byte` are promoted to `int` in arithmetic operations.

```java
byte a = 10;
byte b = 20;
// byte c = a + b; // ❌ Error: Result is int
int c = a + b;     // ✅ Correct
```