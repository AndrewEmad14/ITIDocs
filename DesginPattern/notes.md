# The Four Pillars of Object-Oriented Programming (OOP)

Object-Oriented Programming is built on four core principles that help developers write clean, reusable, and maintainable code.

---

## 1. Encapsulation

**Definition:** Bundling data (fields) and the methods that operate on that data into a single unit (class), while restricting direct access to internal state using access modifiers.

**Key idea:** Hide the internal details and expose only what's necessary.

```java
public class BankAccount {
    private double balance; // hidden from outside

    public BankAccount(double initialBalance) {
        this.balance = initialBalance;
    }

    // Controlled access via public methods
    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }

    public double getBalance() {
        return balance;
    }
}

// Usage
BankAccount account = new BankAccount(1000);
account.deposit(500);
account.withdraw(200);
System.out.println(account.getBalance()); // 1300.0
// account.balance = -9999; ❌ Not allowed — field is private
```

> **Benefit:** Protects the integrity of the object's state and reduces unintended side effects.

---

## 2. Abstraction

**Definition:** Hiding complex implementation details and exposing only the essential features of an object. Achieved through **abstract classes** and **interfaces**.

**Key idea:** Show *what* an object does, not *how* it does it.

```java
// Abstract class defines the "what"
abstract class Shape {
    abstract double area(); // no implementation here

    public void printArea() {
        System.out.println("Area: " + area());
    }
}

// Concrete classes define the "how"
class Circle extends Shape {
    private double radius;

    Circle(double radius) {
        this.radius = radius;
    }

    @Override
    double area() {
        return Math.PI * radius * radius;
    }
}

class Rectangle extends Shape {
    private double width, height;

    Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    @Override
    double area() {
        return width * height;
    }
}

// Usage
Shape c = new Circle(5);
Shape r = new Rectangle(4, 6);

c.printArea(); // Area: 78.53...
r.printArea(); // Area: 24.0
```

> **Benefit:** Reduces complexity by letting users interact with objects at a high level without worrying about internal logic.

---

## 3. Inheritance

**Definition:** A mechanism where a child class (subclass) acquires the properties and behaviors of a parent class (superclass), promoting code reuse.

**Key idea:** "Is-a" relationship — a `Dog` *is a* `Animal`.

```java
// Parent class
class Animal {
    String name;

    Animal(String name) {
        this.name = name;
    }

    public void eat() {
        System.out.println(name + " is eating.");
    }

    public void sleep() {
        System.out.println(name + " is sleeping.");
    }
}

// Child class inherits from Animal
class Dog extends Animal {
    String breed;

    Dog(String name, String breed) {
        super(name); // calls parent constructor
        this.breed = breed;
    }

    public void bark() {
        System.out.println(name + " says: Woof!");
    }
}

class Cat extends Animal {
    Cat(String name) {
        super(name);
    }

    public void meow() {
        System.out.println(name + " says: Meow!");
    }
}

// Usage
Dog dog = new Dog("Rex", "Labrador");
dog.eat();   // Rex is eating.   (inherited)
dog.sleep(); // Rex is sleeping. (inherited)
dog.bark();  // Rex says: Woof!  (own method)

Cat cat = new Cat("Whiskers");
cat.eat();   // Whiskers is eating.
cat.meow();  // Whiskers says: Meow!
```

> **Benefit:** Avoids code duplication; common logic lives in one place and is shared across subclasses.

---

## 4. Polymorphism

**Definition:** The ability of different objects to respond to the same method call in different ways. Comes in two forms:
- **Compile-time (Method Overloading):** Same method name, different parameters.
- **Runtime (Method Overriding):** Subclass provides its own implementation of a parent method.

**Key idea:** One interface, many behaviors.

