# 📘 Complete CSS Cheat Sheet: Modern & Essential Properties

A comprehensive guide to CSS styling with practical examples, best practices, and selector specificity scoring.

---

## 🎯 CSS Selector Specificity

Understanding specificity is crucial for writing maintainable CSS. Specificity determines which style rules are applied when multiple rules target the same element.

### Specificity Calculation

Specificity is calculated as a four-part value: `(a, b, c, d)`

- **a**: Inline styles (`style="..."`)
- **b**: IDs (`#id`)
- **c**: Classes, attributes, pseudo-classes (`.class`, `[attr]`, `:hover`)
- **d**: Elements and pseudo-elements (`div`, `::before`)

### Examples

```css
/* Specificity: (0, 0, 0, 1) */
p { color: blue; }

/* Specificity: (0, 0, 1, 1) */
p.intro { color: blue; }

/* Specificity: (0, 1, 0, 0) */
#header { color: blue; }

/* Specificity: (0, 1, 1, 2) */
#nav .menu li { color: blue; }

/* Specificity: (1, 0, 0, 0) */
<div style="color: blue;"></div>

/* Specificity: (0, 0, 0, 0) - Universal selector */
* { margin: 0; }
```

### Specificity Hierarchy (Lowest to Highest)

```
1. Universal selector (*)                    → (0, 0, 0, 0)
2. Element selectors                         → (0, 0, 0, 1)
3. Class, attribute, pseudo-class            → (0, 0, 1, 0)
4. ID selectors                              → (0, 1, 0, 0)
5. Inline styles (style="...")               → (1, 0, 0, 0)
6. !important (use sparingly)                → Overrides all
```

### Best Practice for Specificity

- Keep specificity as **low as possible**
- Avoid using IDs for styling (reserve for JavaScript)
- Use classes for reusable styles
- Avoid excessive nesting (max 3 levels deep)
- Never use `!important` except in utilities or reset styles

---

## 📦 BOX MODEL & LAYOUT

### `display`

Controls how an element is rendered.

```css
/* Block element - full width, starts new line */
div { display: block; }

/* Inline element - flows with text, ignores width/height */
span { display: inline; }

/* Inline-block - flows inline but respects width/height */
button { display: inline-block; }

/* Flex container - powerful 1D layout */
.container { 
  display: flex;
  justify-content: center;
  align-items: center;
  gap: 1rem;
}

/* Grid container - powerful 2D layout */
.gallery {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  gap: 2rem;
}

/* Hide element but keep layout space */
.hidden { display: none; }

/* Hide but keep layout space (see visibility) */
.invisible { visibility: hidden; }
```

**Best Practice**: Use `flex` or `grid` for modern layouts. Avoid floats except in legacy code.

---

### `margin` & `padding`

Spacing around and inside elements.

```css
/* Padding: inside space */
.box {
  padding: 1rem;                    /* All sides */
  padding: 1rem 2rem;               /* Top/Bottom, Left/Right */
  padding: 1rem 2rem 3rem 4rem;     /* Top, Right, Bottom, Left (TRBL) */
}

/* Margin: outside space */
.element {
  margin: 0 auto;                   /* Center element horizontally */
  margin: 1rem;                     /* All sides */
}

/* Collapsing margins (block elements only) */
.parent { margin-bottom: 2rem; }
.child { margin-top: 1rem; }
/* Result: 2rem gap (larger margin wins) */

/* Using CSS variables for consistency */
:root { --spacing-unit: 1rem; }
.section { padding: var(--spacing-unit); }
```

**Best Practice**: Use consistent spacing scales. Use `margin: 0 auto` for centering blocks. Be aware of margin collapse in block layouts.

---

### `width` & `height`

Dimension properties.

```css
/* Fixed dimensions */
.box { width: 200px; height: 100px; }

/* Percentages (relative to parent) */
.sidebar { width: 25%; }

/* Flexible sizing */
.item {
  width: 100%;                      /* Full parent width */
  max-width: 1200px;               /* Don't exceed max */
  min-width: 200px;                /* Don't go below min */
}

/* Aspect ratio (modern) */
.video-container {
  aspect-ratio: 16 / 9;
  width: 100%;
}

/* Auto sizing */
.content { width: auto; }           /* Shrink to content */

/* Use viewport units carefully */
.full-height { 
  height: 100vh;                    /* Full viewport height */
  height: 100svh;                   /* Small viewport height (mobile) */
}
```

