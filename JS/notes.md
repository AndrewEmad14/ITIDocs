date start from sundaty and ends at saturday

getyear vs getfull year

functions are objcts 

hello + undefined = helloundefined



from creates a new array with the elements of the array passes shallow copied


array.from() //shallow copy values and returns a new array

zzz=300 //global variable

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