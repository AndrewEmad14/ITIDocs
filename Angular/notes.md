# Intro

Angular is a JavaScript framework that allows you to create single-page
applications.it is developed by google
A component-based framework for building scalable web applications
A collection of well-integrated libraries that cover a wide variety of
features, including routing, forms management, client-server
communication, and more

# SPA

Single Page Applications (SPAs) all the HTML generation happens in
the browser. The server only returns one basic HTML page for all
incoming requests (no matter the URL).
But that single HTML page contains a lot of JavaScript code (typically
outsourced into separate files) which is responsible for changing the
HTML code (technically, the DOM).

# angular compiler

  It handles compilation automatically: ng serve uses the Angular Compiler (ngc), which is built on top of tsc. It automatically converts your TypeScript into JavaScript every time you save a file.
  In-Memory only: Unlike running tsc . manually, which generates physical .js files in your folders, ng serve compiles your code in-memory. It serves these virtual files to your browser so your project folder
  stays clean.

# Setting up angular

first you will need to install npm
npm install -g npm //global directory

  npm install -g @angular/cli //installs angular globally

  ng new your-app-name
        --prefix someting , adds prefix to every generated component
        note : it will create your root dir , Dont make the root folder

  ng serve //runs in the browser

  ng serve -o.     //live updates

# cloning form a repo

normally by default the .gitignore ignore node modules but keeps what needs to be downloaded in package.json
run: npm install // installs the packagaes in package.json

# installing bootstrap

npm install bootstrap

in angular.json

  "styles": [
  "node_modules/bootstrap/dist/css/bootstrap.min.css",
  "src/styles.css"
  ],"scripts": [
    "node_modules/bootstrap/dist/js/bootstrap.bundle.min.js"
  ]   // for interactive components

# folder structure

### package.json /pacakge-lock.json

  where the dependencies of the application are defined

##### difference between the two

  package.json are eidtable and you can modify the versions as much as you like of the packages

  package-lock.json are machine generated and lock the versions so that everyone that works on the repo is forced to work with those versions they are not meant to be editied

##### popular packages

  • rxjs, a really cool library for reactive programming. We have a dedicated chapter on this topic
    and about RxJS in particular.
  • zone.js, doing the heavy lifting for detecting the changes (we’ll dive into this later also).

### tsconfig.json

  linter for type script

### angular.json

  configuration for angular cli
  NOTE : you will find you can edit styles and scripts to match external libaries like bootstrap

## src/app

  the main app comoponet

# @Component

a decorator that tell angular that this is a component

it expects a configuration object

## selector property

  it will tell Angular what to look
  for in our HTML pages. Every time Angular finds an element in our HTML which matches the
  selector of the component, it will create an instance of the component, and replace the content of
  the element by the template of the component.

### naming conventions

  prefix-component

## standalone : true

  this is the default since angular v19 , this means that the component doesnt need to be declared in a module in order to be usable

## imports:[]

The property imports: [] is not always strictly required. Its goal is to tell Angular which other
components, pipes and directives can be used inside the template of our component.

## CommonModule

    Most of the components that we create use pipes and directives provided by Angular. These very commonly
    used pipes and directives are declared in an Angular module named CommonModule

# index.html

The CLI created an index.html file for us, which is the single page of our application. You might wonder how it could possibly work, since it doesn’t contain any script element.
When you run ng serve, the CLI calls the TypeScript compiler. The compiler outputs JavaScript files.
The CLI then bundles them and adds the necessary script elements to the index.html file (using Vite
behind the scenes a modern build tool and development server for web projects).

# putting a component inside a component

-first you need to create your custom component
ng generate component your-component-name

-next you should import your-component-name.ts in the app.ts file
AND put it in import: [] attribute

-finally you can use your new tag as much as you like

# interpolation

`<h2>{{ numberOfUsers }} users</h2>`
// displaying a variable inside the typescript to the html
//typing errors of the variables gets detected by the compiler

# signals

A signal is a box which always contains a value. You can get the value inside the box by reading the
signal. And when the signal is writable, you can put another value inside the box by setting or
updating the signal. The value inside the box can be anything: a number, a string, an object, an
array, or even null or undefined.

// this signal can contain a number, and initially contains 42
const count = signal(42);
// this signal can contain a PonyModel, and initially contains Rainbow Dash
const rainbowDash = signal<PonyModel>({
name: 'Rainbow Dash',
color: 'blue'
});
// this signal can contain a PonyModel, and initially contains Pinkie Pie
const pinkiePie: WritableSignal<PonyModel> = signal({
name: 'Pinkie Pie',
color: 'red'
});
// this signal can contain a PonyModel or undefined, and initially contains undefined
const unknownPony = signal<PonyModel | undefined>(undefined);