**Best Practice**: Avoid fixed heights for text containers. Use `max-width` on text content (readable line length ~65-75 chars). Prefer `aspect-ratio` over padding hacks.

---

## 🎨 COLORS & BACKGROUNDS

### `color` & `background-color`

Text and background colors.

```css
/* Named colors */
.text { color: blue; }

/* Hex colors */
.accent { color: #ff6b6b; }

/* RGB/RGBA */
.transparent { color: rgba(255, 107, 107, 0.8); }

/* HSL (easier to adjust) */
.hue { color: hsl(0, 100%, 50%); }

/* Modern: relative colors */
.lighter { color: hsl(from #ff6b6b h s calc(l + 20%)); }

/* CSS variables for theming */
:root {
  --primary: #ff6b6b;
  --secondary: #4ecdc4;
}
.button { background-color: var(--primary); }

/* Dark mode */
@media (prefers-color-scheme: dark) {
  :root {
    --primary: #ff8787;
    --secondary: #80deea;
  }
}
```

### `background`

Background styling and images.

```css
/* Simple background */
.box { background: #f0f0f0; }

/* Image background */
.hero {
  background-image: url('hero.jpg');
  background-size: cover;           /* Cover entire element */
  background-position: center;      /* Center the image */
  background-attachment: fixed;    /* Parallax effect */
  background-repeat: no-repeat;
}

/* Multiple backgrounds */
.card {
  background-image: 
    linear-gradient(135deg, #667eea 0%, #764ba2 100%),
    url('pattern.png');
  background-size: 100% 100%, auto;
}

/* Gradient */
.gradient {
  background: linear-gradient(
    to right,
    #ff6b6b,
    #4ecdc4
  );
}

/* Radial gradient */
.circle {
  background: radial-gradient(
    circle at center,
    #ff6b6b 0%,
    #764ba2 100%
  );
}

/* Conic gradient (pie chart colors) */
.wheel {
  background: conic-gradient(
    from 0deg,
    red,
    yellow,
    lime,
    blue,
    red
  );
}
```

**Best Practice**: Use gradients instead of images for better performance. Always provide fallback colors. Use `background-size: cover` with caution on mobile (can clip content).

---

## 🔤 TYPOGRAPHY

### `font-family`

Font typeface selection.

```css
/* System fonts (fastest) */
body { font-family: system-ui, -apple-system, sans-serif; }

/* Web fonts */
@font-face {
  font-family: 'CustomFont';
  src: url('font.woff2') format('woff2');
  font-weight: 400;
  font-display: swap;               /* Show fallback while loading */
}

/* Font stack (fallback chain) */
h1 {
  font-family: 'Georgia', 'Times New Roman', serif;
  /* Try Georgia, then Times, then any serif */
}

/* Generic families */
/* serif, sans-serif, monospace, cursive, fantasy, system-ui */
```

### `font-size`, `font-weight`, `line-height`

Text sizing and weight.

```css
/* Absolute sizing */
.heading { font-size: 2rem; }
.body { font-size: 1rem; }

/* Relative sizing */
.small { font-size: 0.875rem; }      /* Relative to parent */
.large { font-size: 1.25em; }        /* em = parent's font-size */

/* Font weights */
.light { font-weight: 300; }
.regular { font-weight: 400; }       /* Default */
.bold { font-weight: 700; }

/* Or use named weights */
strong { font-weight: bold; }
.thin { font-weight: 100; }

/* Line height for readability */
.article {
  font-size: 1.1rem;
  line-height: 1.6;                  /* Unitless = multiplier of font-size */
  letter-spacing: 0.5px;             /* Space between letters */
}

/* Text transformation */
.uppercase { text-transform: uppercase; }
.title-case { text-transform: capitalize; }
```

**Best Practice**: Use `line-height: 1.5-1.8` for body text. Use `1rem` as base, scale with multipliers. Prefer semantic font weights (400, 700) for consistency.

