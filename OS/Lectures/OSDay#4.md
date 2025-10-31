# OS Day 4
# Schdueling
    >First-Come First Served
            +First process that comes is the first process that is served 
            +it is easy to implement but has a very long average waiting time
    >Shortest-Job First
            +the process with shortest time is picked first
            +there are two schemes:
                -Non preemptive :once CPU given to the process it cannot be preempted until completes its CPU burst.
                -Preemptive:if a new process arrives with CPU burst length less than remaining time of current executing process, preempt. This scheme is know as the Shortest-Remaining-Time-First (SRTF).
    >Priority
            SJF + Priority 
            +Problem: STARVATION(a process may never execute)
            +Solution: AGING(a process priority increases as time passes)
            NOTE: assume that the lowest number is the hightest prio
    >Round-Robin
        +same as FCFS but with preemption
        +Each process gets a small unit of CPU time (time
        quantum), usually 10-100 milliseconds. After this time
        has elapsed, the process is preempted and added to the
        end of the ready queue.
        • If there are n processes in the ready queue and the time
        quantum is q, then each process gets 1/n of the CPU
        time in chunks of at most q time units at once. No
        process waits more than (n-1)q time units.

        +higher average turnaround than SJF, but better response.
# Dead Lock 
    deadlock happends when a process has a shared rescource and is locked while another process has a shared recource but each other need the others recourse to complete its execution

>4 condition for dead lock
    -Mutal exclusion
    -Hold and wait
    -no preemption
    -circular wait
>how to solve deadlock
    -Geneocide : kill all process
    -kill process by process until the deadlock is solved
    -let the user decide

# Contigous allocation
>External Fragmantation issue
            holes in the meomory and the process must have a adjacent memory in order to go to
we can solve it with compaction
>Internal Framgmentation
            after dividing our meomory into frames and pages there will be holes in the frame but those wholes cant be filled by another application unlike external fragmentation


# Comapction
        Compaction is an operating system memory management technique that combats external fragmentation by moving occupied memory blocks to consolidate all free space into a single, large contiguous block
    first fit
    worst fit
    best fit

# frames and pages
        >memory is divided into frames and frames are divided into pages
        >pages have a NUMBER which is the base address of each page in physical memory
                      OFFSET when combine with the base address define the physical memory address that is sent to the memory unit.
        Numbers are stored in page table
        >meomry now doesnt have to be sequential
        >it is divided into pages and a page table to manges it

# Segmentation
        >compiler divides the code into segemants
        >some OS uses segmeants and frames


# FAQ

    addresbuss must be more that 8 bit because thats the smalles container in the meomry (sussy info)
    logical volume mount
    something in the cloud is called pay as go 
    what that means is that you pay exactly as how u use the serveice
    there is also paging the segmants
        Solution differs from pure segmentation in
        that the segment-table entry contains not the
        base address of the segment, but rather the
        base address of a page table for this segment.