### A signal is both an object and a function. To get the value contained in the signal

// let's read the value of the rainbowDash signal
const value: PonyModel = rainbowDash();
// and print it in the console as JSON
console.log(JSON.stringify(value))

### To change the value of the signal (and thus notify Angular that this signal has a new value), you call its set() method:

rainbowDash.set({
name: 'Rainbow Dash',
color: 'yellow'
});

### Updateing signal properties

##### DONT DO THIS!!!!

    / ❌ Don't do this!
    rainbowDash().color = 'yellow';
    // ❌ Don't do this!
    const pony = rainbowDash();
    pony.color = 'yellow';
    rainbowDash.set(pony);

// angular will not consider the value changed!
// treat signals value as if they were imutable
rainbowDash.update(pony => ({ ...pony, color: 'yellow' })); // overrides color: with yellow

# signals and brute force change detection

//here when the number of user ever changes for any specfic reason the page will be automatically updated
//but that is using brute force change detection which comes at the cost of preformance and comes with many draw back
@Component({
selector: 'ns-root',
template: ' `<h1>PonyRacer</h1>`
` <h2>{{ numberOfUsers }} users</h2>`
'
})
export class App {
// we use protected here to be able to use it inside the template
protected readonly numberOfUsers = 146;  
 }
// the better way is to use signals
@Component({
selector: 'ns-root',
template: '
`<h1>PonyRacer</h1>`
`<h2>{{ numberOfUsers() }} users</h2>`
'
})
export class App {
protected readonly numberOfUsers = signal(146);
}

# Data binding binding

### String interpolation

    Allows you to incorporate dynamic string values into your HTML
    templates
    used like this {{expression}}

### property binding

the [property] allows you to acces a property that is form javascript like textContent src style all that fun stuff

   <p>{{user().name}}</p> === <p>[textContent] = "user().name"</p>
  the advantage it gives you is that it can be dynamically updated according to user input 
  
  ##### Examples:
    [textContent] = "your-text"
    [src]= "your-image"
    [style] = "your-inline-style"
  ###### style property
  [style.color] = "your-color-for-example"
  [style.width.px]="numberExpression" //for specfic units
  static styles and dynamic styles are merged automatically 
  **Examples:**

  @Component({
  selector: 'ns-test1',
  template: '<div style="background-color: white" [style]="dynamicStyles()">
  Hello</div>'
  })
  class StyleBinding1 {
  protected readonly dynamicStyles = signal('margin-top: 1rem; color: black');
  }
  @Component({
  selector: 'ns-test2',
  template: '<div style="background-color: white" [style]="dynamicStyles()">
  Hello</div>'
  })
  class StyleBinding2 {
  protected readonly dynamicStyles = signal({
  'margin-top': '1rem',
  color: 'black'
  });
  }
  @Component({
  selector: 'ns-test3',
  template: '<div style="background-color: white" [style.margin-top]="margin()"
  [style.color]="color()">Hello</div>'
  })
  class StyleBinding3 {
  protected readonly margin = signal('1rem');
  protected readonly color = signal('black');
  }
  @Component({
  selector: 'ns-test4',
  template: '<div style="background-color: white" [style.margin-top.rem]="margin()"
  [style.color]="color()">Hello</div>'
  })
  class StyleBinding4 {
  protected readonly margin = signal(1);
  protected readonly color = signal('black');
  }

###### Class property

