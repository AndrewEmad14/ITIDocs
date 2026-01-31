# Variables 
var myName = "andrew";
myName = 30;
myName = true;
myname = null;
myname = undefiend;

//printing on the console : console.log();
 console.log(x);//undefined (because of hoisting)

 Cooersion === implicit casting
 
 Examples
 zzz = 10;      //global var variabe  
 var x = 50; 
 var y = 6;
 var str = "menna";
 var str2 = "shata";
 var x = 10;
 var y = "20";
  console.log(x-y); // try to cast y to number 
 console.log(str-str2);// NOT a Number failed to cast to int
 console.log(str+x);//integer is cast to string
 console.log(x+false);//booean true 1 false 0 is cast to int
 console.log(x+undefined);//Not A Number
 console.log(typeof NaN);//number
 console.log(typeof x);//number

// console.log(3<2<1);//false<1  0<1


// var x = "menna";
// var age = 30;

//  console.log(x=="menna" && age<20);//true&&false
// console.log(age!="30");//== false doesnt check on the type
// console.log(age!=="30");//=== checks on the type


Falsey Values
| Value | Description |
| :--- | :--- |
| `false` | The boolean keyword false. |
| `0` | The number zero (including 0.0). |
| `-0` | Negative zero. |
| `0n` | BigInt zero (used for large integers). |
| `""` | An empty string (length of 0). |
| `null` | The intentional absence of any object value. |
| `undefined` | A variable that has been declared but not assigned a value. |
| `NaN` | "Not-a-Number" (the result of invalid math). |


Hoisting: your code is taken  on the top of your scope

# JavaScript Variable Declarations: var vs let vs const

## Scope

**var**
- Function-scoped or globally-scoped
- Not block-scoped (ignores `{}` blocks like if, for, while)
- Accessible throughout the entire function or global context

**let**
- Block-scoped
- Only accessible within the nearest enclosing block `{}`
- Creates a new scope in if statements, loops, and any code block

**const**
- Block-scoped
- Same scoping rules as `let`
- Only accessible within the nearest enclosing block `{}`

## Reassignment

**var**
- Can be reassigned
- Value can be changed at any time

**let**
- Can be reassigned
- Value can be changed at any time

**const**
- Cannot be reassigned
- Must be initialized at declaration
- Note: For objects and arrays, the reference cannot change, but properties/elements can be modified

## Redeclaration

**var**
- Can be redeclared in the same scope
- No error thrown when declaring the same variable twice

**let**
- Cannot be redeclared in the same scope
- Throws a SyntaxError if you try to redeclare

**const**
- Cannot be redeclared in the same scope
- Throws a SyntaxError if you try to redeclare

## Hoisting

**var**
- Hoisted to the top of its scope
- Initialized with `undefined`
- Can be accessed before declaration (returns `undefined`)

**let**
- Hoisted to the top of its block
- Not initialized (remains in "Temporal Dead Zone")
- Cannot be accessed before declaration (throws ReferenceError)

**const**
- Hoisted to the top of its block
- Not initialized (remains in "Temporal Dead Zone")
- Cannot be accessed before declaration (throws ReferenceError)


proof that the let and const 

let x= 5;
{
  console.log(x); //cannot access
  let x;
}
## Quick Reference Table

| Feature | var | let | const |
|---------|-----|-----|-------|
| Scope | Function/Global | Block | Block |
| Reassign | ✅ Yes | ✅ Yes | ❌ No |
| Redeclare | ✅ Yes | ❌ No | ❌ No |
| Hoisting | Yes (initialized) | Yes (not initialized) | Yes (not initialized) |

## Best Practices

- Use `const` by default
- Use `let` when you need to reassign
- Avoid `var` in modern JavaScript (ES6+)


## JavaScript Primitive Data Types

JavaScript has **7 primitive data types**:

1. **String**
   - Represents text
   - Example:
     ```js
     "Hello"
     ```

2. **Number**
   - Represents integers and floating-point numbers
   - Example:
     ```js
     42
     3.14
     ```

3. **BigInt**
   - Represents integers larger than `Number.MAX_SAFE_INTEGER`
   - Example:
     ```js
     9007199254740991n
     ```

4. **Boolean**
   - Represents logical values
   - Example:
     ```js
     true
     false
     ```

5. **Undefined**
   - A variable declared but not assigned a value
   - Example:
     ```js
     let x;
     ```

6. **Null**
   - Represents an intentional absence of value
   - Example:
     ```js
     null
     ```

7. **Symbol**
   - Represents a unique and immutable identifier
   - Example:
     ```js
     Symbol("id")
     ```

### Notes
- Primitive values are **immutable**
- They are compared **by value**
- `typeof null === "object"` (this is a historical bug)


# Dialouge Boxes
  1.Prompt 
  2.Alert
  3.Confirm

# number checkers
  isNaN() // check if it is a not a number 
  isFinite() // checks if it is a number(not NaN) AND not Infinity

  Note that those are unreliable because coerison can happen in the parpmeters ,use Number.isNaN or is finite for more reliabe results

# print var with string
  template literal interpolation (or string interpolation)
        `hello$${x}`
  old string concationation
        "hello" + x


# switch
  switch can be used with variables
  switch can be:
    numbers
	•	strings
	•	booleans
	•	objects
	•	functions
  switch uses strict equality

# built in js objects
  //less effecient creates an object more memory and processing
  let x = new String("Andrew");
  let y = new String("Andrew");
  //more efficient  create a primitive data type
  let altx= "Andrew"
  let alty= "Andrew"
  console.log(x === y); //false
  console.log(altx === alty); //true

