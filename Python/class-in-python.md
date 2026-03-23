# Python Classes — Complete Reference

> A structured wrap-up covering everything from this session.  
> Swift comparisons included throughout.

---

## Table of Contents

1. [Defining a Class](#1-defining-a-class)
2. [Inheritance](#2-inheritance)
3. [Polymorphism](#3-polymorphism)
4. [Encapsulation & Access Control](#4-encapsulation--access-control)
5. [Methods & Attributes](#5-methods--attributes)
6. [Decorators](#6-decorators)
7. [Interfaces in Python (ABC)](#7-interfaces-in-python-abc)
8. [Memory Management](#8-memory-management)
9. [Weak References](#9-weak-references)
10. [Reference Cycles in Dynamic Languages](#10-reference-cycles-in-dynamic-languages)

---

## 1. Defining a Class

A class is a blueprint for creating objects. `__init__` is the constructor — it runs when an object is instantiated.

```python
class Animal:
    # Class attribute — shared by ALL instances
    kingdom = "Animalia"

    def __init__(self, name, sound):
        # Instance attributes — unique to each object
        self.name  = name
        self.sound = sound

    def speak(self):
        return f"{self.name} says {self.sound}!"

cat = Animal("Cat", "meow")
dog = Animal("Dog", "woof")

print(cat.speak())                    # Cat says meow!
print(cat.kingdom is dog.kingdom)     # True — same object in memory
```

### Dunder (magic) methods

Special methods with double underscores let you hook into Python's built-in operators.

```python
class Vector:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def __repr__(self):           # for developers / debugging
        return f"Vector({self.x}, {self.y})"

    def __str__(self):            # for end users / print()
        return f"({self.x}, {self.y})"

    def __add__(self, other):     # overloads the + operator
        return Vector(self.x + other.x, self.y + other.y)

    def __len__(self):            # overloads len()
        return 2

v1 = Vector(1, 2)
v2 = Vector(3, 4)
print(v1 + v2)    # (4, 6)
print(len(v1))    # 2
```

---

## 2. Inheritance

A child class inherits attributes and methods from its parent. Use `super()` to call the parent's implementation without hardcoding the parent name.

```python
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        return "..."

    def describe(self):
        return f"I am {self.name}"

# Single inheritance
class Dog(Animal):
    def __init__(self, name, breed):
        super().__init__(name)    # call parent __init__
        self.breed = breed

    def speak(self):              # overrides parent method
        return "Woof!"

d = Dog("Rex", "Labrador")
print(d.speak())      # Woof!   (overridden)
print(d.describe())   # I am Rex  (inherited)
print(isinstance(d, Animal))   # True
```

### Multiple inheritance

```python
class Flyable:
    def fly(self):
        return f"{self.name} is flying"

class Swimmable:
    def swim(self):
        return f"{self.name} is swimming"

class Duck(Animal, Flyable, Swimmable):
    def speak(self):
        return "Quack!"

duck = Duck("Donald")
print(duck.fly())    # Donald is flying
print(duck.swim())   # Donald is swimming

# MRO — Method Resolution Order (C3 linearisation)
print(Duck.__mro__)
# (Duck, Animal, Flyable, Swimmable, object)
```

> **Swift note:** Python's multiple inheritance has no direct Swift equivalent. Swift uses protocols for similar composition.

---

## 3. Polymorphism

Same interface, different behaviour. Python has two flavours.

### Dynamic polymorphism — method overriding (runtime)

Python resolves which method to call at runtime based on the actual object type. This is the default and most idiomatic form.

```python
class Shape:
    def area(self):
        raise NotImplementedError

class Circle(Shape):
    def __init__(self, r): self.r = r
    def area(self): return 3.14 * self.r ** 2

class Rectangle(Shape):
    def __init__(self, w, h): self.w, self.h = w, h
    def area(self): return self.w * self.h

# Same call — different result based on runtime type
shapes = [Circle(5), Rectangle(4, 6), Circle(3)]
for s in shapes:
    print(s.area())    # 78.5, 24, 28.26
```

### Static polymorphism — mimicking overloading

Python has no true method overloading, but you can mimic it with `*args` or default arguments.

```python
class Calculator:
    def add(self, *args):
        return sum(args)

    def greet(self, name=None):
        return f"Hello, {name}!" if name else "Hello, World!"

c = Calculator()
print(c.add(1, 2, 3, 4))    # 10
print(c.greet("Alice"))      # Hello, Alice!
```

### Duck typing — Python's most idiomatic polymorphism

"If it walks like a duck and quacks like a duck, it's a duck." No shared parent required.

```python
class Dog:
    def speak(self): return "Woof"

class Robot:             # no shared parent
    def speak(self): return "Beep boop"

def make_speak(entity):
    print(entity.speak())    # works on anything with .speak()

make_speak(Dog())     # Woof
make_speak(Robot())   # Beep boop
```

---

## 4. Encapsulation & Access Control

Python uses naming conventions — there are no hard `private`/`public` keywords like Java or Swift.

| Convention | Access level | Meaning |
|---|---|---|
| `name` | Public | Accessible anywhere. The default. |
| `_name` | Protected | Internal use by convention. Still accessible — a warning to other developers. |
| `__name` | Private | Name-mangled to `_ClassName__name`. Prevents accidental access in subclasses. |
| `__name__` | Dunder | Reserved for Python internals. Never create your own. |

```python
class BankAccount:
    bank_name = "PyBank"           # public class attribute

    def __init__(self, owner, balance):
        self.owner    = owner      # public
        self._balance = balance    # protected
        self.__pin    = 0000       # private (name-mangled)

    def deposit(self, amount):     # public method
        self._balance += amount

    def _validate(self, pin):      # protected method
        return pin == self.__pin

    def __encrypt(self, data):     # private method
        return data[::-1]

acc = BankAccount("Alice", 1000)
acc.deposit(500)                   # OK — public
print(acc._balance)                # 1500 — works but bad practice
# acc.__pin                        # AttributeError!
print(acc._BankAccount__pin)       # 0 — mangled name (possible but rude)
```

> **Swift note:** Swift's `private`, `fileprivate`, `internal`, `public`, `open` are enforced by the compiler. Python's are conventions respected by tools and developers, not enforced at runtime.

---

## 5. Methods & Attributes

### Types at a glance

| Type | First param | Decorator | Use for |
|---|---|---|---|
| Instance method | `self` | none | Operating on one object's data |
| Class method | `cls` | `@classmethod` | Operating on the class itself; alternative constructors |
| Static method | neither | `@staticmethod` | Utility logic grouped in the class |

```python
class Employee:
    company    = "Acme Corp"    # class attribute — shared
    _headcount = 0

    def __init__(self, name, salary):
        self.name   = name      # instance attribute
        self.salary = salary
        Employee._headcount += 1

    # Instance method
    def raise_salary(self, pct):
        self.salary *= (1 + pct / 100)
        return self.salary

    # Class method — operates on the class
    @classmethod
    def get_headcount(cls):
        return cls._headcount

    # Class method as alternative constructor
    @classmethod
    def from_string(cls, emp_str):
        name, salary = emp_str.split("-")
        return cls(name, int(salary))

    # Static method — no self/cls
    @staticmethod
    def is_workday(day):
        return day.weekday() < 5

e1 = Employee("Alice", 60000)
e2 = Employee.from_string("Bob-70000")     # alternative constructor

print(e1.raise_salary(10))                 # 66000.0
print(Employee.get_headcount())            # 2
```

### Class vs instance attributes

```python
class Counter:
    count = 0          # class attribute — shared across all instances

    def __init__(self):
        Counter.count += 1
        self.id = Counter.count    # instance attribute — unique per object

a = Counter()   # count = 1, a.id = 1
b = Counter()   # count = 2, b.id = 2
print(Counter.count)   # 2
```

---

## 6. Decorators

A decorator is a function that wraps another function to extend or modify its behaviour without changing the original code.

### How they work

```python
def shout(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        return result.upper()
    return wrapper

@shout                      # sugar for: greet = shout(greet)
def greet(name):
    return f"hello, {name}"

print(greet("alice"))       # HELLO, ALICE
```

### `@property` — controlled attribute access

```python
class Temperature:
    def __init__(self, celsius):
        self._celsius = celsius

    @property
    def celsius(self):              # getter
        return self._celsius

    @celsius.setter
    def celsius(self, value):       # setter with validation
        if value < -273.15:
            raise ValueError("Below absolute zero!")
        self._celsius = value

    @celsius.deleter
    def celsius(self):              # deleter — for side-effect cleanup
        del self._celsius

    @property
    def fahrenheit(self):           # computed / read-only property
        return self._celsius * 9/5 + 32

t = Temperature(100)
print(t.fahrenheit)     # 212.0
t.celsius = 37          # calls setter with validation
del t.celsius           # calls deleter (e.g. for logging, revoking, cleanup)
```

> **On deleters:** you rarely need one. The use case is not freeing memory (Python does that automatically) but running side-effect logic on deletion — revoking an API key, closing a connection, logging an event.

### Custom decorator with arguments

```python
import time, functools

def retry(times=3):
    def decorator(func):
        @functools.wraps(func)     # preserves __name__ and __doc__
        def wrapper(*args, **kwargs):
            for attempt in range(times):
                try:
                    return func(*args, **kwargs)
                except Exception:
                    if attempt == times - 1: raise
                    time.sleep(1)
        return wrapper
    return decorator

@retry(times=3)
def fetch_data(url):
    ...    # retries up to 3 times on failure
```

> Always use `@functools.wraps(func)` — it preserves the wrapped function's metadata, which matters for debugging and introspection.

---

## 7. Interfaces in Python (ABC)

Python has no `interface` keyword. Abstract Base Classes (`abc` module) are the equivalent — they enforce a contract that all subclasses must implement.

```python
from abc import ABC, abstractmethod

# The "interface"
class Animal(ABC):
    @abstractmethod
    def speak(self) -> str: ...    # no body — subclass must implement

    @abstractmethod
    def move(self) -> str: ...

class Dog(Animal):
    def speak(self): return "Woof"
    def move(self):  return "Run"

class BadClass(Animal):
    def speak(self): return "Hi"
    # forgot move()!

d = Dog()        # works
b = BadClass()   # TypeError: Can't instantiate abstract class
                 # BadClass without implementing abstract method 'move'
```

ABCs can also contain concrete (non-abstract) methods, making them closer to Swift's abstract classes or partially-implemented protocols. For a pure interface, mark everything `@abstractmethod`.

> **Swift note:** Python's `ABC` ≈ Swift's `protocol` with required methods. The key difference: Swift protocols are enforced at compile time; Python's ABCs raise `TypeError` only at instantiation.

---

## 8. Memory Management

Python uses two mechanisms that work together.

### Reference counting — the primary mechanism

Every object tracks how many variables point to it. When the count hits zero, the memory is freed **immediately**.

```python
import sys

x = object()
print(sys.getrefcount(x))    # 2 (x + getrefcount arg)

y = x
print(sys.getrefcount(x))    # 3

del y
print(sys.getrefcount(x))    # 2

del x    # refcount → 0, object freed immediately
```

### The cycle problem

Reference counting breaks when objects reference each other — neither can ever reach zero.

```python
class Node:
    def __init__(self): self.other = None

a = Node()
b = Node()
a.other = b   # a → b
b.other = a   # b → a  ← cycle!

del a
del b
# Both still in memory!
# refcount(a_obj) = 1 (from b.other)
# refcount(b_obj) = 1 (from a_obj.other)
```

### Cyclic garbage collector — the safety net

Python's GC runs periodically to collect cycles that reference counting missed. It uses three generations — objects that survive longer get checked less frequently.

```python
import gc

gc.collect()         # force a GC run right now
print(gc.get_count())         # (gen0, gen1, gen2) object counts
print(gc.get_threshold())     # (700, 10, 10) — collection triggers
```

| | Reference counting | Cyclic GC |
|---|---|---|
| Timing | Instant, deterministic | Periodic, background |
| What it handles | 95% of objects | Reference cycles |
| You control it | No — automatic | `gc.collect()`, `gc.disable()` |
| Swift equivalent | ARC | No direct equivalent |

> **Swift note:** Python's reference counting ≈ Swift's ARC — same concept, same instant deallocation. Swift adds `weak`/`unowned` to break cycles at the language level. Python's cyclic GC is the runtime-level equivalent safety net.

---

## 9. Weak References

A weak reference points to an object without incrementing its reference count — it won't keep the object alive.

```python
import weakref

obj = SomeClass()
weak = weakref.ref(obj)    # doesn't increment refcount

print(weak())              # <SomeClass object>  — call like a function to dereference
del obj
print(weak())              # None — object was freed
```

### When you need `weakref`

#### Case 1 — parent/child back-reference (cycle)

```python
import weakref

class Node:
    def __init__(self, value):
        self.value    = value
        self.children = []
        self.parent   = None

    def add_child(self, child):
        child.parent = weakref.ref(self)   # weak — won't keep self alive
        self.children.append(child)        # strong — parent owns child

root  = Node("root")
child = Node("child")
root.add_child(child)

parent = child.parent()      # call to dereference
if parent is not None:
    print(parent.value)      # "root"

del root
print(child.parent())        # None — root is gone
```

#### Case 2 — cache / registry

```python
import weakref

cache = weakref.WeakValueDictionary()

def get_resource(key):
    obj = cache.get(key)
    if obj is None:
        obj = ExpensiveResource(key)
        cache[key] = obj
    return obj

r = get_resource("img_001")
del r
# cache entry is automatically removed — object was freed
```

### When you don't need `weakref`

A plain one-directional ownership relationship has no cycle — reference counting handles everything automatically.

```python
class Item:
    def __init__(self, name, price):
        self.name  = name
        self.price = price

class Order:
    def __init__(self):
        self.items = []

    def add(self, item):
        self.items.append(item)    # one direction only — no cycle

order = Order()
order.add(Item("Coffee", 3.5))
del order
# order freed → items freed. No weakref needed.
```

| Situation | Use weakref? |
|---|---|
| Parent ← child back-reference | Yes |
| Cache / registry | Yes (`WeakValueDictionary`) |
| Callback / closure capturing `self` | Yes (`WeakMethod`) |
| Plain owner → owned | No |
| Sibling objects with no back-link | No |

> **Swift note:** `weakref.ref(obj)` ≈ `weak var`. Python has no `unowned` equivalent — a dead weak reference always returns `None` rather than crashing.

---

## 10. Reference Cycles in Dynamic Languages

Dynamic languages like Python make cycles easier to create accidentally because there is no declaration phase — you can attach any attribute to any object at any time with no compiler analysis.

### Reason 1 — no type system enforcing ownership

```python
# No declaration, no compiler, no warning
class Parent: pass
class Child:  pass

p = Parent()
c = Child()
p.child  = c    # p → c
c.parent = p    # c → p  ← cycle, formed silently at runtime
```

In Swift, stored properties must be declared inside the type. The compiler sees the full ownership graph and forces a `weak`/`unowned` decision. Python has no such analysis step.

### Reason 2 — monkey patching

```python
class Engine:
    def __init__(self):
        self.power = 200

class Car:
    def __init__(self):
        self.engine = Engine()
        self.engine.owner = self   # Engine → Car back-ref, from inside Car
        # Engine class never declared this relationship

# Even from completely outside both classes:
e = Engine()
c = Car()
e.buddy = c     # attaching a ref to an existing object, from anywhere
c.engine = e    # cycle — created across two unrelated locations
```

In Swift, you cannot inject a new stored property onto an existing object from outside the type definition.

### Reason 3 — closures silently capturing `self`

The most common real-world case. A closure stored on an object captures `self` strongly with no visible syntax.

```python
class ViewController:
    def __init__(self):
        self.button = Button("OK")

        # Lambda captures `self` strongly — cycle!
        # ViewController → Button (via self.button)
        # Button → ViewController (via callback closure)
        self.button.callback = lambda: self.on_tap()

    def on_tap(self):
        print(f"{self.button.label} tapped")

# Fix: use WeakMethod
import weakref
self.button.callback = weakref.WeakMethod(self.on_tap)
```

Swift equivalent: `{ [weak self] in self?.onTap() }` — capture lists are explicit syntax. Python captures everything strongly by default with no capture list mechanism.

### Reason 4 — indirect cycles through containers

```python
# A list referencing itself
x = []
x.append(x)      # x → x
del x             # refcount stays at 1 — not freed by refcounting

# More realistic: object holds list, list holds object
class EventBus:
    def __init__(self):
        self.listeners = []

    def subscribe(self, listener):
        self.listeners.append(listener)

class Screen:
    def __init__(self, bus):
        self.bus = bus          # Screen → EventBus
        bus.subscribe(self)     # EventBus.listeners → Screen
        # Cycle via the list container

# Fix: explicit cleanup
bus.listeners.remove(screen)   # before deleting screen
```

### Python vs Swift comparison

| | Swift | Python |
|---|---|---|
| Memory model | ARC | Reference counting + cyclic GC |
| Cycle detection | Compiler (compile time) | Cyclic GC (runtime, periodic) |
| Breaking cycles | `weak var`, `unowned` | `weakref.ref`, `WeakMethod`, `WeakValueDictionary` |
| Forgot to break a cycle | Permanent leak | GC collects it eventually |
| Closure capture | Explicit `[weak self]` | Implicit strong capture |
| Inject property on existing object | Impossible | Possible (monkey patching) |

---

*Generated from a Python classes study session.*