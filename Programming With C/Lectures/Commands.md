g++ 
    -g                  //debug mode
    -I                  //header folder
    -o                  //executable file

g++ -g -I./headers ./src/*.cpp -o ./output



gdb executable                      //open gdb with ur exe
gdb run                             //runs your program
gdb lay next                        //debug terminal
gdb break {func} or {line}          //for break points
gdb next                            //next line
gdb step                            //steps into something
gdb ref                             //refresh
gdb watch                           //watch a variable
gdb print                           //prints a variagble
gdb continue                        //continue your code
gdb list                            //list code you are debuging
gdb layout src                      //display layout