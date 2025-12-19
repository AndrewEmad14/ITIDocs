# Personal Java notes

# main boilerplate

    class myClass{
        public static void main(String args[]){

            //your code here;

        }

    };

# Naming conventions

    the donts
        cant start with a number
        one underscore
        -
        @
        .
        /
        #

# args[]

    args are the arguments that the main function takes , the input is sperated by space delimeter
    you can then access said arguments through args[i]
    Beware though the args may be empty so you have to check for the size of the args using
    .length (an attribute for arrays that gives )

# Weird Modifiers

    Native : Marks a method whose implementation is written in non-Java code (usually C/C++) via JNI. Cannot be abstract and native together
    Transient : Prevents a field from being serialized.Used for security or derived data
    Volatile:Ensures visibility of variable changes across threads.	•	Reads always get the latest written value . visibility only
    Synchronized: Provides mutual exclusion and thread safety.atomicity + visiblity

# taking input

    java.util.Scanner
    Scanner scan= new(System.in);
    scan.close()    //be ware that closing a System.in scanner deny anymore input since
                    inputstream is static shared across the application

# Data Types

    • Integers: This group includes byte, short, int, and long, which
    are for whole-valued signed numbers.
    • Floating-point numbers: This group includes float and double,
    which represent numbers with fractional precision.
    • Characters: This group includes char, which represents
    symbols in a character set, like letters and numbers.
    • Boolean: This group includes boolean, which is a special type
    for representing true/false values.

# displaying output

    System.out.println();

# Widening And Narrowing

     Widening Happens implicitly
    int x=5;
    doble y=x;
    BUT Narrowing you have to cast explicitly
    double x=4.3
    int y=(int)x
    does
    char and boolean arent compatiable

# instanceof operator

    instanceof  operator to know the type of class that works in RUNTIME
    String s = "Hello";
    boolean result = s instanceof String;   // true

    Animal a = new Cat();
    System.out.println(a instanceof Cat);     // runtime → true
    System.out.println(a instanceof Animal); // runtime → true


    Animal a = new Animal();
    a instanceof Cat   // false

    Animal a = null;
    System.out.println(a instanceof Animal); // false

# java constructor

    same as c it provides a default constructor

# Variable initilization in class

    can be done in the same line as decleration unlike c

