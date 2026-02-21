# Mongo quick recap

## Table of Contents
0. [Introduction to MongoDB & NoSQL](#introduction-to-mongodb--nosql)
1. [Setup & Installation](#setup--installation)
2. [Basic Concepts](#basic-concepts)
3. [Database & Collection Operations](#database--collection-operations)
4. [CRUD Operations](#crud-operations)
5. [Query Operators](#query-operators)
6. [Projection](#projection)
7. [Update Operations](#update-operations)
8. [Aggregation Pipeline](#aggregation-pipeline)
9. [Relationships & Joins](#relationships--joins)
10. [Indexing](#indexing)
11. [Common Mistakes & Tips](#common-mistakes--tips)
12. [Schema Validation in MongoDB](#schema-validation-in-mongodb)

---
## Introduction to MongoDB & NoSQL

### What is MongoDB?

**MongoDB** is a popular **NoSQL document database** that stores data in flexible, JSON-like documents rather than rigid tables. It was first released in 2009 and has become one of the most widely used databases for modern web applications.

**Key Characteristics:**
- **Document-Oriented**: Data stored as BSON documents (similar to JSON)
- **Flexible Schema**: Documents in the same collection can have different fields
- **Scalable**: Designed for horizontal scaling across multiple servers
- **Developer-Friendly**: Works naturally with programming languages (JSON-like syntax)
- **Fast & Efficient**: Optimized for read/write operations

### What is NoSQL?

**NoSQL** stands for **"Not Only SQL"** and refers to a class of databases that differ from traditional relational databases (like MySQL, PostgreSQL, Oracle).

**NoSQL Characteristics:**
- No rigid schema requirements
- Not based on SQL query language (though some support SQL-like queries)
- Optimized for specific data models (document, key-value, graph, time-series)
- Distributed by design
- Flexible data structures

### Types of NoSQL Databases

| Type | Example | Use Case | Structure |
|------|---------|----------|-----------|
| **Document** | MongoDB, CouchDB | Web apps, content management | JSON-like documents |
| **Key-Value** | Redis, Memcached | Caching, sessions | Simple key-value pairs |
| **Column-Family** | Cassandra, HBase | Time-series, analytics | Column-oriented storage |
| **Graph** | Neo4j | Social networks, relationships | Nodes and edges |
| **Search** | Elasticsearch | Full-text search | Inverted indexes |

---

## NoSQL vs Relational Databases

### Relational Databases (SQL)

**Examples**: MySQL, PostgreSQL, Oracle, SQL Server

**Advantages:**
✅ Structured data with strict schema  
✅ ACID transactions (Atomicity, Consistency, Isolation, Durability)  
✅ Established, mature technology  
✅ Complex queries with JOIN operations  
✅ Data integrity through constraints  

**Disadvantages:**
❌ Rigid schema - hard to change structure  
❌ Vertical scaling (limited)  
❌ Not ideal for unstructured data  
❌ Joins can be slow with large datasets  

**Best For:**
- Financial systems, banking
- Structured business data
- Applications requiring strict data integrity
- Complex relationships between data

---

### NoSQL Databases (MongoDB)

**Advantages:**
✅ Flexible schema - add fields anytime  
✅ Horizontal scaling (easy to distribute)  
✅ Handles unstructured/semi-structured data  
✅ Fast for simple operations  
✅ Developer-friendly (JSON-like)  
✅ Easy to evolve data model  

**Disadvantages:**
❌ No strict ACID transactions (older versions)  
❌ Can lead to data duplication  
❌ Larger file sizes  
❌ Less mature ecosystem  
❌ Requires careful data modeling  

**Best For:**
- Web applications with evolving data
- Content management systems
- Mobile apps
- Real-time analytics
- IoT and sensor data
- Rapidly prototyping applications

---

### Side-by-Side Comparison

| Feature | Relational (SQL) | NoSQL (MongoDB) |
|---------|------------------|-----------------|
| **Schema** | Rigid, predefined | Flexible, dynamic |
| **Data Format** | Tables/Rows | Documents (JSON-like) |
| **Scaling** | Vertical (add resources to one server) | Horizontal (add more servers) |
| **Transactions** | ACID (strict) | Eventual consistency |
| **Join Operations** | Native support (complex queries) | No native JOINs (use $lookup) |
| **Learning Curve** | Moderate | Easier for developers |
| **Data Integrity** | Strong (constraints) | Weak (flexible) |
| **Complex Queries** | Excellent | Good |
| **Simple Queries** | Good | Excellent |
| **Nested Data** | Normalized (multiple tables) | Embedded documents |

---

### When to Choose MongoDB (NoSQL)?

Choose MongoDB when:
- ✅ Your data structure is **not well-defined** or **evolving**
- ✅ You need **rapid development** and quick iterations
- ✅ Your data is **hierarchical or nested** (users with orders, posts with comments)
- ✅ You have **massive scale** requirements
- ✅ You're building **content-heavy applications** (blogs, wikis, CMS)
- ✅ You deal with **unstructured data** (JSON from APIs, logs)
- ✅ You're building **real-time applications** (chat, notifications)

### When to Choose SQL Database?

Choose SQL when:
- ✅ Your data is **highly structured** and **stable**
- ✅ You need **strict ACID compliance** (financial transactions)
- ✅ Your data has **complex relationships** (many-to-many)
- ✅ You need **complex queries** with multiple JOINs
- ✅ **Data integrity** is critical
- ✅ Your application is **write-heavy** with strong consistency needs
- ✅ You're building **enterprise applications** (ERP, CRM)

---

### Real-World Example

**User Registration System:**

**SQL Approach:**
```
Users Table
├── user_id (PK)
├── firstName
├── lastName
├── email

Addresses Table
├── address_id (PK)
├── user_id (FK)
├── city
├── street

Courses Table
├── course_id (PK)
├── courseName

UserCourses Table (Junction)
├── user_id (FK)
├── course_id (FK)
```

Multiple tables, JOINs needed for complete data.

**MongoDB Approach:**
```json
{
  "_id": ObjectId("123"),
  "firstName": "noha",
  "lastName": "hesham",
  "email": "noha@example.com",
  "address": {
    "city": "cairo",
    "street": 10,
    "building": 8
  },
  "courses": ["js", "mvc", "signalR", "expressjs"]
}
```

Single document with all related data embedded.

---
## Setup & Installation

### Prerequisites
- MongoDB uses **BSON** (Binary JSON) format for data storage
- Default **port**: `27017`
- Default **localhost**: `127.0.0.1`
- Uses **TCP/IP** protocol

### Installation on Ubuntu

```bash
# Download MongoDB server (version 8.2.3)
wget https://repo.mongodb.org/apt/ubuntu/dists/[release]/mongodb-org/[version]/amd64/debs/mongodb-org-server_8.2.3_amd64.deb

# Install package
sudo dpkg -i mongodb-org-server_8.2.3_amd64.deb

# Check service status
sudo systemctl status mongod.service

# Start MongoDB server
sudo systemctl start mongod.service
```

### Install MongoDB Shell (mongosh)

```bash
# Download mongosh client
wget https://downloads.mongodb.com/compass/mongodb-mongosh_2.6.0_amd64.deb

# Install client
sudo dpkg -i mongodb-mongosh_2.6.0_amd64.deb

# Start mongosh shell
mongosh
```

### Verify Installation

```bash
# In mongosh shell - check MongoDB version
show dbs;  # Lists all databases
```

---

## Basic Concepts

### Key Terminology

| Term | Description |
|------|-------------|
| **Database** | Container for collections (created on first use) |
| **Collection** | Container for documents (like a table) |
| **Document** | JSON-like object with key-value pairs |
| **Field** | Key in a document |
| **ObjectId** | Unique identifier automatically assigned by MongoDB |
| **BSON** | Binary JSON format used for storage |
| **Cursor** | Pointer to query results that can be iterated |

### Important Note on Empty Databases
- Empty databases don't appear in `show dbs;`
- They're created when you insert your first document

---

## Database & Collection Operations

### Create/Switch to Database

```javascript
use ITI;  // Creates database named ITI or switches to it
```

### Show Current Databases

```javascript
show dbs;  // Lists all non-empty databases
```

### Insert Operations

#### Insert One Document

```javascript
db.instructors.insertOne({
  _id: 16,
  firstName: "Andrew",
  lastName: "Emad",
  age: 21,
  salary: 3600,
  address: {
    city: "mansoura",
    street: 20,
    building: 18
  },
  courses: ["mongodb", "expressjs"]
})
```

#### Insert Many Documents

```javascript
db.instructors.insertMany([
  {
    _id: 6,
    firstName: "noha",
    lastName: "hesham",
    age: 21,
    salary: 3500,
    address: { city: "cairo", street: 10, building: 8 },
    courses: ["js", "mvc", "signalR", "expressjs"]
  },
  {
    _id: 7,
    firstName: "mona",
    lastName: "ahmed",
    age: 21,
    salary: 3600,
    address: { city: "cairo", street: 20, building: 8 },
    courses: ["es6", "mvc", "signalR", "expressjs"]
  }
])
```

**Key Point**: MongoDB is **flexible** - documents don't require all fields. Missing fields won't cause errors.

---

## CRUD Operations

### READ Operations

#### Find All Documents

```javascript
db.instructors.find({});
// Returns a cursor (automatically shows first 20 documents in mongosh)
// Type 'it' to continue iteration
```

**Return Type**: Cursor object

#### Find with Query Filter

```javascript
// Find instructors with salary > 4000
db.instructors.find({ salary: { $gt: 4000 } });

// Find instructors with age <= 25
db.instructors.find({ age: { $lte: 25 } });

// Find by nested field
db.instructors.find({ "address.city": "cairo" });
```

#### Find One Document

```javascript
db.instructors.findOne();
// Returns the first matching document as an object (not a cursor)
// Without query, returns first document
```

#### Get Cursor Type

```javascript
db.instructors.find().constructor.name;  // Returns "Cursor"
```

### Iterate Over Cursor

```javascript
db.instructors.find({}).forEach((document) => {
  print(document);
});
```

### CREATE Operations

Already covered in [Insert Operations](#insert-operations)

### UPDATE Operations

#### Update One Document

```javascript
// Update by filter, set new values
db.instructors.updateOne(
  { firstName: "noha" },
  { $set: { active: true } }
);
```

#### Update Many Documents

```javascript
// Add active property to all instructors
db.instructors.updateMany(
  {},
  { $set: { active: true } }
);
```

#### Update Operators

| Operator | Usage | Example |
|----------|-------|---------|
| `$set` | Set field value | `{ $set: { field: value } }` |
| `$inc` | Increment field | `{ $inc: { salary: -500 } }` |
| `$push` | Add to array | `{ $push: { courses: "jquery" } }` |
| `$pull` | Remove from array | `{ $pull: { courses: "EF" } }` |
| `$rename` | Rename field | `{ $rename: { address: "fullAddress" } }` |
| `$unset` | Remove field | `{ $unset: { courses: "" } }` |

#### Examples

```javascript
// Increment salary for instructors with 3 courses
db.instructors.updateMany(
  { courses: { $size: 3 } },
  { $inc: { salary: -500 } }
);

// Add jquery course to noha hesham
db.instructors.updateOne(
  { firstName: "noha", lastName: "hesham" },
  { $push: { courses: "jquery" } }
);

// Update array element without knowing index (positional operator)
db.instructors.updateOne(
  { firstName: "mazen", courses: "EF" },
  { $set: { "courses.$": "jquery" } }
);

// Rename field for all documents
db.instructors.updateMany(
  {},
  { $rename: { address: "fullAddress" } }
);

// Remove courses property from ahmed mohammed
db.instructors.updateOne(
  { firstName: "ahmed", lastName: "mohammed" },
  { $unset: { courses: "" } }
);
```

### DELETE Operations

#### Delete One Document

```javascript
// Delete instructor named ebtesam with exactly 5 courses
db.instructors.deleteOne({
  firstName: "ebtesam",
  courses: { $size: 5 }
});
```

#### Delete Many Documents

```javascript
db.instructors.deleteMany({ age: { $gt: 30 } });
```

---

## Query Operators

### Comparison Operators

```javascript
// Greater than
db.instructors.find({ salary: { $gt: 4000 } });

// Greater than or equal
db.instructors.find({ age: { $gte: 25 } });

// Less than
db.instructors.find({ age: { $lt: 25 } });

// Less than or equal
db.instructors.find({ age: { $lte: 25 } });

// Equal
db.instructors.find({ age: 21 });

// Not equal
db.instructors.find({ age: { $ne: 21 } });
```

### Logical Operators

```javascript
// AND - implicit (multiple conditions)
db.instructors.find({
  city: "mansoura",
  street: { $in: [10, 14] }  // Street is 10 OR 14
});

// OR - explicit
db.instructors.find({
  $or: [
    { city: "cairo" },
    { city: "mansoura" }
  ]
});

// Multiple conditions with AND
db.instructors.find({
  "address.city": "mansoura",
  "address.street": { $in: [10, 14] }
});
```

### Array Operators

```javascript
// Find instructors with ALL specified courses
db.instructors.find({
  courses: { $all: ["js", "jquery"] }
});

// Find by array size
db.instructors.find({
  courses: { $size: 3 }
});

// Find if element exists in array
db.instructors.find({
  courses: "js"
});
```

### Existence Operators

```javascript
// Documents that have firstName and lastName properties
db.instructors.find({
  firstName: { $exists: true },
  lastName: { $exists: true }
});
```

---

## Projection

**Projection** controls which fields to return in query results.

### Exclude _id by Default

MongoDB includes `_id` by default. To exclude:

```javascript
// Show only firstName and lastName
db.instructors.find(
  {},
  { firstName: 1, lastName: 1, _id: 0 }
);
```

### Common Patterns

```javascript
// Show firstName and salary only (exclude _id)
db.instructors.find(
  { salary: { $gt: 4000 } },
  { firstName: 1, salary: 1, _id: 0 }
);

// Show all except address
db.instructors.find(
  {},
  { address: 0 }
);

// Nested field projection
db.instructors.find(
  { "address.city": "cairo" },
  { firstName: 1, "address.street": 1, _id: 0 }
);
```

### Projection with forEach

```javascript
// Display only names
db.instructors.find({}).forEach((document) => {
  print(document.firstName + " " + document.lastName);
});
```

---

## Sorting & Limiting

### Sort Documents

```javascript
// Sort ascending (1 = ascending, -1 = descending)
db.instructors.find({})
  .sort({ firstName: 1, lastName: -1 });
// Sorts by firstName ascending, then by lastName descending

// Sort with projection
db.instructors.find(
  {
    firstName: { $exists: true },
    lastName: { $exists: true }
  },
  { firstName: 1, lastName: 1, age: 1, _id: 0 }
).sort({ firstName: 1, lastName: -1 });
```

### Limit Results

```javascript
db.instructors.find({}).limit(5);  // Returns only first 5 documents
```

---

## Aggregation Pipeline

**Aggregation** processes data in stages and transforms documents.

### Pipeline Stages

| Stage | Purpose |
|-------|---------|
| `$match` | Filter documents (like WHERE) |
| `$group` | Group by field and accumulate |
| `$project` | Reshape documents |
| `$sort` | Sort results |
| `$limit` | Limit number of results |
| `$lookup` | Join with another collection |
| `$unwind` | Flatten array fields |

### Examples

#### Count Products by Brand

```javascript
db.products.aggregate([
  {
    $group: {
      _id: "$brand_name",
      count: { $sum: 1 }
    }
  },
  {
    $sort: { count: -1 }
  }
]);
```

#### Group by Multiple Fields

```javascript
db.products.aggregate([
  {
    $match: { brand_name: { $in: ["Blue Label", "King", "Washington"] } }
  },
  {
    $group: {
      _id: { brand: "$brand_name", product: "$product_name" },
      count: { $sum: 1 }
    }
  },
  {
    $sort: { "_id.brand_name": 1, "_id.product_name": 1 }
  }
]);
```

#### Maximum Salary per Department (BONUS)

```javascript
db.employees.aggregate([
  {
    $group: {
      _id: "$department_name",
      maxSalary: { $max: "$salary" }
    }
  },
  {
    $project: {
      _id: 0,
      department: "$_id",
      maxSalary: 1
    }
  }
]);
```

#### Count Courses per Instructor

```javascript
db.instructors.find({}).forEach((document) => {
  print(document.firstName + " - " + document.courses.length);
});

// Or with aggregation:
db.instructors.aggregate([
  {
    $project: {
      firstName: 1,
      courseCount: { $size: "$courses" }
    }
  }
]);
```

---

## Relationships & Joins

### Using $lookup (JOIN)

```javascript
// Display employees with department names
db.employees.aggregate([
  {
    $lookup: {
      from: "departments",
      localField: "department_id",
      foreignField: "_id",
      as: "department"
    }
  },
  {
    $project: {
      firstName: 1,
      lastName: 1,
      "department.name": 1
    }
  }
]);
```

### Embedded Documents (Denormalization)

```javascript
// Query with embedded objects
db.instructors.find({
  "address.city": "cairo"
});

// Project nested fields
db.instructors.find(
  { "address.city": "cairo" },
  { firstName: 1, "address.street": 1, salary: 1 }
);
```

---

## Indexing

### Why Indexes Matter
- Speed up query performance
- Especially important for large datasets

### Create Index

```javascript
// Single field index
db.products.createIndex({ brand_name: 1 });

// Compound index (multiple fields)
db.products.createIndex({ brand_name: 1, product_name: 1 });
```

### Compare Query Speed

```javascript
// Without index - slower
db.products.find({ brand_name: "Washington" });

// After creating index - faster
db.products.createIndex({ brand_name: 1 });
db.products.find({ brand_name: "Washington" });
```

### View Indexes

```javascript
db.products.getIndexes();  // Show all indexes on collection
```

---

## Common Mistakes & Tips

### 🚫 Common Mistakes

1. **Forgetting to exclude _id**
   ```javascript
   // Wrong - includes _id
   db.instructors.find({}, { firstName: 1, lastName: 1 });
   
   // Right - excludes _id
   db.instructors.find({}, { firstName: 1, lastName: 1, _id: 0 });
   ```

2. **Confusing find() and findOne() return types**
   ```javascript
   // find() returns Cursor - need to iterate
   let cursor = db.instructors.find({});
   
   // findOne() returns object - can access directly
   let obj = db.instructors.findOne({});
   ```

3. **Using wrong update operator**
   ```javascript
   // Wrong - overwrites entire document
   db.instructors.updateOne({ _id: 6 }, { age: 25 });
   
   // Right - updates only specified fields
   db.instructors.updateOne({ _id: 6 }, { $set: { age: 25 } });
   ```

4. **Array operations without positional operators**
   ```javascript
   // Wrong - replaces entire array
   db.instructors.updateOne(
     { firstName: "mazen" },
     { $set: { courses: ["jquery"] } }
   );
   
   // Right - updates specific array element
   db.instructors.updateOne(
     { firstName: "mazen", courses: "EF" },
     { $set: { "courses.$": "jquery" } }
   );
   ```

### ✅ Best Practices

1. **Use ObjectId for _id** (MongoDB auto-generates)
   ```javascript
   // MongoDB creates _id automatically
   db.instructors.insertOne({ firstName: "john", lastName: "doe" });
   // _id is generated as ObjectId
   ```

2. **Use projection to reduce data transfer**
   ```javascript
   // Don't fetch unnecessary fields
   db.instructors.find({}, { firstName: 1, lastName: 1 });
   ```

3. **Create indexes for frequently queried fields**
   ```javascript
   // If querying by email often:
   db.users.createIndex({ email: 1 });
   ```

4. **Use $all for multi-value matching**
   ```javascript
   // Find instructors with BOTH js AND jquery
   db.instructors.find({ courses: { $all: ["js", "jquery"] } });
   ```

5. **Use $in for OR conditions on same field**
   ```javascript
   // Better than multiple $or conditions
   db.instructors.find({ "address.street": { $in: [10, 14] } });
   ```

6. **Combine queries efficiently**
   ```javascript
   // Combine filter, projection, sort, limit
   db.instructors.find(
     { salary: { $gt: 4000 } },
     { firstName: 1, salary: 1, _id: 0 }
   ).sort({ salary: -1 }).limit(5);
   ```

---

## Quick Reference

### Common Commands

```javascript
// Basic operations
show dbs;
use database_name;
show collections;
db.collection.find({});
db.collection.insertOne({});
db.collection.updateOne({}, { $set: {} });
db.collection.deleteOne({});

// Advanced
db.collection.aggregate([...]);
db.collection.createIndex({field: 1});
db.collection.find({}).sort({field: 1}).limit(10);
db.collection.findOne({query});

// Statistics
db.collection.countDocuments({});
db.collection.estimatedDocumentCount();
```

## Schema Validation in MongoDB

MongoDB provides **schema validation** to enforce structure while keeping the flexible approach. You can validate at the collection level.

#### Create Collection with Schema Validation

```javascript
// Create a collection with JSON Schema validation
db.createCollection("instructors", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["firstName", "lastName", "salary"],
      properties: {
        _id: { bsonType: "objectId" },
        firstName: {
          bsonType: "string",
          description: "First name (required, string)"
        },
        lastName: {
          bsonType: "string",
          description: "Last name (required, string)"
        },
        age: {
          bsonType: "int",
          description: "Age (optional, integer)"
        },
        salary: {
          bsonType: "double",
          description: "Salary (required, double)",
          minimum: 0,
          maximum: 100000
        },
        email: {
          bsonType: "string",
          pattern: "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$",
          description: "Email (optional, valid email format)"
        },
        address: {
          bsonType: "object",
          properties: {
            city: { bsonType: "string" },
            street: { bsonType: "int" },
            building: { bsonType: "int" }
          },
          required: ["city", "street"]
        },
        courses: {
          bsonType: "array",
          items: { bsonType: "string" },
          description: "List of courses (array of strings)"
        },
        active: {
          bsonType: "bool",
          description: "Whether instructor is active"
        }
      }
    }
  },
  validationLevel: "strict",  // Apply to all inserts/updates
  validationAction: "error"   // Reject invalid documents
})
```

#### Add Validation to Existing Collection

```javascript
// If collection already exists, add validator
db.runCommand({
  collMod: "instructors",
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["firstName", "lastName", "salary"],
      properties: {
        firstName: { bsonType: "string" },
        lastName: { bsonType: "string" },
        salary: {
          bsonType: "double",
          minimum: 0
        },
        age: { bsonType: "int" }
      }
    }
  },
  validationLevel: "moderate",  // Apply only to new inserts/updates
  validationAction: "warn"      // Log warning but allow
})
```

---

### Schema Validation Options

#### Validation Levels

| Level | Behavior |
|-------|----------|
| **strict** | Apply schema to all inserts and updates (default for new collections) |
| **moderate** | Apply only to new inserts and updates (skip existing documents) |

#### Validation Actions

| Action | Behavior |
|--------|----------|
| **error** | Reject documents that don't match schema (raises error) |
| **warn** | Allow documents but log warning if they don't match |

---

### JSON Schema Types in MongoDB

```javascript
{
  bsonType: "string"      // String values
  bsonType: "int"         // Integer numbers
  bsonType: "double"      // Floating-point numbers
  bsonType: "bool"        // Boolean (true/false)
  bsonType: "object"      // Nested documents
  bsonType: "array"       // Arrays
  bsonType: "objectId"    // MongoDB ObjectId
  bsonType: "date"        // Date objects
  bsonType: "null"        // Null values
}
```

---

### Practical Schema Examples

#### Example 1: User Collection with Validation

```javascript
db.createCollection("users", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["email", "firstName", "lastName"],
      properties: {
        _id: { bsonType: "objectId" },
        firstName: {
          bsonType: "string",
          minLength: 2,
          maxLength: 50
        },
        lastName: {
          bsonType: "string",
          minLength: 2,
          maxLength: 50
        },
        email: {
          bsonType: "string",
          pattern: "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
        },
        age: {
          bsonType: "int",
          minimum: 13,
          maximum: 120
        },
        createdAt: {
          bsonType: "date"
        }
      }
    }
  },
  validationLevel: "strict",
  validationAction: "error"
})
```

#### Example 2: Products Collection

```javascript
db.createCollection("products", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["name", "price", "brand_name"],
      properties: {
        _id: { bsonType: "objectId" },
        name: {
          bsonType: "string",
          description: "Product name"
        },
        price: {
          bsonType: "double",
          minimum: 0,
          description: "Price must be >= 0"
        },
        brand_name: {
          bsonType: "string",
          enum: ["Washington", "King", "Blue Label"],
          description: "Only these brands allowed"
        },
        quantity: {
          bsonType: "int",
          minimum: 0
        },
        tags: {
          bsonType: "array",
          items: { bsonType: "string" }
        },
        inStock: {
          bsonType: "bool"
        }
      }
    }
  },
  validationLevel: "strict",
  validationAction: "error"
})
```

---

### Testing Schema Validation

#### Valid Insert (Should Succeed)

```javascript
db.instructors.insertOne({
  firstName: "noha",
  lastName: "hesham",
  age: 21,
  salary: 3500,
  address: {
    city: "cairo",
    street: 10,
    building: 8
  },
  courses: ["js", "mvc"],
  active: true
})
// Success! Document inserted
```

#### Invalid Insert (Should Fail - Missing Required Field)

```javascript
db.instructors.insertOne({
  firstName: "mona",
  // lastName is missing - REQUIRED field!
  salary: 3600
})
// Error: Document failed validation
```

#### Invalid Insert (Should Fail - Wrong Type)

```javascript
db.instructors.insertOne({
  firstName: "ahmed",
  lastName: "hassan",
  age: "twenty-five",  // Should be int, not string!
  salary: 4000
})
// Error: Document failed validation (age must be int)
```

#### Invalid Insert (Should Fail - Out of Range)

```javascript
db.instructors.insertOne({
  firstName: "sara",
  lastName: "ali",
  salary: 150000  // Exceeds maximum: 100000
})
// Error: Document failed validation (salary > maximum)
```

---

### Update with Schema Validation

When schema validation is enabled, updates must also comply:

```javascript
// Valid update
db.instructors.updateOne(
  { firstName: "noha" },
  { $set: { salary: 4000 } }  // Valid salary
)
// Success!

// Invalid update - violates schema
db.instructors.updateOne(
  { firstName: "noha" },
  { $set: { salary: -1000 } }  // salary < minimum!
)
// Error: Document failed validation
```

---

### Best Practices for Schemas

1. **Design your schema** even if MongoDB is flexible
   ```javascript
   // Plan your data structure before coding
   // Document expected fields and types
   ```

2. **Use validation for critical collections**
   ```javascript
   // Validate user, product, order collections
   // Less critical collections can be flexible
   ```

3. **Use moderate validation for evolving apps**
   ```javascript
   // Start with validationLevel: "moderate"
   // Graduate to "strict" when data is stable
   ```

4. **Document required vs optional fields**
   ```javascript
   required: ["firstName", "lastName", "email"],
   // Optional: age, phone, address
   ```

5. **Add constraints for data integrity**
   ```javascript
   minimum: 0,      // Price can't be negative
   enum: ["..."],   // Only specific values allowed
   pattern: "...",  // Email format validation
   ```

6. **Use descriptive field descriptions**
   ```javascript
   description: "Email (required, valid email format)"
   ```

---

### When to Enforce Schemas

| Scenario | Recommendation |
|----------|-----------------|
| **Early prototype** | Skip validation - focus on features |
| **Growing app** | Use moderate validation - log warnings |
| **Production app** | Strict validation with error action |
| **Financial data** | Always strict validation with error action |
| **Evolving data** | Use $jsonSchema with careful planning |

---


using mongo atlas is better than local because it is managed and i can access the db without the server it is hosting , more reasearch on the subject