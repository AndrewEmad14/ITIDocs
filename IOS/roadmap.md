# iOS & SwiftUI Mastery Curriculum
### Target Project: Gym Buddy — iOS & iPadOS
### Standard: Industry-Ready iOS Engineer

---

## How to Use This Document

Every phase builds on the previous. Do not skip phases. Each task has a clear goal, a reference to official documentation, and a deliverable. At the end of every phase is a **mini project** that ties all tasks together using the Gym Buddy domain. Phase 8 is the full production application.

**Mentorship Protocol:** When working through tasks with your mentor, follow the session flow defined in your instructions. Every claim, pattern, and recommendation must be backed by official documentation.

---

## Curriculum Overview

| Phase | Title | Focus |
|---|---|---|
| 0 | Re-entry & Calibration | Swift refresh, SwiftUI mental model, Xcode tooling |
| 1 | Swift Language Mastery | Generics, protocols, property wrappers, error handling |
| 2 | SwiftUI Core | Declarative UI, state management, layout, animation |
| 3 | App Architecture & Lifecycle | MVVM, DI, app lifecycle, routing |
| 4 | Async, Networking & Data | Swift Concurrency, URLSession, SwiftData, offline-first |
| 5 | Platform APIs | HealthKit, Notifications, Camera, Widgets, Sign in with Apple |
| 6 | Quality & Debugging | XCTest, Instruments, Accessibility, MetricKit |
| 7 | Capstone Integration | iPad layout, full feature integration, App Store prep |
| 8 | Production Application | Gym Buddy, full build, real users, production monitoring |

---

## Industry-Standard Libraries Reference

These are the libraries you will encounter in real iOS codebases. They are integrated progressively across phases.

