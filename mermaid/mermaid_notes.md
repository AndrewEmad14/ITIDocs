# Personal Mermaid Notes

## Table of Contents

- [What is Mermaid?](#what-is-mermaid)
- [Basic Syntax](#basic-syntax)
- [Diagram Types Overview](#diagram-types-overview)
- [Flowchart](#flowchart)
  - [Direction](#direction)
  - [Node Shapes](#node-shapes)
  - [Link / Arrow Types](#link--arrow-types)
  - [Subgraphs](#subgraphs)
- [Sequence Diagram](#sequence-diagram)
  - [Message Arrow Types](#message-arrow-types)
  - [Loops & Conditions](#loops--conditions)
  - [Activation Bars](#activation-bars)
- [Class Diagram](#class-diagram)
  - [Visibility Modifiers](#visibility-modifiers)
  - [Relationships](#relationships)
  - [Cardinality](#cardinality)
- [State Diagram](#state-diagram)
  - [Nested States](#nested-states)
- [Entity Relationship (ER) Diagram](#entity-relationship-er-diagram)
- [Gantt Chart](#gantt-chart)
- [Pie Chart](#pie-chart)
- [Mind Map](#mind-map)
- [Git Graph](#git-graph)
- [Timeline](#timeline)
- [Quadrant Chart](#quadrant-chart)
- [Styling & Themes](#styling--themes)
  - [Built-in Themes](#built-in-themes)
  - [Node Styling](#node-styling-flowchart)
  - [CSS Classes](#css-classes)
- [Comments](#comments)
- [Common Pitfalls](#common-pitfalls)
- [Quick Reference — All Shape Syntax](#quick-reference--all-shape-syntax)
- [Setup in VS Code](#setup-in-vs-code)
- [Embedding in GitHub](#embedding-in-github)

---

## What is Mermaid?

Mermaid is a JavaScript-based diagramming tool that lets you create diagrams and charts using simple text syntax inside Markdown files.

Supported in: **GitHub**, **GitLab**, **Notion**, **Obsidian**, **VS Code** (with extensions), **Typora**, and more.

---

## Basic Syntax

Every Mermaid diagram starts by declaring its **diagram type** on the first line inside a code block tagged with `mermaid`.

````md
```mermaid
<diagram_type>
    <your content here>
```
````

---

## Diagram Types Overview

| Type | Keyword | Use Case |
|------|---------|----------|
| Flowchart | `flowchart` / `graph` | Processes, decision trees |
| Sequence | `sequenceDiagram` | Object interactions over time |
| Class | `classDiagram` | OOP class structure |
| State | `stateDiagram-v2` | State machines |
| Entity Relationship | `erDiagram` | Database schemas |
| Gantt | `gantt` | Project timelines |
| Pie Chart | `pie` | Data proportions |
| Mind Map | `mindmap` | Brainstorming / topic trees |
| Git Graph | `gitGraph` | Git branching |
| Timeline | `timeline` | Chronological events |
| Quadrant | `quadrantChart` | 2-axis categorization |

---

## Flowchart

### Direction

```mermaid
flowchart LR
    A --> B
```

| Keyword | Direction |
|---------|-----------|
| `LR` | Left → Right |
| `RL` | Right → Left |
| `TB` | Top → Bottom |
| `BT` | Bottom → Top |

---

### Node Shapes

```mermaid
flowchart LR
    A[Rectangle]
    B(Rounded)
    C([Stadium])
    D[[Subroutine]]
    E[(Database)]
    F((Circle))
    G{Diamond}
    H{{Hexagon}}
    I[/Parallelogram/]
    J[\Parallelogram Alt\]
    K[/Trapezoid\]
    L[\Trapezoid Alt/]
```

| Shape | Syntax | Meaning |
|-------|--------|---------|
| Rectangle | `[text]` | Default process step |
| Rounded | `(text)` | Start / end (soft) |
| Stadium | `([text])` | Terminal |
| Subroutine | `[[text]]` | Predefined process |
| Database | `[(text)]` | Data storage |
| Circle | `((text))` | Junction / connector |
| Diamond | `{text}` | Decision |
| Hexagon | `{{text}}` | Preparation step |
| Parallelogram | `[/text/]` | Input / output |
| Trapezoid | `[/text\]` | Manual operation |

---

### Link / Arrow Types

```mermaid
flowchart LR
    A --> B
    C --- D
    E -.-> F
    G ==> H
    I --o J
    K --x L
    M <--> N
```

| Syntax | Meaning |
|--------|---------|
| `-->` | Arrow (directed) |
| `---` | Open line (no arrow) |
| `-.->` | Dotted arrow |
| `==>` | Thick arrow |
| `--o` | Circle end |
| `--x` | Cross end |
| `<-->` | Bidirectional |

### Arrow Labels

```mermaid
flowchart LR
    A -->|yes| B
    A -->|no| C
```

**📝 Note:** Text goes between `|pipes|` after the arrow.

---

### Subgraphs

```mermaid
flowchart LR
    subgraph Frontend
        A[React] --> B[State]
    end
    subgraph Backend
        C[API] --> D[DB]
    end
    B --> C
```

```md
subgraph <title>
    <nodes>
end
```

---

## Sequence Diagram

Used to show how objects/actors interact **over time**.

```mermaid
sequenceDiagram
    participant Client
    participant Server
    participant DB

    Client->>Server: HTTP Request
    Server->>DB: Query
    DB-->>Server: Result
    Server-->>Client: HTTP Response
```

### Message Arrow Types

| Syntax | Meaning |
|--------|---------|
| `->>` | Solid arrow (sync call) |
| `-->>` | Dashed arrow (response) |
| `-x` | Solid with X (async, no reply) |
| `--x` | Dashed with X |

### Loops & Conditions

```mermaid
sequenceDiagram
    loop Every 5s
        Client->>Server: Ping
        Server-->>Client: Pong
    end

    alt Success
        Server-->>Client: 200 OK
    else Failure
        Server-->>Client: 500 Error
    end

    opt Optional Step
        Client->>Server: Extra call
    end
```

### Activation Bars

```mermaid
sequenceDiagram
    Client->>+Server: Request
    Server-->>-Client: Response
```

**📝 Note:** `+` activates the bar, `-` deactivates it.

---

## Class Diagram

Used to model **OOP structure**: classes, attributes, methods, and relationships.

```mermaid
classDiagram
    class Animal {
        +String name
        +int age
        +makeSound() void
    }

    class Dog {
        +String breed
        +fetch() void
    }

    Animal <|-- Dog
```

### Visibility Modifiers

| Symbol | Meaning |
|--------|---------|
| `+` | public |
| `-` | private |
| `#` | protected |
| `~` | package/internal |

### Relationships

| Syntax | Relationship |
|--------|-------------|
| `<|--` | Inheritance (extends) |
| `<|..` | Realization (implements) |
| `-->` | Association |
| `--` | Link |
| `..>` | Dependency |
| `*--` | Composition |
| `o--` | Aggregation |

### Cardinality

```mermaid
classDiagram
    Customer "1" --> "0..*" Order : places
```

**📝 Note:** Put cardinality in quotes on each side of the arrow.

---

## State Diagram

Used to model **state machines** — how a system transitions between states.

```mermaid
stateDiagram-v2
    [*] --> Idle
    Idle --> Running : start()
    Running --> Paused : pause()
    Paused --> Running : resume()
    Running --> [*] : stop()
```

| Syntax | Meaning |
|--------|---------|
| `[*]` | Initial or final state |
| `-->` | Transition |
| `: label` | Transition label (event/action) |

### Nested States

```mermaid
stateDiagram-v2
    state "Active" as Active {
        [*] --> Loading
        Loading --> Ready
    }
    [*] --> Active
    Active --> [*]
```

---

## Entity Relationship (ER) Diagram

Used to design **database schemas**.

```mermaid
erDiagram
    CUSTOMER ||--o{ ORDER : places
    ORDER ||--|{ LINE_ITEM : contains
    PRODUCT ||--o{ LINE_ITEM : "included in"

    CUSTOMER {
        int id PK
        string name
        string email
    }
    ORDER {
        int id PK
        date created_at
        int customer_id FK
    }
```

### Relationship Notation

| Left | Right | Meaning |
|------|-------|---------|
| `\|\|` | `\|\|` | Exactly one |
| `\|o` | `o\|` | Zero or one |
| `\|\{` | `\}\|` | One or more |
| `o\{` | `\}o` | Zero or more |

---

## Gantt Chart

Used to represent **project timelines and schedules**.

```mermaid
gantt
    title Project Timeline
    dateFormat  YYYY-MM-DD

    section Planning
    Requirements   :done,    req,  2024-01-01, 2024-01-07
    Design         :active,  des,  2024-01-08, 10d

    section Development
    Backend        :         be,   2024-01-18, 14d
    Frontend       :         fe,   after be,   7d

    section Testing
    QA             :crit,    qa,   after fe,   5d
```

### Task Modifiers

| Keyword | Meaning |
|---------|---------|
| `done` | Completed task |
| `active` | Currently in progress |
| `crit` | Critical path |
| `after <id>` | Starts after another task |

---

## Pie Chart

```mermaid
pie title Browser Market Share
    "Chrome" : 65
    "Firefox" : 15
    "Safari" : 12
    "Other" : 8
```

**📝 Note:** Values don't need to add up to 100 — Mermaid calculates percentages automatically.

---

## Mind Map

```mermaid
mindmap
  root((Mermaid))
    Diagrams
      Flowchart
      Sequence
      Class
    Use Cases
      Documentation
      Planning
      Architecture
    Platforms
      GitHub
      Obsidian
      VS Code
```

**📝 Note:** Indentation defines the hierarchy. The root node uses `(())` for a circle shape.

---

## Git Graph

```mermaid
gitGraph
    commit id: "Initial"
    branch develop
    checkout develop
    commit id: "Feature A"
    commit id: "Feature B"
    checkout main
    merge develop id: "Merge to main"
    commit id: "Hotfix"
```

### Commands

| Command | Description |
|---------|-------------|
| `commit` | Add a commit |
| `branch <name>` | Create new branch |
| `checkout <name>` | Switch to branch |
| `merge <name>` | Merge branch into current |

---

## Timeline

```mermaid
timeline
    title History of the Web
    1991 : World Wide Web invented
    1995 : JavaScript created
    2005 : AJAX popularized
    2009 : Node.js released
    2013 : React released
    2016 : Vue.js released
```

---

## Quadrant Chart

```mermaid
quadrantChart
    title Feature Priority Matrix
    x-axis Low Effort --> High Effort
    y-axis Low Impact --> High Impact
    quadrant-1 Do First
    quadrant-2 Plan It
    quadrant-3 Delegate
    quadrant-4 Avoid

    Feature A: [0.2, 0.8]
    Feature B: [0.8, 0.7]
    Feature C: [0.3, 0.2]
    Feature D: [0.75, 0.3]
```

**📝 Note:** Coordinates are `[x, y]` between `0` and `1`.

---

## Styling & Themes

### Built-in Themes

```md
%%{init: {'theme': 'dark'}}%%
```

| Theme | Description |
|-------|-------------|
| `default` | Light theme |
| `dark` | Dark background |
| `forest` | Green tones |
| `neutral` | Monochrome |
| `base` | Customizable base |

### Node Styling (Flowchart)

```mermaid
flowchart LR
    A[Start] --> B[Process]
    style A fill:#4CAF50,color:#fff,stroke:#388E3C
    style B fill:#2196F3,color:#fff,stroke:#1565C0
```

```md
style <nodeId> fill:<color>, stroke:<color>, color:<textColor>
```

### CSS Classes

```mermaid
flowchart LR
    A:::greenBox --> B:::blueBox
    classDef greenBox fill:#4CAF50,color:white
    classDef blueBox fill:#2196F3,color:white
```

**📝 Note:** Apply with `:::className` after the node ID.

---

## Comments

```mermaid
flowchart LR
    %% This is a comment
    A --> B
```

Use `%%` for single-line comments anywhere in the diagram.

---

## Common Pitfalls

### ⚠️ Special Characters in Labels

If your label contains `(`, `)`, `[`, `]`, or quotes — wrap it in **quotes**:

```mermaid
flowchart LR
    A["User (Authenticated)"] --> B["Dashboard [Main]"]
```

### ⚠️ Direction Must Be First Line

```mermaid
flowchart TD   %%  ✅ direction declared on same line as type
    A --> B
```

### ⚠️ Indentation Matters in Mind Maps

Mind map hierarchy is purely indent-based. Mixing tabs and spaces will break it.

### ⚠️ ER Attribute Syntax

Each attribute must be on its own line:

```md
ENTITY {
    type name constraint
}
```

---

## Quick Reference — All Shape Syntax

```mermaid
flowchart TD
    A[Rectangle]
    B(Rounded Rectangle)
    C([Stadium / Pill])
    D[[Subroutine]]
    E[(Cylinder / DB)]
    F((Circle))
    G{Diamond}
    H{{Hexagon}}
    I[/Parallelogram/]
    J[\Parallelogram Alt\]
    K[/Trapezoid\]
    L[\Trapezoid Alt/]
```

---

## Setup in VS Code

1. Install extension: **Mermaid Preview** or **Markdown Preview Mermaid Support**
2. Open any `.md` file
3. Use `Ctrl+Shift+V` to preview

### Live Editor (No Install)

Visit **[mermaid.live](https://mermaid.live)** — paste code, see diagram instantly.

---

## Embedding in GitHub

GitHub renders Mermaid automatically in `.md` files:

````md
```mermaid
flowchart LR
    A --> B
```
````

**⚠️ Warning:** Not all Mermaid diagram types are supported on all platforms. Flowcharts, sequence, and class diagrams have the widest support.
