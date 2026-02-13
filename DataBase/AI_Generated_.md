# Comprehensive Database Guide: Concepts & MySQL Implementation

## Table of Contents
1. [Introduction to Databases](#introduction)
2. [Database Types & Architecture](#database-architecture)
3. [Database Design & Modeling](#database-design)
4. [SQL Fundamentals](#sql-fundamentals)
5. [Database Objects & Optimization](#database-objects)
6. [Normalization](#normalization)

---

## Introduction to Databases

### Why Databases Matter

Every application has two fundamental layers:
- **Application Layer**: User-facing interface
- **Database Layer**: Data storage and management

### Database Management Systems (DBMS) Overview

Modern DBMS options fall into two categories:

**Relational DBMS** (Enterprise & Open Source)
- Open Source: MySQL, PostgreSQL (suitable for small to medium projects)
- Proprietary: Microsoft SQL Server, Oracle Database, IBM Db2 (enterprise-grade for large-scale projects)

**Limitations of Spreadsheets (e.g., Excel)**
- Cannot handle large volumes of data
- No support for foreign keys or referential integrity
- Data redundancy leads to inconsistency
- No enforced data relationships
- Limited concurrent user access
- Incompatible with modern application frameworks

---

## Database Architecture

### DBMS Schema Levels

A DBMS operates across three levels of abstraction:

**External Schema (View Level)**
- Defines what data users see and how it's presented
- User-specific perspectives of the database
- Provides data independence for different user groups

**Conceptual Schema (Logical Level)**
- Contains all tables and relationships between data
- Implementation-independent representation
- Defines the overall structure and business rules

**Physical Schema (Storage Level)**
- Describes how data is physically stored on disk
- Defines access paths and storage locations
- Determines how the DBMS retrieves data efficiently

### Metadata

Metadata is "data about data" and includes:
- **Schema Information**: Table names, column names, data types (integer, string, etc.), primary keys, and foreign keys
- **Structural Information**: Table relationships and view definitions
- **Administrative Details**: User information, ownership, creation/modification dates
- **Descriptive Information**: Table descriptions, column definitions, and business context
- **Performance Information**: Database size, storage metrics, and performance statistics

### DBMS Environment Models

**Centralized Environments**
- Mainframe: Traditional centralized computing (slow, single point of failure)
- Client-Server (2-Tier): Client requests, server responds
- Internet Computing (3-Tier): Client → Application Server → Database Server

**Distributed Environments**
- **Replication** (Homogeneous): Identical database copies across locations
  - Partial Replication: Subset of data copied
  - Full Replication: Complete database copied
- **Fragmentation** (Heterogeneous): Data distributed across different systems
  - Horizontal Fragmentation: Rows distributed by condition
  - Vertical Fragmentation: Columns distributed by subset

---

## Database Design & Modeling

### Data Models

**Conceptual Data Model**
- Uses concepts close to how users perceive data
- High-level abstraction using entities and relationships
- Independent of any specific database technology

**Physical Data Model**
- Describes how data is physically stored on disk
- Specifies file structures and access paths
- Optimized for performance and storage efficiency

### Software Development Life Cycle (SDLC)

Database development follows structured steps:

1. **Analysis & Requirements Gathering** (System Analyst)
   - Interview stakeholders
   - Document business rules
   - Identify data needs

2. **Database Design** (Database Designer)
   - Create Entity-Relationship Diagrams (ERD)
   - Define tables and relationships
   - Establish constraints and keys

3. **Implementation** (DBA / Database Developer)
   - Database Administrator: Installation, backup, recovery, security
   - Database Developer: Schema creation, performance tuning
   - Application Developer: Integration with application layer

4. **Testing & Maintenance**
   - Quality assurance
   - Performance monitoring
   - Ongoing optimization and updates

### Entity-Relationship Diagrams (ERD)

#### Entity Types

**Strong Entity**
- Has a primary key (at least one unique identifier)
- Can exist independently
- Example: Employee (identified by EmployeeID)

**Weak Entity**
- No primary key of its own
- Must be fully dependent on a parent entity
- Identified by combination of parent's primary key and partial key
- Example: Dependent (identified by EmployeeID + DependentName)
- Important: A weak entity cannot be reassigned to another parent entity

#### Attribute Types

- **Simple/Atomic Attributes**: Single, indivisible values
- **Composite Attributes**: Can be broken down (e.g., Address → Street, City, Zip)
- **Derived Attributes**: Calculated from other attributes (e.g., Bill from Quantity × Price)
- **Multivalued Attributes**: Can have multiple values for one entity (e.g., Phone Numbers)
- **Primary Key (PK)**: Uniquely identifies each record
- **Foreign Key (FK)**: References another table's primary key

#### Relationship Types

**By Degree** (Number of entities involved)
- **Binary**: Between 2 entities (most common)
- **Ternary**: Between 3 entities (creates separate table with FKs from each entity)
- **Unary**: An entity relates to itself (e.g., Employee supervises Employee)

**By Cardinality** (Data occurrence constraints)
- **One-to-One (1:1)**: Each record in Table A relates to exactly one record in Table B
- **One-to-Many (1:M)**: One record in Table A relates to many in Table B
- **Many-to-Many (M:M)**: Records in both tables can relate to multiple records in the other

**By Participation** (Dependency constraints)
- **Total (Must)**: Every record in the entity must participate in the relationship
- **Partial (May)**: Some records may not participate in the relationship

### Entity-Relationship Mapping to Tables

**Mapping Rules Based on Cardinality & Participation**

| Cardinality | Participation | Strategy |
|-------------|---|---|
| 1:1 | May-Must | Place FK in "May" side table |
| 1:1 | May-May | FK in either table, or create separate table |
| 1:1 | Must-Must | Merge tables (they represent same entity) |
| 1:M | May-Must | Place FK in "Many" side table |
| 1:M | May-May | Place FK in "Many" side table |
| 1:M | Must-Must | Place FK in "Many" side table |
| M:M | Any | Create junction table with FKs from both entities |

**Special Considerations**

- **Multivalued Attributes**: Create separate table with FK to parent entity
- **Composite Attributes**: Decompose into atomic columns
- **Weak Entities**: Include parent's PK as part of own identifier
- **Unary Relationships (Self-referencing)**:
  - 1:M: Add self-referencing FK in same table
  - M:M: Create junction table with two FKs to same entity
- **Primary Key Design**: Prefer single PK; if using composite key, consider surrogate key for simplicity

### Non-Relational Databases (NoSQL)

When traditional relational databases aren't suitable, NoSQL offers alternatives.

**Characteristics of NoSQL Databases**
- No fixed table structure
- No formal primary/foreign key constraints
- No enforced data integrity constraints
- No formal relationships between data
- High performance for specific use cases
- Data typically stored as JSON or binary formats

**Advantages**
- Excellent for high-velocity data ingestion
- Handles variety of data types and structures
- Highly scalable horizontally
- Fast read/write operations
- Ideal for media and unstructured data storage

**NoSQL Database Types**

1. **Document-Oriented** (MongoDB)
   - Stores data as JSON/BSON documents
   - Flexible schema
   - Querying within documents

2. **Key-Value** (Redis, Oracle NoSQL)
   - Simple key-value pairs
   - Ultra-fast retrieval
   - Suitable for caching and sessions

3. **Column-Family** (Apache HBase, Cassandra)
   - Optimized for column-based queries
   - Highly scalable
   - Efficient for time-series data

4. **Graph** (Neo4j)
   - Represents relationships as edges
   - Excellent for social networks and recommendations
   - Efficient relationship traversal

**When to Use NoSQL**
- High data velocity (real-time streaming)
- High variety (unstructured or semi-structured data)
- High complexity (interconnected relationships)
- High volume (massive scale data)
- Flexible schema requirements

---

## SQL Fundamentals

### SQL Sublanguages

SQL is divided into three main categories:

#### Data Definition Language (DDL)
Used to define database structure. **Auto-commits changes.**

```sql
CREATE TABLE employees (
    employee_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100),
    salary DECIMAL(10,2)
);

ALTER TABLE employees ADD COLUMN hire_date DATE;

DROP TABLE employees;  -- Removes table definition and data

TRUNCATE TABLE employees;  -- Removes all data but keeps structure
```

#### Data Manipulation Language (DML)
Used to interact with data. Requires explicit commit for persistence.

```sql
SELECT employee_id, name FROM employees WHERE salary > 50000;

INSERT INTO employees (name, salary) VALUES ('John Doe', 60000);

UPDATE employees SET salary = 65000 WHERE employee_id = 1;

DELETE FROM employees WHERE employee_id = 1;

MERGE INTO target_table USING source_table  -- SQL Server, Oracle syntax
    ON condition
    WHEN MATCHED THEN UPDATE SET columns
    WHEN NOT MATCHED THEN INSERT;
```

#### Data Control Language (DCL)
Manages user permissions and security.

```sql
GRANT SELECT, INSERT ON employees TO user_name;

REVOKE DELETE ON employees FROM user_name;
```

### Data Types

**Numeric Types**
```sql
INT, BIGINT, SMALLINT, TINYINT  -- Integers
DECIMAL(precision, scale)        -- Fixed-point (e.g., DECIMAL(10,2))
FLOAT, DOUBLE                    -- Floating-point
```

Example: `DECIMAL(10,2)` = 10 total digits, 2 after decimal point (e.g., 12345678.90)

**String Types**
```sql
VARCHAR(length)      -- Variable-length string
CHAR(length)         -- Fixed-length string
TEXT                 -- Large text
```

**Date/Time Types**
```sql
DATE                 -- YYYY-MM-DD
TIME                 -- HH:MM:SS
DATETIME/TIMESTAMP   -- Date and time combined
```

**Date Conversion Function**
```sql
STR_TO_DATE("17-6-2022", "%d-%m-%Y")  -- Converts string to DATE

-- Format specifiers: %d (day), %m (month), %Y (4-digit year), %y (2-digit year)
```

### SELECT Statements

**Basic SELECT with WHERE**
```sql
SELECT column1, column2
FROM table_name
WHERE condition;
```

**Aggregate Functions**
```sql
COUNT(*)             -- Total number of rows
SUM(column)          -- Sum of numeric values
AVG(column)          -- Average value
MAX(column)          -- Maximum value
MIN(column)          -- Minimum value
```

**Grouping Results**
```sql
SELECT department_id, COUNT(*), AVG(salary)
FROM employees
GROUP BY department_id;
```

**Filtering Grouped Results**
```sql
SELECT department_id, COUNT(*) as emp_count
FROM employees
GROUP BY department_id
HAVING COUNT(*) > 5;  -- HAVING filters grouped results (use after GROUP BY)
```

**Important**: Cannot use column aliases in WHERE or HAVING clauses directly; must repeat the expression.

### Order of Execution in SELECT Statements

Understanding the execution order is critical for writing correct queries. **The logical order of execution is different from the written order.**

**Written Order:**
```sql
SELECT column1, column2
FROM table_name
WHERE condition
GROUP BY column
HAVING aggregate_condition
ORDER BY column;
```

**Actual Execution Order:**

1. **FROM** - Identifies the table(s) to retrieve data from
2. **WHERE** - Filters rows based on conditions (applied BEFORE grouping)
   - Cannot use aggregate functions here
   - Cannot use aliases created in SELECT
   - Row-level filtering
3. **GROUP BY** - Groups rows by specified columns
   - Collapses rows into groups
   - Each group becomes one result row
4. **HAVING** - Filters groups based on aggregate conditions (applied AFTER grouping)
   - Must use with aggregate functions
   - Filters entire groups, not individual rows
   - Can use aliases if supported by DBMS
5. **SELECT** - Retrieves specified columns
   - Executes after grouping
   - This is why aliases created here can't be used in WHERE or HAVING
6. **ORDER BY** - Sorts the final result set (executed last)

**Practical Example:**

```sql
SELECT department_id, COUNT(*) as emp_count, AVG(salary) as avg_salary
FROM employees
WHERE salary > 30000              -- Step 2: Filter rows BEFORE grouping
GROUP BY department_id            -- Step 3: Group remaining rows
HAVING COUNT(*) > 5               -- Step 4: Filter groups AFTER grouping
ORDER BY avg_salary DESC;         -- Step 6: Sort results
```

**Explanation:**
1. FROM employees: Start with employee table
2. WHERE salary > 30000: Remove employees earning ≤ $30,000
3. GROUP BY department_id: Group remaining employees by department
4. HAVING COUNT(*) > 5: Keep only departments with more than 5 employees
5. SELECT: Calculate count and average for each department
6. ORDER BY: Sort by average salary descending

**Key Rules Based on Execution Order:**

| Clause | Can Use Aggregate Functions? | Can Use Aliases? | Purpose |
|---|---|---|---|
| WHERE | ❌ No | ❌ No | Filter individual rows before grouping |
| GROUP BY | ❌ No | ⚠️ DBMS dependent | Group rows together |
| HAVING | ✅ Yes | ⚠️ DBMS dependent | Filter groups after aggregation |
| SELECT | ✅ Yes | ✅ Yes | Choose columns and create aliases |
| ORDER BY | ✅ Yes | ✅ Yes | Sort final results |

**Common Mistakes:**

```sql
-- ❌ WRONG: Using aggregate in WHERE
SELECT department_id, COUNT(*) as emp_count
FROM employees
WHERE COUNT(*) > 5        -- Error: Aggregate functions not allowed in WHERE
GROUP BY department_id;

-- ✅ CORRECT: Use HAVING instead
SELECT department_id, COUNT(*) as emp_count
FROM employees
GROUP BY department_id
HAVING COUNT(*) > 5;

-- ❌ WRONG: Using alias in WHERE
SELECT salary * 1.1 as increased_salary
FROM employees
WHERE increased_salary > 50000    -- Error: Alias not yet created

-- ✅ CORRECT: Repeat the expression
SELECT salary * 1.1 as increased_salary
FROM employees
WHERE salary * 1.1 > 50000;
```

**Handling Duplicate Column Names**
```sql
SELECT employees.employee_id, departments.department_id
FROM employees, departments;

-- Use table name or alias to disambiguate
SELECT e.employee_id, d.department_id
FROM employees e, departments d;
```

### JOIN Operations

JOINs combine data from multiple tables. **Use JOIN syntax with ON for clarity; WHERE implicitly performs INNER JOIN.**

**INNER JOIN** (Default)
```sql
SELECT e.employee_id, e.name, d.department_name
FROM employees e
INNER JOIN departments d ON e.department_id = d.department_id;
-- Returns only rows where condition matches in both tables
```

**LEFT OUTER JOIN**
```sql
SELECT e.employee_id, e.name, d.department_name
FROM employees e
LEFT OUTER JOIN departments d ON e.department_id = d.department_id;
-- Returns all rows from left table; NULL for unmatched right table rows
```

**RIGHT OUTER JOIN**
```sql
SELECT e.employee_id, e.name, d.department_name
FROM employees e
RIGHT OUTER JOIN departments d ON e.department_id = d.department_id;
-- Returns all rows from right table; NULL for unmatched left table rows
```

**FULL OUTER JOIN**
```sql
SELECT e.employee_id, e.name, d.department_name
FROM employees e
FULL OUTER JOIN departments d ON e.department_id = d.department_id;
-- Returns all rows from both tables; NULL where not matched
-- Note: Not available in MySQL; use UNION of LEFT and RIGHT JOINs
```

**Self-Join** (Unary Relationship)
```sql
SELECT manager.employee_id, manager.name, employee.name
FROM employees manager
INNER JOIN employees employee ON manager.employee_id = employee.manager_id;
```

### INSERT Statements

```sql
INSERT INTO employees (employee_id, name, salary)
VALUES (1, 'John Doe', 60000);

-- Best Practice: Always specify column names
-- Do NOT manually insert AUTO_INCREMENT values; let database generate them
INSERT INTO employees (name, salary)
VALUES ('Jane Smith', 65000);
```

---

## Database Objects & Optimization

### Views

A view is a virtual table based on a query result. Views provide abstraction and security.

**Creating a View**
```sql
CREATE OR REPLACE VIEW emps_depts_view AS
SELECT e.employee_id, e.last_name, e.salary, e.email, e.hire_date,
       e.department_id, d.department_name
FROM employees e
INNER JOIN departments d ON e.department_id = d.department_id;
```

**Querying a View**
```sql
SELECT employee_id, last_name, department_id
FROM emps_depts_view
WHERE department_id = 90;
```

**WITH CHECK OPTION**
```sql
CREATE OR REPLACE VIEW simple_vu20 AS
SELECT * FROM employees
WHERE department_id = 20
WITH CHECK OPTION;
-- Prevents updates that would exclude row from view definition
```

### Indexing

Indexes speed up data retrieval during SELECT and JOIN operations.

**Performance Optimization Layers**

1. **Hardware**: Server specifications, memory (RAM), CPU speed
2. **Networking**: Network infrastructure, bandwidth, latency
3. **Software (Application)**: Algorithm efficiency, query design, nested loops optimization
4. **Database (DBA)**: Query optimization, indexing strategy, statistics

**Index Benefits**
- Dramatically speeds up SELECT queries
- Accelerates JOIN operations
- Improves WHERE clause filtering
- Trade-off: Slower INSERT/UPDATE/DELETE (must update indexes)

**Creating an Index**
```sql
CREATE INDEX idx_salary ON employees(salary);

CREATE UNIQUE INDEX idx_email ON users(email);
```

---

## Normalization

Normalization is the process of organizing database structure to minimize redundancy and improve data integrity. It involves progressive levels of refinement.

### First Normal Form (1NF)

**Requirements**
- All values must be atomic (indivisible, single values)
- Each record must be unique (enforced by primary key)
- No repeating groups or arrays in a single cell
- No multivalued attributes

**Example Violation**
```
Employee Table (violates 1NF):
| EmployeeID | Name    | Phone Numbers      |
|------------|---------|-------------------|
| 1          | John    | 555-1111, 555-2222|
```

**Fix: Move multivalued attributes to separate table**
```
Employee Table:
| EmployeeID | Name    |
|------------|---------|
| 1          | John    |

Phone Table:
| EmployeeID | Phone      |
|------------|-----------|
| 1          | 555-1111  |
| 1          | 555-2222  |
```

### Second Normal Form (2NF)

**Requirements**
- Must already be in 1NF
- No partial dependencies (only applies when primary key is composite)
- Every non-key column must depend on the **entire** primary key, not just part of it

**Example Violation** (Composite PK: CourseID + StudentID)
```
Enrollment Table (violates 2NF):
| CourseID | StudentID | CourseName | InstructorName |
|----------|-----------|------------|----------------|
| 101      | 1         | Math       | Dr. Smith      |
```
Problem: CourseName depends only on CourseID, not the full key.

**Fix: Separate into multiple tables**
```
Enrollment Table:
| CourseID | StudentID | Grade |
|----------|-----------|-------|
| 101      | 1         | A     |

Course Table:
| CourseID | CourseName | InstructorName |
|----------|------------|----------------|
| 101      | Math       | Dr. Smith      |
```

### Third Normal Form (3NF)

**Requirements**
- Must already be in 2NF
- No transitive dependencies
- Non-key columns must not depend on other non-key columns

**Example Violation**
```
Employee Table (violates 3NF):
| EmployeeID | Name    | DepartmentID | DepartmentName |
|------------|---------|--------------|----------------|
| 1          | John    | 10           | Sales          |
```
Problem: DepartmentName depends on DepartmentID (another non-key column), not directly on EmployeeID.

**Fix: Separate into multiple tables**
```
Employee Table:
| EmployeeID | Name    | DepartmentID |
|------------|---------|--------------|
| 1          | John    | 10           |

Department Table:
| DepartmentID | DepartmentName |
|--------------|----------------|
| 10           | Sales          |
```

### Normalization Summary Table

| Normal Form | Focus | Example Problem | Solution |
|---|---|---|---|
| 1NF | Atomic values | Multiple phone numbers in one cell | Move multivalued data to separate table |
| 2NF | Composite PK dependencies | Column depends on part of composite key | Create separate tables for each entity |
| 3NF | Transitive dependencies | Column depends on another non-key column | Separate dependent data into new table |

### Implementation Best Practices

- Start implementation with the smallest entities first (those with no foreign key dependencies)
- Ensure every action is tested before committing
- Use transactions to maintain consistency
- Set default schema to avoid repetitive schema references: `USE schema_name;`
- Include column names in INSERT statements for clarity and flexibility

---

## Common Database Terminology

**CRM** (Customer Relationship Management): Software for managing customer interactions and data

**POS** (Point Of Sale): System for processing retail transactions

**ERP** (Enterprise Resource Planning): Integrated software for managing business operations

**Primary Key (PK) Constraints**
- Cannot be NULL
- Must be unique
- Only one per table (though composite keys can contain multiple columns)

**Foreign Key (FK)**
- References another table's primary key
- Enforces referential integrity
- Can be NULL if relationship is optional

---
