
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
    npm install -g npm          //global directory

    npm install -g @angular/cli //installs angular globally

    ng new your-app-name 
          --prefix someting , adds prefix to every generated component
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
  <h2>{{ numberOfUsers }} users</h2> // displaying a variable inside the typescript to the html
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
      template: '<h1>PonyRacer</h1>
        <h2>{{ numberOfUsers }} users</h2>
      '
      })
      export class App {
      // we use protected here to be able to use it inside the template
      protected readonly numberOfUsers = 146;  
      }
  // the better way is to use signals
    @Component({
    selector: 'ns-root',
    template: `
    <h1>PonyRacer</h1>
    <h2>{{ numberOfUsers() }} users</h2>
    `
    })
    export class App {
    protected readonly numberOfUsers = signal(146);
    }

# side notes
      @Component({
      selector: 'ns-root',
      template: '<h1>PonyRacer</h1>'
      })
      export class App {
      // we use protected here to be able to use it inside the template
      protected readonly numberOfUsers = 146;  
      }