[class]=`array of style classes
        a single string of classes
        an object where each class is an attributed with a value of true and false
[class.classname]="isClassName()";

**Examples:**

  @Component({
  selector: 'ns-test1',
  template: '<div class="card" [class]="dynamicClasses()">Hello</div>'
  })
  class ClassBinding1 {
  protected readonly dynamicClasses = signal(['highlighted', 'big']);
  }
  @Component({
  selector: 'ns-test2',
  template: '<div class="card" [class]="dynamicClasses()">Hello</div>'
  })
  class ClassBinding2 {
  protected readonly dynamicClasses = signal('highlighted big');
  }
  @Component({
  selector: 'ns-test3',
  template: '<div class="card" [class]="dynamicClasses()">Hello</div>'
  })
  class ClassBinding3 {
  protected readonly dynamicClasses = signal({
  highlighted: true,
  big: true,
  faded: false
  });
  }
  @Component({
  selector: 'ns-test4',
  template:
  '<div class="card" [class.highlighted]="isHighlighted()" [class.big]="isBig()"
  [class.faded]="isFaded()">Hello</div>'
  })

  class ClassBinding4 {
  protected readonly isHighlighted = signal(true);
  protected readonly isBig = signal(true);
  protected readonly isFaded = signal(false);
  }

### Event Binding

  Event binding allows you to listen for and respond to user actions such as

keystrokes, mouse movements, clicks, and touches.
Example : <button (click)="onSave()">Save</button>
you can access the event in the method called! You just have to pass `$event` to your method:
` <div (click)="onButtonClick($event)">`
`<button>Click me!</button>`
`</div>`
Then you can handle the event in your component class:

    onButtonClick(event: Event) {
    console.log(event);
    }

the event bubbles up by default you can cancel propgation or prevent default behavior

One cool feature is that you can also easily handle keyboard events with:
`<textarea (keydown.space)="onSpacePress()">Press space!</textarea>`

### Two way Binding


Two-way binding combines property binding with event binding for
example to two way binding [(ngModel)]
<input [(ngModel)]="username" placeholder="Enter name...">
Note : you need to import import { FormsModule } from '@angular/forms' for two way
binding in forms in app module to work

**Note**: you cant chain expressions for example:
//forbidden, as the expression is an assignment
//this will throw an error
<component [property]="user = 'Cédric'"></component>
it cannot also contain keywords like if or var

# local variables

Local variables are
variables that you can dynamically declare in your template using the # syntax.

**Example**
`<input type="text" #name>`
her name is a refernce to the input element i can then use it for multiple things like

**to access its value**

{{name.value}}

**send it as a a paramter when triggering an event**

`<button (click)="doSomething(myInput)">Click me</button>`

**use its built in functions**

`<button (click)="name.focus()">Focus the input</button>`

# running

when running the app it runs for src as a root folder , keep that it mind when using relative path

# assets

put the assets folder in the src folder
adjust angular.json to match your assets location
"assets": [
{
"glob": "**/*",
"input": "src/assets",
"output": "/assets/"
},
{
"glob": "favicon.ico",
"input": "src/",
"output": "/"
}
]
you can also put your stuff in public to access it easily

# Common UI Libaries

### Angular Material

https://material.angular.dev/

### Ng Bootstrap

https://ng-bootstrap.github.io/#/getting-started

### PrimeNG

https://primeng.org/installation

# Directives

Directives are classes that add additional behavior to elements in your Angular
applications.they dont have a view or to put it another way components are directives with a view.they also enrich HTML by letting you attach a custom behavior to existing HTML elements.you can attach several directives to a single component
there are two kind of Directives:

### Attribute

  you can genrerate yor custom directive using
  ng g d directive-name

**it will look something like this for example**
this is a very simple directive that does nothing but gets activated if the attribute doNothing is on an element:

  @Directive({
  selector: '[doNothing]'
  })
  export class DoNothing {
  constructor() {
  console.log('Do nothing directive');
  }
  }

  @Component({
  selector: 'ns-test',
  template: '<div doNothing>Click me</div>',
  imports: [DoNothing]
  })
  export class Test {}

### Structural

##### the old deprecated directives: ngif, ngfor, ngswitch
  ```html
    //ngif

    <div *ngIf="isLoggedIn">
      <p>Welcome back!</p>
    </div>

    <div *ngIf="!isLoggedIn">
      <p>Please log in</p>
    </div>

    //ngfor

    <ul>
      <li *ngFor="let item of items">
        {{ item.name }} - ${{ item.price }}
      </li>
    </ul>

    items = [
      { name: 'Apple', price: 1.50 },
      { name: 'Banana', price: 0.75 },
      { name: 'Orange', price: 2.00 }
    ];

    //ng switch

    <div [ngSwitch]="userRole">
    <div *ngSwitchCase="'admin'">
      <p>Admin Panel</p>
    </div>
    <div *ngSwitchCase="'user'">
      <p>User Dashboard</p>
    </div>
    <div *ngSwitchDefault>
      <p>Guest View</p>
    </div>

  </div>
```
##### the new syntax @if @for @switch @let

**@if**

```html
<div>
  @if (races().length === 0) {
  <h2>No races to come</h2>
  } @else if (races().length === 1) {
  <h2>Only one race to come</h2>
  } @else {
  <h2>Some races to come</h2>
  }
</div>
```

note for signals :

Signals can sometimes contain a null or undefined value.
In the template, if we use race().name, we get a TypeScript error indicating that race() can be undefined.
// you have to enable strictNullChecks to get it

