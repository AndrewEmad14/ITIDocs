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

# in regards to file paths
  1. Use server-relative paths in HTML/CSS/JS

  ✅ <link rel="stylesheet" href="/style/home.css">
  ✅ <img src="/public/images/serbal.jpg">
  ✅ <script src="/script.js"></script>
  ❌ Don't use ../style/home.css (relative paths don't work for HTTP)
  ❌ Don't use C:/Users/... (full file paths)