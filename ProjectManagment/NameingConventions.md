# Snake & Ladder Game - Project Structure & Naming Conventions

## Project File Structure

```
snake-and-ladder/
│
├── index.html                          # Entry point (Home/Start page)
├── game.html                           # Game page
├── result.html                         # Result/Leaderboard page
│
├── css/
│   ├── global.css                      # Global styles, CSS variables, resets
│   ├── home.css                        # Home page specific styles
│   ├── game.css                        # Game page specific styles
│   ├── result.css                      # Result page specific styles
│   └── instructions-modal.css          # Instructions popup styles
│
├── js/
│   ├── utils/
│   │   ├── storage.js                  # LocalStorage management utilities
│   │   └── helpers.js                  # General helper functions
│   │
│   ├── components/
│   │   ├── instructions-modal.js       # Instructions popup component
│   │   └── dice.js                     # Dice animation and logic
│   │
│   ├── game-logic/
│   │   ├── board.js                    # Board rendering and management
│   │   ├── player.js                   # Player class and management
│   │   ├── game-state.js               # Game state management
│   │   └── rules.js                    # Snake & ladder logic, win conditions
│   │
│   ├── pages/
│   │   ├── home.js                     # Home page initialization
│   │   ├── game.js                     # Game page initialization
│   │   └── result.js                   # Result page initialization
│   │
│   └── config/
│       └── game-config.js              # Game configuration (board size, snakes, ladders)
│
└── assets/
    ├── images/
    │   ├── board/
    │   │   ├── snake-*.png             # Snake images
    │   │   └── ladder-*.png            # Ladder images
    │   │
    │   ├── dice/
    │   │   └── dice-*.png              # Dice face images (if using images)
    │   │
    │   └── icons/
    │       └── *.svg                   # UI icons
    │
    └── audio/                          # Optional sound effects
        ├── dice-roll.mp3
        ├── snake-bite.mp3
        └── ladder-climb.mp3
```

---

## Reasoning Behind Structure

### Root Level
- **Separate HTML files**: Each major page (home, game, result) has its own HTML file for clear separation of concerns and easier navigation.

### CSS Directory
- **Modular approach**: Each page has its own CSS file to avoid bloat and improve maintainability.
- **global.css**: Contains CSS variables (colors, fonts), resets, and shared styles used across all pages.
- **Component-specific CSS**: Modal and reusable components have dedicated stylesheets.

### JS Directory

#### `/utils`
Contains pure utility functions that don't depend on game logic:
- **storage.js**: Handles all localStorage operations (save/load game state, player data)
- **helpers.js**: Generic helper functions (random numbers, array shuffling, DOM manipulation)

#### `/components`
Reusable UI components that can be used across different pages:
- **instructions-modal.js**: Popup logic accessible from any page
- **dice.js**: Dice rolling animation and randomization

#### `/game-logic`
Core game mechanics separated by responsibility:
- **board.js**: Renders the board, handles visual updates
- **player.js**: Player class with properties (name, color, position) and methods
- **game-state.js**: Manages current game state (turn tracking, active players)
- **rules.js**: Implements snake/ladder mechanics, movement validation, win conditions

#### `/pages`
Page-specific initialization and event handlers:
- Each file initializes its respective page and wires up UI interactions

#### `/config`
Configuration files for easy game customization:
- **game-config.js**: Define board layout, snake positions, ladder positions, rules

### Assets Directory
Organized by type (images, audio) with subcategories for easy management and scalability.

---

## Naming Conventions

### 1. Files and Folders

```javascript
// Folders: lowercase with hyphens (kebab-case)
game-logic/
instructions-modal.css

// Files: lowercase with hyphens (kebab-case)
game-state.js
instructions-modal.js
home.css
```

**Reason**: Kebab-case is URL-friendly, cross-platform compatible, and widely used in web development.

---

### 2. JavaScript Variables and Functions

