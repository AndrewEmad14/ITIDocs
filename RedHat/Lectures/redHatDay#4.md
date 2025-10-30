# redhat day 4#

# Processes
    system starts process called daemons which are processes that run in the background and provide services

    every proces has PID

    cpu runs one process at a time


    Niceness values range from -20 to +19
# Commands
    nice [-n adjustment]    command
    nice -n 20 makewhatis
    renice [number]  -p [pid]
    ps          //processes that are currently running on the cpu
        -l      detailed desc
    pstree  
            displayers the tree of process es
    <process>&      process can run in the background (enabling it to work simultaneously)
        [job id] [process id]
    kill
            -l                                      list signal names
        default kill alone is to terminate
        send signals to process
        -STOP           %[jobID] or [process id]                           //stops the process
    fg               [jobID]                   //brings the process to the foreground
    top     terminal sysmonitor
    pgrep                                   pgrep looks through the currently running processes
                                            and lists the process IDs which match the selection
                                            criteria to  stdout.
            -l                      //details
            -x                      //exact match

    "|" : This operator is used to redirect the standard output (stdout) of one command to the standard input (stdin) of another command 
    ">" :  This operator is used to redirect the standard output (stdout) of a command to a file (overwrite)
    ">>" : same as above but it appends
    "<":take the output of the second and puts it in the first

    to redirect errors
    ls /etc fdf >err>result
    diff                differnce between two files
                        it gives instruction on how to make file1 like file2
    grep    search a file
        ^ starts with       ^h
        $ ends with         h$
    tr replace a char or string with another char
    cut -d: -f1,5,6 /etc/passwd | more
            cuts specific text form file
    sort
            -n                  // to sort by numbers instead of strings
            -k                  //key (column)
            -t:
    whereis command or app
        location of command or app
    w           
        who is online

# SIGNALS
    a signal is a message sent to a process to perform a certain action
# FAQ
    tty = ?             /thats a daemon
    alias inside the sudo is all capital

    top assigment
    sort by meomory
    works only for 2mins and refreshes every 30s
    switching inside the terminal is not the same as loging in
    ls -R / 2> /dev/null | sort > result &
    /dev/null if i dont want to create a file for the error