---

### `text-align`, `text-decoration`, `text-overflow`

Text alignment and styling.

```css
/* Text alignment */
.center { text-align: center; }
.left { text-align: left; }
.right { text-align: right; }
.justify { text-align: justify; }    /* Avoid - poor readability */

/* Text decoration */
a {
  text-decoration: underline;
  text-decoration-color: blue;
  text-decoration-thickness: 2px;
  text-underline-offset: 4px;
}

.no-underline { text-decoration: none; }

/* Text shadow */
h1 {
  text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
}

/* Text overflow handling */
.truncate {
  white-space: nowrap;               /* Prevent wrapping */
  overflow: hidden;
  text-overflow: ellipsis;           /* Show ... at end */
}

/* Multiple lines truncation */
.clamp-lines {
  display: -webkit-box;
  -webkit-line-clamp: 3;             /* Show max 3 lines */
  -webkit-box-orient: vertical;
  overflow: hidden;
}
```

---

## 🌈 EFFECTS & TRANSFORMATIONS

### `box-shadow`

Shadow effects around elements.

```css
/* Simple shadow */
.card {
  box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

/* Offset shadows */
.elevated {
  box-shadow: 5px 5px 15px rgba(0,0,0,0.2);
  /* offset-x, offset-y, blur-radius, spread-radius, color */
}

/* Multiple shadows (layering) */
.depth {
  box-shadow: 
    0 1px 3px rgba(0,0,0,0.12),
    0 1px 2px rgba(0,0,0,0.24);
}

/* Inset shadow */
.inset {
  box-shadow: inset 0 2px 4px rgba(0,0,0,0.2);
}
```

**Best Practice**: Layer multiple shadows for depth. Keep blur radius moderate (4-15px). Use subtle shadows on light backgrounds, stronger on dark.

---

### `transform`

Modify element appearance without affecting layout.

```css
/* Translation (movement) */
.slide {
  transform: translateX(10px);       /* Move right 10px */
  transform: translateY(-5px);       /* Move up 5px */
  transform: translate(10px, -5px);  /* Both axes */
}

/* Scale (resize) */
.zoom {
  transform: scale(1.2);             /* 120% of original */
  transform: scaleX(1.5);            /* Stretch horizontally */
}

/* Rotation */
.spin {
  transform: rotate(45deg);          /* Clockwise rotation */
}

/* Skew (shear) */
.skew {
  transform: skewX(10deg);           /* Shear horizontally */
}

/* Combined transforms (order matters!) */
.complex {
  transform: translateX(50px) rotate(45deg) scale(1.2);
}

/* 3D transforms */
.perspective {
  perspective: 1000px;
}

.flip {
  transform: rotateY(180deg);        /* Flip around Y axis */
  transform: rotateX(90deg);         /* Flip around X axis */
}

/* Transform origin (pivot point) */
.rotate-from-corner {
  transform-origin: bottom right;
  transform: rotate(45deg);
}
```

**Best Practice**: Transforms don't trigger layout recalculation (very performant). Use `transform` for animations instead of changing `left`/`top`. Always define `transform-origin` if not using center.

---

### `opacity`

Element transparency.

```css
/* Full opacity to transparent */
.fade {
  opacity: 1;                        /* Fully opaque */
  opacity: 0.5;                      /* 50% transparent */
  opacity: 0;                        /* Fully transparent */
}

/* Hover effect */
button:hover {
  opacity: 0.8;                      /* Subtle hover feedback */
}
```

**Best Practice**: Use `opacity` for fade effects. For color transparency, use `rgba()` or `hsla()` instead.

---

### `filter`

Visual effects (blur, brightness, etc.).

```css
/* Blur effect */
.blur { filter: blur(5px); }

/* Brightness adjustment */
.dim { filter: brightness(0.7); }
.bright { filter: brightness(1.2); }

/* Contrast */
.high-contrast { filter: contrast(1.5); }

/* Grayscale */
.grayscale { filter: grayscale(100%); }
.partial-gray { filter: grayscale(50%); }

/* Hue rotation */
.red-to-purple { filter: hue-rotate(45deg); }

/* Saturation */
.vibrant { filter: saturate(2); }

/* Combining filters */
.artistic {
  filter: brightness(1.1) saturate(1.2) contrast(1.1);
}

/* Drop shadow (similar to box-shadow but applies to shape) */
.shadow {
  filter: drop-shadow(5px 5px 10px rgba(0,0,0,0.3));
}
```