```java
// Runtime Polymorphism (Method Overriding)
class Animal {
    public void makeSound() {
        System.out.println("Some generic animal sound...");
    }
}

class Dog extends Animal {
    @Override
    public void makeSound() {
        System.out.println("Woof!");
    }
}

class Cat extends Animal {
    @Override
    public void makeSound() {
        System.out.println("Meow!");
    }
}

class Duck extends Animal {
    @Override
    public void makeSound() {
        System.out.println("Quack!");
    }
}

// Usage — same method call, different behavior
Animal[] animals = { new Dog(), new Cat(), new Duck() };

for (Animal a : animals) {
    a.makeSound();
}
// Output:
// Woof!
// Meow!
// Quack!


// Compile-time Polymorphism (Method Overloading)
class Calculator {
    public int add(int a, int b) {
        return a + b;
    }

    public double add(double a, double b) {
        return a + b;
    }

    public int add(int a, int b, int c) {
        return a + b + c;
    }
}

// Usage
Calculator calc = new Calculator();
System.out.println(calc.add(2, 3));       // 5
System.out.println(calc.add(2.5, 3.5));   // 6.0
System.out.println(calc.add(1, 2, 3));    // 6
```

> **Benefit:** Makes code more flexible and extensible — new types can be added without changing existing code.

---

## Summary Table

| Pillar | Core Idea | Java Mechanism |
|---|---|---|
| **Encapsulation** | Hide internal state | `private` fields + getters/setters |
| **Abstraction** | Expose only essentials | `abstract` classes, `interface` |
| **Inheritance** | Reuse parent behavior | `extends` keyword |
| **Polymorphism** | One interface, many forms | Method overriding & overloading |


# The SOLID Principles

SOLID is an acronym for five design principles that make software more understandable, flexible, and maintainable. Coined by Robert C. Martin (Uncle Bob).

---

## 1. S — Single Responsibility Principle (SRP)

**Definition:** A class should have **one and only one reason to change** — meaning it should only have one job.

**Key idea:** Don't make a class do too many things.

### ❌ Violation

```java
class Employee {
    private String name;
    private String email;

    // Responsibility 1: Employee data
    public String getName() { return name; }

    // Responsibility 2: Database logic — doesn't belong here!
    public void saveToDatabase() {
        System.out.println("Saving " + name + " to DB...");
    }

    // Responsibility 3: Email logic — doesn't belong here either!
    public void sendWelcomeEmail() {
        System.out.println("Sending email to " + email);
    }
}
```

### ✅ Correct

```java
// Responsibility 1: Only holds employee data
class Employee {
    private String name;
    private String email;

    Employee(String name, String email) {
        this.name = name;
        this.email = email;
    }

    public String getName()  { return name; }
    public String getEmail() { return email; }
}

// Responsibility 2: Only handles persistence
class EmployeeRepository {
    public void save(Employee employee) {
        System.out.println("Saving " + employee.getName() + " to DB...");
    }
}

// Responsibility 3: Only handles notifications
class EmployeeMailer {
    public void sendWelcomeEmail(Employee employee) {
        System.out.println("Sending welcome email to " + employee.getEmail());
    }
}
```

> **Benefit:** Each class is easier to test, understand, and change without breaking unrelated functionality.

---

## 2. O — Open/Closed Principle (OCP)

**Definition:** Software entities should be **open for extension, but closed for modification**.

**Key idea:** Add new behavior by adding new code, not by editing existing code.

### ❌ Violation

```java
class DiscountCalculator {
    // Every time a new discount type is added, this method must be modified
    public double calculate(String customerType, double price) {
        if (customerType.equals("Regular")) {
            return price * 0.95;
        } else if (customerType.equals("VIP")) {
            return price * 0.80;
        } else if (customerType.equals("Student")) {  // new type = modifying existing code ❌
            return price * 0.85;
        }
        return price;
    }
}
```

### ✅ Correct

```java
// Closed for modification — this interface never changes
interface DiscountStrategy {
    double apply(double price);
}

// Open for extension — just add a new class
class RegularDiscount implements DiscountStrategy {
    @Override
    public double apply(double price) { return price * 0.95; }
}

class VIPDiscount implements DiscountStrategy {
    @Override
    public double apply(double price) { return price * 0.80; }
}

class StudentDiscount implements DiscountStrategy {
    @Override
    public double apply(double price) { return price * 0.85; }
}

// This class never needs to change when new discounts are added
class DiscountCalculator {
    public double calculate(DiscountStrategy strategy, double price) {
        return strategy.apply(price);
    }
}

// Usage
DiscountCalculator calc = new DiscountCalculator();
System.out.println(calc.calculate(new VIPDiscount(), 100));     // 80.0
System.out.println(calc.calculate(new StudentDiscount(), 100)); // 85.0
```

