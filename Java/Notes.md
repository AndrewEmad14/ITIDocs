# Personal Java notes

# main boilerplate

    class myClass{
        public static void main(String args[]){

            //your code here;

        }

    };

# args[]

    args are the arguments that the main function takes , the input is sperated by space delimeter
    you can then access said arguments through args[i]
    Beware though the args may be empty so you have to check for the size of the args using
    .length (an attribute for arrays that gives )

# taking input

    java.util.Scanner
    Scanner scan= new(System.in);
    scan.close()    //be ware that closing a System.in scanner deny anymore input since
                    inputstream is static shared across the application

# displaying output

    System.out.println();

# java constructor

    same as c it provides a default constructor

# Variable initilization in class

    can be done in the same line as decleration unlike c

# innerClass

    1. Non-static (Member) Inner Class
        Defined as a non-static member of the outer class.
        Has access to all members (even private) of the outer class.
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

            // Or with lambda (modern alternative for functional interfaces):
            Runnable r2 = () -> System.out.println("Running!");

# Wrapper class

    int  -> Integer
    collections work only with wrappers
    Genereics   work only with wrappers
    Autoboxing : Automatic conversion from a primitive to its wrapper class.
    Unboxing: Automatic conversion from a wrapper class to its primitive type.

# String

    Strings are constant; their values cannot be changed after they are created
    what happens when you x+="hi"? x=new String(oldString+hi)

# StringBuilder

    A mutable sequence of characters. This class provides an API compatible with StringBuffer, but with no guarantee of synchronization (muatble string)

    string builder is used for its mutablity and speed , if you change it uses the same memory unlike strings that remove the whole array and creats a brand new one

    becareful that is not threadsafe , use append to benfit form the speed not + since it converts to string which defeats the purpose of the whole thing

# StringBuffer

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
            Java Generics: Type erasure with compile-time type checking
        a. Unbounded :
            public void printList(List<?> list) { ... }
        b. Upper Bounded :
            public void processNumbers(List<? extends Number> list) { ... }
        c. Lower Bounded:
            public void addIntegers(List<? super Integer> list) { ... }

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

# FAQ

    all object are stored by refrence thus they are in the heap
    Serializable:
    an object's state can be converted into a format, like a stream of bytes, so it can be saved or transmitted and later restored to its original state. This process allows objects to be stored in a file or database, sent over a network, or passed between different programming environments

# Personal Questions