**Best Practice**: Filters can be expensive (GPU intensive). Use sparingly for animations. `drop-shadow` works on transparent images; `box-shadow` doesn't.

---

## 🎬 ANIMATIONS & TRANSITIONS

### `transition`

Smooth property changes.

```css
/* Basic transition */
button {
  background-color: blue;
  transition: background-color 0.3s ease;
}

button:hover {
  background-color: darkblue;
}

/* Transition multiple properties */
.box {
  transition: 
    background-color 0.3s ease,
    transform 0.2s ease-out,
    opacity 0.3s linear;
}

/* Transition all properties (use cautiously) */
.element {
  transition: all 0.3s ease;
}

/* Transition timing functions */
.linear { transition-timing-function: linear; }
.ease { transition-timing-function: ease; }
.ease-in { transition-timing-function: ease-in; }
.ease-out { transition-timing-function: ease-out; }
.ease-in-out { transition-timing-function: ease-in-out; }

/* Cubic bezier for custom timing */
.custom {
  transition-timing-function: cubic-bezier(0.68, -0.55, 0.265, 1.55);
}

/* Transition delay */
.delayed {
  transition: all 0.3s ease 0.1s;    /* 0.1s delay before transition */
}
```

**Best Practice**: Specify properties you're transitioning (not `all`). Use `ease-out` for entering, `ease-in` for leaving. Keep durations 0.2-0.4s for UI, longer for large movements.

---

### `animation`

Keyframe animations.

```css
/* Define animation */
@keyframes slide-in {
  from {
    opacity: 0;
    transform: translateX(-100px);
  }
  to {
    opacity: 1;
    transform: translateX(0);
  }
}

/* Apply animation */
.animated {
  animation: slide-in 0.5s ease-out;
}

/* Detailed animation properties */
.element {
  animation-name: slide-in;
  animation-duration: 0.5s;
  animation-timing-function: ease-out;
  animation-delay: 0.1s;
  animation-iteration-count: 1;      /* How many times */
  animation-direction: normal;       /* or reverse, alternate */
  animation-fill-mode: forwards;     /* Keep end state */
}

/* Shorthand */
.short {
  animation: slide-in 0.5s ease-out 0.1s 1 normal forwards;
}

/* Infinite animation */
.spin {
  animation: rotate 2s linear infinite;
}

@keyframes rotate {
  from { transform: rotate(0deg); }
  to { transform: rotate(360deg); }
}

/* Percentage-based keyframes */
@keyframes bounce {
  0% { transform: translateY(0); }
  25% { transform: translateY(-10px); }
  50% { transform: translateY(0); }
  75% { transform: translateY(-5px); }
  100% { transform: translateY(0); }
}

/* Pause animation on hover */
.animation-play {
  animation: bounce 1s ease-in-out infinite;
}

.animation-play:hover {
  animation-play-state: paused;
}
```

**Best Practice**: Use `animation-fill-mode: forwards` to keep end state. Use `animation-play-state: paused` for interactive control. Prefer shorter durations (0.5-1s) for UI animations.

---

## 🎯 POSITIONING & LAYERING

### `position`

Element positioning context.

```css
/* Static (default) */
.default { position: static; }       /* Normal document flow */

/* Relative positioning */
.relative {
  position: relative;
  top: 10px;                         /* Offset from original position */
  left: 5px;
}

/* Absolute positioning (relative to nearest positioned ancestor) */
.modal {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);  /* Center trick */
}

/* Fixed positioning (relative to viewport) */
.sticky-nav {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1000;                     /* Keep above other content */
}

/* Sticky positioning (hybrid of relative + fixed) */
.sticky-header {
  position: sticky;
  top: 0;
  background: white;
  z-index: 10;                       /* Must have z-index for scroll context */
}
```

### `z-index`

