## OS Day 3 ##

# Data
<Data is divided iinto 4 parts>(usually)

1.Stack
2.Data
3.BSS
4.Heap

as a developer we are intrested in the data part in the meomory

we use assembly for two reasons 
1. to access data that isnot in the memory 
2. to optimize the instruction if i cannot get to the desired result with my program


# Process State

>when the process is replaced by another its current data that is in the register is stored so that when it returns to the running state we can continue where we left off

<we have 5 states>
    new -> ready -> running -> waiting ->Terminated

<Process Control Block>
    info associated with each process like:
                >process state
                >program counter
                >Cpu registers
                >Cpu Scheduling info
                >Meomory Managment info
                >accounting info
                >I/O status info
<PCB size is constant across all process no matter the process (it is like a data strcuture)>

# Kind of Systems

<Multi-Programming-systems>
    some process excuting at all times
    Maximize cpu utilization
<Time-Sharing>
    best responsivness
    switch the cpu among process frequently
    users can interact with a program while it's executing
    virtually run process at thte same time

# Process Scheduling Queues

>Job Queue
        set of all processes in the system
>Ready Queue
        set of all processes residing in main memory
>Device Queues

# kind of Schedulars
>long term schedular (job scheduler)    // old way 

>mid term schedular  (swapping or virtual memory)
>when the ready queue is full it loads it in a memory in the hard/ssd disk

>Short term Scheduler (Cpu scheduler)
        >form ready -> Running

# kind of process
>I/O bound process
>Cpu bound process
<proper system preformance>
        a mix between the two
        
# OS system Desgin structure
>simple sturcture
>layered approach
>microservices
>modular 
# FAQ
>OS reserves memory for instructions and data
>DMA is hardware mangaed by software
>process in ready queue is the process that is loaded
>fork : system call creates a new process
>exec : System call used after a fork to replace the process memory space with a new program
>zombie process: a child process whose parent died or was killed 
>semaphore or mutex are used to lock a shared resource with the process that is currently uses >until he finishes it