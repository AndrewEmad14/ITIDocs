to get started with node

install node

if you want to run something in node
node index.js

to use any of the commands you write you can type it after

node index.js add

to use or import certain libaries use require :
const fs = require("fs");  
const todos = JSON.parse(fs.readFileSync(todosPath, "utf-8"));

notice that the paths differ form each os thats why we path function :
const path = require("path");
const todosPath = path.join(\_\_dirname, "todos.json");

if you want to access the arguments you can do it form the porcess.args
const [, , command, value] = process.argv;

//here i am destructuring to get the second and third values in the process.argv array in variable command and vlaue

how to take input form the user?
const { createInterface } = require("node:readline");
const rl = createInterface({
input: process.stdin,
output: process.stdout,
});

Questions?
async function runCLI(){
const answer1 = await rl.question("what is your item name");
const answer2 = await rl.question("what is your item size");
console.log(answer1 + answer2);
rl.close();
}
remeber to close the stream