Layering order (only works with positioned elements).

```css
/* z-index creates stacking context */
.background { z-index: 1; }
.middle { z-index: 10; }
.foreground { z-index: 100; }

/* Common layering scale */
:root {
  --z-dropdown: 100;
  --z-modal: 1000;
  --z-toast: 2000;
}

/* Stacking contexts prevent z-index wars */
.modal-backdrop {
  position: fixed;
  z-index: 999;
}

.modal {
  position: fixed;
  z-index: 1000;
}
```

**Best Practice**: Use consistent z-index naming/variables. Keep fixed/sticky elements in high ranges. Remember: `z-index` only works with positioned elements (`position` != `static`).

---

## 🔍 BORDERS & OUTLINES

### `border`

Element borders.

```css
/* Simple border */
.box {
  border: 1px solid black;           /* width, style, color */
}

/* Individual sides */
.box {
  border-top: 2px solid red;
  border-right: 3px dashed blue;
  border-bottom: 1px dotted green;
  border-left: 4px double orange;
}

/* Border radius (rounded corners) */
.rounded {
  border-radius: 8px;                /* All corners */
  border-radius: 50%;                /* Circle */
  border-radius: 8px 0;              /* Top-left/right and bottom-right/left */
}

/* Asymmetric radius */
.custom {
  border-radius: 10px 20px 30px 40px;  /* TL, TR, BR, BL */
}

/* Border styles */
.solid { border: 1px solid black; }
.dashed { border: 1px dashed black; }
.dotted { border: 1px dotted black; }
.double { border: 3px double black; }

/* Border with image */
.image-border {
  border: 10px solid transparent;
  border-image: url('border.png') 10 stretch;
}
```

### `outline`