```javascript
// Variables: camelCase
let playerCount = 2;
let currentPlayer = null;
let diceValue = 0;
let isGameActive = false;

// Constants: UPPER_SNAKE_CASE
const MAX_PLAYERS = 4;
const BOARD_SIZE = 100;
const WINNING_POSITION = 100;

// Functions: camelCase with verb prefix
function rollDice() { }
function movePlayer(playerId, steps) { }
function checkForSnakeOrLadder(position) { }
function initializeGame() { }
function updatePlayerPosition(player) { }
function getPlayerById(id) { }
function hasPlayerWon(position) { }

// Boolean functions: prefix with 'is', 'has', 'can', 'should'
function isValidMove(position) { }
function hasWon(player) { }
function canRollDice() { }
```

---

### 3. CSS Classes

```css
/* BEM Methodology (Block__Element--Modifier) */

/* Blocks (main components) */
.game-board { }
.player-card { }
.dice-container { }
.modal { }


/* State classes: prefix with 'is-' or 'has-' */
.is-active { }
.is-disabled { }
.is-winner { }
.has-snake { }
.has-ladder { }
```

**Reason**: Kebab provides clear, self-documenting class names and prevents CSS conflicts. Utility and state prefixes make special-purpose classes immediately recognizable.

---

### 4. HTML IDs

```html
<!-- Use camelCase for IDs -->
<div id="gameBoard"></div>
<button id="rollDiceBtn"></button>
<input id="playerNameInput" />
<div id="instructionsModal"></div>
<div id="timerDisplay"></div>

<!-- Be specific and descriptive -->
<button id="startGameBtn">Play</button>
<button id="nextTurnBtn">Next</button>
<div id="leaderboardContainer"></div>
```

**Reason**: IDs are unique identifiers, camelCase distinguishes them from classes and makes them easy to reference in JavaScript.

---

### 5. JavaScript Classes

```javascript
// Classes: PascalCase
class Player {
    constructor(name, color) {
        this.name = name;
        this.color = color;
        this.position = 0;
    }
}

class GameBoard {
    constructor(size) {
        this.size = size;
        this.snakes = [];
        this.ladders = [];
    }
}

class GameState {
    constructor() {
        this.players = [];
        this.currentTurn = 0;
        this.isActive = false;
    }
}
```

**Reason**: PascalCase is the standard convention for classes in JavaScript and makes them easily distinguishable from functions and variables.

---

### 6. Data Attributes

```html
<!-- Use kebab-case for data attributes -->
<div class="game-board__cell" 
     data-position="45" 
     data-has-snake="true"
     data-snake-destination="12">
</div>

<button class="player-card" 
        data-player-id="1" 
        data-player-color="#ff0000">
</button>
```

---

## Summary Table

| Element | Convention | Example |
|---------|-----------|---------|
| Files & Folders | kebab-case | `game-logic/`, `player.js` |
| Variables | camelCase | `playerCount`, `currentTurn` |
| Constants | UPPER_SNAKE_CASE | `MAX_PLAYERS`, `BOARD_SIZE` |
| Functions | camelCase (verb prefix) | `rollDice()`, `movePlayer()` |
| Classes | PascalCase | `Player`, `GameBoard` |
| CSS Classes | BEM / kebab-case | `.game-board__cell--active` |
| HTML IDs | camelCase | `gameBoard`, `rollDiceBtn` |
| Data Attributes | kebab-case | `data-player-id`, `data-position` |

---

## Additional Best Practices

1. **Comments**: Use JSDoc-style comments for functions
```javascript
/**
 * Moves player to new position and handles snakes/ladders
 * @param {Object} player - Player object
 * @param {number} steps - Number of steps to move
 * @returns {number} Final position after snakes/ladders
 */
function movePlayer(player, steps) { }
```

2. **Event Handlers**: Prefix with 'handle' or 'on'
```javascript
function handleDiceRoll() { }
function onPlayerMove() { }
```

3. **Async Functions**: Be explicit
```javascript
async function loadGameState() { }
async function saveGameResult() { }
```

4. **Meaningful Names**: Avoid abbreviations unless universally understood
```javascript
// Good
let playerPosition = 45;

// Avoid
let pPos = 45;
```

This structure provides a scalable, maintainable foundation for your Snake & Ladder game!