# regex
  regular expression class (strin
  var regxEmail = new RegExp(/^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|.(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/)
  var regxEmail = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|.(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;

  var res = regxEmail.test("hamada@gmail.com"); // check the regex
  
# Math  static class with some useful operations

# Array 
arrays can take any object of any type , it can even take functions
// var arr = new Array();
// var arr1 = [1,2,"menna",true,[20,30]];

# Dates
  The Date object uses milliseconds since January 1, 1970 (UTC). 
  Creating dates can be confusing—new Date("2024-01-15") might interpret the string differently depending on timezone. 
  Month numbers are zero-indexed (0 = January, 11 = December)

# Functions
  var x = new Function(); //function is an object so you can declare it a var

  function myFunc(x,y){
      //var x;
      
      return x+y;
      //return undefiend
  }

  # Types of Functions in JavaScript

  ## Function Declarations

  ```javascript
  function greet(name) {
    return "Hello " + name;
  }
  ```

  These are hoisted (available before they're declared in the code) and are the traditional way to define functions.

  ## Function Expressions

  ```javascript
  const greet = function(name) {
    return "Hello " + name;
  };
  greet()
  ```
  
  These aren't hoisted and are assigned to variables. They can be named or anonymous.

  ## Arrow Functions

  ```javascript
  const greet = (name) => {
    return "Hello " + name;
  };
  ```

  A concise syntax introduced in ES6. They have implicit return for single expressions: `const greet = (name) => "Hello " + name;`. They don't have their own `this` binding, which matters in certain contexts.

  ## Anonymous Functions

  Functions without names, often used as callbacks or immediately invoked:

  ```javascript
  setTimeout(function() { console.log("hi"); }, 1000);
  ```

  ## Immediately Invoked Function Expression (IIFE)

  ```javascript
  (function() {
    console.log("runs immediately");
  })();
  ```

  Runs the moment it's defined. Useful for creating scope and avoiding global variables.

  ## Callback Functions

  Functions passed as arguments to other functions, typically used with `setTimeout`, `addEventListener`, or array methods like `map()`.

  ## Higher-Order Functions

  Functions that take other functions as arguments or return functions. Very common in JavaScript:

  ```javascript
  const multiplier = (factor) => (num) => num * factor;
  const double = multiplier(2);
  ```

  ## Async Functions

  ```javascript
  async function fetchData() {
    const data = await fetch('/api');
    return data;
  }
  ```

  Syntax for working with promises more cleanly.



# DOM manpulation
  # DOM Manipulation in JavaScript

## What is the DOM?

The Document Object Model (DOM) is a tree-like representation of the HTML page. JavaScript can access and modify it to change what users see and interact with.

## Selecting Elements

### `getElementById()`
```javascript
const element = document.getElementById('myId');
```
Selects a single element by its ID.

### `querySelector()`
```javascript
const element = document.querySelector('.myClass');
const element = document.querySelector('#myId');
const element = document.querySelector('div p');
```
Selects the first element matching a CSS selector.

### `querySelectorAll()`
```javascript
const elements = document.querySelectorAll('.myClass');
```
Selects all elements matching a CSS selector. Returns a NodeList.

### `getElementsByClassName()`
```javascript
const elements = document.getElementsByClassName('myClass');
```
Selects all elements with a specific class.

### `getElementsByTagName()`
```javascript
const elements = document.getElementsByTagName('div');
```
Selects all elements of a specific tag type.

## Modifying Content

### `textContent`
```javascript
element.textContent = "New text";
const text = element.textContent;
```
Gets or sets the text content. Treats input as plain text (safer for user input).

### `innerHTML`
```javascript
element.innerHTML = "<p>New HTML</p>";
```
Gets or sets HTML content. Can execute scripts if misused, so be careful with user input.

### `innerText`
```javascript
element.innerText = "New text";
```
Similar to `textContent` but respects CSS visibility.

## Modifying Attributes

### `setAttribute()`
```javascript
element.setAttribute('data-id', '123');
element.setAttribute('class', 'active');
```
Sets an attribute on an element.

### `getAttribute()`
```javascript
const value = element.getAttribute('data-id');
```
Gets the value of an attribute.

### `removeAttribute()`
```javascript
element.removeAttribute('disabled');
```
Removes an attribute from an element.

### Direct property access
```javascript
element.id = 'newId';
element.title = 'Hover text';
element.href = 'https://example.com';
```
Some attributes can be accessed directly as properties.

## Modifying Classes

### `classList.add()`
```javascript
element.classList.add('active');
element.classList.add('class1', 'class2');
```
Adds one or more classes.

### `classList.remove()`
```javascript
element.classList.remove('active');
```
Removes one or more classes.

### `classList.toggle()`
```javascript
element.classList.toggle('active');
```
Adds the class if absent, removes it if present.

### `classList.contains()`
```javascript
if (element.classList.contains('active')) {
  console.log('Element is active');
}
```
Checks if an element has a specific class.

## Modifying Styles

### Inline styles
```javascript
element.style.color = 'red';
element.style.backgroundColor = 'blue';
element.style.fontSize = '16px';
```
Modifies CSS properties directly. Use camelCase for hyphenated properties.

### Getting computed styles
```javascript
const color = window.getComputedStyle(element).color;
```
Gets the final computed style of an element.

## Creating and Removing Elements

### `createElement()`
```javascript
const newDiv = document.createElement('div');
newDiv.textContent = 'Hello';
```
Creates a new element in memory (not yet in the page).

### `appendChild()`
```javascript
parent.appendChild(newDiv);
```
Adds an element as the last child of a parent.

### `insertBefore()`
```javascript
parent.insertBefore(newDiv, referenceElement);
```
Inserts an element before another element.

### `removeChild()`
```javascript
parent.removeChild(child);
```
Removes a child element.

### `remove()`
```javascript
element.remove();
```
Removes the element itself from the DOM.

### `replaceChild()`
```javascript
parent.replaceChild(newElement, oldElement);
```
Replaces one child with another.

## Navigating the DOM

### Parent and children
```javascript
const parent = element.parentElement;
const children = element.children;
const firstChild = element.firstChild;
const lastChild = element.lastChild;
```

### Siblings
```javascript
const nextSibling = element.nextElementSibling;
const prevSibling = element.previousElementSibling;
```
## Cloning
    const clone = original.cloneNode(true);
## Best Practices

- Use `querySelector()` and `querySelectorAll()` for modern, flexible selection
- Use `textContent` instead of `innerHTML` when dealing with plain text (more secure)
- Cache DOM selections in variables if you use them multiple times
- Use `classList` for managing classes instead of directly modifying the `class` attribute
- Use event delegation for dynamically added elements
- Be cautious with `innerHTML` when handling user input (risk of XSS attacks)



# Event property
  var div = document.querySelector("div");
  function test(e){
      console.log(e.target);
  }
  div.onclick=function(){

  }
  div.onclick = test //callbackfunction

# setTimeout
  The setTimeout() method of the Window interface sets a timer which executes a function or specified piece of code once the timer expires.

  setTimeout(() => {
  console.log("this is the first message");
}, 5000);


# Classes

What are Classes?
Classes are templates for creating objects with properties (data) and methods (functions). They make it easier to organize and reuse code using object-oriented programming (OOP).
Basic Class Structure
javascriptclass ClassName {
  constructor(parameter1, parameter2) {
    this.property1 = parameter1;
    this.property2 = parameter2;
  }
  
  method1() {
    // code here
  }
  
  method2() {
    // code here
  }
}

// Creating an instance
const obj = new ClassName(value1, value2);
Constructor
The constructor() method runs automatically when you create a new instance. It initializes the object's properties.
javascriptclass Car {
  constructor(brand, color) {
    this.brand = brand;
    this.color = color;
  }
}

const myCar = new Car('Toyota', 'red');
console.log(myCar.brand);   // Toyota
console.log(myCar.color);   // red
Methods
Methods are functions inside a class. They perform actions on the object's data.
javascriptclass Calculator {
  constructor(num) {
    this.num = num;
  }
  
  add(x) {
    return this.num + x;
  }
  
  subtract(x) {
    return this.num - x;
  }
  
  multiply(x) {
    return this.num * x;
  }
}

const calc = new Calculator(10);
console.log(calc.add(5));      // 15
console.log(calc.subtract(3)); // 7
console.log(calc.multiply(2)); // 20
Inheritance (extends)
Inheritance allows a child class to inherit properties and methods from a parent class using the extends keyword.
javascriptclass Animal {
  constructor(name) {
    this.name = name;
  }
  
  speak() {
    console.log(this.name + ' makes a sound');
  }
}

class Dog extends Animal {
  // Inherits name and speak() from Animal
}

const dog = new Dog('Buddy');
dog.speak();  // Buddy makes a sound
super() - Calling Parent Constructor
Use super() to call the parent class constructor and access parent properties.
javascriptclass Animal {
  constructor(name, type) {
    this.name = name;
    this.type = type;
  }
  
  info() {
    console.log(`${this.name} is a ${this.type}`);
  }
}

class Dog extends Animal {
  constructor(name, type, breed) {
    super(name, type);  // Call parent constructor
    this.breed = breed;
  }
  
  info() {
    super.info();  // Call parent method
    console.log(`Breed: ${this.breed}`);
  }
}

const dog = new Dog('Max', 'Dog', 'German Shepherd');
dog.info();
// Max is a Dog
// Breed: German Shepherd
Method Overriding
Override a parent method by redefining it in the child class.
javascriptclass Vehicle {
  start() {
    console.log('Vehicle starting...');
  }
}

class Car extends Vehicle {
  start() {  // Override parent method
    console.log('Car engine starting...');
  }
}

const car = new Car();
car.start();  // Car engine starting...
Abstract Classes
An abstract class cannot be instantiated directly but can be extended by other classes. You can simulate this in JavaScript:
javascriptclass User {
  constructor(name, age) {
    // Prevent instantiation of this class
    if (this.constructor === User) {
      throw new Error('User is an abstract class and cannot be instantiated');
    }
    this.name = name;
    this.age = age;
  }
  
  print() {
    console.log(this.name, this.age);
  }
}

class Employee extends User {
  constructor(name, age, salary) {
    super(name, age);
    this.salary = salary;
  }
  
  print() {
    console.log(`Employee: ${this.name}, Age: ${this.age}, Salary: $${this.salary}`);
  }
  
  calcSalary(bonus) {
    return this.salary + bonus;
  }
}

class Student extends User {
  constructor(name, age, grades) {
    super(name, age);
    this.grades = grades;
  }
  
  calcMyGrades(percentage) {
    return this.grades + percentage + '%';
  }
}

// var user = new User('John', 30);  // Error: User is abstract

const emp = new Employee('Menna', 25, 3000);
emp.print();  // Employee: Menna, Age: 25, Salary: $3000
console.log(emp.calcSalary(500));  // 3500

const stu = new Student('Hamada', 20, 60);
stu.print();  // Hamada 20
console.log(stu.calcMyGrades(10));  // 60 + 10%
toString() Method
The toString() method returns a string representation of an object. When you use an object in a string context, toString() is automatically called.
javascriptclass Person {
  constructor(name, age) {
    this.name = name;
    this.age = age;
  }
  
  toString() {
    return `${this.name} (${this.age} years old)`;
  }
}

const person = new Person('Alice', 28);
console.log(person);           // Person object
console.log(person.toString()); // Alice (28 years old)
console.log(person + '');      // Alice (28 years old) - toString() called automatically
document.write(person);        // Alice (28 years old)

# super
  you must call the super if you are extending form class + you are implementing a constructor

# Promises , call-back-hell, async and await
  # Callback Hell, Promises, and Async/Await in JavaScript

## Callback Hell (Pyramid of Doom)

Callback hell occurs when you nest multiple callbacks, making code hard to read and maintain.

### Example of Callback Hell

```javascript
function getUser(userId, callback) {
  setTimeout(() => {
    const user = { id: userId, name: 'John', departmentId: 5 };
    callback(user);
  }, 1000);
}

function getDepartment(deptId, callback) {
  setTimeout(() => {
    const dept = { id: deptId, name: 'Engineering' };
    callback(dept);
  }, 1000);
}

function getProjects(deptId, callback) {
  setTimeout(() => {
    const projects = ['Project A', 'Project B', 'Project C'];
    callback(projects);
  }, 1000);
}

// CALLBACK HELL - Hard to read and maintain
getUser(1, function(user) {
  console.log('User:', user);
  
  getDepartment(user.departmentId, function(dept) {
    console.log('Department:', dept);
    
    getProjects(dept.id, function(projects) {
      console.log('Projects:', projects);
      
      // More nested callbacks...
      // This gets ugly quickly!
    });
  });
});
```

### Problems with Callback Hell

- **Hard to read** - Deep nesting makes code difficult to follow
- **Error handling is messy** - Need try-catch or error callbacks at each level
- **Code duplication** - Repetitive error handling logic
- **Hard to maintain** - Difficult to modify or debug
- **Can't use return statements effectively** - Logic is fragmented

---

## Promises with .then()

Promises provide a cleaner way to handle asynchronous operations. A promise represents a value that may not be available yet but will be eventually.

### Promise States

1. **Pending** - Initial state, operation hasn't completed
2. **Fulfilled** - Operation completed successfully, has a value
3. **Rejected** - Operation failed, has a reason/error

### Creating a Promise

```javascript
const myPromise = new Promise((resolve, reject) => {
  // resolve(value) - fulfills the promise
  // reject(error) - rejects the promise
});
```

### Simple Promise Example

```javascript
function getUser(userId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (userId > 0) {
        const user = { id: userId, name: 'John' };
        resolve(user);  // Fulfill the promise
      } else {
        reject('Invalid user ID');  // Reject the promise
      }
    }, 1000);
  });
}

// Using .then() and .catch()
getUser(1)
  .then((user) => {
    console.log('User:', user);
  })
  .catch((error) => {
    console.log('Error:', error);
  });
```

### Promise Chain with .then()

Chain multiple promises to avoid callback hell:

```javascript
function getUser(userId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve({ id: userId, name: 'John', departmentId: 5 });
    }, 1000);
  });
}

function getDepartment(deptId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve({ id: deptId, name: 'Engineering' });
    }, 1000);
  });
}

function getProjects(deptId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve(['Project A', 'Project B', 'Project C']);
    }, 1000);
  });
}

// PROMISE CHAIN - Much cleaner than callback hell!
getUser(1)
  .then((user) => {
    console.log('User:', user);
    return getDepartment(user.departmentId);  // Return next promise
  })
  .then((dept) => {
    console.log('Department:', dept);
    return getProjects(dept.id);  // Return next promise
  })
  .then((projects) => {
    console.log('Projects:', projects);
  })
  .catch((error) => {
    console.log('Error:', error);
  });
```

### .then() Returns a New Promise

Each `.then()` call returns a new promise, allowing chaining:

```javascript
getUser(1)
  .then((user) => {
    console.log('Step 1:', user);
    return user.id;  // Return value becomes input to next .then()
  })
  .then((userId) => {
    console.log('Step 2: User ID is', userId);
    return getDepartment(5);
  })
  .then((dept) => {
    console.log('Step 3:', dept);
  })
  .catch((error) => {
    console.log('Error at any step:', error);
  });
```

### Error Handling with .catch()

```javascript
function fetchData(url) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (url) {
        resolve({ data: 'Success' });
      } else {
        reject('URL is required');
      }
    }, 1000);
  });
}

fetchData('')
  .then((result) => {
    console.log('Data:', result);
  })
  .catch((error) => {
    console.log('Caught error:', error);  // Catches error from any .then()
  })
  .finally(() => {
    console.log('Operation completed');  // Runs regardless of success/failure
  });
```

### .finally() - Always Executes

```javascript
let isLoading = true;

fetchData('/api/users')
  .then((data) => {
    console.log('Data received:', data);
  })
  .catch((error) => {
    console.log('Error:', error);
  })
  .finally(() => {
    isLoading = false;  // Cleanup code - runs in both success and failure
    console.log('Request finished');
  });
```

### Promise.all() - Multiple Promises

Execute multiple promises and wait for all to complete:

```javascript
function getUser() {
  return new Promise((resolve) => {
    setTimeout(() => resolve({ name: 'John' }), 1000);
  });
}

function getSettings() {
  return new Promise((resolve) => {
    setTimeout(() => resolve({ theme: 'dark' }), 1500);
  });
}

function getNotifications() {
  return new Promise((resolve) => {
    setTimeout(() => resolve([]), 800);
  });
}

// Run all promises in parallel, wait for all to complete
Promise.all([getUser(), getSettings(), getNotifications()])
  .then(([user, settings, notifications]) => {
    console.log('User:', user);
    console.log('Settings:', settings);
    console.log('Notifications:', notifications);
  })
  .catch((error) => {
    console.log('One or more promises failed:', error);
  });
```

### Promise.race() - First Completed Promise

```javascript
Promise.race([getUser(), getSettings()])
  .then((result) => {
    console.log('First completed:', result);
  });
```

### Practical Example: API Calls with .then()

```javascript
function login(email, password) {
  return fetch('/api/login', {
    method: 'POST',
    body: JSON.stringify({ email, password })
  })
  .then((response) => response.json())
  .then((data) => {
    if (data.token) {
      localStorage.setItem('token', data.token);
      return data;
    } else {
      throw new Error('Login failed');
    }
  });
}

function getProfile(token) {
  return fetch('/api/profile', {
    headers: { Authorization: `Bearer ${token}` }
  })
  .then((response) => response.json());
}

// Chain login and get profile
login('user@example.com', 'password')
  .then((loginData) => {
    console.log('Logged in:', loginData);
    return getProfile(loginData.token);
  })
  .then((profile) => {
    console.log('Profile:', profile);
  })
  .catch((error) => {
    console.log('Error:', error);
  });
```

---

## Async/Await

Async/await is syntactic sugar over promises. It allows you to write asynchronous code that looks synchronous and is easier to read.

### Basic Async/Await Syntax

```javascript
async function myFunction() {
  // await only works inside async functions
  const result = await somePromise;
}
```

### Simple Example

```javascript
function getUser(userId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({ id: userId, name: 'John' });
    }, 1000);
  });
}

// Using async/await
async function displayUser() {
  const user = await getUser(1);
  console.log('User:', user);
}

displayUser();
```

### Async/Await with Multiple Operations

```javascript
function getUser(userId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({ id: userId, name: 'John', departmentId: 5 });
    }, 1000);
  });
}

function getDepartment(deptId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({ id: deptId, name: 'Engineering' });
    }, 1000);
  });
}

function getProjects(deptId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(['Project A', 'Project B']);
    }, 1000);
  });
}

// ASYNC/AWAIT - Cleanest and most readable!
async function getUserInfo() {
  try {
    const user = await getUser(1);
    console.log('User:', user);
    
    const dept = await getDepartment(user.departmentId);
    console.log('Department:', dept);
    
    const projects = await getProjects(dept.id);
    console.log('Projects:', projects);
    
  } catch (error) {
    console.log('Error:', error);
  }
}

getUserInfo();
```

### Error Handling with Try/Catch

```javascript
async function fetchData(url) {
  try {
    const response = await fetch(url);
    const data = await response.json();
    console.log('Data:', data);
    return data;
    
  } catch (error) {
    console.log('Error fetching data:', error);
  }
  
  finally {
    console.log('Request completed');
  }
}

fetchData('/api/users');
```

### Async/Await with Parallel Operations

```javascript
async function loadData() {
  try {
    // Sequential - one after another
    const user = await getUser(1);
    const dept = await getDepartment(user.departmentId);
    
    // Parallel - all at once using Promise.all()
    const [posts, comments, likes] = await Promise.all([
      getPosts(user.id),
      getComments(user.id),
      getLikes(user.id)
    ]);
    
    console.log('User:', user);
    console.log('Posts:', posts);
    console.log('Comments:', comments);
    
  } catch (error) {
    console.log('Error:', error);
  }
}

loadData();
```

### Waiting for Multiple Values

```javascript
async function processData() {
  const promise1 = Promise.resolve(3);
  const promise2 = new Promise((resolve) => setTimeout(() => resolve('foo'), 100));
  const promise3 = fetch('/api/data').then((r) => r.json());
  
  const [result1, result2, result3] = await Promise.all([
    promise1,
    promise2,
    promise3
  ]);
  
  console.log(result1);  // 3
  console.log(result2);  // 'foo'
  console.log(result3);  // API response
}

processData();
```

### Practical Example: Login with Async/Await

```javascript
async function login(email, password) {
  try {
    const response = await fetch('/api/login', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ email, password })
    });
    
    const data = await response.json();
    
    if (!response.ok) {
      throw new Error(data.message || 'Login failed');
    }
    
    localStorage.setItem('token', data.token);
    console.log('Login successful');
    return data;
    
  } catch (error) {
    console.log('Login error:', error);
    throw error;
  }
}

async function getProfile(token) {
  const response = await fetch('/api/profile', {
    headers: { Authorization: `Bearer ${token}` }
  });
  
  return await response.json();
}

async function authenticateUser(email, password) {
  try {
    const loginData = await login(email, password);
    const profile = await getProfile(loginData.token);
    console.log('Profile:', profile);
    
  } catch (error) {
    console.log('Authentication failed:', error);
  }
}

authenticateUser('user@example.com', 'password');
```

### Async Functions Always Return Promises

```javascript
async function getValue() {
  return 42;
}

// getValue() returns a promise that resolves to 42
getValue().then((value) => {
  console.log(value);  // 42
});

// Can also await it
const value = await getValue();
console.log(value);  // 42
```

---

## Comparison: Callback vs Promise vs Async/Await

### Callback Hell
```javascript
getUser(1, (user) => {
  getDepartment(user.deptId, (dept) => {
    getProjects(dept.id, (projects) => {
      console.log(projects);
    });
  });
});
```

### Promise Chain
```javascript
getUser(1)
  .then((user) => getDepartment(user.deptId))
  .then((dept) => getProjects(dept.id))
  .then((projects) => console.log(projects))
  .catch((error) => console.log('Error:', error));
```

### Async/Await (Cleanest)
```javascript
async function loadData() {
  try {
    const user = await getUser(1);
    const dept = await getDepartment(user.deptId);
    const projects = await getProjects(dept.id);
    console.log(projects);
  } catch (error) {
    console.log('Error:', error);
  }
}

loadData();
```

---

## Complete Real-World Example: Data Processing Pipeline

```javascript
// Simulated API calls
function fetchUsers() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve([
        { id: 1, name: 'Alice' },
        { id: 2, name: 'Bob' }
      ]);
    }, 1000);
  });
}

function fetchUserPosts(userId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve([
        { id: 1, title: 'Post 1', userId },
        { id: 2, title: 'Post 2', userId }
      ]);
    }, 500);
  });
}

function fetchComments(postId) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve(['Comment 1', 'Comment 2']);
    }, 300);
  });
}

// Using async/await
async function loadAllData() {
  try {
    console.log('Fetching users...');
    const users = await fetchUsers();
    console.log('Users:', users);
    
    // Process each user
    for (const user of users) {
      console.log(`\nFetching posts for ${user.name}...`);
      const posts = await fetchUserPosts(user.id);
      console.log(`Posts for ${user.name}:`, posts);
      
      // Fetch comments for all posts in parallel
      const commentPromises = posts.map((post) => 
        fetchComments(post.id)
      );
      
      const allComments = await Promise.all(commentPromises);
      console.log('All comments:', allComments);
    }
    
  } catch (error) {
    console.log('Error:', error);
  } finally {
    console.log('\nData loading completed');
  }
}

loadAllData();
```

---

## Key Takeaways

| Approach | Pros | Cons |
|----------|------|------|
| **Callbacks** | Simple for single async operation | Callback hell, hard to read, error handling messy |
| **Promises** | Chain multiple operations, better error handling | Still requires multiple `.then()` calls |
| **Async/Await** | Looks synchronous, easy to read, clean error handling | Must use try/catch, requires ES2017+ |

**Best Practice**: Use **async/await** for modern JavaScript applications. It's the most readable and maintainable approach for handling asynchronous code.

# Window and Location Methods in JavaScript

## window.open()

Opens a new browser window or tab.

### Syntax

```javascript
const newWindow = window.open(url, target, features);
```

### Parameters

- `url` - The URL to load (optional, defaults to blank page)
- `target` - Where to open the page: `'_blank'` (new tab), `'_self'` (same window), `'_parent'`, `'_top'`, or a named window
- `features` - Comma-separated list of window features (width, height, etc.)

### Examples

#### Open a new tab

```javascript
const newTab = window.open('https://example.com', '_blank');
```

#### Open a new window with specific size

```javascript
const newWindow = window.open(
  'https://example.com',
  '_blank',
  'width=600,height=400,left=100,top=100'
);
```

#### Open in the same window

```javascript
window.open('https://example.com', '_self');
```

#### Practical Example: Open popup with close button

```javascript
const openPopupBtn = document.querySelector('#openPopup');

openPopupBtn.addEventListener('click', function() {
  const popup = window.open(
    'popup.html',
    'popup',
    'width=500,height=300,left=200,top=200'
  );
  
  if (!popup) {
    alert('Popup was blocked by the browser');
  }
});
```

## window.close()

Closes the current window or a previously opened window.

### Syntax

```javascript
window.close();
// or
windowObject.close();
```

### Examples

#### Close current window

```javascript
const closeBtn = document.querySelector('#closeBtn');

closeBtn.addEventListener('click', function() {
  window.close();
});
```

#### Close a popup window

```javascript
let popup;

document.querySelector('#openPopup').addEventListener('click', () => {
  popup = window.open('popup.html', 'popup', 'width=400,height=300');
});

document.querySelector('#closePopup').addEventListener('click', () => {
  if (popup) {
    popup.close();
  }
});
```

#### Practical Example: Confirm before closing

```javascript
const closeBtn = document.querySelector('#closeBtn');

closeBtn.addEventListener('click', function() {
  if (confirm('Are you sure you want to close this window?')) {
    window.close();
  }
});
```

## window.print()

Opens the print dialog for the current page.

### Syntax

```javascript
window.print();
```

### Examples

#### Simple print button

```javascript
const printBtn = document.querySelector('#printBtn');

printBtn.addEventListener('click', function() {
  window.print();
});
```

#### Print with confirmation

```javascript
document.querySelector('#printBtn').addEventListener('click', function() {
  if (confirm('Do you want to print this page?')) {
    window.print();
  }
});
```

#### Practical Example: Print specific content

```html
<button id="printInvoice">Print Invoice</button>

<div id="invoice" class="print-content">
  <h1>Invoice #12345</h1>
  <p>Amount: $100.00</p>
  <p>Date: 2024-01-31</p>
</div>
```

```javascript
document.querySelector('#printInvoice').addEventListener('click', function() {
  // Hide non-print elements
  document.body.style.display = 'none';
  document.querySelector('#invoice').style.display = 'block';
  
  window.print();
  
  // Restore page
  location.reload();
});
```

#### Using CSS for print

```css
@media print {
  .no-print {
    display: none;
  }
  
  .print-content {
    margin: 0;
    padding: 0;
  }
}
```

## history.back()

Goes back to the previous page (equivalent to clicking the back button).

### Syntax

```javascript
history.back();
```

### Examples

#### Simple back button

```javascript
const backBtn = document.querySelector('#backBtn');

backBtn.addEventListener('click', function() {
  history.back();
});
```

#### Practical Example: Confirm navigation

```javascript
document.querySelector('#backBtn').addEventListener('click', function() {
  if (confirm('You have unsaved changes. Go back anyway?')) {
    history.back();
  }
});
```

## history.forward()

Goes forward to the next page (equivalent to clicking the forward button).

### Syntax

```javascript
history.forward();
```

### Examples

#### Simple forward button

```javascript
const forwardBtn = document.querySelector('#forwardBtn');

forwardBtn.addEventListener('click', function() {
  history.forward();
});
```

## history.go()

Goes to a specific page in the session history.

### Syntax

```javascript
history.go(number);
```

### Parameters

- Positive numbers go forward
- Negative numbers go back
- 0 reloads the current page

### Examples

#### Go back 2 pages

```javascript
history.go(-2);
```

#### Go forward 1 page

```javascript
history.go(1);
```

#### Reload current page

```javascript
history.go(0);
// Same as location.reload()
```

#### Practical Example: Navigation controls

```javascript
const backBtn = document.querySelector('#backBtn');
const forwardBtn = document.querySelector('#forwardBtn');
const reloadBtn = document.querySelector('#reloadBtn');

backBtn.addEventListener('click', () => history.back());
forwardBtn.addEventListener('click', () => history.forward());
reloadBtn.addEventListener('click', () => history.go(0));
```

#### Go back to a specific page in history

```javascript
document.querySelector('#goBack3').addEventListener('click', () => {
  history.go(-3);  // Go back 3 pages
});
```

## location.replace()

Replaces the current page in the history with a new page. Unlike regular navigation, the current page is not saved in history.

### Syntax

```javascript
location.replace(url);
```

### Examples

#### Simple redirect

```javascript
location.replace('https://example.com');
```

#### Redirect after login

```javascript
document.querySelector('#loginForm').addEventListener('submit', async (e) => {
  e.preventDefault();
  
  const response = await fetch('/api/login', {
    method: 'POST',
    body: new FormData(e.target)
  });
  
  if (response.ok) {
    location.replace('/dashboard');  // User can't go back to login
  }
});
```

#### Practical Example: Redirect if not authenticated

```javascript
function checkAuth() {
  const token = localStorage.getItem('authToken');
  
  if (!token) {
    location.replace('/login');  // Redirect without history
  }
}

checkAuth();
```

#### Replace vs regular navigation

```javascript
// Regular navigation - user can go back
location.href = 'page2.html';

// Replace - user CANNOT go back to this page
location.replace('page2.html');
```

## Other Useful location Properties and Methods

### location.href

Gets or sets the complete URL of the page.

```javascript
// Get current URL
const currentUrl = location.href;
console.log(currentUrl);

// Navigate to new page (saves in history)
location.href = 'https://example.com';

// Practical example: redirect with delay
setTimeout(() => {
  location.href = '/thank-you';
}, 3000);
```

### location.pathname

Gets the path portion of the URL.

```javascript
// If URL is https://example.com/products/shoes
console.log(location.pathname);  // /products/shoes
```

### location.hostname

Gets the domain name.

```javascript
// If URL is https://example.com/page
console.log(location.hostname);  // example.com
```

### location.search

Gets the query string from the URL.

```javascript
// If URL is https://example.com?id=123&name=alice
console.log(location.search);  // ?id=123&name=alice

// Parse query parameters
const params = new URLSearchParams(location.search);
console.log(params.get('id'));    // 123
console.log(params.get('name'));  // alice
```

#### Practical Example: Read query parameters

```javascript
function getQueryParam(param) {
  const params = new URLSearchParams(location.search);
  return params.get(param);
}

const userId = getQueryParam('id');
console.log('User ID:', userId);
```

### location.hash

Gets the fragment identifier (hash) from the URL.

```javascript
// If URL is https://example.com#section2
console.log(location.hash);  // #section2

// Listen for hash changes
window.addEventListener('hashchange', () => {
  console.log('Hash changed to:', location.hash);
});
```

#### Practical Example: Single-page app routing

```javascript
function handleRouting() {
  const hash = location.hash.slice(1);  // Remove #
  
  if (hash === 'home') {
    showHome();
  } else if (hash === 'about') {
    showAbout();
  } else if (hash === 'contact') {
    showContact();
  }
}

window.addEventListener('hashchange', handleRouting);
window.addEventListener('load', handleRouting);

// Navigation
document.querySelector('#homeLink').addEventListener('click', () => {
  location.hash = 'home';
});
```

### location.protocol

Gets the protocol (http, https, etc.).

```javascript
console.log(location.protocol);  // https:

// Check if secure
if (location.protocol === 'https:') {
  console.log('This is a secure connection');
}
```

### location.reload()

Reloads the current page.

```javascript
// Reload from cache
location.reload();

// Reload from server (bypass cache)
location.reload(true);
```

#### Practical Example: Refresh data

```javascript
const refreshBtn = document.querySelector('#refreshBtn');

refreshBtn.addEventListener('click', () => {
  location.reload();
});
```

## Complete Example: Navigation Menu

```javascript
// Navigation with all methods
const navMenu = {
  back: () => history.back(),
  forward: () => history.forward(),
  goBack3: () => history.go(-3),
  reload: () => location.reload(),
  goHome: () => location.href = '/',
  replaceWithLogin: () => location.replace('/login'),
  openNewTab: () => window.open('https://example.com', '_blank'),
  print: () => window.print(),
};

// Attach to buttons
document.querySelector('#backBtn').addEventListener('click', navMenu.back);
document.querySelector('#forwardBtn').addEventListener('click', navMenu.forward);
document.querySelector('#reloadBtn').addEventListener('click', navMenu.reload);
document.querySelector('#homeBtn').addEventListener('click', navMenu.goHome);
document.querySelector('#printBtn').addEventListener('click', navMenu.print);
document.querySelector('#newTabBtn').addEventListener('click', navMenu.openNewTab);
```

## Key Differences

| Method | Saves in History | Use Case |
|--------|-----------------|----------|
| `location.href` | Yes | Regular navigation |
| `location.replace()` | No | Redirect user away (no going back) |
| `history.back()` | No (just uses history) | Go back one page |
| `window.open()` | Yes (in new tab/window) | Open new window |










# JavaScript Event Listener 

## 1. addEventListener() - The Standard Method

```javascript
const button = document.getElementById('myButton');

button.addEventListener('click', function(event) {
  console.log('Button clicked!');
});

// With arrow function
button.addEventListener('click', (event) => {
  console.log('Button clicked!');
});

// With named function
function handleClick(event) {
  console.log('Button clicked!');
}
button.addEventListener('click', handleClick);
```

**Pros:**
- Can attach multiple handlers to the same event
- Can remove listeners with `removeEventListener()`
- Best practice for modern JavaScript

**Cons:**
- Slightly more verbose than alternatives

---

## 2. DOM Property Event Handlers

```javascript
const button = document.getElementById('myButton');

button.onclick = function(event) {
  console.log('Button clicked!');
};

// Or with arrow function
button.onclick = (event) => {
  console.log('Button clicked!');
};
```

**Pros:**
- Simple and concise syntax
- Easy to read

**Cons:**
- Only one handler per event type (overwrites previous handlers)
- Can't remove handler without setting to `null`

---

## 3. Inline Event Handlers (HTML attributes)

```html
<button onclick="handleClick(event)">Click me</button>

<script>
function handleClick(event) {
  console.log('Button clicked!');
}
</script>
```

**Pros:**
- Quick for prototyping

**Cons:**
- Mixes HTML and JavaScript (violates separation of concerns)
- Harder to maintain
- Security concerns (can expose to XSS)
- **Not recommended for production code**

---

## 4. Event Delegation

```javascript
// Instead of adding listeners to multiple elements,
// add one listener to their parent
document.body.addEventListener('click', function(event) {
  // Check if the clicked element matches your selector
  if (event.target.matches('.my-button')) {
    console.log('Button clicked!');
  }
});

// Works with dynamically added elements too!
// Even if buttons are added later, the listener still works
```

**Pros:**
- Efficient for many similar elements
- Works with dynamically added elements
- Better performance
- Single listener instead of many

**Cons:**
- Slightly more complex logic
- Need to check event.target

---

## 5. jQuery (if you're using it)

```javascript
$('#myButton').on('click', function(event) {
  console.log('Button clicked!');
});

// Or shorthand
$('#myButton').click(function(event) {
  console.log('Button clicked!');
});

// Event delegation in jQuery
$('body').on('click', '.my-button', function(event) {
  console.log('Button clicked!');
});
```

**Pros:**
- Simple syntax
- Cross-browser compatibility
- Built-in event delegation

**Cons:**
- Requires jQuery library
- Overkill if only using for events

---




## Common Events You Can Listen For

- `click` - Mouse click
- `dblclick` - Double click
- `mousedown` / `mouseup` - Mouse button press/release
- `mouseover` / `mouseout` - Mouse enters/leaves element
- `keydown` / `keyup` / `keypress` - Keyboard events
- `submit` - Form submission
- `change` - Input value changes
- `input` - Input value changes (fires immediately)
- `focus` / `blur` - Element gains/loses focus
- `load` - Page or image finishes loading
- `scroll` - User scrolls

---

## Recommendation

For most modern JavaScript projects:
- **Use `addEventListener()`** as your default choice
- **Use event delegation** when dealing with many similar elements or dynamically added content
- **Avoid inline HTML handlers** in production code
- Use DOM property handlers (`onclick`, etc.) only for simple, one-off cases





# Event Propagation in JavaScript: Capturing vs. Bubbling

When an event occurs on a DOM element, it doesn't just fire on that single element. Instead, it propagates through the DOM tree in three phases:

## The Three Phases

1. **Capturing phase** (or "trickling") - event travels DOWN from the root to the target
2. **Target phase** - event reaches the actual target element
3. **Bubbling phase** - event travels UP from the target back to the root

## Visual Flow
```
Document Root
    ↓ Capturing
  <div>
    ↓ Capturing
  <button> ← Target
    ↑ Bubbling
  </div>
    ↑ Bubbling
Document Root
```

## addEventListener Syntax
```javascript
element.addEventListener(event, handler, useCapture);
```

- `useCapture` is `false` by default (bubbling phase)
- Set to `true` to listen during capturing phase

## Bubbling (Default Behavior)

Most common and the default. Events bubble UP from the target to ancestors:
```javascript
document.querySelector('.parent').addEventListener('click', () => {
  console.log('Parent clicked');
});

document.querySelector('.child').addEventListener('click', () => {
  console.log('Child clicked');
});

// Clicking child logs:
// "Child clicked"
// "Parent clicked"
```

## Capturing

Events capture DOWN from root to target:
```javascript
document.querySelector('.parent').addEventListener('click', () => {
  console.log('Parent clicked');
}, true); // Note the 'true'

document.querySelector('.child').addEventListener('click', () => {
  console.log('Child clicked');
}, true);

// Clicking child logs:
// "Parent clicked"
// "Child clicked"
```

## Stopping Propagation
```javascript
element.addEventListener('click', (e) => {
  e.stopPropagation(); // Stops bubbling/capturing
  e.stopImmediatePropagation(); // Also stops other handlers on same element
});
```

## Practical Use Cases

**Bubbling** is useful for:
- Event delegation (handling events on many children via one parent listener)
- Most general event handling

**Capturing** is useful for:
- Intercepting events before they reach their targets
- Implementing features like global click-outside handlers
- Preventing default behavior before child handlers run

## Events That Don't Bubble

Some events don't bubble: `focus`, `blur`, `load`, `unload`, `scroll` (in some cases). Use their bubbling equivalents like `focusin`/`focusout` if needed.

# to use script in the begining of the html instead of the end

  normally you have to write script in the end of the html to wait for the dom to load
  but if you use 
  < script type = module> you can put it on top!! also i alows you to export the stuff in the scrip outside
  using export



# AJAX
 What is AJAX?AJAX stands for Asynchronous JavaScript and XML. It's a technique that allows web pages to send and receive data from a server asynchronously without reloading the page. This creates a smoother, more responsive user experience.

# default
  Default Export Syntax
  javascript// Class definition and default export
  export default class User {
    constructor(name, age) {
      this.name = name;
      this.age = age;
    }
    
    display() {
      console.log(`${this.name} is ${this.age} years old`);
    }
  }
  Importing Default Export
  javascript// Import the default export with any name you want
  import User from './User.js';

  const user = new User('John', 25);
  user.display();  // John is 25 years old



# to be organized



what are classes actually in javascript

import export native code

default in exporting classes

date start from sundaty and ends at saturday

getyear vs getfull year

functions are objcts 

hello + undefined = helloundefined

getbyclassName can be used when we add elemetns dyynamically since it returns a collection 

querySelectorAll returns a node list and doesnt append

from creates a new array with the elements of the array passes shallow copied

event object
this === e.target
array.from() //shallow copy values and returns a new array

transpiler ??
the new js and the frameworks transforms the new script into the native one

zzz=300 //global variable

babel

switch uses triple equal

e.key gets you key value
e.code get you physical key value

destructring 
let x=[1,2];
let [first,second] = x
console.log(first,second) //1 2
// swap
let first = 1;
let second =2;
[first,second] = [second,first];
console.log(first,second) //2 1

property object and how does classes work etc

array.at().  supports negative index

let is also hoisted but restiricts access to the variable until initiliazed

template literal : `${variable}`

in the arrow function , its this is taken from the prev scope not the this of the caller

... //search  // it uses polling not looping spread
if while for isnt considered scope
var z = 10;
var z. // this is nt an update z is equal to 10

hoisting only happens to var

ways to handle events in js

finish the desgin first

submit reloads the page by default

textContent vs createTextNode + append. 
first overwrites , second appends
query selector returns an element object representing the first element in the document that matches the specified set of CSS selectors, or null is returned if there are no matches.

If you need a list of all elements matching the specified selectors, you should use querySelectorAll() instead.


for variable in object
each of the variables is treated as a string object
for variable of object
each of the variables is treated as values instead