> **Benefit:** Adding new features doesn't risk breaking existing, tested code.

---

## 3. L — Liskov Substitution Principle (LSP)

**Definition:** Objects of a subclass should be **substitutable for objects of their superclass** without altering the correctness of the program.

**Key idea:** A subclass should honor the contract of its parent — never break expected behavior.

### ❌ Violation

```java
class Bird {
    public void fly() {
        System.out.println("Flying...");
    }
}

// Penguin IS-A Bird, but it can't fly — violates LSP!
class Penguin extends Bird {
    @Override
    public void fly() {
        throw new UnsupportedOperationException("Penguins can't fly!"); // ❌ breaks the contract
    }
}

// This code breaks when a Penguin is passed in
void makeBirdFly(Bird bird) {
    bird.fly(); // Throws exception for Penguin!
}
```

### ✅ Correct

```java
// Separate behaviors into proper abstractions
interface Bird {
    void eat();
}

interface FlyingBird extends Bird {
    void fly();
}

class Sparrow implements FlyingBird {
    @Override
    public void eat() { System.out.println("Sparrow eating."); }

    @Override
    public void fly() { System.out.println("Sparrow flying."); }
}

class Penguin implements Bird {
    @Override
    public void eat() { System.out.println("Penguin eating."); }
    // No fly() — penguins simply don't have it ✅
}

// Safe — only FlyingBirds are asked to fly
void makeBirdFly(FlyingBird bird) {
    bird.fly();
}

// Usage
makeBirdFly(new Sparrow()); // ✅ Works fine
// makeBirdFly(new Penguin()); // ✅ Won't even compile — Penguin isn't a FlyingBird
```

> **Benefit:** Subtypes can safely replace their supertypes, making polymorphism reliable and predictable.

---

## 4. I — Interface Segregation Principle (ISP)

**Definition:** A class should **not be forced to implement interfaces it does not use**. Prefer many small, specific interfaces over one large, general-purpose one.

**Key idea:** Don't put too much into one interface.

### ❌ Violation

```java
// A bloated interface — forces all implementors to define everything
interface Worker {
    void work();
    void eat();
    void sleep();
}

// A robot doesn't eat or sleep, but is forced to implement them ❌
class Robot implements Worker {
    @Override
    public void work()  { System.out.println("Robot working."); }

    @Override
    public void eat()   { throw new UnsupportedOperationException("Robots don't eat!"); }

    @Override
    public void sleep() { throw new UnsupportedOperationException("Robots don't sleep!"); }
}
```

### ✅ Correct

```java
// Small, focused interfaces
interface Workable {
    void work();
}

interface Eatable {
    void eat();
}

interface Sleepable {
    void sleep();
}

// Human implements all three
class Human implements Workable, Eatable, Sleepable {
    @Override
    public void work()  { System.out.println("Human working."); }

    @Override
    public void eat()   { System.out.println("Human eating."); }

    @Override
    public void sleep() { System.out.println("Human sleeping."); }
}

// Robot only implements what it needs ✅
class Robot implements Workable {
    @Override
    public void work() { System.out.println("Robot working."); }
}
```

> **Benefit:** Classes only depend on what they actually use, reducing coupling and the impact of changes.

---

## 5. D — Dependency Inversion Principle (DIP)

**Definition:** High-level modules should **not depend on low-level modules**. Both should depend on **abstractions**. Abstractions should not depend on details — details should depend on abstractions.

**Key idea:** Depend on interfaces, not concrete implementations.

### ❌ Violation

```java
// Low-level class
class MySQLDatabase {
    public void saveData(String data) {
        System.out.println("Saving to MySQL: " + data);
    }
}

// High-level class is tightly coupled to MySQLDatabase ❌
// Switching to PostgreSQL means rewriting this class
class UserService {
    private MySQLDatabase db = new MySQLDatabase(); // direct dependency

    public void createUser(String name) {
        db.saveData(name);
    }
}
```

### ✅ Correct