# Free Floating Block

    class FreeBlocksExample
    {

    static{ // Free Floating Block

    System.out.println("Free floating block");

    }

    { // Common code among all Constructors
    System.out.println("Common Construtor body");

    }
    public FreeBlocksExample(){

    System.out.println("Default constr");

    }

# interface

    An interface is syntactically similar to an abstract class, in that
    you can specify one or more methods that have no body.
    An interface specifies what must be done
    one class can implement any number of interfaces.
    Variables can be declared in an interface, but they are implicitly public,
    static, and final.
    To define a set of shared constants, create an interface that contains only
    these constants, without any methods.
    in jdk 8 you can have default implementation for methods

    interface InterfaceA {
        public void saySomething();
        default public void sayHi() {
        System.out.println("Hi");
        }
    }
    you can also overide the default method with your OWN default method
    OR you can make it ABSTRACT again by re declaring it
    @Override
        class Animal {
        void makeSound() {
            System.out.println("Some sound");
        }
        }

        class Dog extends Animal {
            @Override
            void makeSound() {  // Overrides the method in Animal
                System.out.println("Bark");
            }
        }
    @Override tells the compiler: “I intend for this method to override a superclass method.”
    If the superclass method doesn’t exist (or is incorrectly spelled), the compiler will throw an error.

    Static method in an interface

        same as static method in a class except you dont have to implement it

        what is the difference between it and the default? you dont need a class that implements the method you can use the instance directly

    Private interface methods:
        Beginning with JDK 9, an interface can include a private
        method.
        • A private interface method can be called only by a default
        method or another private method defined by the same
        interface.
        • Because a private interface method is specified private, it
        cannot be used by code outside the interface in which it is
        defined.
        • This restriction includes sub-interface because a private
        interface method is not accessible by a sub-interface.
    IMPORTANT NOTES
    by default methods in an interface are public and abstract
    YOU CANNOT reduce their visibility: for example implementing the method private
    YOU CANNOT make it static , because interface methods are instance methods by desgin
    YOU CAN make it final to stop other methods from overriding

# Call Back

     // 1. Define a callback interface
    interface Callback {
        void onComplete(String result);
        void onError(String error);
    }

    // 2. Class that performs async work and uses the callback
    class DataFetcher {
        public void fetchData(Callback callback) {
            // Simulate some work
            try {
                Thread.sleep(1000);
                String data = "Data from server";
                callback.onComplete(data);  // Call back when done
            } catch (Exception e) {
                callback.onError(e.getMessage());  // Call back on error
            }
        }
    }

    // 3. Using the callback
    public class Main {
        public static void main(String[] args) {
            DataFetcher fetcher = new DataFetcher();

            // Pass callback implementation
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

# Functional Interface

    These interfaces are  called Single Abstract Method
    interfaces (SAM Interfaces). //only one abstract method allowed
    @FunctionalInterface    //an anotation that insures the interface has only one
                              abstract function

# innerClass

    Why use inner class?
        1. It is a way of logically grouping classes that are only used in one place.
        2.It increases encapsulation.
        3. Nested classes can lead to more readable and maintainable code.
    1. Non-static (Member) Inner Class
        Defined as a non-static member of the outer class.
        Has access to all members (even private) of the outer class.
        AND the outer class has access to all private members of the inner class
        Must be instantiated within the context of an outer class instance.
            Example:
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
    2. Static Nested Class
        Declared with static keyword.
        Does NOT have access to outer instance members (only static ones).
        Does NOT require an instance of the outer class.
            Example:
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
    3. Local Inner Class
        Defined inside a method.
        Can only be used within that method.
        Can access final or effectively final local variables.
            Example:
                    void method() {
                        final int z = 30;
                        class Local {
                            void print() {
                                System.out.println(z); // ✅ z is effectively final
                            }
                        }
                        Local l = new Local();
                    }
    4. Anonymous Inner Class
        Has no name; defined and instantiated in one line.
        Often used for implementing interfaces or extending classes on the fly (e.g., event listeners).
            Example:
                                Runnable r = new Runnable() {
                public void run() {
                    System.out.println("Running!");
                }
            };
    When you compile the java file, two class files will be produced:
        MyClass.class
        MyClass$MyInnerClass.class
            // Or with lambda (modern alternative for functional interfaces):
            Runnable r2 = () -> System.out.println("Running!");

# Wrapper class

    There are three reasons that you might use a wrapper class
    rather than a primitive:
    1. As an argument of a method that expects an object.
    2. To use constants defined by the class,
    • such as MIN_VALUE and MAX_VALUE, that provide the upper and lower
    bounds of the data type.
    3. To use class methods for
    • converting values to and from other primitive types,
    • converting to and from strings,
    • converting between number systems (decimal, octal, hexadecimal, binary).

    int  -> Integer
    collections work only with wrappers
    Genereics   work only with wrappers
    Autoboxing : Automatic conversion from a primitive to its wrapper class.
    Unboxing: Automatic conversion from a wrapper class to its primitive type.
    IMPORTANT autoboxing happens on values, not on types

# String

    Strings are constant; their values cannot be changed after they are created
    what happens when you x+="hi"?
    x=new String(oldString+hi)
    String literals are put inside a stringpool for memory optimization
    Example:
    String a = "hi";
    String b= "hi";
    both b and a are pointing at the same place in the memory inside the string pool
    Note: you can use .intern() to check if the string already exsist in the string pool
    if you want to optomize the memory
    Example:
        // Java program to illustrate intern() method
        class GFG {
            public static void main(String[] args) {

                // S1 refers to object in the Heap Area
                String s1 = new String("GFG");

                // S2 refers to object in the SCP Area
                String s2 = s1.intern();

                // Comparing memory locations
                System.out.println(s1 == s2);   //true

                // Comparing values
                System.out.println(s1.equals(s2));  //true

                // S3 refers to object in the SCP Area
                String s3 = "GFG";

                // Comparing s2 and s3 in SCP
                System.out.println(s2 == s3);  //true
            }
        }
        VIP NOTE : dont use == when comparing strings as it compares adresses not actual content , use .equals() instead;

# StringBuilder

    Final : cannot extend
    Faster
    A mutable sequence of characters. This class provides an API compatible with StringBuffer, but with no guarantee of synchronization (muatble string)

    string builder is used for its mutablity and speed , if you change it uses the same memory unlike strings that remove the whole array and creats a brand new one

    becareful that is not threadsafe , use append to benfit form the speed not + since it converts to string which defeats the purpose of the whole thing
    remeber to use .toString() when passing it to ensure immutability

    it uses a fixed size char array and increse its capacity once it is exceeded

# StringBuffer.

    Slower
    A thread-safe, mutable sequence of characters. A string buffer is like a String, but can be modified. At any point in time it contains some particular sequence of characters, but the length and content of the sequence can be changed through certain method calls.

    String buffers are safe for use by multiple threads. The methods are synchronized where necessary so that all the operations on any particular instance behave as if they occur in some serial order that is consistent with the order of the method calls made by each of the individual threads involved.

# CoVariance vs Variance

    Covariance
    means that if Rectangle is a subtype of Shape, then Container<Rectangle> is also considered a subtype of Container<Shape>.
    In other words: the subtyping relationship is preserved.
    Example in Java - Arrays are covariant:
        Rectangle[] rectangles = new Rectangle[5];
        Shape[] shapes = rectangles; // ✅ This works! Arrays are covariant
        shapes[0] = new Circle(); // 💥 RUNTIME ERROR: ArrayStoreException  !
    Invariance
    means that even if Rectangle is a subtype of Shape, Container<Rectangle> is NOT considered a subtype of Container<Shape>.
    In other words: the subtyping relationship is NOT preserved.
    Example in Java - ArrayList are invarient
        ArrayList<Rectangle> rectangles = new ArrayList<>();
        ArrayList<Shape> shapes = rectangles; // ❌ COMPILATION ERROR: Generics are invariant

# generics

        Template vs Generic:
            C++ Templates: Code generation at compile-time
                Generate separate code for each type used
                True parametric polymorphism
                Code is instantiated at compile-time for each type
            Java Generics: Type erasure with compile-time type checking
                Use type erasure - generic type info removed at compiletime and replaced with object
                WHY NOT USED OBJECT AND SCREW GENERIC?
                generics allows the complier to type check IN COMPILE TIME
                if we use object the crash will happen in RUNTIME
                Single compiled class for all type parameters
                Types are checked at compile-time but erased to Object (or bound) at runtime
                Must use wrappers ,no primitive types
        a. Unbounded :
            public void printList(List<?> list) { ... }
        b. Upper Bounded :
            public void processNumbers(List<? extends Number> list) { ... }
        c. Lower Bounded:
            public void addIntegers(List<? super Integer> list) { ... }
        Use When:
        Return the same specific type that was passed in
        Preserve type information for the caller
        Work with the specific subtype's unique methods
        Remeber that you cant have say a static instance with a T since this generic is only for the instance
        you will have to use wild cards instead

# wild cards and generics

        all parameters must be of the same type T
        you must define it first
        Example:
        public <T> T getFirst(List<T> list) {
           return list.get(0);
        }

        // Usage:
        List<String> strings = Arrays.asList("a", "b");
        String first = getFirst(strings); // T is String

        public void printList(List<?> list) {
            for (Object item : list) {
                System.out.println(item);
            }
        }

        // With T - you can READ and WRITE
            public <T> void addAndGet(List<T> list, T item) {
                list.add(item);      // ✅ Can write
                T retrieved = list.get(0); // ✅ Can read
            }

        // With ? - you can only READ (as Object)
            public void process(List<?> list) {
                list.add("something"); // ❌ Error! Don't know what type the list holds
                Object item = list.get(0); // ✅ Can only read as Object
            }

# High order functions ISH

    Stream API (Java 8+)
    A Stream is not a data structure - it's a pipeline for processing data. Think of it as a conveyor belt where you can:

    Get data from a source (collection, array, etc.)
    Apply operations (filter, map, sort, etc.)
    Produce a result (collect, count, find, etc.)

    supports Parrelism
    Intermediate operations (return a Stream):

        filter(Predicate<T>) - filters elements based on a condition
        map(Function<T, R>) - transforms each element
        flatMap(Function<T, Stream<R>>) - flattens nested streams
        peek(Consumer<T>) - performs action without modifying stream
        sorted(Comparator<T>) - sorts elements using a comparator
        distinct() - removes duplicates (uses equals/hashCode)
        limit(long) - truncates stream
        skip(long) - skips elements

    Terminal operations (produce a result):

        forEach(Consumer<T>) - performs action on each element
        forEachOrdered(Consumer<T>) - forEach but maintains order
        reduce(BinaryOperator<T>) - combines elements into single result
        collect(Collector<T, A, R>) - collects into collection/map
        anyMatch(Predicate<T>) - checks if any element matches
        allMatch(Predicate<T>) - checks if all elements match
        noneMatch(Predicate<T>) - checks if no elements match
        findFirst() - finds first element
        findAny() - finds any element
        min(Comparator<T>) - finds minimum
        max(Comparator<T>) - finds maximum

    Collection methods (Java 8+)

        forEach(Consumer<T>) - iterates over collection
        removeIf(Predicate<T>) - removes elements matching predicate
        replaceAll(UnaryOperator<T>) - replaces all elements (List)

    Map methods (Java 8+)

        forEach(BiConsumer<K, V>) - iterates over key-value pairs
        compute(K, BiFunction<K, V, V>) - computes new value
        computeIfAbsent(K, Function<K, V>) - computes if key absent
        computeIfPresent(K, BiFunction<K, V, V>) - computes if key present
        merge(K, V, BiFunction<V, V, V>) - merges values
        replaceAll(BiFunction<K, V, V>) - replaces all values

    Optional methods (Java 8+)

        map(Function<T, R>) - transforms value if present   return map
        flatMap(Function<T, Optional<R>>) - flattens nested Optionals return map BUT expects function+stream
        filter(Predicate<T>) - filters based on condition
        ifPresent(Consumer<T>) - executes if value present
        ifPresentOrElse(Consumer<T>, Runnable) - executes with fallback
        or(Supplier<Optional<T>>) - provides alternative Optional

    CompletableFuture methods (Java 8+)

        thenApply(Function<T, R>) - transforms result
        thenAccept(Consumer<T>) - consumes result
        thenRun(Runnable) - runs after completion
        thenCompose(Function<T, CompletableFuture<R>>) - chains futures
        exceptionally(Function<Throwable, T>) - handles exceptions
        handle(BiFunction<T, Throwable, R>) - handles both success and failure

    Thread/Executor methods

        execute(Runnable) - executes a task
        submit(Callable<T>) - submits task for execution

    Arrays utility (Java 8+)

        Arrays.setAll(T[], IntFunction<T>) - sets all elements using function
        Arrays.parallelSetAll(T[], IntFunction<T>) - parallel version
        Arrays.sort(T[], Comparator<T>) - sorts with custom comparator

    Note: find any is non deterministic in parrel

# Exceptions

    RuntimeException

    • A runtime exception happens due to a programming error. They are also
    known as unchecked exceptions.
    • These exceptions are not checked at compile-time but run-time.

    Inorder to create a custom exception

    1.extend form exception class
    2.implement the constructor by either taking a message or giving a hardcoded message to the super()

    class MyException extends Exception {
        MyException() {
            super("YO I AM A NEW EXCEPTION");
        }

        MyException(String message) {
            super(message);
        }
    }
    Inorder to use your exception

    thorws after the function arguments to declare that this function throws an excption
    throw  to throw the exception after a certain action

    public void checkTrue(Boolean test) throws MyException {
        if (test) {
            System.out.println("Successful");
        } else {
            throw new MyException("Failed");
        }
    }
    As a general rule, you should catch those exceptions that you
    know how to handle and propagate those that you do not
    know how to handle.
    Rethrowing and Chaining Exceptions
    try
        {
        // call a method to access the database
        }
        catch (SQLException e)
        {
        Throwable se = new ServletException("database error");
        se.initCause(e);
        throw se;
        }
    • This wrapping technique is highly recommended. It allows you to
    throw high level exceptions in subsystems without losing the
    details of the original failure.
    Rethrowing and Chaining Exceptions

    finally exectues code whererther the error is thrown or not

    CAUTION: A finally clause can yield unexpected
    results when it contains return statements.
    Suppose you exit the middle of a try block with a
    return statement.
     Try-with-Resources
    • In its simplest variant, the try-with-resources statement has the
    form
    try (Resource res = . . .)
    {

    //work with res

    }
    • When the try block exits, then res.close() is called automatically.
    Notes:
    •If several method calls throw different exceptions,
    •then you can do either of the following:

    1. Write separate try-catch blocks for each method.
    2. Put them all inside the same try block and then
    write multiple catch blocks for it
    (one catch for each exception type).

    3. Put them all inside the same try block and then
    just catch the parent of all exceptions: Exception.



    Notes:
    •If more than one catch block are written after each
    other,

    • then you must take care not to handle a parent exception
    before a child exception

    • (i.e. a parent should not mask over a child).

    • Anyway, the compiler will give an error if you attempt to do so.


    • An exception is considered to be one of the parts of a
    method’s signature. So, when you override a method that
    throws a certain exception, you have to take the
    following into consideration:
    • You may throw the same exception.
    • You may throw a subclass of the exception
    • You may decide not to throw an exception at all
    • You CAN’T throw any different exceptions other than the
    exception(s) declared in the method that you are attempting
    to override

    avilable super options
    Exception() - no arguments
    Exception(String message) - with a message
    Exception(String message, Throwable cause) - with message and cause
    Exception(Throwable cause) - with just a cause

    Runtime Exceptions
        Null and Reference Issues:

        NullPointerException - attempting to use a null reference
        ClassCastException - invalid casting between types

        Array Issues:

        ArrayIndexOutOfBoundsException - accessing invalid array index
        NegativeArraySizeException - creating array with negative size

        Arithmetic Issues:

        ArithmeticException - illegal arithmetic operation (e.g., division by zero)

        Illegal Arguments:

        IllegalArgumentException - method receives inappropriate argument
        NumberFormatException - failed string-to-number conversion (subclass of IllegalArgumentException)
        IllegalStateException - method called at inappropriate time

        Unsupported Operations:

        UnsupportedOperationException - requested operation not supported

        Security:

        SecurityException - security manager denies access

        Concurrency:

        IllegalMonitorStateException - illegal monitor operation
        ConcurrentModificationException - concurrent modification detected

# try resoursces implements closable

    the closing happends in reverse order
    the close() checked exception is supressed
    niether cat nor finally are required
    the close exception doesnt have to throw a checked exception

# MISC

     Data Access Object
    all object are stored by refrence thus they are in the heap
    Serializable:
    an object's state can be converted into a format, like a stream of bytes, so it can be saved or transmitted and later restored to its original state. This process allows objects to be stored in a file or database, sent over a network, or passed between different programming environments

    java was created by sun with a team that consitsts of james goseling

    java applet was a new network program a special kind of Java program that is designed to be transmitted over the Internet and automatically executed inside a Java-compatible web browser.

    java programs runs on java virtual machine (JVM)(interpeter)

    the output of a Java compiler is not executable code. Rather, it is bytecode.
    Java also supports Remote Method Invocation (RMI),

    The keyword static allows main( ) to be called without having
    to instantiate a particular instance of the class.
    This is necessary since main( ) is called by the Java Virtual
    Machine before any objects are made.

    char in java is 2 byte

    uniary operators return the same data type

    intUniaryOperator is a prebuilt interface that takes an integer

    super and extend works with the origin class
    for example T extends animal or T super animal works with animal

    short and byte are promted to int in arthmetic operations
