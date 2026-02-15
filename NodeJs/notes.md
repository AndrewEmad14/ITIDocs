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