Outline (outside border, doesn't affect layout).

```css
/* Outline */
.focus:focus {
  outline: 2px solid blue;
  outline-offset: 2px;               /* Space between element and outline */
}

/* Remove default outline (accessibility concern - provide alternative) */
button:focus {
  outline: none;
  box-shadow: 0 0 0 3px rgba(66, 153, 225, 0.5);
}
```

**Best Practice**: Never remove `outline` without providing a focus indicator. Keep `outline-offset` positive for better visibility.

---

## 🎭 PSEUDO-CLASSES & PSEUDO-ELEMENTS

### Pseudo-Classes (Select based on state)

```css
/* Link states */
a:link { color: blue; }
a:visited { color: purple; }
a:hover { color: red; }
a:active { color: darkred; }

/* Form states */
input:focus { border-color: blue; }
input:disabled { opacity: 0.5; }
input:checked { background: green; }

/* Child selection */
li:first-child { margin-top: 0; }
li:last-child { margin-bottom: 0; }
li:nth-child(2n) { background: #f0f0f0; }    /* Even children */
li:nth-child(odd) { background: white; }     /* Odd children */

/* Type-based */
p:only-of-type { margin: 0; }
div:empty { display: none; }

/* Target and focus */
a:target { background: yellow; }
*:focus { outline: 2px solid blue; }

/* User interaction */
button:hover:active { transform: scale(0.95); }
```

### Pseudo-Elements (Create virtual elements)

```css
/* ::before and ::after */
.icon::before {
  content: "→";
  margin-right: 0.5rem;
}

/* Clear floats (old method) */
.clearfix::after {
  content: "";
  display: table;
  clear: both;
}

/* Decorative lines */
h2::before {
  content: "";
  display: inline-block;
  width: 4px;
  height: 1em;
  background: blue;
  margin-right: 0.5em;
}

/* Selection styling */
::selection {
  background: yellow;
  color: black;
}

/* Scrollbar styling (browser-specific) */
::-webkit-scrollbar { width: 10px; }
::-webkit-scrollbar-track { background: #f0f0f0; }
::-webkit-scrollbar-thumb { background: #888; }

/* Placeholder text */
input::placeholder {
  color: #999;
  opacity: 1;
}

/* First letter/line */
p::first-letter { font-size: 2em; font-weight: bold; }
p::first-line { color: blue; }
```

**Best Practice**: Use `::before` and `::after` for decorative elements only. Don't hide important content in pseudo-elements.

---

## 📱 RESPONSIVE DESIGN

### `@media` Queries

Responsive styling based on device features.

```css
/* Mobile-first approach */
.container {
  width: 100%;
  padding: 1rem;
}

/* Tablet and up */
@media (min-width: 768px) {
  .container {
    width: 750px;
    margin: 0 auto;
  }
}

/* Desktop and up */
@media (min-width: 1024px) {
  .container {
    width: 960px;
  }
}

/* Large desktop */
@media (min-width: 1440px) {
  .container {
    width: 1200px;
  }
}

/* Orientation */
@media (orientation: portrait) {
  body { font-size: 14px; }
}

@media (orientation: landscape) {
  body { font-size: 16px; }
}

/* Dark mode */
@media (prefers-color-scheme: dark) {
  body {
    background: #1a1a1a;
    color: #f0f0f0;
  }
}

/* Reduced motion (accessibility) */
@media (prefers-reduced-motion: reduce) {
  * {
    animation-duration: 0.01ms !important;
    transition-duration: 0.01ms !important;
  }
}

/* Light mode */
@media (prefers-color-scheme: light) {
  body {
    background: white;
    color: #333;
  }
}

/* High contrast mode */
@media (prefers-contrast: more) {
  body {
    border: 2px solid;
    font-weight: bold;
  }
}
```

**Best Practice**: Use mobile-first approach (`min-width`). Use semantic breakpoints (tablet, desktop). Always respect `prefers-reduced-motion` and `prefers-color-scheme`.

---

## 🔧 FLEXBOX DEEP DIVE

```css
/* Flex container */
.container {
  display: flex;
  
  /* Direction of main axis */
  flex-direction: row;                /* default: left to right */
  /* flex-direction: column; */       /* top to bottom */
  /* flex-direction: row-reverse; */  /* right to left */
  
  /* Alignment on main axis */
  justify-content: flex-start;        /* default */
  justify-content: center;            /* center items */
  justify-content: space-between;     /* distribute with gaps */
  justify-content: space-around;      /* gaps around items */
  justify-content: space-evenly;      /* equal gaps everywhere */
  
  /* Alignment on cross axis */
  align-items: flex-start;
  align-items: center;                /* center on cross axis */
  align-items: stretch;               /* default: fill cross axis */
  
  /* Multiple lines of items */
  flex-wrap: nowrap;                  /* default: single line */
  flex-wrap: wrap;                    /* multiple lines */
  
  /* Alignment of wrapped lines */
  align-content: center;
  align-content: space-between;
  
  /* Gap between items */
  gap: 1rem;
  column-gap: 2rem;
  row-gap: 1rem;
}

/* Flex items */
.item {
  /* Growth factor (when extra space available) */
  flex-grow: 0;                       /* default */
  flex-grow: 1;                       /* grow equally */
  
  /* Shrink factor (when space constrained) */
  flex-shrink: 1;                     /* default */
  flex-shrink: 0;                     /* don't shrink */
  
  /* Base size before growth/shrink */
  flex-basis: auto;                   /* default */
  flex-basis: 200px;
  
  /* Shorthand: flex: grow shrink basis */
  flex: 1 1 0;                        /* equal growth/shrink, no base size */
  flex: 1;                            /* shorthand for above */
  
  /* Individual alignment override */
  align-self: center;
  align-self: flex-end;
  
  /* Exact width */
  width: 200px;
}
```

**Best Practice**: Use `flex: 1` for equal-width items. Use `justify-content` for main axis, `align-items` for cross axis. Use `gap` instead of margins.

---

## 📊 GRID DEEP DIVE

```css
/* Grid container */
.grid {
  display: grid;
  
  /* Define columns */
  grid-template-columns: 1fr 2fr 1fr;           /* 3 columns: 1:2:1 ratio */
  grid-template-columns: repeat(3, 1fr);        /* Same: 3 equal columns */
  grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));  /* Responsive */
  grid-template-columns: 200px 1fr 200px;       /* Fixed + flexible */
  
  /* Define rows */
  grid-template-rows: auto 1fr auto;
  grid-auto-rows: minmax(100px, auto);          /* All rows auto-sized */
  
  /* Gap between cells */
  gap: 1rem;
  column-gap: 2rem;
  row-gap: 1rem;
  
  /* Alignment of items within cells */
  justify-items: center;                        /* Horizontal */
  align-items: center;                          /* Vertical */
  
  /* Alignment of grid within container */
  justify-content: center;                      /* Horizontal */
  align-content: center;                        /* Vertical */
}

/* Grid items */
.item {
  /* Span across columns/rows */
  grid-column: 1 / 3;                           /* From column 1 to 3 */
  grid-column: span 2;                          /* Span 2 columns */
  grid-row: 1 / 4;                              /* From row 1 to 4 */
  
  /* Alignment override */
  justify-self: center;
  align-self: end;
}

/* Named grid areas */
.grid {
  grid-template-areas:
    "header header header"
    "sidebar main main"
    "footer footer footer";
}

.header { grid-area: header; }
.sidebar { grid-area: sidebar; }
.main { grid-area: main; }
.footer { grid-area: footer; }
```

**Best Practice**: Use `auto-fit` or `auto-fill` for responsive grids. Use `minmax()` for fluid sizing. Name areas for complex layouts. Use grid for 2D, flex for 1D.

---

## 🌐 MODERN CSS FEATURES

### CSS Variables (Custom Properties)

```css
/* Define variables */
:root {
  --primary-color: #ff6b6b;
  --secondary-color: #4ecdc4;
  --spacing: 1rem;
  --border-radius: 8px;
  --shadow: 0 2px 8px rgba(0,0,0,0.1);
}

/* Use variables */
.button {
  background: var(--primary-color);
  padding: var(--spacing);
  border-radius: var(--border-radius);
  box-shadow: var(--shadow);
}

/* Fallback values */
.element {
  color: var(--theme-color, blue);    /* Use blue if --theme-color undefined */
}

/* Scoped variables */
.dark-mode {
  --primary-color: #ff8787;
  --secondary-color: #80deea;
}

/* Dynamic variables with JavaScript */
/* document.documentElement.style.setProperty('--primary-color', '#123456'); */
```

### CSS Calc

```css
/* Dynamic sizing */
.container {
  width: calc(100% - 2rem);
  padding: calc(var(--spacing) * 2);
  height: calc(100vh - 60px);         /* Viewport minus header */
}

/* Responsive sizing */
.font {
  font-size: calc(1rem + 2vw);        /* Scale with viewport */
}

/* Complex calculations */
.grid-item {
  width: calc((100% - (3 * 1rem)) / 3); /* Account for gaps */
}
```

### `clamp()`

```css
/* Responsive sizing without media queries */
.heading {
  font-size: clamp(1rem, 5vw, 3rem);  /* Min: 1rem, Ideal: 5vw, Max: 3rem */
}

.padding {
  padding: clamp(1rem, 2vw, 2rem);
}
```

**Best Practice**: Use `clamp()` for responsive typography. Use variables for consistency across large projects. Use `calc()` for component-specific calculations.

---

## 🔒 OVERFLOW & VISIBILITY

### `overflow`

How to handle content that overflows container.

```css
/* Hidden overflow (clip content) */
.box {
  overflow: hidden;
  width: 200px;
  height: 200px;
}

/* Scrollable overflow */
.scrollable {
  overflow: auto;                     /* Only show scrollbar if needed */
  overflow: scroll;                   /* Always show scrollbars */
  overflow-x: auto;                   /* Horizontal scroll only */
  overflow-y: auto;                   /* Vertical scroll only */
}

/* Visible overflow (default) */
.box {
  overflow: visible;
}

/* Enable clipping context (for overflow) */
.container {
  overflow: hidden;                   /* Creates new stacking context */
}
```

### `visibility` & `display`

```css
/* display: none - remove from flow */
.hidden { display: none; }            /* Element takes no space */

/* visibility: hidden - keep in flow */
.invisible { visibility: hidden; }    /* Space reserved, element not visible */

/* visibility: visible - show element */
.visible { visibility: visible; }

/* Difference example */
.container {
  display: flex;
  height: 200px;
}

.box { width: 100px; }

.display-none { display: none; }      /* 3 boxes side by side */
.visibility-hidden { visibility: hidden; } /* 4 spaces, 3rd is invisible */
```

---

## 🎯 OTHER ESSENTIAL PROPERTIES

### `cursor`

Mouse cursor appearance.

```css
/* Different cursor styles */
.default { cursor: default; }
.pointer { cursor: pointer; }         /* Hand icon (clickable) */
.text { cursor: text; }               /* Text selection cursor */
.grab { cursor: grab; }               /* Grabbing hand */
.grabbing { cursor: grabbing; }
.wait { cursor: wait; }               /* Loading spinner */
.help { cursor: help; }               /* Question mark */
.no-drop { cursor: no-drop; }
.not-allowed { cursor: not-allowed; }
.move { cursor: move; }
.cell { cursor: cell; }

/* Custom cursor */
.custom {
  cursor: url('cursor.png'), auto;    /* Custom image, fallback to auto */
}
```

### `pointer-events`

Whether element responds to mouse events.

```css
/* Disable pointer events (click-through) */
.overlay {
  pointer-events: none;               /* Can't click this element */
}

.overlay.active {
  pointer-events: auto;               /* Re-enable pointer events */
}
```

### `user-select`

Text selection behavior.

```css
/* Prevent text selection */
.no-select {
  user-select: none;
}

/* Allow text selection (default) */
.selectable {
  user-select: text;
}

/* Select all on click */
.select-all {
  user-select: all;
}
```

### `list-style`

List styling.

```css
/* Remove default list styles */
ul {
  list-style: none;
  padding: 0;
  margin: 0;
}

/* Custom list markers */
li {
  list-style-type: circle;           /* or square, disc, decimal, etc. */
  list-style-image: url('bullet.svg');
  list-style-position: inside;        /* or outside */
}
```

---

## 🎓 BEST PRACTICES SUMMARY

### Performance

- Minimize repaints: avoid changing `width`, `height`, `position` during animations
- Use `transform` and `opacity` for animations (GPU accelerated)
- Debounce scroll/resize listeners
- Use CSS instead of JavaScript for animations when possible
- Minimize specificity to enable style overrides

### Accessibility

- Always provide focus indicators (don't remove `outline` without replacement)
- Ensure sufficient color contrast (WCAG AA: 4.5:1 for text)
- Don't rely on color alone to convey information
- Respect `prefers-reduced-motion`
- Use semantic HTML (avoid divs for buttons/links)
- Ensure interactive elements are at least 44x44px

### Maintainability

- Use meaningful class names (BEM or similar)
- Keep specificity low
- Use CSS variables for theming
- Group related properties
- Document complex selectors
- Use mobile-first media queries
- Avoid `!important` (use only in utilities)

### CSS Naming Conventions (BEM)

```css
/* Block: main component */
.card { }

/* Element: part of component */
.card__header { }
.card__body { }
.card__footer { }

/* Modifier: variation */
.card--featured { }
.card--disabled { }

/* Usage */
<div class="card card--featured">
  <div class="card__header"></div>
  <div class="card__body"></div>
</div>
```

---

## 📋 SPECIFICITY QUICK REFERENCE

| Selector | Specificity | Example |
|----------|-------------|---------|
| Universal | (0,0,0,0) | `*` |
| Element | (0,0,0,1) | `div` |
| Class | (0,0,1,0) | `.class` |
| Attribute | (0,0,1,0) | `[type="text"]` |
| Pseudo-class | (0,0,1,0) | `:hover` |
| ID | (0,1,0,0) | `#id` |
| Inline style | (1,0,0,0) | `style=""` |
| `!important` | Overrides all | Exception |

**Remember**: Lower specificity = more maintainable code!

---

## 🔗 Quick Links & Resources

- [MDN Web Docs - CSS](https://developer.mozilla.org/en-US/docs/Web/CSS/)
- [CSS Tricks](https://css-tricks.com/)
- [Can I Use](https://caniuse.com/) - Browser support
- [Chrome DevTools](https://developer.chrome.com/docs/devtools/) - Debugging CSS

---

**Last Updated**: 2026 | CSS Level 3 & 4 Features Included