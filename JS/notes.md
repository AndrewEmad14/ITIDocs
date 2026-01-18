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











not using corse or https error in. web
type = module
export keyword

sync must all finish and then the async code will execute

call back hell
  callback(){
    let x;
      callback(){
        x=5
        callback(){
          x+=1
        }
      }
  }
  //code back expands horizontly
ajax is concept to request without refresh

  promises sperate the declration from the usage

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