```java
// Abstraction — the contract both sides depend on
interface Database {
    void saveData(String data);
}

// Low-level detail depends on the abstraction
class MySQLDatabase implements Database {
    @Override
    public void saveData(String data) {
        System.out.println("Saving to MySQL: " + data);
    }
}

class PostgreSQLDatabase implements Database {
    @Override
    public void saveData(String data) {
        System.out.println("Saving to PostgreSQL: " + data);
    }
}

class MongoDBDatabase implements Database {
    @Override
    public void saveData(String data) {
        System.out.println("Saving to MongoDB: " + data);
    }
}

// High-level class depends on the abstraction, not a concrete class ✅
class UserService {
    private Database db; // depends on interface

    // Dependency is injected from outside
    UserService(Database db) {
        this.db = db;
    }

    public void createUser(String name) {
        db.saveData(name);
    }
}

// Usage — swap the database without touching UserService
UserService service1 = new UserService(new MySQLDatabase());
service1.createUser("Alice"); // Saving to MySQL: Alice

UserService service2 = new UserService(new PostgreSQLDatabase());
service2.createUser("Bob");   // Saving to PostgreSQL: Bob
```

> **Benefit:** High-level business logic is completely decoupled from infrastructure details, making the system easy to swap, test, and extend.

---

## Summary Table

| Letter | Principle | Core Rule |
|---|---|---|
| **S** | Single Responsibility | One class = one job |
| **O** | Open/Closed | Extend behavior, don't modify existing code |
| **L** | Liskov Substitution | Subclasses must honor their parent's contract |
| **I** | Interface Segregation | Many small interfaces > one large interface |
| **D** | Dependency Inversion | Depend on abstractions, not concrete classes |


# Upcasting and Downcasting in Java

Casting in Java refers to converting an object reference from one type to another within an **inheritance hierarchy**. There are two directions: **up** toward the parent, and **down** toward the child.

---

## The Hierarchy Used in Examples

```java
class Animal {
    public void eat() {
        System.out.println("Animal is eating.");
    }
}

class Dog extends Animal {
    public void bark() {
        System.out.println("Dog is barking.");
    }
}

class Cat extends Animal {
    public void meow() {
        System.out.println("Cat is meowing.");
    }
}
```

---

## 1. Upcasting

**Definition:** Casting a **child** object to a **parent** type.

- Done **implicitly** (automatically) — no cast syntax required.
- The object is treated as its parent type.
- You **lose access** to child-specific methods through that reference.
- The actual object in memory is still the child — only the reference type changes.

### Syntax

```java
Animal animal = new Dog(); // implicit upcast — no (Animal) needed
```

### Example

```java
Animal animal = new Dog(); // Dog IS-A Animal ✅

animal.eat();  // ✅ Works — eat() is defined in Animal
// animal.bark(); ❌ Compile error — bark() is not visible through Animal reference
```

### Why Use Upcasting?

The main power of upcasting is **polymorphism** — you can write code that works with the parent type and handles any subclass uniformly.

```java
class AnimalShelter {
    // Accepts ANY Animal subclass — Dog, Cat, Bird, etc.
    public void feed(Animal animal) {
        animal.eat();
    }
}

AnimalShelter shelter = new AnimalShelter();

shelter.feed(new Dog()); // Animal is eating.
shelter.feed(new Cat()); // Animal is eating.
```

```java
// Store mixed subtypes in one list
List<Animal> animals = new ArrayList<>();
animals.add(new Dog()); // upcast
animals.add(new Cat()); // upcast

for (Animal a : animals) {
    a.eat(); // polymorphic call
}
```

> **Key rule:** Upcasting is always **safe** — a Dog is always an Animal.

---

## 2. Downcasting

**Definition:** Casting a **parent** reference back down to a **child** type.

- Done **explicitly** — you must write the cast.
- Gives back access to child-specific methods.
- **Unsafe** — can throw `ClassCastException` at runtime if done incorrectly.
- Only works if the underlying object is actually an instance of the target type.

### Syntax

```java
Animal animal = new Dog();     // upcast first
Dog dog = (Dog) animal;        // explicit downcast
```

### Example