### Networking
| Library | Purpose | When You'll Use It |
|---|---|---|
| `URLSession` (native) | HTTP layer | Phase 1, 4 |
| [Alamofire](https://github.com/Alamofire/Alamofire) | Cleaner API, retry logic, interceptors | Phase 4 |
| [Moya](https://github.com/Moya/Moya) | Network abstraction on Alamofire | Phase 4 (optional) |

### Image Loading
| Library | Purpose | When You'll Use It |
|---|---|---|
| `AsyncImage` (native) | Basic async image loading | Phase 2 |
| [Kingfisher](https://github.com/onevcat/Kingfisher) | Caching, transitions, placeholders | Phase 4 |

### Dependency Injection
| Library | Purpose | When You'll Use It |
|---|---|---|
| Manual DI (native) | `@EnvironmentObject`, init injection | Phase 3 |
| [Factory](https://github.com/hmlongco/Factory) | Compile-time safe DI container | Phase 3 |

### Architecture
| Library | Purpose | When You'll Use It |
|---|---|---|
| MVVM (pattern) | Separation of concerns | Phase 3+ |
| [TCA](https://github.com/pointfreeco/swift-composable-architecture) | Unidirectional, testable state | Phase 3 (studied), Phase 8 (applied) |
| [Combine](https://developer.apple.com/documentation/combine) | Reactive framework, native | Phase 4 |

### Testing
| Library | Purpose | When You'll Use It |
|---|---|---|
| `XCTest` (native) | Unit + UI testing | Phase 6 |
| [Quick + Nimble](https://github.com/Quick/Quick) | BDD-style tests | Phase 6 |
| [SnapshotTesting](https://github.com/pointfreeco/swift-snapshot-testing) | UI regression | Phase 6 |

### Monitoring
| Library | Purpose | When You'll Use It |
|---|---|---|
| [Firebase Crashlytics](https://firebase.google.com/docs/crashlytics) | Crash reporting | Phase 8 |
| [Firebase Analytics](https://firebase.google.com/docs/analytics) | Event tracking | Phase 8 |
| [Pulse](https://github.com/kean/Pulse) | Network debug logger | Phase 4 |

---

---

# Phase 0 — Re-entry & Calibration

> **Goal:** Surface what is rusted, close the gaps, and rebuild your mental model of SwiftUI before writing a single line of production code. This is not a beginner course — it is a calibration.

**Exit Criteria:** Before moving to Phase 1, answer these without hesitation:
- What is the difference between `@State` and `@Binding` — who owns the data?
- Why does SwiftUI prefer `struct` over `class` for Views?
- What triggers a SwiftUI view to re-render?
- What is the difference between `class` and `struct` mutation behavior?

---

## 0.1 — Swift Language Re-calibration

### Task 0.1.1 — Optionals in Practice
Write five separate functions that each demonstrate a different optional-handling strategy: `if let`, `guard let`, `??` (nil coalescing), optional chaining, and forced unwrap. After writing them, write a comment above each explaining **when** that strategy is appropriate and when it is dangerous.

**What it targets:** Optionals are the number one source of iOS crashes. You must be able to choose the right unwrapping strategy without thinking.

**Deliverable:** A Swift playground file with five functions and written justifications.

**Reference:** [The Swift Programming Language — Optionals](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/thebasics/#Optionals)

---

### Task 0.1.2 — Value vs Reference Semantics
Implement a `WorkoutSet` model as a `struct`. Then implement the same model as a `class`. Write a small test harness that assigns a value to a new variable, mutates the copy, and prints both. Observe and document the difference in behavior. Write a paragraph explaining which you would choose for Gym Buddy data models and why.

**What it targets:** This is the most important conceptual divide in Swift. SwiftUI's entire rendering model depends on value semantics.

**Deliverable:** Two implementations, a test harness, and a written explanation.

**Reference:** [Choosing Between Structures and Classes — Apple](https://developer.apple.com/documentation/swift/choosing-between-structures-and-classes)

---

### Task 0.1.3 — Closures to Async/Await Bridge
Write a function that fetches mock workout data using a completion handler closure. Then rewrite the exact same function using `async/await`. The mock data can be a hardcoded array — no real network needed yet.

**What it targets:** Closures are still everywhere in legacy codebases. You must be able to read closure-based code and understand how modern `async/await` replaced it.

**Deliverable:** Two versions of the same function, with comments explaining what changed and why.

**Reference:** [Swift Concurrency — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/concurrency/)

---

### Task 0.1.4 — Functional Collection Operations
Given an array of `Meal` structs (use your model from the session), use `map`, `filter`, `reduce`, `compactMap`, and `flatMap` to answer five questions without using a single `for` loop:
1. Get the name of every meal
2. Get only meals above 500 calories
3. Calculate total calories for the day
4. Safely extract calorie counts from an array of optional meals
5. Flatten a nested array of meal arrays into one array

**What it targets:** These operators are used constantly in Swift. If you reach for `for` loops first, you are writing C in Swift.

**Deliverable:** Five expressions using functional operators, each with a comment explaining the choice.

**Reference:** [Collection Transformations — Swift Docs](https://developer.apple.com/documentation/swift/array)

---

### Task 0.1.5 — Generics Warm-Up
Implement a generic function `clamp<T: Comparable>(_ value: T, min: T, max: T) -> T` that constrains any comparable value between a minimum and maximum. Then use it to clamp: a calorie goal between 1200 and 4000, a rep count between 1 and 100, and a body weight between 30.0 and 300.0.

**What it targets:** Generics are how you write reusable, type-safe code. They underpin SwiftUI's entire API.

**Deliverable:** The generic function and three use-case demonstrations.

**Reference:** [Generics — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/generics/)

---

## 0.2 — SwiftUI Mental Model Reset

### Task 0.2.1 — The Rendering Contract
Build a counter view with a button that increments a number. Then write a comment in the code explaining: **why does changing `count` cause the view to re-render?** Your explanation must reference the SwiftUI documentation's description of state — not your own intuition.

**What it targets:** Most SwiftUI bugs come from not understanding the rendering contract. You must be able to explain it precisely.

**Deliverable:** A counter view + a written explanation citing the docs.

**Reference:** [Managing State — Apple SwiftUI Docs](https://developer.apple.com/documentation/swiftui/managing-user-interface-state)

---

### Task 0.2.2 — Binding and Data Ownership
Build a parent view that owns a `mealName: String` state variable. Pass it down to a child `MealNameEditor` view that can edit it. The parent must display the current value. No `@EnvironmentObject`, no globals — only `@State` and `@Binding`.

**What it targets:** Binding is the two-way channel. Understanding who owns the data is the foundation of every architecture decision in SwiftUI.

**Deliverable:** A parent view, a child editor view, and a comment explaining who owns the state and why.

**Reference:** [Binding — Apple SwiftUI Docs](https://developer.apple.com/documentation/swiftui/binding)

---

### Task 0.2.3 — Lists and Mutations
Build a meal log screen that displays a `List` of `Meal` items. Implement swipe-to-delete and drag-to-reorder. Add a button that adds a new placeholder meal to the list.

**What it targets:** `List` with `ForEach` is one of the most used patterns in iOS. Deletions and reordering are expected knowledge at any iOS interview.

**Deliverable:** A working meal list with add, delete, and reorder.

**Reference:** [List — Apple SwiftUI Docs](https://developer.apple.com/documentation/swiftui/list)

---

### Task 0.2.4 — Navigation and Tab Structure
Build the skeleton of Gym Buddy's main navigation: a `TabView` with four tabs (Dashboard, Nutrition, Workouts, Progress). Each tab should use a `NavigationStack`. Tapping an item in a list should push a detail view.

**What it targets:** Navigation is where most iOS beginners get stuck. `NavigationStack` replaced `NavigationView` in iOS 16 — you must use the modern API.

**Deliverable:** A four-tab app with working push navigation in at least one tab.

**Reference:** [NavigationStack — Apple SwiftUI Docs](https://developer.apple.com/documentation/swiftui/navigationstack)

---

### Task 0.2.5 — Animation Basics
Add a visual indicator to the Dashboard tab that toggles between "On Track" and "Behind" states. Animate the transition using `withAnimation`. Use a conditional modifier to change the color and scale of the indicator.

**What it targets:** Animation in SwiftUI is declarative — you describe states, not transitions. Understanding this distinction is critical.

**Deliverable:** An animated state indicator with at least one color and one scale transition.

**Reference:** [Animation — Apple SwiftUI Docs](https://developer.apple.com/documentation/swiftui/animation)

---

## 0.3 — Xcode & Tooling Re-entry

### Task 0.3.1 — Device and Simulator Setup
Create a new SwiftUI project from scratch. Run it on the iOS Simulator. Then configure signing and run it on a physical device. Document any provisioning issues you encounter and how you resolved them.

**What it targets:** Developers returning to iOS often waste hours on signing. Understanding the basics eliminates this friction.

**Reference:** [Simulator — Apple Docs](https://developer.apple.com/documentation/xcode/running-your-app-in-simulator-or-on-a-device)

---

### Task 0.3.2 — LLDB Debugger
Place a breakpoint inside your meal list's delete handler. Run the app, trigger the breakpoint, and use `po` in the LLDB console to inspect the meal being deleted. Print the meal's `id` and `name` from the console.

**What it targets:** Most developers only use `print()`. LLDB is orders of magnitude more powerful and is expected knowledge at senior level.

**Reference:** [LLDB Debugger — Apple](https://developer.apple.com/documentation/xcode/stepping-through-code-and-inspecting-variables-in-the-debugger)

---

### Task 0.3.3 — Logging with `Logger`
Replace every `print()` statement in your Phase 0 code with `os.Logger`. Use appropriate log levels (`debug`, `info`, `error`). Write a comment explaining why `Logger` is preferred over `print()` in production builds.

**What it targets:** `print()` has no log levels, no filtering, and significant performance overhead in production. `Logger` is the industry standard.

**Reference:** [Logger — Apple Docs](https://developer.apple.com/documentation/os/logger)

---

### Task 0.3.4 — Reading a Crash Report
Force a crash in your app (force-unwrap a nil optional). Let it crash on the simulator. Find the crash report in Xcode's Devices & Simulators window. Identify the offending line and explain what the stack trace is telling you.

**What it targets:** Reading crash reports is a daily task for production iOS engineers. Xcode symbolication connects memory addresses to source lines.

**Reference:** [Analyzing Crash Reports — Apple](https://developer.apple.com/documentation/xcode/analyzing-a-crash-report)

---

## Phase 0 — Mini Project: Gym Buddy Shell

**Build the navigable skeleton of Gym Buddy.**

### Requirements
- Four-tab navigation: Dashboard, Nutrition, Workouts, Progress
- Each tab uses `NavigationStack`
- Dashboard shows a hardcoded summary card: calories remaining, today's date, a streak count
- Nutrition tab shows a static `List` of three hardcoded meals with swipe-to-delete
- An "Add Meal" button that appends a placeholder meal to the list
- All state managed with `@State` — no ViewModels yet
- All `print()` replaced with `Logger`
- App runs on both iPhone and iPad simulator without layout breakage

### What You Are Proving
You can build a navigable, stateful SwiftUI application from scratch using only native tools and the correct modern APIs.

---

---

# Phase 1 — Swift Language Mastery

> **Goal:** Go beyond syntax. Develop the language instincts that separate a Swift developer from an iOS developer who happens to write Swift.

**Exit Criteria:**
- You can write and explain a generic, protocol-constrained function
- You understand the difference between a protocol with and without associated types
- You can implement a custom property wrapper and explain what it compiles down to
- You can model a state machine using enums with associated values

---

## 1.1 — Generics

### Task 1.1.1 — Generic Network Response Wrapper
Write a generic `APIResponse<T>` struct that wraps any decodable type. It should carry either a success value of type `T` or an error. Do not use `Result<T, E>` — build the wrapper manually first so you understand what `Result` is doing under the hood.

**Reference:** [Generics — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/generics/)

---

### Task 1.1.2 — Generic Paginated List
Build a generic `PaginatedList<T>` struct that holds an array of items, a current page number, and a boolean indicating whether more pages exist. Write a method that merges a new page of items into the existing list.

**Reference:** [Generic Types — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/generics/#Generic-Types)

---

### Task 1.1.3 — Type Constraints
Write a generic function `findMax<T: Comparable>(_ items: [T]) -> T?` that returns the maximum value in any array of comparable items. Use it to find the heaviest `WorkoutSet` by weight, the highest calorie meal, and the longest workout duration.

**Reference:** [Type Constraints — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/generics/#Type-Constraints)

---

## 1.2 — Protocols & Protocol-Oriented Programming

### Task 1.2.1 — Protocol Definitions
Define a `Loggable` protocol that requires a `logDescription: String` computed property. Conform `Meal`, `WorkoutSet`, and a new `HydrationEntry` struct to it. Write a function that accepts any `Loggable` and prints its description.

**Reference:** [Protocols — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/protocols/)

---

### Task 1.2.2 — Protocol Extensions with Default Implementations
Add a default implementation to `Loggable` that formats the description as `"[TypeName] logged at [date]"`. Then override it specifically for `Meal` to include calorie count. This is the core of Protocol-Oriented Programming.

**Reference:** [Protocol Extensions — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/protocols/#Protocol-Extensions)

---

### Task 1.2.3 — Associated Types
Define a `Repository` protocol with an associated type `Model`. It should require `fetch() async throws -> [Model]`, `save(_ model: Model) async throws`, and `delete(id: UUID) async throws`. Implement a `MealRepository` that conforms to it with in-memory storage.

**Reference:** [Associated Types — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/generics/#Associated-Types)

---

## 1.3 — Property Wrappers

### Task 1.3.1 — `@UserDefaultsBacked`
Implement a `@propertyWrapper` called `@UserDefaultsBacked<T>` that reads and writes any `Codable` value to `UserDefaults`. Use it to persist the user's daily calorie goal. This is the pattern that `@AppStorage` is built on — understanding the primitive makes you better with the abstraction.

**Reference:** [Property Wrappers — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/properties/#Property-Wrappers)

---

### Task 1.3.2 — `@Clamped`
Implement a `@Clamped` property wrapper that accepts a `ClosedRange<T>` and constrains any `Comparable` value within it. Use it on a `WorkoutSet.reps` property to prevent invalid entries (e.g., negative reps or more than 100).

**Reference:** [Property Wrappers — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/properties/#Property-Wrappers)

---

## 1.4 — Error Handling

### Task 1.4.1 — Typed Error Domain
Define a `NutritionError` enum conforming to `Error` with cases covering: `foodNotFound`, `invalidBarcode`, `apiRateLimited(retryAfter: Int)`, and `decodingFailed(reason: String)`. Write a function that throws each case under different conditions and handles them with exhaustive `catch` blocks.

**Reference:** [Error Handling — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/errorhandling/)

---

### Task 1.4.2 — Result Type in Practice
Rewrite the function from Task 1.4.1 to return `Result<Food, NutritionError>` instead of throwing. Then write a call site that handles both cases using `switch`. Explain in a comment when you would choose `throws` vs `Result` as a return type.

**Reference:** [Result — Apple Docs](https://developer.apple.com/documentation/swift/result)

---

## 1.5 — Enums and State Machines

### Task 1.5.1 — Workout Session State Machine
Model an active workout session as an enum:

```swift
enum WorkoutSessionState {
    case idle
    case active(startedAt: Date)
    case resting(secondsRemaining: Int)
    case completed(duration: TimeInterval, totalSets: Int)
    case cancelled
}
```

Write a `WorkoutSessionManager` struct (not class — yet) with a `transition(_ event: SessionEvent)` method that enforces valid state transitions. Invalid transitions should throw a typed error.

**Reference:** [Enumerations — Swift Book](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/enumerations/)

---

## Phase 1 — Mini Project: Gym Buddy Data Layer

**Build the complete, type-safe data model layer for Gym Buddy.**

### Requirements

#### Models (all `struct`, all `Codable`, all `Identifiable`)
- `Meal` with `Macros`, `loggedAt`, `modifiedAt`, `UUID` id, and `calculatedCalories` computed property
- `WorkoutSession` with associated exercises
- `Exercise` with name, muscle group (enum), and equipment type (enum)
- `WorkoutSet` with reps, weight, and a `@Clamped` wrapper on reps
- `HydrationEntry` with millilitres and timestamp
- `UserProfile` with daily calorie goal backed by `@UserDefaultsBacked`

#### Repository Layer
- A `Repository` protocol with associated type `Model`
- In-memory implementations: `MealRepository`, `WorkoutRepository`

#### Error Handling
- A typed `GymBuddyError` enum covering nutrition, workout, and persistence domains

#### State Machine
- `WorkoutSessionState` with valid transitions enforced

### What You Are Proving
You can design a complete, type-safe domain model layer that another engineer could build a UI on top of without asking you questions.

---

---

# Phase 2 — SwiftUI Core

> **Goal:** Master the declarative UI model. Build complex, reusable, and animated interfaces that work correctly on both iPhone and iPad.

**Exit Criteria:**
- You can explain what triggers a view body re-evaluation
- You can design a reusable component library
- You understand the difference between `@State`, `@Binding`, `@StateObject`, and `@ObservedObject`
- You can build an adaptive layout that responds to size class changes

---

## 2.1 — State Management Deep Dive

### Task 2.1.1 — `@State` vs `@Binding` Ownership Rules
Build a `NutritionLogView` with an `AddMealSheet`. The sheet edits a draft `Meal`. The parent only receives the final meal when the user taps "Save". Implement this with correct state ownership — no child view should own state it does not originate.

**Reference:** [State and Data Flow — Apple](https://developer.apple.com/documentation/swiftui/state-and-data-flow)

---

### Task 2.1.2 — `@StateObject` vs `@ObservedObject`
Build a `TimerViewModel` class conforming to `ObservableObject` that counts up every second using a `Timer`. Use it in two views: one that owns it (`@StateObject`) and one that observes it (`@ObservedObject`). Destroy and recreate the observing view and document what happens to the timer.

**What it targets:** This distinction causes real production bugs. `@StateObject` survives re-renders. `@ObservedObject` does not own the lifecycle.

**Reference:** [StateObject — Apple Docs](https://developer.apple.com/documentation/swiftui/stateobject)

---

### Task 2.1.3 — `@EnvironmentObject` for App-Wide State
Move `UserProfile` into an `@EnvironmentObject` injected at the app root. Access it in three deeply nested views without passing it through every intermediate view. Write a comment explaining why this is not always the right tool.

**Reference:** [EnvironmentObject — Apple Docs](https://developer.apple.com/documentation/swiftui/environmentobject)

---

## 2.2 — Layout System

### Task 2.2.1 — Custom Layout with `Layout` Protocol
Implement a `MacroRingLayout` using the `Layout` protocol that positions three circular progress indicators (protein, carbs, fat) in a triangle formation. Do not use `ZStack` with hardcoded offsets.

**Reference:** [Layout Protocol — Apple Docs](https://developer.apple.com/documentation/swiftui/layout)

---

### Task 2.2.2 — `GeometryReader` for Proportional Layouts
Build a calorie progress bar that fills proportionally to the day's calorie intake vs goal. Use `GeometryReader` to make the bar width responsive to its container. Do not hardcode any pixel values.

**Reference:** [GeometryReader — Apple Docs](https://developer.apple.com/documentation/swiftui/geometryreader)

---

### Task 2.2.3 — Adaptive iPad Layout with `horizontalSizeClass`
Take your Phase 0 shell. On iPhone, keep the `TabView`. On iPad, replace it with a `NavigationSplitView` with a sidebar. Use `@Environment(\.horizontalSizeClass)` to switch between the two layouts.

**Reference:** [NavigationSplitView — Apple Docs](https://developer.apple.com/documentation/swiftui/navigationsplitview)

---

## 2.3 — Reusable Components

### Task 2.3.1 — Custom `ViewModifier`
Build a `CardModifier` that applies a rounded corner, drop shadow, and background color. Apply it to every card in the app via a `.card()` convenience extension on `View`.

**Reference:** [ViewModifier — Apple Docs](https://developer.apple.com/documentation/swiftui/viewmodifier)

---

### Task 2.3.2 — Custom `ButtonStyle`
Build a `PrimaryButtonStyle` and a `DestructiveButtonStyle` that animate a scale effect on press. Apply them throughout the app.

**Reference:** [ButtonStyle — Apple Docs](https://developer.apple.com/documentation/swiftui/buttonstyle)

---

### Task 2.3.3 — `PreferenceKey` for Upward Data Flow
Build a scroll view where a child view reports its own height to its parent using `PreferenceKey`. Use this to dynamically size a sticky header above the scroll view.

**Reference:** [PreferenceKey — Apple Docs](https://developer.apple.com/documentation/swiftui/preferencekey)

---

## 2.4 — Animation & Transitions

### Task 2.4.1 — `matchedGeometryEffect` for Hero Animations
Build a workout list where tapping a workout expands it into a full-screen detail view using a hero transition via `matchedGeometryEffect`.

**Reference:** [matchedGeometryEffect — Apple Docs](https://developer.apple.com/documentation/swiftui/view/matchedgeometryeffect(id:in:properties:anchor:issource:))

---

### Task 2.4.2 — Swift Charts for Progress Visualization
Using the Swift Charts framework, build:
- A bar chart showing daily calorie intake for the past 7 days
- A line chart showing body weight over the past 30 days
- A pie/donut chart showing today's macro breakdown

**Reference:** [Swift Charts — Apple Docs](https://developer.apple.com/documentation/charts)

---

## Phase 2 — Mini Project: Gym Buddy Full UI

**Build the complete UI for Gym Buddy using only mock/hardcoded data.**

### Requirements
- Dashboard: macro ring, calorie progress bar, streak counter, today's workout card
- Nutrition: meal list, add meal sheet with form validation, macro breakdown chart
- Workouts: exercise list, active workout logger with rest timer, sets/reps/weight input
- Progress: weight chart (30 days), calorie chart (7 days), personal records list
- Adaptive layout: `NavigationSplitView` on iPad, `TabView` on iPhone
- All reusable components use custom `ViewModifier` and `ButtonStyle`
- Hero transition between workout list and workout detail

### What You Are Proving
You can build a production-quality UI that is adaptive, animated, and reusable — with no business logic in any View.

---

---

# Phase 3 — App Architecture & Lifecycle

> **Goal:** Understand how a real iOS app is structured from cold launch to termination, and how to architect code that scales with a team.

**Exit Criteria:**
- You can trace the complete iOS app lifecycle from launch to background
- You can architect a feature using MVVM with full separation of concerns
- You can implement dependency injection without a third-party framework
- You understand what TCA is and when you would choose it over MVVM

---

## 3.1 — iOS App Lifecycle

### Task 3.1.1 — Lifecycle Mapping
Without writing any UI, create a document mapping every lifecycle event for a SwiftUI app: cold launch, foreground, background, scene disconnect, and termination. For each event, write what Gym Buddy should do (e.g., "on background: flush pending SwiftData writes").

**Reference:** [App and Scene Lifecycle — Apple](https://developer.apple.com/documentation/swiftui/app-organization)

---

### Task 3.1.2 — Background Task Registration
Implement a `BGAppRefreshTask` that simulates syncing the user's workout log when the app is backgrounded. Log each lifecycle event using `Logger` with appropriate levels.

**Reference:** [BackgroundTasks — Apple Docs](https://developer.apple.com/documentation/backgroundtasks)

---

## 3.2 — MVVM Architecture

### Task 3.2.1 — ViewModel Extraction
Take your Phase 2 Nutrition screen. Extract all business logic into a `NutritionViewModel: ObservableObject`. The view should contain zero business logic — only layout code and calls to the ViewModel. Write a list of rules you followed to decide what belongs in the View vs the ViewModel.

**Reference:** [Managing Model Data — Apple](https://developer.apple.com/documentation/swiftui/managing-model-data-in-your-app)

---

### Task 3.2.2 — ViewModel Unit Testability
Refactor `NutritionViewModel` so it depends on a `MealRepositoryProtocol` injected via initializer — not instantiated internally. Prove it is testable by writing two unit tests: one for adding a meal, one for deleting a meal, using a mock repository.

---

## 3.3 — Dependency Injection

### Task 3.3.1 — Manual DI Container
Build a `DependencyContainer` struct that holds all app-level dependencies (repositories, services). Inject it at the app root via `@EnvironmentObject`. Every ViewModel receives its dependencies through its initializer — no singleton access inside ViewModels.

---

### Task 3.3.2 — Factory Library Integration
Replace your manual container with [Factory](https://github.com/hmlongco/Factory). Register all dependencies in a `Container` extension. Compare the ergonomics and explain in writing when manual DI is sufficient vs when a library adds value.

**Reference:** [Factory Documentation](https://hmlongco.github.io/Factory/documentation/factory/)

---

## 3.4 — The Composable Architecture (Study)

### Task 3.4.1 — TCA Mental Model
Do not implement TCA yet. Read the [TCA README](https://github.com/pointfreeco/swift-composable-architecture) and the first two tutorials. Then write a document answering: What problem does TCA solve that MVVM does not? When would you choose TCA for Gym Buddy? What is the cost of adopting it?

**Reference:** [TCA Documentation](https://pointfreeco.github.io/swift-composable-architecture/main/documentation/composablearchitecture/)

---

## 3.5 — Deep Linking & Routing

### Task 3.5.1 — URL Scheme Navigation
Register a custom URL scheme `gymbuddy://`. Implement handlers for: `gymbuddy://nutrition/log`, `gymbuddy://workout/start`, and `gymbuddy://progress`. Each URL should navigate the app to the correct screen from any state.

**Reference:** [onOpenURL — Apple Docs](https://developer.apple.com/documentation/swiftui/view/onopenurl(perform:))

---

## Phase 3 — Mini Project: Gym Buddy Architecture Refactor

**Refactor the Phase 2 UI to use production-grade architecture.**

### Requirements
- Every screen has a dedicated ViewModel with zero business logic in Views
- All ViewModels receive dependencies via initializer injection
- A `DependencyContainer` is injected at the root using Factory
- Deep link handling for all four main screens
- Background task registered for workout sync
- Full lifecycle logging with `Logger`
- Every ViewModel has at least two unit tests

### What You Are Proving
Your code is structured the way a team would structure it. Another engineer could own any single ViewModel without touching the rest of the app.

---

---

# Phase 4 — Async, Networking & Data

> **Goal:** Build a real data layer. Fetch from APIs, persist locally, handle failures gracefully, and serve cached data when the network is unavailable.

**Exit Criteria:**
- You can use `async/await`, `TaskGroup`, and `AsyncStream` correctly
- You can model an offline-first data layer
- You understand SwiftData's schema, migrations, and query system
- You can integrate Alamofire and explain when it adds value over `URLSession`

---

## 4.1 — Swift Concurrency

### Task 4.1.1 — `async/await` Network Layer
Build a `NutritionAPIClient` using `URLSession` and `async/await` that fetches food data from the [Open Food Facts API](https://world.openfoodfacts.org/data). Decode the response into your `Food` model. Handle HTTP errors, decoding errors, and network unavailability with typed errors.

**Reference:** [URLSession — Apple Docs](https://developer.apple.com/documentation/foundation/urlsession)

---

### Task 4.1.2 — `TaskGroup` for Concurrent Requests
On the Dashboard, you need to load: today's meals, today's workout, and the user's weight for the chart — simultaneously. Use `TaskGroup` to fire all three requests concurrently and merge results when all complete.

**Reference:** [TaskGroup — Swift Concurrency Docs](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/concurrency/#Task-Groups)

---

### Task 4.1.3 — `AsyncStream` for Live Data
Build a `RestTimerService` that publishes countdown ticks using `AsyncStream<Int>`. A view should subscribe to this stream and update a countdown display. Cancel the stream when the view disappears.

**Reference:** [AsyncStream — Apple Docs](https://developer.apple.com/documentation/swift/asyncstream)

---

## 4.2 — Alamofire Integration

### Task 4.2.1 — Replace URLSession with Alamofire
Rewrite `NutritionAPIClient` using Alamofire. Add a `RequestInterceptor` that automatically retries failed requests up to 3 times with exponential backoff. Explain in a comment what Alamofire is doing that would require significant boilerplate with raw `URLSession`.

**Reference:** [Alamofire Documentation](https://alamofire.github.io/Alamofire/)

---

## 4.3 — SwiftData Persistence

### Task 4.3.1 — SwiftData Schema
Convert your Phase 1 data models to SwiftData `@Model` classes. Define relationships between `WorkoutSession` and `WorkoutSet`, and between `Meal` and `Macros`. Write a `ModelContainer` configuration that supports both persistent and in-memory storage (the latter for tests).

**Reference:** [SwiftData — Apple Docs](https://developer.apple.com/documentation/swiftdata)

---

### Task 4.3.2 — Queries and Filtering
Using `@Query`, build a nutrition log that filters meals by date, sorts by `loggedAt`, and updates automatically when the data changes. Implement a search that filters by meal name.

**Reference:** [Query — Apple SwiftData Docs](https://developer.apple.com/documentation/swiftdata/query)

---

### Task 4.3.3 — Schema Migrations
Add a `notes: String?` field to `Meal` using a `SchemaMigrationPlan`. Write the migration so existing data is preserved. Document what happens if you add a required (non-optional) field without a migration.

**Reference:** [Migrating Your Data — Apple](https://developer.apple.com/documentation/swiftdata/preserving-your-app-s-model-data-across-launches)

---

## 4.4 — Offline-First Architecture

### Task 4.4.1 — Cache-First Strategy
Build a `FoodSearchService` that: first returns cached results from SwiftData, simultaneously fetches from the API in the background, and updates the cache (and therefore the UI) when the remote response arrives. On network failure, serve the cache silently.

**Reference:** [Combine — Apple Docs](https://developer.apple.com/documentation/combine) *(for reactive cache invalidation)*

---

## Phase 4 — Mini Project: Gym Buddy Live Data

**Replace all hardcoded data with real network and persistence layers.**

### Requirements
- Food search hits Open Food Facts API via Alamofire with retry logic
- Exercise database fetched from Wger API
- All meals, workouts, and hydration entries persisted in SwiftData
- Dashboard loads concurrently using `TaskGroup`
- Rest timer uses `AsyncStream`
- Offline mode: app is fully functional with cached data when network is unavailable
- Schema migration plan in place for future model changes
- Kingfisher used for any remote food images

### What You Are Proving
Your app works end-to-end with real data. It handles failures gracefully. A user could lose their internet connection mid-session and not notice.

---

---

# Phase 5 — Platform APIs

> **Goal:** Use iOS as a platform, not just a runtime. Integrate the device capabilities that make an app feel native.

**Exit Criteria:**
- You can request, handle, and recover from permission denials for any system resource
- You can schedule and handle local notifications with actions
- You have integrated HealthKit for reading and writing health data
- You have built a working WidgetKit widget

---

## 5.1 — HealthKit Integration

### Task 5.1.1 — Read Steps and Active Energy
Request HealthKit authorization for step count and active energy. Display today's step count on the Dashboard. Handle the case where the user denies permission — show a degraded state, not a crash.

**Reference:** [HealthKit — Apple Docs](https://developer.apple.com/documentation/healthkit)

---

### Task 5.1.2 — Write Workouts to Health App
After a workout is completed, write it as an `HKWorkout` to HealthKit. This makes Gym Buddy a first-class citizen in the Health app ecosystem.

**Reference:** [HKWorkout — Apple Docs](https://developer.apple.com/documentation/healthkit/hkworkout)

---

## 5.2 — Local Notifications

### Task 5.2.1 — Scheduled Meal Reminders
Using `UNUserNotificationCenter`, schedule daily notifications reminding the user to log their meals. Implement three separate notification schedules: breakfast, lunch, and dinner. Allow the user to configure the times in Settings.

**Reference:** [UNUserNotificationCenter — Apple Docs](https://developer.apple.com/documentation/usernotifications/unusernotificationcenter)

---

### Task 5.2.2 — Notification Actions
Add actionable buttons to the workout reminder notification: "Start Workout" (deep links to the workout screen) and "Snooze 30 Minutes" (reschedules the notification). Handle both actions in the app delegate.

**Reference:** [UNNotificationAction — Apple Docs](https://developer.apple.com/documentation/usernotifications/unnotificationaction)

---

## 5.3 — Camera & Photo Library

### Task 5.3.1 — Barcode Scanner for Food Logging
Implement a barcode scanner using `AVCaptureSession` that scans a food product's EAN barcode and queries Open Food Facts with the result. Wrap the camera view in a `UIViewRepresentable` since SwiftUI has no native camera API.

**Reference:** [AVFoundation — Apple Docs](https://developer.apple.com/documentation/avfoundation)

---

## 5.4 — WidgetKit

### Task 5.4.1 — Calorie Summary Widget
Build a home screen widget using WidgetKit that shows: calories consumed today, calories remaining, and a mini macro bar. The widget must read from a shared `AppGroup` container so it accesses the same SwiftData store as the main app.

**Reference:** [WidgetKit — Apple Docs](https://developer.apple.com/documentation/widgetkit)

---

### Task 5.4.2 — Lock Screen Widget
Build a lock screen widget (circular) showing today's calorie progress as a percentage.

**Reference:** [Creating Lock Screen Widgets — Apple](https://developer.apple.com/documentation/widgetkit/creating-lock-screen-widgets-and-watch-complications)

---

## 5.5 — Sign in with Apple

### Task 5.5.1 — Authentication Flow
Implement Sign in with Apple using `ASAuthorizationController`. Store the user credential securely in Keychain. Handle the cases: first sign-in, returning user, and revoked credentials.

**Reference:** [Sign in with Apple — Apple Docs](https://developer.apple.com/documentation/authenticationservices/implementing-user-authentication-with-sign-in-with-apple)

---

## Phase 5 — Mini Project: Gym Buddy Platform Integration

**Wire Gym Buddy into the iOS platform ecosystem.**

### Requirements
- HealthKit: reads steps, writes completed workouts
- Barcode scanner in the food logging flow
- Three configurable meal reminder notifications with actions
- Home screen widget (calorie summary) and lock screen widget (progress ring)
- Sign in with Apple for account creation
- All permissions handled gracefully — denied state never crashes the app
- App Group configured for widget data sharing

### What You Are Proving
Gym Buddy is a platform-native application. It feels like it belongs on iOS, not like a web app wrapped in a shell.

---

---

# Phase 6 — Quality & Debugging

> **Goal:** Ship with confidence. Write tests that catch regressions, use Instruments to find real performance problems, and make the app accessible to everyone.

**Exit Criteria:**
- You can write unit tests for any ViewModel in isolation
- You can write a UI test that executes a complete user flow
- You have profiled the app and fixed at least one real memory or performance issue
- Your app passes a basic VoiceOver audit

---

## 6.1 — Unit Testing with XCTest

### Task 6.1.1 — ViewModel Test Suite
Write a complete unit test suite for `NutritionViewModel`. Cover: adding a meal, deleting a meal, calorie calculation, validation logic (empty name, zero calories), and API failure handling. Use mock repositories injected via the initializer.

**Reference:** [XCTest — Apple Docs](https://developer.apple.com/documentation/xctest)

---

### Task 6.1.2 — BDD Tests with Quick + Nimble
Rewrite three of your most complex tests using [Quick + Nimble](https://github.com/Quick/Quick). Compare readability. Write a comment explaining when BDD-style tests add clarity vs when they add noise.

---

### Task 6.1.3 — Snapshot Testing
Using [SnapshotTesting](https://github.com/pointfreeco/swift-snapshot-testing), capture reference snapshots of: the Dashboard view, the nutrition log, and the macro breakdown chart. Set up CI-friendly snapshot comparison so regressions are caught before they ship.

---

## 6.2 — UI Testing

### Task 6.2.1 — End-to-End Workout Flow
Write a `XCUITest` that: launches the app, navigates to Workouts, starts a new workout, adds three exercises with sets, completes the workout, and verifies the summary screen shows the correct duration.

**Reference:** [XCUITest — Apple Docs](https://developer.apple.com/documentation/xctest/xcuiapplication)

---

## 6.3 — Instruments & Performance

### Task 6.3.1 — Time Profiler Audit
Profile the app launch using the Time Profiler instrument. Identify the three most expensive operations on the main thread during launch. Propose (and implement) at least one optimization.

**Reference:** [Instruments — Apple](https://developer.apple.com/tutorials/data/downloads/Instruments.pdf)

---

### Task 6.3.2 — Memory Leak Hunt
Run the Leaks instrument during a full user session (log meal, start workout, view charts, background app). Find and fix any retain cycles. Common location: closures capturing `self` strongly in ViewModels.

---

## 6.4 — Accessibility

### Task 6.4.1 — VoiceOver Audit
Enable VoiceOver on your simulator. Navigate the entire app using only VoiceOver gestures. Document every element that is unlabelled, confusing, or inaccessible. Fix them using `accessibilityLabel`, `accessibilityHint`, and `accessibilityValue`.

**Reference:** [Accessibility — Apple Docs](https://developer.apple.com/documentation/accessibility)

---

### Task 6.4.2 — Dynamic Type Support
Test the app with the largest Dynamic Type setting enabled. Fix any layouts that break, truncate unexpectedly, or become unreadable.

**Reference:** [Dynamic Type — Apple HIG](https://developer.apple.com/design/human-interface-guidelines/typography)

---

## 6.5 — Production Monitoring

### Task 6.5.1 — Firebase Crashlytics Integration
Integrate [Firebase Crashlytics](https://firebase.google.com/docs/crashlytics/get-started?platform=ios). Force a non-fatal error and a crash in a development build. Verify both appear in the Firebase console. Add custom keys to crash reports (e.g., current screen, user's calorie goal).

---

### Task 6.5.2 — MetricKit Diagnostics
Implement `MXMetricManagerSubscriber` to receive `MXMetricPayload` reports. Log hang rate, launch time, and memory usage to your analytics system. Set a threshold: if average launch time exceeds 1 second, log a warning.

**Reference:** [MetricKit — Apple Docs](https://developer.apple.com/documentation/metrickit)

---

## Phase 6 — Mini Project: Gym Buddy Quality Pass

**Make Gym Buddy shippable.**

### Requirements
- 80%+ unit test coverage on all ViewModels
- At least one end-to-end UI test per major user flow
- Zero memory leaks reported by Instruments
- App launch time under 1 second on iPhone 12 (Instruments verified)
- Full VoiceOver navigation possible on all screens
- Dynamic Type: all text readable at accessibility sizes
- Firebase Crashlytics integrated and receiving test events
- Snapshot tests covering all four main screens

### What You Are Proving
You do not just write features. You ship quality.

---

---

# Phase 7 — Capstone Integration

> **Goal:** Bring everything together into a single, coherent, production-ready application. This is the phase where the app stops being a collection of features and becomes a product.

**Exit Criteria:**
- The app runs on iPhone and iPad with no layout issues
- All features are integrated and work together end-to-end
- The app is ready for TestFlight distribution

---

## 7.1 — Full Feature Integration

### Task 7.1.1 — Data Consistency Audit
With all features live, verify that data flows correctly end-to-end: a meal logged in Nutrition appears in the Dashboard calorie count, a completed workout updates HealthKit, and the widget reflects today's data within 15 minutes.

---

### Task 7.1.2 — iPad Layout Completion
Conduct a full iPad layout audit. Every screen must use `NavigationSplitView` correctly. No full-screen modals on iPad that should be popovers. No iPhone-only layouts breaking on 12.9" screens.

**Reference:** [Designing for iPadOS — Apple HIG](https://developer.apple.com/design/human-interface-guidelines/designing-for-ipados)

---

### Task 7.1.3 — App Store Preparation
Configure: app icon (all sizes), launch screen, App Store screenshots (iPhone and iPad), privacy manifest (`PrivacyInfo.xcprivacy`), and required capability declarations. Write the App Store description and keywords.

**Reference:** [App Store Connect Help — Apple](https://developer.apple.com/help/app-store-connect/)

---

### Task 7.1.4 — TestFlight Distribution
Archive the app, upload to App Store Connect, and distribute to at least one external tester via TestFlight. Resolve any binary rejection issues from automated App Store review.

**Reference:** [TestFlight — Apple Docs](https://developer.apple.com/testflight/)

---

## Phase 7 — Mini Project: Gym Buddy Beta

**Ship Gym Buddy to TestFlight.**

### Requirements
- All Phase 0–6 features integrated and functional
- Zero crashes on launch for any TestFlight tester
- App Store assets complete: icon, screenshots, description
- Privacy manifest declares all data usage
- Passes automated App Store review checks (no manual review required at this stage)
- At least one real user has installed and used it

### What You Are Proving
You can take an app from idea to users' hands without being blocked at any step of the process.

---

---

# Phase 8 — Production Application

> **Goal:** Build Gym Buddy as a real product. No hand-holding. No guided tasks. You architect, build, and ship. The mentorship protocol shifts from guided learning to senior engineer PR review.

**This phase has no task list. You drive.**

---

## The Rules of Phase 8

- You propose every architectural decision before implementing it
- Every feature branch ends with a code review using the full review protocol
- No feature ships without tests
- No "I'll refactor this later" — production quality from day one
- You own the product roadmap: what gets built next is your call

---

## Phase 8 Milestones

### Milestone 1 — Architecture Review (No Code Yet)
Present your full architecture:
- Data model diagram with all SwiftData relationships
- Navigation map showing every screen and transition
- Dependency graph showing how ViewModels relate to repositories and services
- Decision log: why MVVM over TCA, why SwiftData over Core Data, why Alamofire over URLSession

I review. You may not write a line of production code until the architecture is approved.

---

### Milestone 2 — Data Layer
- Complete SwiftData schema with all relationships and migrations planned
- All repositories with protocol abstractions
- Full unit test suite for all repositories (in-memory container)
- Offline-first service layer complete

---

### Milestone 3 — Core Feature Loop
The minimum viable Gym Buddy: log a meal, log a workout, see the dashboard update. Everything else is secondary.
- MVVM enforced: zero business logic in any View
- Navigation working on both iPhone and iPad
- No placeholder or hardcoded data anywhere

---

### Milestone 4 — Platform Integration
- HealthKit reading and writing
- Notifications with actions
- Barcode scanner
- Home screen and lock screen widgets
- Sign in with Apple

All permissions handled gracefully. No feature assumes it was granted.

---

### Milestone 5 — Polish & Edge Cases
The features that separate an app from a demo:
- Empty states for every list (first launch, no data, search no results)
- Error states with retry actions
- Loading states with appropriate skeletons or indicators
- Accessibility: full VoiceOver support, Dynamic Type
- Onboarding flow for new users (goal setting, unit preference, notification opt-in)

---

### Milestone 6 — Production Delivery
- Instruments: launch time, memory, hang rate — all within acceptable thresholds
- Firebase Crashlytics and Analytics live
- App Store assets finalized
- App Store submission — target approval
- Post-launch: monitor Crashlytics for day-one issues, respond within 24 hours

---

## What Phase 8 Produces

A live, shipped iOS application that you built to production standard. It is the answer to every "what have you built?" question in any iOS engineering interview.

---

---

## References — Master List

| Resource | URL |
|---|---|
| Swift Language Guide | https://docs.swift.org/swift-book/documentation/the-swift-programming-language/ |
| SwiftUI Documentation | https://developer.apple.com/documentation/swiftui |
| SwiftData | https://developer.apple.com/documentation/swiftdata |
| Swift Concurrency | https://docs.swift.org/swift-book/documentation/the-swift-programming-language/concurrency/ |
| URLSession | https://developer.apple.com/documentation/foundation/urlsession |
| Combine | https://developer.apple.com/documentation/combine |
| HealthKit | https://developer.apple.com/documentation/healthkit |
| WidgetKit | https://developer.apple.com/documentation/widgetkit |
| UserNotifications | https://developer.apple.com/documentation/usernotifications |
| XCTest | https://developer.apple.com/documentation/xctest |
| MetricKit | https://developer.apple.com/documentation/metrickit |
| Swift Charts | https://developer.apple.com/documentation/charts |
| Instruments | https://developer.apple.com/tutorials/data/downloads/Instruments.pdf |
| Accessibility | https://developer.apple.com/documentation/accessibility |
| Apple HIG — iPadOS | https://developer.apple.com/design/human-interface-guidelines/designing-for-ipados |
| App Store Connect | https://developer.apple.com/help/app-store-connect/ |
| TestFlight | https://developer.apple.com/testflight/ |
| Alamofire | https://alamofire.github.io/Alamofire/ |
| Kingfisher | https://github.com/onevcat/Kingfisher |
| Factory DI | https://hmlongco.github.io/Factory/documentation/factory/ |
| TCA | https://pointfreeco.github.io/swift-composable-architecture/main/documentation/composablearchitecture/ |
| Quick + Nimble | https://github.com/Quick/Quick |
| SnapshotTesting | https://github.com/pointfreeco/swift-snapshot-testing |
| Firebase Crashlytics | https://firebase.google.com/docs/crashlytics |
| Open Food Facts API | https://world.openfoodfacts.org/data |
| Wger Exercise API | https://wger.de/api/v2/ |