As a signal is a function, TypeScript has no way to know that the returned value is still not null inside the if.
In this case, it can be handy to use an alias to store the value of the signal.
@if (race(); as raceValue) {
`<h1>{{ raceValue.name }}</h1>`
}

**@for**
for is will loop and create the below html , if the races() is empty it will go to the @empty instruction

@for requires a track parameter his is mainly for performance reasons,
as it helps Angular to track the items in the collection and to update the DOM only when needed

```html
<div>
  <h2>Races</h2>
  <ul>
    @for (race of races(); track race.id) {
    <li>{{ race.name }}</li>
    }@empty{
    <li>no races</li>
    }
  </ul>
</div>
```

@for also exposes some variables that can be useful:

```html
• $index, the index of the current item, starting at zero • $first, a boolean
that is true if the element is the first of the collection • $last, a boolean
that is true if the element is the last of the collection • $even, a boolean
that is true if the element has an even index • $odd, a boolean that is true if
the element has an odd index
```

**Example**

```html
<ul>
  @for (race of races(); track race.id; let isEven = $even) {
  <li [class.grey]="isEven">{{ race.name }}</li>
  }
</ul>
```

**@switch**

```html
<div>
  @switch (races().length) { @case (0) {
  <h2>No races to come</h2>
  } @case (1) {
  <h2>Only one race to come</h2>
  } @default {
  <h2>Some races to come</h2>
  } }
</div>
```

##### if you have old structural directives there is a command by angular to automatically migrate to the new one

ng g @angular/core:control-flow
ng generate @angular/core:ngclass-to-class
ng generate @angular/core:ngstyle-to-style

**@let**
define a variable in the template, using the @let instruction, without having to declare it in the
component class.

```html
@let countPlusTwo = count() + 2;
<p>{{ countPlusTwo }}</p>
```

# sharing data between components

important note : In Angular, data flows into a component via properties, and flows out of a component via events.

## old way

#### Input

##### child component

  import { Component, Input } from '@angular/core';

  @Component({
    selector: 'app-child',
    template: `<p>{{ message }}</p>`
  })
  export class ChildComponent {
    @Input() message: string = '';
  }

##### parent component

  import { Component } from '@angular/core';
  import { Child } from './child/child'; // dont forget to import the child in
                                            the parent

  @Component({
    selector: 'app-parent',
    template: `<app-child [message]="parentMessage"></app-child>`,
    imports:[Child]
  })
  export class ParentComponent {
    parentMessage = 'Hello from Parent!';
  }

#### output

##### child component

  import { Component, Output, EventEmitter } from '@angular/core';

  @Component({
    selector: 'app-child',
    template: `<button (click)="sendMessage()">Click Me</button>`
  })
  export class ChildComponent {
    @Output() messageEvent = new EventEmitter<string>();

    sendMessage() {
      this.messageEvent.emit('Hello from Child!');
    }
  }

##### parent component

  import { Component } from '@angular/core';

  @Component({
    selector: 'app-parent',
    template: `
      <app-child (messageEvent)="handleMessage($event)"></app-child>
      <p>{{ receivedMessage }}</p>
    `
  })
  export class ParentComponent {
    receivedMessage = '';

    handleMessage(message: string) {
      this.receivedMessage = message;
    }
  }

## new way

#### Input

##### child component

  import { Component, input } from '@angular/core';
  @Component({
    selector: 'app-child',
    template: `<p>{{ message() }}</p>`
  })
  export class ChildComponent {
    message = input<string>('default value');
  }

##### parent component

  import { Component } from '@angular/core';

  @Component({
    selector: 'app-parent',
    template: `<app-child [message]="parentMessage"></app-child>`
  })
  export class ParentComponent {
    parentMessage = 'Hello from Parent!';
  }

### output

##### child component

  import { Component, output } from '@angular/core';
  @Component({
    selector: 'app-child',
    template: `<button (click)="sendMessage()">Click Me</button>`
  })
  export class ChildComponent {
    messageEvent = output<string>();

    sendMessage() {
      this.messageEvent.emit('Hello from Child!');
    }
  }

##### parent component

  import { Component } from '@angular/core';
  @Component({
    selector: 'app-parent',
    template: `
      <app-child (messageEvent)="handleMessage($event)"></app-child>
      <p>{{ receivedMessage }}</p>
    `
  })
  export class ParentComponent {
    receivedMessage = '';

    handleMessage(message: string) {
      this.receivedMessage = message;
    }
  }

# Component life cycle (HOOKS)

Components and directives have a lifecycle. When Angular must display a component, it starts by
constructing it and thus calls the component class constructor.

