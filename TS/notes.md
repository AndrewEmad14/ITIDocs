# Breif intro
  inorder to use Typescript you have to either download the extension for vscode
  or by npm install -g typescript 

# Static type checking
  the typescript check for types and behaviors in COMPILE TIME instad of RUNTIME with javascript
  ### Examples
  ##### Js
    // Accessing the property 'toLowerCase'
    // on 'message' and then calling it
    message.toLowerCase();
    // Calling 'message'
    message();
   // message isnt a funciotn error in runtime
  ##### Ts
    const message = "hello!";
    message();
    //This expression is not callable.
    //Type 'String' has no call signatures. error in compiler time
  ## You can now catch typos in compile time!!!
    const announcement = "Hello World!";
 
    // How quickly can you spot the typos?
    announcement.toLocaleLowercase();
    announcement.toLocalLowerCase();
    
    // We probably meant to write this...
    announcement.toLocaleLowerCase();

# Type Tooling
  That means TypeScript can be leveraged for editing code too, and the core type-checker can provide error messages and code completion as you type in the editor.
# Typscript command
  ## tsc --init
    creates tsconfig.json
  ## npm init -y
    initliazes npm and automatically answer yes for all questions
  ## npm install
    install the npm modules from the package.json and creates a package-lock file
  ## node your-convert.js file
    to run the file
  ### tsc your-file.ts
  it outputs a your-file.js with the converted type checked code
  even if typescript found errors
  if you dont want to update the file if it found errors you can use:
  ### tsc --noEmitOnError your-file.ts
  there will be no update or output if there is a wrong type
# TypeScript Motto
  TypeScript’s core values: much of the time, you will know better than TypeScript.
  tsc --noEmitOnError hello.ts if you dont want the 
# Explicit types
  let x:string;
  x = 5 //error
  x= "hi" //works
# functions
   printPoint(msg:string /*params*/):number/*return type*/ {
    console.log("msg");
    return 1;
  }
  if lets say you want to return an array or a promise you have to specify the type of promise/array
  async function getFavoriteNumber(): Promise<number> {
  return 26;
  }
# Anonymous functions and contextual typing
  const names = ["Alice", "Bob", "Eve"];
 
  // Contextual typing for function - parameter s inferred to have type string
  names.forEach(function (s) {
    console.log(s.toUpperCase());
  });
  
  // Contextual typing also applies to arrow functions
  names.forEach((s) => {
    console.log(s.toUpperCase());
  });
# Type Inferance
 TypeScript knows the JavaScript language and will generate types for you in many cases. For example in creating a variable and assigning it to a particular value, TypeScript will use the value as its type.
## Ex:
 let helloWorld = "Hello World";
# Changing target ECMASCRIPT
  tsc --target es2015 // this works for one file command

  if you want to permenintely enforces a certain target
  npx tsc --init
  in the json file :
  target: "your-ecmaScript-version"
  tsc will generate the script according to the ecmma script version now
  NOTE: for some reason using tsc with the specifc file ignores the config

# other useful configs
  "sourceMap": true and "declarationMap": true enabled in your tsconfig.json.
  1. script.js.map (The Source Map)
  This is a "bridge" between your original TypeScript code and the generated JavaScript.

      Why it's there: Browsers and Node.js run the .js file, but if there’s an error, you want to see the line number in your .ts file.
      The benefit: It allows you to debug (set breakpoints) directly inside your TypeScript code within the VS Code Debugger or Chrome DevTools.

  2. script.d.ts.map (The Declaration Map)
  This is a bridge for your Declaration Files (.d.ts).

      Why it's there: You have "declaration": true on, which generates a file describing the "shape" of your code (classes, types, etc.) for other developers to use.
      The benefit: If someone (or you in a different project) uses your compiled code and clicks "Go to Definition" on a function, the .map file tells the editor to open the original .ts source file instead of the messy .d.ts file.

  Should you keep them?

      Development: Keep them! They make debugging a million times easier.
      Production: Usually, you exclude .map files from your final website/server to keep the file size smaller and your source code private.

  If they are cluttering your folder, you can set "outDir": "./dist" in your config to send all generated files to a separate folder.
  Do you want to know how to hide these files in your VS Code sidebar so they don't distract you?

# Optionals
  In TypeScript, the ? modifier is strictly reserved for class properties, interface properties, or function parameters.

  they are used to make a parameter optional , meaning it has the posibility to be null or not

  function printName(obj: { first: string; last?: string }) {
    //Error - might crash if 'obj.last' wasn't provided!
    console.log(obj.last.toUpperCase());
    //'obj.last' is possibly 'undefined'.
    if (obj.last !== undefined) {
      // OK
      console.log(obj.last.toUpperCase());
    }
  
    // A safe alternative using modern JavaScript syntax:
    console.log(obj.last?.toUpperCase());
  }
 
  printName({ first: "Bob" });
  printName({ first: "Alice", last: "Alisson" });
  you can forcefully unwrap an optional using !
