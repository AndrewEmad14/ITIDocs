Tight timeline. Let's make it count — no fluff, high-signal only.

At **Junior/Mid level** with **theory + system design**, they're testing whether you *understand Angular*, not just whether you've used it. Given 1–2 days, we need ruthless prioritization.

---

## Your Study Plan — 1–2 Days

I'm splitting this into **Tier 1 (must know cold)** and **Tier 2 (know well enough to discuss)**. Tier 3 exists but skip it given your timeline.

---

## 🔴 Tier 1 — Non-Negotiable (Day 1)

These will appear in almost every Angular interview at this level.

---

### 1. Component Architecture & Lifecycle Hooks
**What they ask:** *"Walk me through the component lifecycle"* / *"When would you use ngOnInit vs constructor?"*

The constructor is for dependency injection — it runs before Angular has set up bindings. `ngOnInit` is where your component logic starts because inputs are resolved by then.

Key hooks to know cold: `ngOnInit`, `ngOnChanges`, `ngOnDestroy`, `ngAfterViewInit`

📄 [Angular Lifecycle Hooks — Official Docs](https://angular.dev/guide/components/lifecycle)

---

### 2. Change Detection — This is where mid-level candidates separate
**What they ask:** *"What is Change Detection? What's the difference between Default and OnPush?"*

Think of it like Django's ORM query cycle — Angular's CD is the mechanism that decides *when* to re-render. `Default` checks everything on every event. `OnPush` only checks when an `@Input` reference changes or an Observable emits — this is the performance play.

📄 [Change Detection — Angular Docs](https://angular.dev/best-practices/skipping-subtrees)

---

### 3. Dependency Injection & Providers
**What they ask:** *"How does DI work in Angular? What's the difference between providedIn: 'root' vs component-level providers?"*

Angular's DI is a hierarchical injector tree — similar to how Django middleware wraps request handling in layers. `root` = singleton for the whole app. Component-level = new instance per component.

📄 [DI in Angular — Official Docs](https://angular.dev/guide/di)

---

### 4. RxJS & Observables — Expect this heavily
**What they ask:** *"What's the difference between Subject, BehaviorSubject, Observable?"* / *"When do you use switchMap vs mergeMap?"*

This is the #1 topic mid-level candidates get wrong. Know these cold:

| Concept | One-liner |
|---|---|
| `Observable` | Lazy stream — nothing runs until subscribed |
| `Subject` | Observable + Observer — multicasts to many |
| `BehaviorSubject` | Subject that replays the last value to new subscribers |
| `switchMap` | Cancels previous inner observable — use for HTTP search |
| `mergeMap` | Runs all inner observables concurrently |
| `takeUntil` | The standard pattern for unsubscribing on destroy |

📄 [RxJS Official Docs](https://rxjs.dev/guide/overview)
📄 [Angular + RxJS Patterns](https://angular.dev/guide/defer)

---

### 5. Routing — Guards & Lazy Loading
**What they ask:** *"How do you protect a route? What is lazy loading and why does it matter?"*

Guards (`CanActivate`, `CanDeactivate`) are Angular's middleware — exactly like Django middleware on a route. Lazy loading splits your bundle so modules load on demand. This is a system design talking point too.

📄 [Angular Router — Official Docs](https://angular.dev/guide/routing)

---

## 🟠 Tier 2 — Know Well Enough to Discuss (Day 2 Morning)

---

### 6. Modules vs Standalone Components
Angular 14+ introduced standalone components — no `NgModule` required. Know *why* this matters: modules added boilerplate; standalone components simplify the mental model and align with how React/Vue think.

📄 [Standalone Components](https://angular.dev/guide/components/importing)

---

### 7. Forms — Template-Driven vs Reactive
**The key distinction:** Template-driven is async and implicit (Angular manages the model). Reactive is synchronous and explicit — you control the `FormGroup` directly. For anything non-trivial, Reactive is the correct answer.

📄 [Reactive Forms](https://angular.dev/guide/forms/reactive-forms)

---

### 8. HTTP Client & Interceptors
Interceptors are the Angular equivalent of Django middleware — they wrap every HTTP request/response. Know how to attach auth headers and handle errors globally here.

📄 [HttpClient — Angular Docs](https://angular.dev/guide/http)

---

### 9. System Design Angle — What to Expect
At Junior/Mid with system design, they're not asking you to design Twitter. Expect:

- *"How would you structure a large Angular app?"* → Feature modules or standalone, shared module, core module pattern
- *"How would you handle state?"* → Services + BehaviorSubject for simple state; NgRx for complex (know the tradeoff, don't oversell NgRx)
- *"How would you optimize a slow Angular app?"* → OnPush, lazy loading, `trackBy` in `*ngFor`, async pipe to avoid manual subscriptions

📄 [Angular Style Guide](https://angular.dev/style-guide)

---

## How to Actually Study This in 1–2 Days

**Day 1:**
- Lifecycle hooks → DI → Change Detection → RxJS operators (in that order)
- For each: read the doc, then explain it out loud to yourself without looking

**Day 2 Morning:**
- Routing/Guards → Forms → Interceptors → System design talking points
- Practice answering *"explain X to a non-Angular dev"* — interviewers love this

**Day 2 Afternoon:**
- Do 2–3 mock questions cold. I can run you through them here if you want.

---

## Where Do You Want to Start?

Pick the topic that feels weakest and we'll drill it properly — concept first, then I'll hit you with interview-style questions.

Which one is it?