```java
Animal animal = new Dog(); // actual object is Dog

// Downcast to access Dog-specific behavior
Dog dog = (Dog) animal;
dog.bark(); // ✅ Dog is barking.
dog.eat();  // ✅ Animal is eating.
```

### The Danger — ClassCastException

```java
Animal animal = new Cat(); // actual object is Cat

Dog dog = (Dog) animal; // ❌ Compiles fine, but CRASHES at runtime!
// java.lang.ClassCastException: Cat cannot be cast to Dog
```

The compiler doesn't catch this — it only fails at runtime. This is why you should always guard downcasts.

---

## 3. The `instanceof` Guard

Always use `instanceof` before downcasting to check the actual type at runtime and avoid `ClassCastException`.

```java
Animal animal = new Dog();

if (animal instanceof Dog) {
    Dog dog = (Dog) animal;
    dog.bark(); // ✅ Safe
} else if (animal instanceof Cat) {
    Cat cat = (Cat) animal;
    cat.meow(); // ✅ Safe
}
```

### Modern Java (Java 16+) — Pattern Matching

Java 16 introduced **pattern matching for instanceof**, combining the check and cast in one line.

```java
Animal animal = new Dog();

// Old way
if (animal instanceof Dog) {
    Dog dog = (Dog) animal;
    dog.bark();
}

// New way — pattern matching (Java 16+)
if (animal instanceof Dog dog) {
    dog.bark(); // dog is already cast and ready ✅
}
```

---

## 4. Full Example — Putting It All Together

```java
class Animal {
    public void eat() {
        System.out.println(getClass().getSimpleName() + " is eating.");
    }
}

class Dog extends Animal {
    public void bark() {
        System.out.println("Woof!");
    }
}

class Cat extends Animal {
    public void meow() {
        System.out.println("Meow!");
    }
}

public class Main {
    public static void main(String[] args) {

        // --- Upcasting (implicit) ---
        Animal a1 = new Dog(); // Dog → Animal
        Animal a2 = new Cat(); // Cat → Animal

        a1.eat(); // Dog is eating.
        a2.eat(); // Cat is eating.

        // a1.bark(); ❌ Not accessible — reference is Animal type


        // --- Downcasting (explicit) ---
        Animal animal = new Dog();

        if (animal instanceof Dog dog) {
            dog.bark(); // ✅ Woof!
        }


        // --- Wrong downcast — safely caught ---
        Animal anotherAnimal = new Cat();

        if (anotherAnimal instanceof Dog dog) {
            dog.bark(); // ⛔ Skipped — anotherAnimal is a Cat, not a Dog
        } else {
            System.out.println("Not a Dog — skipping bark.");
        }


        // --- Polymorphic list using upcasting ---
        List<Animal> shelter = new ArrayList<>();
        shelter.add(new Dog());
        shelter.add(new Cat());
        shelter.add(new Dog());

        for (Animal a : shelter) {
            a.eat(); // polymorphic

            // Downcast to trigger unique behavior per type
            if (a instanceof Dog d) d.bark();
            if (a instanceof Cat c) c.meow();
        }
    }
}
```

**Output:**
```
Dog is eating.
Cat is eating.
Woof!
Not a Dog — skipping bark.
Dog is eating.
Woof!
Cat is eating.
Meow!
Dog is eating.
Woof!
```

---

## Summary Table

| | Upcasting | Downcasting |
|---|---|---|
| **Direction** | Child → Parent | Parent → Child |
| **Syntax** | Implicit (automatic) | Explicit `(Type)` required |
| **Safety** | Always safe ✅ | Can throw `ClassCastException` ⚠️ |
| **Access** | Only parent methods | Full child methods restored |
| **Guard needed?** | No | Yes — use `instanceof` |
| **Use case** | Polymorphism, flexible APIs | Recover specific behavior after upcast |

---

## Quick Mental Model

```
Dog → Animal     (Upcast)   — zoom out, lose detail, always safe
Animal → Dog     (Downcast) — zoom in, gain detail, verify first!
```

buisness / presistance /presentatoin



what does the pattern consist of

name
intent
motivation 
structure
code examples


assosaition = use in function

compostion = only attribute

aggreation = compostion + assosication


if we dont abstract the decorator it will be misleading