# interface
  if you want to explicitly enforce a type for an object you can make it in an interface

## Ex
  #### You can explicitly describe this object’s shape using an interface declaration:
  interface User{
    name: string;
    id: number;
  };
  #### You can then declare that a JavaScript object conforms to the shape of your new interface by using syntax like : 
  const user:User = {
    name: "haai",
    id: 1,
  };

#### same goes for classes

  class UserAccount {
  name: string;
  id: number;
 
  constructor(name: string, id: number) {
    this.name = name;
    this.id = id;
  }
}
when implementing an interface you have to redeclare the proprites and implement the functions
    interface Animal {
      name: string;
      makeSound(): void;
    }

    interface Moveable {
      speed: number;
      move(): void;
    }

    class Dog implements Animal, Moveable {
      name: string;
      speed: number;

      constructor(name: string, speed: number) {
        this.name = name;
        this.speed = speed;
      }

      makeSound() {
        console.log("Woof!");
      }

      move() {
        console.log(`Moving at ${this.speed} km/h`);
      }
    }

# DataTypes
  boolean, bigint, null, number, string, symbol, and undefined

  ## Unkonwn
    // A good example would be in wrapping a JSON parser. JSON
    // data can come in many different forms and the creator
    // of the json parsing function won't know the shape of the
    // data - the person calling that function should.

    const jsonParser = (jsonString: string) => JSON.parse(jsonString);

    const myAccount = jsonParser(`{ "name": "Dorothea" }`);

    myAccount.name;
    myAccount.email;

    // here jsonParser has the return type of any, so then does myAccount. It's possible to fix this with generics - but it's also possible to fix this with unknown.

    const jsonParserUnknown = (jsonString: string): unknown => JSON.parse(jsonString);

     //here i specefically say the type is unknown meaning i excpect the consumer of such a function to specify the type

    const myOtherAccount = jsonParserUnknown(`{ "name": "Samuel" }`);

    myOtherAccount.name; //error

    // The object myOtherAccount cannot be used until the type has
    // been declared to TypeScript. This can be used to ensure
    // that API consumers think about their typing up-front:
  #### type assertion
    type User = { name: string };
    const myUserAccount = jsonParserUnknown(`{ "name": "Samuel" }`) as User;   
    myUserAccount.name;

  ## Never
    never means it shouldnt return any value it only throws

    void means it can return undefined 
# Type Alias
    type Point = {
      x: number;
      y: number;
    };
    // Exactly the same as the earlier example
    function printCoord(pt: Point) {
      console.log("The coordinate's x value is " + pt.x);
      console.log("The coordinate's y value is " + pt.y);
    }
 
printCoord({ x: 100, y: 100 });
# Composing Types
  
  ### you can create complex types using two methods:
  ##### UNION 
  here we can define the possible types of a variable

    let x: string|number ;
    x =5;
    x= "haii";
  
  we can take this further by specifing the possible values for a type or variable

  let x : 5|6;  // x values can be only 5 and 6

  you can define the type with your complex union

  type WindowStates = "open" | "closed" ;
  let windowX : WindowStates;

  ##### Generics
    interface Backpack<Type> {
    add: (obj: Type) => void;
    get: () => Type;
    }
    
    // This line is a shortcut to tell TypeScript there is a
    // constant called `backpack`, and to not worry about where it came from.
    declare const backpack: Backpack<string>;
    
    // object is a string, because we declared it above as the variable part of Backpack.
    const object = backpack.get();
    
    // Since the backpack variable is a string, you can't pass a number to the add function.
    backpack.add(23);


# declare
  declare is used to tell the compiler "this thing (usually a variable) exists already, and therefore can be referenced by other code, also there is no need to compile this statement into any JavaScript".

  Common Use Case:

  You add a reference to your web page to a JavaScript file that the compiler knows nothing about. maybe it is a script coming from some other domain like 'foo.com'. when evaluated the script will create an object with some useful API methods and assign it to the identifier 'fooSdk' on the global scope.

  You want your TypeScript code to be able to call fooSdk.doSomething(), but since your compiler does not know fooSdk variable exists, you will get a compilation error.

  You then use the declare keyword as a way of telling the compiler "trust me, this variable exists and has this type". The compiler will use this statement to statically check other code but will not trans-compile it into any JavaScript in the output.

# Structural Type (Duck Typing)
    interface Point {
    x: number;
    y: number;
    }
    
    function logPoint(p: Point) {
      console.log(`${p.x}, ${p.y}`);
    }
    
    // logs "12, 26"
    const point  = { x: 12, y: 26 }; // it type is {x:number , y:number}
    logPoint(point);// the ts compiler checks at compile time if the vairable passed
                    //can function as a duck, if it can then it is a duck
    const maybePoint = {x:12 , y:27,z:28};
    logPoint(maybePoint);// duck or structral typing only requires a subset of the objects
                        // fields to match 

    const notPoint = {x:1};
    const notPointEither = {x:"haai",y:"hellow"};
    logPoint(notPoint); //type y is missing
    logPoint(notPointEither) // incompatiable types