| Hook                  | Purpose                   |
| --------------------- | ------------------------- |
| constructor           | Component instantiation   |
| ngOnChanges           | Input properties changed  |
| ngOnInit              | Component initialized     |
| ngDoCheck             | Custom change detection   |
| ngAfterContentInit    | Content projected         |
| ngAfterContentChecked | Projected content checked |
| ngAfterViewInit       | View initialized          |
| ngAfterViewChecked    | View checked              |
| ngOnDestroy           | Component destroyed       |

remeber to import what you choose to implement
also ngOnChanges need SimpleChanges passed as a parameter and imported

**One thing is very important to understand: inputs are passed after the componenthas been constructed. It’s thus forbidden to read inputs while the component is being constructed.**

###### Example

  export class Pony {
  readonly color = input.required<string>();
  constructor() {
  // ❌ Don't do this
  console.log(`My initial color is ${this.color()}`);
  }
  }

With the signal inputs, trying to do that will lead to an exception being thrown by the InputSignal.
With the legacy inputs, trying to do that will just give you the default value of the property, rather
than the one actually bound by the parent component.

**ngOnInit**

  export class Pony implements OnInit {
  readonly color = input.required<string>();
  ngOnInit() {
  // ✅ Do this
  console.log(`My initial color is ${this.color()}`);
  }
  }

**ngOnChanges**

  export class Pony implements OnChanges {
    readonly color = input.required<string>();
    ngOnChanges(changes: SimpleChanges<Pony>): void {
    const ponyChange = changes.color;
    if (ponyChange) {
    console.log(`Color changed from ${ponyChange.previousValue}`);
    console.log(`to ${ponyChange.currentValue}`);
    console.log(`Is it the first change? ${ponyChange.isFirstChange()}`);
  }
  // but you can also access the new value by reading the input
  console.log(`My new color is ${this.color()}`);
  }

**ngOnDestroy**

  The ngOnDestroy phase is designed to clean the component – for example, to cancel background
  tasks. Here, the Pony is logging "hello" every second when it is created. When the component is
  removed from the page, you want to stop the setInterval to avoid a memory leak:

  export class Pony implements OnDestroy {
  readonly color = input.required<string>();
  private readonly interval: number;
  101
  constructor() {
  this.interval = window.setInterval(() => console.log(`My color is ${this.color()}
  `), 1000);
  }
  ngOnDestroy(): void {
  window.clearInterval(this.interval);
  }
  }

  If you don’t do this, JavaScript will keep the instance of the component in memory, and it will log every second forever.

# events

events are objects that can be accessed when triggering an event
what inside the event depends on the kind of the event
for example a mouse event containts
target // the element that triggered the event
button // the button which the mouse clicked

# vanilla change detection

remeber in signals when we said that you shouldnt try to change the value but instead change the entire reference so that angular could detect the change here?

there is a similar case here ,to recreate what i had to go through:
1.you have an @input you wish to detect its changes
2.you will have to use ngonChanges() 3. update the values of the array or whichever datatype you chose

ngOnChanges only triggers when the reference of the @Input property changes

# side notes

  @Component({
  selector: 'ns-root',
  template: '<h1>PonyRacer</h1>'
  })
  export class App {
  // we use protected here to be able to use it inside the template
  protected readonly numberOfUsers = 146;
  }

# routers (to be revised more accurately)

### to setup routers:

  1.in app.routes.ts fill in your routes
      {path:'path-name',component:Component-name}
  2.in your main page put the tag <route-outlet></route-outlet>
    also import router outlet in the component you will use it in
    this will tell angular to fill this part when its navigated to
  3.in your nav bar for example or the place with the <a> tags place your path and import Router and RouterLink in you type script file

  `<a routerLink="/hi">Go to hi</a>`


  routerLinkActive="active" // hellps you specify which link is active

  //this helps in styling your links
  .navbar-brand.active, .btn.active {
      font-weight: bold;
      color: #17e898  !important;
  }
  { path: '**', component: PageNotFoundComponent } // this is a wild card like a 404 not found
                                                  // beware that the orders matters , put it at the very bottom

### dynamic routers steps

  1. in app.routes.ts fill in your new dynamic route
      {path:'path-name/:your-other-parm',component:Component-name}
  2. in your app.config.ts inside the providers
      provideRouter(routes,**withComponentInputBinding()**) angular does type conversion , this helps when your params isnt a string
  3. in the your link specify your prams
    [routerLink]="['/product-details',product.id]"
  4. declare an input signal by your param inside the link you wish to route to
    id = input.required<number>();

    **Note: the name of the input must match the parmeter route exactly**
