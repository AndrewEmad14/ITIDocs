
## OS DAY 2 ##

<3 Types of App Users>
-> person
-> developer
-> App

<3 ways to interact>
->GUI
->CLI
->API Systemcall

# WebHook
    
<webhook is a lightweight, event-driven communication that automatically sends data between applications via HTTP. Triggered by specific events, webhooks automate communication between application programming interfaces (APIs) and can be used to activate workflows, such as in GitOps environments.>

# WebSockets

<are used to create bidirection communication between the client and the server BUT it is heavy>

# MQTT Broker 

<a light way Pub/Sub services that creates commnication between client and server>
[Mosquito,EMQX,HiveMQ]
subscribers always send to the broker a msg that tell it its alive



# How Does the Os Run?
 
PowerON ==>        BIOS       ==>      BootLoader Menu  ==>   Linux(Kernel)     ==>   Systemd
              Check Hardware            Menu to All OS       runs in the ram            

<sudo systemctl enable mongod.service>      //enables run on startup
               <disable>                     //disable on startup

<OS turn off on idle until an action happens>

# I/O Request 
        OS is interrupt driven
<polling>
    i am always asking is the task done or is has the value changed
<interrupt>
    if the task is done or if the value is changed tell me

# Sync vs Async
    Sync (synchronous) is sequential and blocking, meaning tasks must complete one after another, while async (asynchronous) is non-blocking and allows multiple tasks to run concurrently

# interrupts
    hardware --tells-->cpu--fires-->OS -->deals with interrupt from the vector 
    the Os must know the kind of intterupts because there is an interrupt:Table(vector) 
    [Interrupt Service Routine]

# how do we talk to the hardware

  <3 ways>
    PortMapped 
        ---0 for i/o 1 for ram  address
    MeomoryMapped
        ---certain address would only be for controlling the i/o but you cannot communicate with said address without the permession of the OS THROUGH systemcalls
    DMA
        ---Direct memory access :
        imagine a seceratry which handles the communication between the i/0 , ram and cpu

  <3 types of busses>
    data bus
    address bus
    control bus

# FAQ
  <when to write Assembly in c?>
    when what you need isnt in the ram
  <why do we use logical address instead of physical>
    because you cant gaurntee that the physical addres will stay the same everytime

   interrupts happens because of software 
    system call , divide by zero , accesssing restricted memory
   interrupts have the highest priority than any task
<problems with shrinking>

1.if windows 11 close bitlocker