# Type vs Interface
Type aliases and interfaces are very similar, and in many cases you can choose between them freely. Almost all features of an interface are available in type, the key distinction is that a type cannot be re-opened to add new properties vs an interface which is always extendable.


**Interface** is specifically for defining object shapes. It's optimized for describing the structure of objects and classes, supports declaration merging (you can declare the same interface multiple times and they'll combine), and is the standard way to define contracts for object-oriented code.

**Type** is more flexible. It can represent any type—objects, primitives, unions, tuples, and more. You can use it for object shapes too, but it can't be merged. Each type declaration is final.

In practice, for most everyday use cases like defining object shapes, either works. Interfaces are slightly more conventional for OOP patterns, while types are better when you need unions, tuples, or working with non-object types. If you need declaration merging (like extending third-party types), interfaces are your only choice.

Here's a quick example:

```typescript
// Interface - good for object contracts
interface User {
  name: string;
  age: number;
}

// Type - more flexible
type Status = "active" | "inactive" | "pending";
type Config = { host: string; port: number };
```
### Merging means

interface User {
  name: string;
  
}
interface User {
  
  age: number;

}

function greet(aUser:User) {
    console.log(`Hello ${aUser.age}`)
  }
const  aUser= {name: "hello",age:1}

greet(aUser)

it merges interfaces with the same name



# Literal Inference

  When you initialize a variable with an object, TypeScript assumes that the properties of that object might change values later. For example, if you wrote code like this:
    const obj = { counter: 0 };
    if (someCondition) {
      obj.counter = 1;
    }
  TypeScript doesn’t assume the assignment of 1 to a field which previously had 0 is an error. it gave it a value of 0 before now its one

  Problem arise when i want to pass an object of a certain type but i have a generic one like:

  declare function handleRequest(url: string, method: "GET" | "POST"): void;
 
  const req = { url: "https://example.com", method: "GET" };
  handleRequest(req.url, req.method);

  here i will have to use type assertion

  handleRequest(req.url, req.method as "GET");

  or you can use as const to convert the entire object to  be type literals

  const req = { url: "https://example.com", method: "GET" } as const;
  handleRequest(req.url, req.method);


  # const vs read ony
  ### const 
    stops the reassigment of a variable 
    if the the variable happens to be an object then it will change its properties normally 
    Ex:
    const name = "John";
    name = "Jane"; // Error: Cannot assign to 'name' because it is a constant

    const obj = { age: 30 };
    obj = { age: 25 }; // Error: Cannot reassign the object

    obj.age = 25; // This is allowed - you're modifying the object's properties

  ### readonly
    stops the reassigments of properties of an object
    Ex:
    interface User {
    readonly name: string;
    age: number;
  }

  const user: User = { name: "John", age: 30 };
  user.name = "Jane"; // Error: Cannot assign to 'name' because it is a read-only property
  user.age = 25; // This is allowed


# decorators
    A Decorator is a special kind of declaration that can be attached to a class declaration, method, accessor, property, or parameter. Decorators use the form @expression, where expression must evaluate to a function that will be called at runtime with information about the decorated declaration.

    @decorator
    class player{}
    decorator(player)
  ## decorator composition
    multiple decorators can be applied like
    @f @g x
    
    or
    @f
    @g
    x
    equvilant to f(g(x))

  ## Example
    function Frozen(constructor: Function) {
      Object.freeze(constructor);
      Object.freeze(constructor.prototype);
    }

    @Frozen
    class IceCream {
      flavor: string;
      constructor(flavor: string) {
        this.flavor = flavor;
      }
    }

console.log(Object.isFrozen(IceCream));//true

# Narrowing
  in the following example i want to implement differnt behavior in the padleft function:

    function padLeft(padding: number | string, input: string): string {
    return " ".repeat(padding) + input;
    }

  Argument of type 'string | number' is not assignable to parameter of type 'number'.
    Type 'string' is not assignable to type 'number'.
  
  **as you can see here i cant pass a paramter of type x | y to a function that takes type x**

  and here comes the use of typeof operator 

    function padLeft(padding: number | string, input: string): string {
      if (typeof padding === "number") {
        return " ".repeat(padding) + input;
      }
      return padding + input;
    }
  
  while this may see normal in javascript there is alot going under the convers here

  Within our if check, TypeScript sees typeof padding === "number" and understands that as a special form of code called a **type guard**.

  a quick note , null is considered an **object**

  so somehting like

  if(typeof arr === "object") //to check if it is an array

  isnt entierly correct since null is an object

