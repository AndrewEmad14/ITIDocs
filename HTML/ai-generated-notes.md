# HTML Cheat Sheet: Complete Guide to HTML Tags

## Table of Contents
1. [Document Structure](#document-structure)
2. [Text Content](#text-content)
3. [Lists](#lists)
4. [Tables](#tables)
5. [Links & Navigation](#links--navigation)
6. [Media](#media)
7. [Forms & Input](#forms--input)
8. [Semantic HTML](#semantic-html)
9. [Interactive & Modern Elements](#interactive--modern-elements)
10. [Metadata & Head Elements](#metadata--head-elements)
11. [Best Practices for Classes & IDs](#best-practices-for-classes--ids)

---

## Document Structure

### `<!DOCTYPE html>`
Declares the document as HTML5. Must be the first line of every HTML document.

```html
<!DOCTYPE html>
```

**Why `<!DOCTYPE html>` is Essential:**

Without the DOCTYPE declaration, you'll face serious problems:

- **Quirks Mode:** Browser enters "quirks mode" and uses outdated rendering rules from old browsers
- **CSS Issues:** Styling behaves unpredictably; margins, padding, and box model may not work correctly
- **JavaScript Problems:** Some modern JavaScript features may not work as expected
- **Form Validation:** HTML5 form validation (required, email, etc.) won't function
- **Media Elements:** Video and audio may not play properly
- **Meta Tags Ignored:** Viewport and other meta tags may not be recognized
- **Inconsistent Display:** Page looks different across browsers
- **SEO Issues:** Search engines may not properly index your content

**Always include it!**

### `<html>`
Root element that wraps all content.

```html
<html lang="en">
  <!-- Content goes here -->
</html>
```

**Best Practice:** Always include the `lang` attribute for accessibility and SEO.

### `<head>`
Contains metadata, title, links to stylesheets, and other document information.

```html
<head>
  <meta charset="UTF-8">
  <title>Page Title</title>
</head>
```

### `<body>`
Contains all visible content of the page.

```html
<body>
  <h1>Welcome to my website</h1>
  <p>This is visible content.</p>
</body>
```

---

## Text Content

### `<h1>` through `<h6>`
**Display:** Block  
Heading levels. Use only one `<h1>` per page.

```html
<h1>Main Heading</h1>
<h2>Subheading</h2>
<h3>Sub-subheading</h3>
```

**Best Practice:** Follow a logical hierarchy. Don't skip levels (e.g., don't jump from `<h1>` to `<h3>`).

### `<p>`
**Display:** Block  
Paragraph of text.

```html
<p>This is a paragraph. It contains a block of text separated by whitespace.</p>
```

### `<strong>` vs `<b>`
**Display:** Inline  
- `<strong>`: Semantic emphasis, indicates importance
- `<b>`: Stylistic boldness without semantic meaning

```html
<p><strong>Important:</strong> Read the instructions carefully.</p>
<p>The winning team was <b>Boston Celtics</b>.</p>
```

### `<em>` vs `<i>`
**Display:** Inline  
- `<em>`: Semantic emphasis (italics)
- `<i>`: Stylistic italics without semantic meaning

```html
<p>This is <em>really</em> important.</p>
<p>The species name is <i>Canis lupus familiaris</i>.</p>
```

### `<mark>`
**Display:** Inline  
Highlights text for reference or notation.

```html
<p>The most <mark>important</mark> part is highlighted.</p>
```

### `<small>`
**Display:** Inline  
Represents side comments or small print.

```html
<p>Regular text <small>(with small print disclaimer)</small></p>
```

### `<del>` and `<ins>`
**Display:** Inline  
Represents deleted and inserted text with strikethrough and underline.

```html
<p>Original price: <del>$50</del> <ins>$30</ins></p>
```

### `<sub>` and `<sup>`
**Display:** Inline  
Subscript and superscript.

```html
<p>Water is H<sub>2</sub>O</p>
<p>E = mc<sup>2</sup></p>
```

### `<code>`, `<pre>`, `<kbd>`, `<samp>`
**Display:** `<code>`, `<kbd>`, `<samp>` = Inline | `<pre>` = Block  
Formatting for code and computer-related text.

```html
<p>Use the <code>let</code> keyword to declare variables.</p>

<pre><code>
function hello() {
  console.log("Hello, World!");
}
</code></pre>

<p>Press <kbd>Ctrl</kbd> + <kbd>C</kbd> to copy.</p>
<p>Output: <samp>Hello, World!</samp></p>
```

### `<br>` and `<hr>`
**Display:** `<br>` = Inline | `<hr>` = Block  
Line break and horizontal rule.

```html
<p>Line one<br>Line two</p>
<hr>
<p>New section after the line.</p>
```

**Best Practice:** Avoid using `<br>` for spacing; use CSS margins instead.

### `<blockquote>`
**Display:** Block  
Extended quotation.

```html
<blockquote cite="https://example.com">
  <p>The only way to do great work is to love what you do.</p>
  <footer>— Steve Jobs</footer>
</blockquote>
```

---

## Lists

### `<ul>` - Unordered List
**Display:** Block  
List with no particular order.

```html
<ul>
  <li>First item</li>
  <li>Second item</li>
  <li>Third item</li>
</ul>
```

### `<ol>` - Ordered List
**Display:** Block  
Numbered list.

```html
<ol>
  <li>First step</li>
  <li>Second step</li>
  <li>Third step</li>
</ol>
```

**Attributes:**
```html
<ol start="5" reversed>
  <li>Fifth item</li>
  <li>Fourth item</li>
</ol>
```

### `<dl>` - Description List
**Display:** Block  
Pairs of terms and definitions.

```html
<dl>
  <dt>HTML</dt>
  <dd>HyperText Markup Language</dd>
  <dt>CSS</dt>
  <dd>Cascading Style Sheets</dd>
</dl>
```

---

## Tables

### `<table>`
**Display:** Block  
Container for tabular data with rows and columns.

```html
<table>
  <tr>
    <th>Name</th>
    <th>Age</th>
    <th>City</th>
  </tr>
  <tr>
    <td>John</td>
    <td>28</td>
    <td>New York</td>
  </tr>
  <tr>
    <td>Jane</td>
    <td>34</td>
    <td>Los Angeles</td>
  </tr>
</table>
```

### `<thead>`
**Display:** Block  
Groups header rows in a table.

```html
<table>
  <thead>
    <tr>
      <th>Product</th>
      <th>Price</th>
      <th>Stock</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Laptop</td>
      <td>$999</td>
      <td>15</td>
    </tr>
  </tbody>
</table>
```

### `<tbody>`
**Display:** Block  
Groups body rows in a table (main data rows).

```html
<table>
  <thead>
    <tr>
      <th>Month</th>
      <th>Sales</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>January</td>
      <td>$50,000</td>
    </tr>
    <tr>
      <td>February</td>
      <td>$65,000</td>
    </tr>
  </tbody>
</table>
```

### `<tfoot>`
**Display:** Block  
Groups footer rows in a table (summary/totals).

```html
<table>
  <thead>
    <tr>
      <th>Item</th>
      <th>Quantity</th>
      <th>Price</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Widget A</td>
      <td>10</td>
      <td>$100</td>
    </tr>
    <tr>
      <td>Widget B</td>
      <td>5</td>
      <td>$75</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th>Total</th>
      <td>15</td>
      <td>$175</td>
    </tr>
  </tfoot>
</table>
```

### `<tr>`
**Display:** Block  
Table row.

```html
<table>
  <tr>
    <td>Cell 1</td>
    <td>Cell 2</td>
    <td>Cell 3</td>
  </tr>
</table>
```

### `<td>`
**Display:** Block (inline in table context)  
Table data cell.

```html
<tr>
  <td>Regular data cell</td>
  <td>Another data cell</td>
</tr>
```

### `<th>`
**Display:** Block (inline in table context)  
Table header cell. Semantic element for column/row headers.

```html
<tr>
  <th scope="col">Column Header</th>
  <th scope="col">Another Header</th>
</tr>

<!-- Row header -->
<tr>
  <th scope="row">Row Label</th>
  <td>Data</td>
</tr>
```

**Attributes:**
- `scope="col"` - Header for a column
- `scope="row"` - Header for a row
- `colspan="n"` - Spans across n columns
- `rowspan="n"` - Spans across n rows

### `<caption>`
**Display:** Block  
Title or explanation for the table content.

```html
<table>
  <caption>Q1 2024 Sales Report</caption>
  <thead>
    <tr>
      <th>Month</th>
      <th>Revenue</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>January</td>
      <td>$120,000</td>
    </tr>
  </tbody>
</table>
```

### `<colgroup>` and `<col>`
**Display:** None (metadata)  
Groups and styles columns in a table.

```html
<table>
  <colgroup>
    <col style="background-color: #f0f0f0;">
    <col style="background-color: #ffffff;">
    <col style="background-color: #f0f0f0;">
  </colgroup>
  <thead>
    <tr>
      <th>Name</th>
      <th>Email</th>
      <th>Phone</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>John</td>
      <td>john@example.com</td>
      <td>555-1234</td>
    </tr>
  </tbody>
</table>
```

**With `span` attribute:**
```html
<colgroup>
  <col span="2" style="background-color: lightblue;">
  <col style="background-color: lightgreen;">
</colgroup>
```

---

## Complete Table Example

```html
<table>
  <caption>Student Grades - Fall 2024</caption>
  
  <colgroup>
    <col style="width: 150px;">
    <col style="width: 80px;">
    <col style="width: 80px;">
    <col style="width: 80px;">
  </colgroup>
  
  <thead>
    <tr>
      <th scope="col">Student Name</th>
      <th scope="col">Math</th>
      <th scope="col">Science</th>
      <th scope="col">English</th>
    </tr>
  </thead>
  
  <tbody>
    <tr>
      <th scope="row">Alice Johnson</th>
      <td>A</td>
      <td>A-</td>
      <td>A</td>
    </tr>
    <tr>
      <th scope="row">Bob Smith</th>
      <td>B+</td>
      <td>B</td>
      <td>B+</td>
    </tr>
    <tr>
      <th scope="row">Carol Davis</th>
      <td>A-</td>
      <td>A</td>
      <td>A-</td>
    </tr>
  </tbody>
  
  <tfoot>
    <tr>
      <th scope="row">Class Average</th>
      <td>A-</td>
      <td>A-</td>
      <td>A</td>
    </tr>
  </tfoot>
</table>
```

---

## Table Best Practices

1. **Always use semantic elements:**
   - Use `<thead>` for headers, `<tbody>` for data, `<tfoot>` for summaries
   - Use `<th>` for headers with appropriate `scope` attribute
   - Use `<caption>` to describe table purpose

2. **Accessibility:**
   ```html
   <!-- Good: Clear scope and caption -->
   <table>
     <caption>Product Inventory</caption>
     <thead>
       <tr>
         <th scope="col">Product</th>
         <th scope="col">Quantity</th>
       </tr>
     </thead>
     <tbody>
       <tr>
         <td>Item A</td>
         <td>100</td>
       </tr>
     </tbody>
   </table>
   ```

3. **For complex tables with merged cells:**
   ```html
   <table>
     <tr>
       <th colspan="2">Contact Information</th>
     </tr>
     <tr>
       <td>Email:</td>
       <td>user@example.com</td>
     </tr>
     <tr>
       <th rowspan="2">Address:</th>
       <td>123 Main St</td>
     </tr>
     <tr>
       <td>New York, NY 10001</td>
     </tr>
   </table>
   ```

4. **Add styling classes for reusable table styles:**
   ```html
   <table class="data-table data-table--striped data-table--bordered">
     <thead class="data-table__head">
       <tr>
         <th class="data-table__header">Column 1</th>
         <th class="data-table__header">Column 2</th>
       </tr>
     </thead>
     <tbody class="data-table__body">
       <tr class="data-table__row">
         <td class="data-table__cell">Data 1</td>
         <td class="data-table__cell">Data 2</td>
       </tr>
     </tbody>
   </table>
   ```

---

## Links & Navigation

### `<a>`
**Display:** Inline  
Anchor/hyperlink.

```html
<!-- External link -->
<a href="https://example.com">Visit Example</a>

<!-- Email link -->
<a href="mailto:user@example.com">Send Email</a>

<!-- Phone link -->
<a href="tel:+1234567890">Call Us</a>

<!-- Anchor link (same page) -->
<a href="#section-id">Jump to Section</a>

<!-- Link with title -->
<a href="/page" title="Page Description">Page</a>

<!-- Link with download -->
<a href="/file.pdf" download>Download PDF</a>
```

### `<nav>`
**Display:** Block  
Semantic container for navigation links.

```html
<nav>
  <ul>
    <li><a href="/">Home</a></li>
    <li><a href="/about">About</a></li>
    <li><a href="/contact">Contact</a></li>
  </ul>
</nav>
```

---

## Media

### `<img>`
**Display:** Inline-block  
Image element.

```html
<img src="image.jpg" alt="Description of image" width="300" height="200">
```

**Best Practice:** Always include descriptive `alt` text for accessibility.

### `<picture>`
**Display:** Inline-block  
Responsive images with multiple sources.

```html
<picture>
  <source media="(min-width: 768px)" srcset="large.jpg">
  <source media="(min-width: 480px)" srcset="medium.jpg">
  <img src="small.jpg" alt="Responsive image">
</picture>
```

### `<figure>` and `<figcaption>`
**Display:** Block  
Image or diagram with caption.

```html
<figure>
  <img src="chart.png" alt="Sales chart">
  <figcaption>Sales data for Q1 2024</figcaption>
</figure>
```

### `<video>`
**Display:** Inline-block  
Embedded video content.

```html
<video width="640" height="480" controls poster="poster.jpg">
  <source src="video.mp4" type="video/mp4">
  <source src="video.webm" type="video/webm">
  Your browser doesn't support HTML video.
</video>
```

### `<audio>`
**Display:** Inline-block  
Embedded audio content.

```html
<audio controls>
  <source src="audio.mp3" type="audio/mpeg">
  <source src="audio.wav" type="audio/wav">
  Your browser doesn't support HTML audio.
</audio>
```

### `<source>`
**Display:** None (metadata)  
Specifies media resources for `<video>`, `<audio>`, and `<picture>`.

```html
<video controls>
  <source src="movie.mp4" type="video/mp4">
  <source src="movie.ogg" type="video/ogg">
</video>
```

### `<iframe>`
**Display:** Inline-block  
Embeds another HTML page.

```html
<iframe src="https://example.com" width="800" height="600" title="Example Page"></iframe>

<!-- YouTube video -->
<iframe width="560" height="315" src="https://www.youtube.com/embed/dQw4w9WgXcQ" 
  title="YouTube video" frameborder="0" allowfullscreen></iframe>

<!-- Google Maps -->
<iframe width="100%" height="400" 
  src="https://www.google.com/maps/embed?pb=!1m18!..." 
  style="border:0;" allowfullscreen="" loading="lazy"></iframe>

<!-- PDF -->
<iframe src="document.pdf" width="100%" height="600"></iframe>
```

**Best Practice:** Always include a `title` attribute for accessibility. Use `sandbox` attribute to restrict permissions for security.

```html
<!-- Secure iframe with restricted permissions -->
<iframe src="untrusted-content.html" 
  sandbox="allow-scripts allow-same-origin"
  title="Embedded content"></iframe>
```

---

## Forms & Input

### `<form>`
**Display:** Block  
Container for form elements.

```html
<form action="/submit" method="POST">
  <!-- Form content -->
</form>
```

### `<input>`
**Display:** Inline-block  
Single-line text input and other form controls.

```html
<!-- Text input -->
<input type="text" name="username" placeholder="Enter username" required>

<!-- Email input -->
<input type="email" name="email" required>

<!-- Password input -->
<input type="password" name="password" required>

<!-- Checkbox -->
<input type="checkbox" name="agree" id="agree">
<label for="agree">I agree to terms</label>

<!-- Radio button -->
<input type="radio" name="choice" value="yes"> Yes
<input type="radio" name="choice" value="no"> No

<!-- Number input -->
<input type="number" name="age" min="0" max="120">

<!-- Date input -->
<input type="date" name="birthday">

<!-- Color picker -->
<input type="color" name="favorite-color">

<!-- File input -->
<input type="file" name="document" accept=".pdf,.doc">

<!-- Submission -->
<input type="submit" value="Submit">
<input type="reset" value="Clear">
```

### `<textarea>`
**Display:** Block  
Multi-line text input.

```html
<textarea name="message" rows="5" cols="40" placeholder="Enter your message..."></textarea>
```

### `<label>`
**Display:** Inline | Inline-block (with styling)  
Associates text with form inputs.

```html
<label for="email">Email Address:</label>
<input type="email" id="email" name="email">
```

**Best Practice:** Always use `<label>` with the `for` attribute for accessibility.

### `<select>` and `<option>`
**Display:** Inline-block  
Dropdown menu.

```html
<select name="country">
  <option value="">-- Select --</option>
  <option value="us">United States</option>
  <option value="uk">United Kingdom</option>
  <option value="ca" selected>Canada</option>
</select>
```

### `<optgroup>`
**Display:** None (metadata)  
Groups options in a dropdown.

```html
<select name="fruit">
  <optgroup label="Citrus">
    <option>Orange</option>
    <option>Lemon</option>
  </optgroup>
  <optgroup label="Berries">
    <option>Strawberry</option>
    <option>Blueberry</option>
  </optgroup>
</select>
```

### `<datalist>`
**Display:** None (metadata)  
Predefined options for input with suggestions.

```html
<input type="text" list="browsers" placeholder="Browser name">
<datalist id="browsers">
  <option value="Chrome">
  <option value="Firefox">
  <option value="Safari">
</datalist>
```

### `<fieldset>` and `<legend>`
**Display:** Block  
Groups related form elements.

```html
<fieldset>
  <legend>Personal Information</legend>
  <label>Name: <input type="text" name="name"></label>
  <label>Email: <input type="email" name="email"></label>
</fieldset>
```

### `<output>`
Represents the result of a calculation.

```html
<form oninput="result.value = parseInt(a.value) + parseInt(b.value)">
  <input type="number" id="a" value="5"> +
  <input type="number" id="b" value="3">
  = <output id="result" name="result"></output>
</form>
```

---

## Semantic HTML

Semantic elements provide meaning to the browser and developers about page structure.

### `<header>`
**Display:** Block  
Introductory content or navigation.

```html
<header>
  <h1>My Website</h1>
  <nav>
    <ul>
      <li><a href="/">Home</a></li>
      <li><a href="/about">About</a></li>
    </ul>
  </nav>
</header>
```

### `<main>`
**Display:** Block  
Main content of the document (one per page).

```html
<main>
  <article>
    <h1>Article Title</h1>
    <p>Article content...</p>
  </article>
</main>
```

### `<article>`
**Display:** Block  
Self-contained, independent content.

```html
<article>
  <h2>Blog Post Title</h2>
  <p>Posted on <time datetime="2024-01-15">January 15, 2024</time></p>
  <p>Article content goes here...</p>
</article>
```

### `<section>`
**Display:** Block  
Groups thematically related content.

```html
<section id="services">
  <h2>Our Services</h2>
  <p>Description of services...</p>
</section>
```

### `<aside>`
**Display:** Block  
Sidebar content, related but tangential information.

```html
<aside>
  <h3>Related Links</h3>
  <ul>
    <li><a href="#">Link 1</a></li>
    <li><a href="#">Link 2</a></li>
  </ul>
</aside>
```

### `<footer>`
**Display:** Block  
Footer content of document or section.

```html
<footer>
  <p>&copy; 2024 My Company. All rights reserved.</p>
  <nav>
    <a href="/privacy">Privacy Policy</a>
    <a href="/terms">Terms of Service</a>
  </nav>
</footer>
```

### `<time>`
**Display:** Inline  
Represents a date/time value.

```html
<p>Published on <time datetime="2024-01-15T10:30:00Z">January 15, 2024</time></p>
```

---

## Interactive & Modern Elements

### `<details>` and `<summary>`
**Display:** Block  
Collapsible/expandable content.

```html
<details>
  <summary>Click to expand</summary>
  <p>This content is hidden until the user clicks the summary.</p>
</details>
```

### `<dialog>` (Modern)
**Display:** Block (can be positioned as modal)  
Modal dialog box.

```html
<dialog id="modal">
  <h2>Dialog Title</h2>
  <p>Dialog content goes here.</p>
  <button onclick="document.getElementById('modal').close()">Close</button>
</dialog>

<button onclick="document.getElementById('modal').showModal()">Open Dialog</button>
```

**JavaScript Example:**
```javascript
// Open modal
document.getElementById('modal').showModal();

// Close modal
document.getElementById('modal').close();
```

### `<template>` (Modern)
**Display:** None (not rendered)  
Holds HTML that isn't rendered immediately, useful for JavaScript.

```html
<template id="item-template">
  <div class="item">
    <h3 class="item-title"></h3>
    <p class="item-description"></p>
  </div>
</template>

<script>
  const template = document.getElementById('item-template');
  const clone = template.content.cloneNode(true);
  clone.querySelector('.item-title').textContent = 'Item Name';
  document.body.appendChild(clone);
</script>
```

### `<progress>`
**Display:** Inline-block  
Visual progress bar.

```html
<label for="upload">Upload progress:</label>
<progress id="upload" value="70" max="100"></progress> 70%
```

### `<meter>`
**Display:** Inline-block  
Represents a scalar measurement within a range (gauge).

```html
<label for="storage">Disk usage:</label>
<meter id="storage" value="6" min="0" max="10"></meter>
```

### `<canvas>` (Modern)
**Display:** Inline-block  
Container for graphics drawn with JavaScript.

```html
<canvas id="drawing" width="400" height="300"></canvas>

<script>
  const canvas = document.getElementById('drawing');
  const ctx = canvas.getContext('2d');
  ctx.fillStyle = 'blue';
  ctx.fillRect(10, 10, 100, 100);
</script>
```

### `<svg>` (Modern)
**Display:** Inline-block  
Scalable vector graphics.

```html
<svg width="100" height="100">
  <circle cx="50" cy="50" r="40" fill="red" />
  <rect x="10" y="10" width="30" height="30" fill="blue" />
</svg>
```

### `<embed>` and `<object>`
**Display:** Inline-block  
External content (PDFs, plugins, etc.).

```html
<!-- Embed PDF -->
<embed src="document.pdf" type="application/pdf" width="100%" height="600px">

<!-- Alternative for older browsers -->
<object data="document.pdf" type="application/pdf" width="100%" height="600px">
  <p>PDF not supported. <a href="document.pdf">Download PDF</a></p>
</object>
```

---

## Metadata & Head Elements

### `<meta>`
**Location:** `<head>` (not rendered)  
Metadata about the HTML document.

```html
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta name="description" content="Page description for search engines">
<meta name="keywords" content="html, css, javascript">
<meta name="author" content="John Doe">
<meta property="og:title" content="Open Graph Title">
<meta property="og:image" content="image.jpg">
```

### `<title>`
**Location:** `<head>` (not rendered in body)  
Page title (appears in browser tab).

```html
<title>My Awesome Website</title>
```

### `<link>`
**Location:** `<head>` (not rendered)  
Links external resources like stylesheets.

```html
<link rel="stylesheet" href="styles.css">
<link rel="icon" href="favicon.ico">
<link rel="preconnect" href="https://fonts.googleapis.com">
```

### `<style>`
**Display:** None (styling applied to page)  
Inline CSS styles.

```html
<style>
  body {
    font-family: Arial, sans-serif;
    background-color: #f5f5f5;
  }
</style>
```

### `<script>`
**Display:** None (when in head) | Inline-block (when in body)  
JavaScript code or external scripts.

```html
<!-- External script -->
<script src="script.js"></script>

<!-- Inline script -->
<script>
  console.log('Hello, World!');
</script>

<!-- Deferred loading -->
<script src="script.js" defer></script>

<!-- Asynchronous loading -->
<script src="script.js" async></script>
```

---

## Best Practices for Classes & IDs

### ID Naming Convention

IDs should be unique within a page and follow these guidelines:

```html
<!-- Good: Descriptive, lowercase, hyphens for spaces -->
<div id="main-header"></div>
<section id="featured-products"></section>
<button id="submit-btn"></button>

<!-- Avoid: Cryptic, generic, or using underscores -->
<!-- Bad -->
<div id="div1"></div>
<section id="section_products"></section>
<button id="btn"></button>
```

**Rules for IDs:**
- Use lowercase letters, numbers, and hyphens
- Must start with a letter
- Must be unique on the page
- Reserve for JavaScript hooks and page anchors
- Use only when necessary

### Class Naming Convention

Classes are reusable and should follow BEM (Block Element Modifier) or utility-first approaches:

```html
<!-- BEM Convention -->
<div class="card">
  <header class="card__header">
    <h2 class="card__title">Title</h2>
  </header>
  <div class="card__body">
    <p>Content</p>
  </div>
  <footer class="card__footer">
    <button class="card__button card__button--primary">Save</button>
    <button class="card__button card__button--secondary">Cancel</button>
  </footer>
</div>

<!-- Utility-First Approach (Tailwind-style) -->
<div class="flex gap-4 p-6 bg-white rounded-lg shadow">
  <img class="w-24 h-24 rounded-full" src="avatar.jpg" alt="User">
  <div class="flex-1">
    <h2 class="text-xl font-bold">John Doe</h2>
    <p class="text-gray-600">Software Developer</p>
  </div>
</div>

<!-- Semantic Class Names -->
<div class="product-card">
  <img class="product-image" src="product.jpg" alt="Product">
  <h3 class="product-title">Product Name</h3>
  <p class="product-price">$19.99</p>
  <button class="btn btn-primary">Add to Cart</button>
</div>
```

### Combined Best Practices Example

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Product Page</title>
</head>
<body>
  <!-- ID for JavaScript targeting -->
  <header id="main-header" class="site-header">
    <nav class="site-header__nav">
      <a href="/" class="site-header__logo">Logo</a>
      <ul class="nav-list">
        <li class="nav-item"><a href="/products" class="nav-link">Products</a></li>
        <li class="nav-item"><a href="/about" class="nav-link">About</a></li>
      </ul>
    </nav>
  </header>

  <main id="main-content">
    <section class="featured-section">
      <h1 class="featured-section__title">Featured Products</h1>
      
      <div class="product-grid">
        <article class="product-card">
          <img src="product.jpg" alt="Product Name" class="product-card__image">
          <h2 class="product-card__title">Product Name</h2>
          <p class="product-card__description">Product description</p>
          <button id="add-product-1" class="btn btn--primary">Add to Cart</button>
        </article>
      </div>
    </section>
  </main>

  <footer id="main-footer" class="site-footer">
    <p class="site-footer__copyright">&copy; 2024 Company Name</p>
  </footer>
</body>
</html>
```

### Naming Convention Summary

| Pattern | Use Case | Example |
|---------|----------|---------|
| **IDs** | Unique elements, JS hooks, page anchors | `id="main-header"` |
| **Classes (BEM)** | Reusable components, structured styling | `class="card__header card__header--large"` |
| **Classes (Utility)** | Rapid prototyping, frameworks like Tailwind | `class="flex gap-4 p-4"` |
| **Semantic Classes** | Descriptive, simple naming | `class="product-card"` |

---

## Quick Reference Chart

```
DOCUMENT STRUCTURE
├─ <!DOCTYPE html>
├─ <html>
├─ <head>
└─ <body>

CONTENT STRUCTURE
├─ <header>
├─ <nav>
├─ <main>
│  ├─ <article>
│  ├─ <section>
│  └─ <aside>
└─ <footer>

TEXT CONTENT
├─ <h1>–<h6>
├─ <p>
├─ <strong>, <em>
├─ <mark>, <small>
├─ <code>, <pre>
└─ <blockquote>

LISTS
├─ <ul> + <li>
├─ <ol> + <li>
└─ <dl> + <dt> + <dd>

TABLES
├─ <table>
├─ <thead>
├─ <tbody>
├─ <tfoot>
├─ <tr>
├─ <td>
├─ <th>
├─ <caption>
└─ <colgroup> + <col>

MEDIA
├─ <img>
├─ <picture>
├─ <figure>
├─ <video>
└─ <audio>

INTERACTIVE
├─ <details> + <summary>
├─ <dialog>
├─ <template>
├─ <canvas>
├─ <svg>
└─ <progress>

FORMS
├─ <form>
├─ <input> (multiple types)
├─ <textarea>
├─ <select> + <option>
├─ <label>
├─ <fieldset> + <legend>
└─ <output>
```

---

## Common Patterns

### Navigation Menu
```html
<nav class="navbar">
  <ul class="navbar__list">
    <li class="navbar__item">
      <a href="/" class="navbar__link navbar__link--active">Home</a>
    </li>
    <li class="navbar__item">
      <a href="/about" class="navbar__link">About</a>
    </li>
  </ul>
</nav>
```

### Card Component
```html
<article class="card card--featured">
  <img src="image.jpg" alt="Description" class="card__image">
  <div class="card__content">
    <h2 class="card__title">Title</h2>
    <p class="card__description">Description text</p>
  </div>
  <footer class="card__footer">
    <button class="btn btn--primary">Action</button>
  </footer>
</article>
```

### Form with Validation
```html
<form id="contact-form" class="contact-form" novalidate>
  <fieldset class="form__group">
    <legend>Contact Information</legend>
    
    <div class="form__field">
      <label for="email" class="form__label">Email:</label>
      <input 
        type="email" 
        id="email" 
        name="email" 
        class="form__input"
        required
        placeholder="your@email.com"
      >
    </div>

    <div class="form__field">
      <label for="message" class="form__label">Message:</label>
      <textarea 
        id="message" 
        name="message" 
        class="form__textarea"
        required
        rows="5"
      ></textarea>
    </div>
  </fieldset>

  <button type="submit" class="btn btn--primary">Send</button>
</form>
```

---

This cheat sheet covers all essential HTML tags, modern additions, and professional naming conventions. Happy coding!