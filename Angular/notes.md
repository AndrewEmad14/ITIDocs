ng serve -o    runs the app and is responsive to my changes (-o)
Regarding the conversion of TypeScript to JavaScript:

    It handles compilation automatically: ng serve uses the Angular Compiler (ngc), which is built on top of tsc. It automatically converts your TypeScript into JavaScript every time you save a file.
    In-Memory only: Unlike running tsc . manually, which generates physical .js files in your folders, ng serve compiles your code in-memory. It serves these virtual files to your browser so your project folder stays clean.